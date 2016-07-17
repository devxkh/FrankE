#include <XEngine.hpp>

#include <XEDAL/PhysFS/PhysFSWrapper.h>
#include <XEDAL/PhysFS/PhysFSArchive.h>
#include <XEPhysics/Physics/gkDynamicsWorld.h>

#include <algorithm>

//INITIALIZE_EASYLOGGINGPP

void ControllerThread(XE::XEngine* engine)
{
	//return;
	while (engine->running() || !engine->isInitialized())
	{

		if (engine->isInitialized())
		{
			// let the state update the game
			//todo	engine->lastState()->update();
		//	engine->getCtrlMgr().update(); //update Controller

			//update physics 
			//	engine->getScene().getDynamicsWorld()->step(evt.timeSinceLastFrame);
		}

		//	engine->renderUpdate();

		//if (engine->getCtrlMgr().getController(0))
		//	engine->getCtrlMgr().update(); //update Controller
	}
}

namespace XE
{
	class ViewManager2
	{
	public:
		ViewManager2(XEngine* test);

	};

	XEngine::XEngine() :
		m_initialized(false)
		, m_resume(false)
		, m_running(true)
		//	mControllerThread(ControllerThread, this),
		, mGraphicsManager(this)
		, m_clock()
		, m_NetworkManager()
		, _lua(*this)
		, _soundMgr()
		, m_OgreSceneManager(mGraphicsManager)
	{		
		//plog::init(plog::debug, "HelloLog.txt"); // Step2: initialize the logger.
		//el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level ,tid: %thread msg: %msg");

		PhysFS::init(""); // init PhysFS system
	}

	XEngine::~XEngine()
	{

	}

	void XEngine::init()
	{
		LOG(plog::info) << "XEngine():init";


		//singlethreaded renderer	engine->getGraphicsManager().updateRenderer();
		//		engine->getGraphicsManager().updateRenderer();
		//controller->getControllerView().getCameraController().getOgreCamera();
		//texturemanager initialized in createrenderwindow!!!
		//renderwindow is create from current rendersystem!
		//Step 1 - RenderWindow
		mGraphicsManager.createRenderWindow(settings.FBSettings()->windowTitle()->c_str());// controller->getCameraController().getOgreCamera().__OgreCameraPtr);

												   //Step 1 Hlms
		mGraphicsManager.registerHlms(); //needs initialized root and renderwindow from rendersytem for vaomanager

										 //Step 2 Init Resourcesystem - needs hlms
		initResourceSystem();

		//Step 3 atlas
		//	mGraphicsManager.getGUIRenderer().loadAtlas("UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

		//Step 4 scene
		m_OgreSceneManager.create();

		registerObject(_lua.state);
		m_NetworkManager.registerObject(_lua.state);
		
		m_IDAL->open();
	}

	void XEngine::registerObject(sol::state& lua)
	{
		lua.new_usertype<XEngine>("XEngine",

			//properties
			"graphicsMgr", sol::property(&XEngine::getGraphicsManager),
			"networkMgr", sol::property(&XEngine::getNetworkManager),
			"ogreSceneMgr", sol::property(&XEngine::getOgreSceneManager),
			"soundMgr", sol::property(&XEngine::getSoundMgr),
			"scene", sol::property(&XEngine::getScene),
			"dal", sol::property(&XEngine::getDAL),
			"lua", sol::property(&XEngine::getLua),
			"isInitialized", sol::property(&XEngine::isInitialized),

			//functions
			"quit", &XEngine::quit,
			//"run", &XEngine::run  unique_ptr ! parameter
			"nextState", &XEngine::nextState,
			"lastState", &XEngine::lastState
		);

		auto stateView = lua.set("XEngine", this); //set object instance
	}

	void XEngine::quit()
	{
		m_running = false;
	}


	void XEngine::setScene(std::unique_ptr<Scene> scene)
	{
		m_scene = std::move(scene);
	}

	void XEngine::setDAL(std::unique_ptr<IDAL> idal)
	{
		m_IDAL = std::move(idal);
	}

	void XEngine::setNextState(std::unique_ptr<XEState> state)
	{
		m_states.top()->m_next = std::move(state);
	}

	void XEngine::run(std::unique_ptr<XEState> state)
	{
		m_running = true;
		m_initialized = true;

		m_states.push(std::move(state));

	}

	void XEngine::nextState()
	{
		if (m_resume)
		{
			// cleanup the current state
			if (!m_states.empty())
			{
				m_states.pop();
			}

			// resume previous state
			if (!m_states.empty())
			{
				m_states.top()->resume();
			}

			m_resume = false;
		}

		// there needs to be a state
		if (!m_states.empty())
		{
			std::unique_ptr<XEState> temp = m_states.top()->next();

			// only change states if there's a next one existing
			if (temp != nullptr)
			{
				// replace the running state
				if (temp->isReplacing())
					m_states.pop();
				// pause the running state
				else
					m_states.top()->pause();

				m_states.push(std::move(temp));
			}
		}
	}

	void XEngine::lastState()
	{
		m_resume = true;
	}

	void XEngine::update()
	{
		//bool test = false;
		//if (test)
		//{
		//	mGraphicsManager.getIntoRendererQueue().push([this]() {
		//		//saving 
		//	DataStreamPtr shaderCacheFileout = mGraphicsManager.getRoot()->createFileStream("F:/Projekte/coop/XGame/data/MyCache.cache", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
		//	GpuProgramManager::getSingleton().saveMicrocodeCache(shaderCacheFileout);
		//
		//	
		//		//loading
		//		//GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
		//		//DataStreamPtr shaderCacheFile = mGraphicsManager.getRoot()->openFileStream("F:/Projekte/coop/XGame/data/MyCache.cache");
		//		//GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
		//	});
		//}
//		sf::Time elapsed1 = m_clock.getElapsedTime();

		sf::Time dt = m_clock.restart();
		sf::Uint64 time = dt.asMicroseconds();

		double timeSinceLast = time / 1000000.0;
		timeSinceLast = std::min(1.0, timeSinceLast); //Prevent from going haywire.

		m_scene->update(timeSinceLast);

		m_states.top()->update(timeSinceLast);

#if UseRenderThread == 0
		mGraphicsManager.updateRenderer();  // only in singlethread mode! -> else it's  the job of the graphicsmanager!
#endif

		mGraphicsManager.getFromRendererQueue().TriggerAllHandler();

		//	XE::WindowEventUtilities::messagePump(); //dont use it or .net wrapper crash!
	}

	void XEngine::draw()
	{
		// let the state draw the screen
		m_states.top()->draw();
	}

	//needs Hlms !
	void XEngine::initResourceSystem()
	{
		//PhysFS::addToSearchPath(settings.FBSettings()->resourceData()->dbDataFolder()->c_str(), true);// set the searchpath

		
		mGraphicsManager.getIntoRendererQueue().push([this]() {

		//	Ogre::ArchiveFactory *fac = new PhysFS::PhysFSArchiveFactory;

	//		Ogre::ArchiveManager::getSingleton().addArchiveFactory(fac);

			//Ogre::ConfigFile cf;
			//std::stringstream ss;
			//ss << settings.FBSettings()->resourceData()->assetsFolder()->c_str() << "\\resources.cfg";

			//cf.load(ss.str() , "\t:=", true);

			//Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
			//Ogre::String secName, typeName, archName;
			//Ogre::String sec, type, arch;

			//// go through all specified resource groups
			//while (seci.hasMoreElements())
			//{
			//	sec = seci.peekNextKey();
			//	Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
			//	Ogre::ConfigFile::SettingsMultiMap::iterator i;

			//	// go through all resource paths
			//	for (i = settings->begin(); i != settings->end(); i++)
			//	{
			//		type = i->first;
			//		arch = i->second;

			//		//#if XE_PLATFORM == XE_PLATFORM_APPLE || XE_PLATFORM == XE_PLATFORM_APPLE_IOS
			//		//				// OS X does not set the working directory relative to the app,
			//		//				// In order to make things portable on OS X we need to provide
			//		//				// the loading with it's own bundle path location
			//		//				if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
			//		//					arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
			//		//#endif

			//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec, true);
			//	}
			//}
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("F:/Projekte/coop/XGame/data/assets","FileSystem", "General", true, true);


			//initialise for gorilla shaders intitialization
			std::string lNameOfResourceGroup = "General";
			{
				Ogre::ResourceGroupManager& lRgMgr = Ogre::ResourceGroupManager::getSingleton();

				lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
				lRgMgr.loadResourceGroup(lNameOfResourceGroup);
			}
		});
	}

}