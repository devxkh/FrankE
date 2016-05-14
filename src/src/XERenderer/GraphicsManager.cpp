#include <XERenderer/GraphicsManager.hpp>

#include <XEngine.hpp>

#include <Ogre/RenderSystems/Direct3D11/include/OgreD3D11Plugin.h>
#include <Ogre/RenderSystems/GL3Plus/include/OgreGL3PlusPlugin.h>

//#include <Ogre/OgreMain/include/Compositor/OgreCompositorManager2.h>
#include <XERenderer/OgreWorkspace.hpp>
#include <Ogre/OgreMain/include/OgreFrameStats.h>

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbs.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>


#include <XEScripts/LUAEngine.h>
//#include <Ogre/OgreMain/include/OgreRoot.h>


namespace XE
{
	//#define GRAPHICS_THREAD 1  //compile with graphics render thread

	GraphicsManager::GraphicsManager(XE::XEngine* engine) :
		mRoot(OGRE_NEW Ogre::Root())

		, mWindowManager()
		, _t_OgreWorkspace(nullptr) //creates window in mainthread
		, my_QueueManager()
		, my_FromRSQueueManager()
		//#ifdef GRAPHICS_THREAD
		, mRenderThread(nullptr), // &GraphicsManager::RenderThread, this, this, engine),
		//#endif
		mEngine(engine)
		, m_GUIRenderer(*this)
	{
		_renderTasks.push_back(RenderTask(RenderTaskID::AnimationAddTimes));
		_renderTasks.push_back(RenderTask(RenderTaskID::AnimationTimes));
		_renderTasks.push_back(RenderTask(RenderTaskID::DebugLines));
		_renderTasks.push_back(RenderTask(RenderTaskID::RenderBody));
		_renderTasks.push_back(RenderTask(RenderTaskID::Camera));
		_renderTasks.push_back(RenderTask(RenderTaskID::RenderGUI));

		createRenderer();

#if UseRenderThread == 1
		//singlethread using updateRenderer function -> disable render function in engine!!!
		//renderthread
		mRenderThread = new (std::thread)(&GraphicsManager::RenderThread, this, this, engine);
#endif

		registerObject(engine->getLua().state);
		m_GUIRenderer.registerObject(engine->getLua().state);
	}

	GraphicsManager::~GraphicsManager()
	{
		delete mRenderThread;
		delete _t_OgreWorkspace;
	}

	//Ogre::TexturePtr GraphicsManager::createTextureRenderTarget(int width, int height)
	//{
	//	//todo lock and stop render thread while adding RenderTarget
	//	return OgreWorkspace::createTextureRenderTarget(width, height); //need window handle (else wnd is hidden), always a renderwindow is needed
	//	//return rt;
	//}

	void GraphicsManager::resizeRenderWindow(size_t w, size_t h)
	{
		getIntoRendererQueue().push([this, w, h](){

			_t_RenderWindow->windowMovedOrResized();
			//_t_RenderWindow->resize(w, h);
		});
	}

	void GraphicsManager::createRenderWindow(const std::string& title)
	{
		//todo manage multiple windows
		sf::Window* window = mWindowManager.createWindow(sf::VideoMode(800, 600), title, sf::Style::Default);


		getIntoRendererQueue().push([this, window](){

			//todo lock and stop render thread while adding renderwindow
			_t_RenderWindow = OgreWorkspace::_t_createRenderWindow(window); //need window handle (else wnd is hidden), always a renderwindow is needed
		});
	}

	void GraphicsManager::registerObject(sol::state& lua)
	{
		lua.new_usertype<GraphicsManager>("GraphicsManager",

			//properties
			"guiRenderer", sol::property(&GraphicsManager::getGUIRenderer)

			//functions
			//"quit", &XEngine::quit,
			);

		auto stateView = lua.set("GraphicsManager", this); //set object instance
	}

	void GraphicsManager::setRenderSystem()
	{
	
		//D3D11RenderSystem* mRenderSystem = new D3D11RenderSystem();
		Ogre::GL3PlusRenderSystem* mRenderSystem = new Ogre::GL3PlusRenderSystem();
		// Register the render system
		mRoot->addRenderSystem(mRenderSystem);
		mRoot->setRenderSystem(mRenderSystem);
	}

	//void GraphicsManager::createWorkspace(Ogre::uint16 renderwindowID, OgreCamera* camera)
	//{
	//	//dont pass pointer you want to change in the thread!!! or else the old pointer gets invalid
	//	my_QueueManager.push([this, camera](){
	//		//	OgreCamera* gg = camera;
	//		_t_OgreWorkspace = OGRE_NEW_T(OgreWorkspace, Ogre::MEMCATEGORY_GEOMETRY)(*mEngine, *this);
	//		_t_OgreWorkspace->_t_createWorkspace(_t_RenderWindow, camera); //_t_RenderWindow only usable after initialization!

	//	});
	//}

	void GraphicsManager::registerHlms(void)
	{
		getIntoRendererQueue().push([this](){
	
//		Ogre::ConfigFile cf;
	//	cf.load("resources2.cfg");

		Ogre::String dataFolder = "F:/Projekte/coop/XEngine/data/Test/XETController";//cf.getSetting("DoNotUseAsResource", "Hlms", "");

		if (dataFolder.empty())
			dataFolder = "./";
		else if (*(dataFolder.end() - 1) != '/')
			dataFolder += "/";

		Ogre::String shaderSyntax = "GLSL";
		if (mRoot->getRenderSystem()->getName() == "Direct3D11 Rendering Subsystem")
			shaderSyntax = "HLSL";

		Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Common/" + shaderSyntax,
			"FileSystem", true);

		Ogre::ArchiveVec library;
		library.push_back(archiveLibrary);

		Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Unlit/" + shaderSyntax,
			"FileSystem", true);

		Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
		Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);

		Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Pbs/" + shaderSyntax,
			"FileSystem", true);
		Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &library);
		Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);

	
			//loading
			//GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
			//DataStreamPtr shaderCacheFile = mRoot->openFileStream("F:/Projekte/coop/XGame/data/MyCache.cache");
			//GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
	
	});
	}

	RenderTask& GraphicsManager::GetRenderTask(RenderTaskID id)
	{
		return _renderTasks[id];
	}

	void GraphicsManager::updateRenderer()
	{
		my_QueueManager.TriggerAllHandler();

		my_FromRSQueueManager.push([this](){
			const Ogre::FrameStats*  stats = mRoot->getFrameStats();

			m_FrameStats.Fps = stats->getFps();
			m_FrameStats.AvgFps = stats->getAvgFps();
			m_FrameStats.BestTime = stats->getBestTime();
			m_FrameStats.WorstTime = stats->getWorstTime();

			_renderTasks[RenderTaskID::AnimationTimes].isDone = true; 
			//_renderTasks[RenderTaskID::DebugLines].isDone = true;
		//	_renderTasks[RenderTaskID::RenderBody].isDone = true;
			_renderTasks[RenderTaskID::Camera].isDone = true;
			
			// ->>> old Vers. -> in pass
			mEngine->getGraphicsManager().getGUIRenderer().update();
		});
		
		if(mRoot->isInitialised())
			mRoot->renderOneFrame();
	}

	void GraphicsManager::createRenderer()
	{
		setRenderSystem();

		//Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual("EyeTexture", "General", Ogre::TextureType::TEX_TYPE_2D, 1182 * 2, 1461, 0, Ogre::PixelFormat::PF_A8R8G8B8, Ogre::TU_RENDERTARGET);

		////compositorManager->addWorkspace(mSceneMgr, mWindow, mCamera, "MyOwnWorkspace", true);

		//m_compositorManager->addWorkspace(mScene.getSceneMgr(), tex->getBuffer()->getRenderTarget(), 0, "SampleBrowserWorkspace", true);

		//shows config dialog
	//	if (mRoot->restoreConfig() || mRoot->showConfigDialog())
//		{
			// initialise root
			mRoot->initialise(false);	
	//	}
	}

	void GraphicsManager::RenderThread(GraphicsManager* graphicsMgr, XE::XEngine* engine)
	{
		while (engine->running() || !engine->isInitialized())
		{
			if (engine->isInitialized())
				updateRenderer();
			else
				my_QueueManager.TriggerAllHandler();
		}
	}
} // namespace XE