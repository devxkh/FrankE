#include <XERenderer/GraphicsManager.hpp>

#include <XEngine.hpp>

#include <Ogre/RenderSystems/Direct3D11/include/OgreD3D11Plugin.h>
#include <Ogre/RenderSystems/GL3Plus/include/OgreGL3PlusPlugin.h>
#include <XERenderer/OgreWorkspace.hpp>
#include <Ogre/OgreMain/include/OgreFrameStats.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbs.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <XEScripts/LUAEngine.h>

#include <Ogre/OgreMain/include/OgreLog.h>
#include <Ogre/OgreMain/include/OgreLogManager.h>

#include <XERenderer/Hlms/XEHlmsProjection.hpp>
#include <XERenderer/Hlms/XEHlmsUnlit.hpp>

#include <plog/Appenders/ConsoleAppender.h>

#include <algorithm>

#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorWorkspaceDef.h"
#include "Compositor/OgreCompositorNode.h"
#include "Compositor/OgreCompositorNodeDef.h"

#include "Compositor/Pass/PassQuad/OgreCompositorPassQuadDef.h"

namespace XE
{
	//#define GRAPHICS_THREAD 1  //compile with graphics render thread

	GraphicsManager::GraphicsManager(XE::XEngine* engine) :
		mRoot(0)

		//	, mWindowManager()
		, my_QueueManager()
		, my_FromRSQueueManager()
		//#ifdef GRAPHICS_THREAD
		, mRenderThread(nullptr), // &GraphicsManager::RenderThread, this, this, engine),
		//#endif
		mAccumTimeSinceLastLogicFrame(0),
		mEngine(engine)
		, m_GUIRenderer(*this)
		, m_SdlWindow(0)
		, m_ogreLog()
		, _isRenderThreadFinished(true)
	{
	//	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender; 
	//	plog::init(plog::debug, "HelloLog.txt", 1000000).addAppender(&consoleAppender);
		plog::init(plog::debug, "HelloLog.txt", 1000000);// .addAppender(&consoleAppender); // Step2: initialize the logger.
	
		new Ogre::LogManager();// Creating the manager. This may only be called once!
		auto m_pLog = LogManager::getSingleton().createLog("log.txt", true, true);
		m_pLog->setDebugOutputEnabled(false);
		m_pLog->addListener(&m_ogreLog);


		mRoot = OGRE_NEW Ogre::Root();

		_renderTasks.push_back(RenderTask(RenderTaskID::AnimationAddTimes));
		_renderTasks.push_back(RenderTask(RenderTaskID::AnimationTimes));
		_renderTasks.push_back(RenderTask(RenderTaskID::DebugLines));
		_renderTasks.push_back(RenderTask(RenderTaskID::RenderBody));
		_renderTasks.push_back(RenderTask(RenderTaskID::Camera));
		_renderTasks.push_back(RenderTask(RenderTaskID::RenderGUI));
		_renderTasks.push_back(RenderTask(RenderTaskID::RenderEditorUI));

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			LOG(plog::error) << "Cannot initialize SDL2! - GraphicsSystem::initialize";

		createRenderer();

#ifdef UseRenderThread
		//singlethread using updateRenderer function -> disable render function in engine!!!
		//renderthread
		mRenderThread = new (std::thread)(&GraphicsManager::RenderThread, this, this, engine);
#endif

		registerObject(engine->getLua().state);
		m_GUIRenderer.registerObject(engine->getLua().state);
	}

	GraphicsManager::~GraphicsManager()
	{
	
		if (m_SdlWindow)
		{
			// Restore desktop resolution on exit
			SDL_SetWindowFullscreen(m_SdlWindow, 0);
			SDL_DestroyWindow(m_SdlWindow);
			m_SdlWindow = 0;
		}

		SDL_Quit();
	}

	//Ogre::TexturePtr GraphicsManager::createTextureRenderTarget(int width, int height)
	//{
	//	//todo lock and stop render thread while adding RenderTarget
	//	return OgreWorkspace::createTextureRenderTarget(width, height); //need window handle (else wnd is hidden), always a renderwindow is needed
	//	//return rt;
	//}

	SDL_Window* GraphicsManager::getWindow() {
		return m_SdlWindow;
	}

	void GraphicsManager::resizeRenderWindow(size_t w, size_t h)
	{
		
		getIntoRendererQueue().push([this, w, h]() {

			m_GUIRenderer._t_resizeRenderWindow(w, h);
			
			_t_RenderWindow->windowMovedOrResized();
			//_t_RenderWindow->resize(w, h);
		});
	}

	void GraphicsManager::createRenderWindow(const std::string& title)
	{
		int screen = 0;
		int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
		int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

		bool fullscreen = false;//Ogre::StringConverter::parseBool(cfgOpts["Full Screen"].currentValue);
		if (fullscreen)
		{
			posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
			posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
		}

		m_SdlWindow = SDL_CreateWindow(
			title.c_str(),    // window title
			posX,               // initial x position
			posY,               // initial y position
			800,              // width, in pixels
			600,             // height, in pixels
			SDL_WINDOW_SHOWN
			| (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);

		//todo manage multiple windows
		//sf::Window* window = mWindowManager.createWindow(sf::VideoMode(800, 600), title, sf::Style::Default);

		getIntoRendererQueue().push([this]() {
			
			m_GUIRenderer._t_resizeRenderWindow(800,600);

			


			_t_RenderWindow = OgreWorkspace::_t_createRenderWindow(m_SdlWindow); //need window handle (else wnd is hidden), always a renderwindow is needed
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
#if UseRenderSystem == 1
		Ogre::GL3PlusRenderSystem* mRenderSystem = new Ogre::GL3PlusRenderSystem();
#else if UseRenderSystem == 2
		//D3D11RenderSystem* mRenderSystem = new D3D11RenderSystem();
#endif
		// Register the render system
		mRoot->addRenderSystem(mRenderSystem);
		mRoot->setRenderSystem(mRenderSystem);
	}

	float GraphicsManager::getAccumTimeSinceLastLogicFrame()
	{
		return mAccumTimeSinceLastLogicFrame;
	}

	void GraphicsManager::setFullScreen(SDL_Window* wnd, bool fullscreen)
	{
		SDL_SetWindowFullscreen(wnd, fullscreen);
	}


	void GraphicsManager::registerHlms(void)
	{
		getIntoRendererQueue().push([this]() {

			Ogre::String dataFolder = mEngine->settings.resourceData.hlmsDataFolder;

			if (dataFolder.empty())
				dataFolder = "./";
			else if (*(dataFolder.end() - 1) != '/')
				dataFolder += "/";


			Ogre::String shaderSyntax = "GLSL";
			if (mRoot->getRenderSystem()->getName() == "Direct3D11 Rendering Subsystem")
				shaderSyntax = "HLSL";

			Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Common/" + shaderSyntax, "FileSystem", true);
			Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Unlit/" + shaderSyntax, "FileSystem", true);
			//Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/XEUnlit/" + shaderSyntax, "FileSystem", true);
			Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Pbs/" + shaderSyntax, "FileSystem", true);

			Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Common/Any", "FileSystem", true);
			Ogre::Archive *archivePbsLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Pbs/Any", "FileSystem", true);
			Ogre::Archive *archiveUnlitLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Unlit/Any", "FileSystem", true);

			Ogre::ArchiveVec library;
			library.push_back(archiveLibrary);
			library.push_back(archiveLibraryAny);
			library.push_back(archiveUnlitLibraryAny);

			XEHlmsProjection *xeHlmsUnlit = OGRE_NEW XEHlmsProjection(archiveUnlit, &library, Ogre::HLMS_USER0, "projection");
			mRoot->getHlmsManager()->registerHlms(xeHlmsUnlit);

			Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
			mRoot->getHlmsManager()->registerHlms(hlmsUnlit);


			Ogre::ArchiveVec libraryPbs;
			libraryPbs.push_back(archiveLibrary);
			libraryPbs.push_back(archiveLibraryAny);
			libraryPbs.push_back(archivePbsLibraryAny);

			Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &libraryPbs);
			mRoot->getHlmsManager()->registerHlms(hlmsPbs);

			mEngine->getResourceMgr()._t_registerHLMSResources();

		});
	}

	RenderTask& GraphicsManager::GetRenderTask(RenderTaskID id)
	{
		return _renderTasks[id];
	}

	void GraphicsManager::setShadowMappingUseBackFaces(bool useBackFaces)
	{
		getIntoRendererQueue().push([this, useBackFaces]()
		{
			Ogre::HlmsManager *hlmsManager = getRoot()->getHlmsManager();

			//http://www.ogre3d.org/forums/viewtopic.php?f=25&t=88836#p529968
			hlmsManager->setShadowMappingUseBackFaces(useBackFaces);
		});
	}

	double timeSinceLast = 1.0 / 60.0;

	void GraphicsManager::updateRenderer()
	{
	//	mAccumTimeSinceLastLogicFrame = 0; //TODO not needed? always 0 ?

		my_QueueManager.TriggerAllHandler();

		my_FromRSQueueManager.push([this]() { //executed in mainthread

			const Ogre::FrameStats*  stats = mRoot->getFrameStats();

			m_FrameStats.Fps = stats->getFps();
			m_FrameStats.AvgFps = stats->getAvgFps();
			m_FrameStats.BestTime = stats->getBestTime();
			m_FrameStats.WorstTime = stats->getWorstTime();


			_renderTasks[RenderTaskID::AnimationTimes].isDone = true;
			//_renderTasks[RenderTaskID::DebugLines].isDone = true;
		//	_renderTasks[RenderTaskID::RenderBody].isDone = true;
		//	_renderTasks[RenderTaskID::Camera].isDone = true;

			// ->>> old Vers. -> in pass
			mEngine->getGraphicsManager().getGUIRenderer().update();
		});
				
	
		if (mRoot->isInitialised())
			mRoot->renderOneFrame();
		
	//	auto elapsedTimeMainThread = m_clock.restart();

		//sf::Uint64 time = elapsedTimeMainThread.asMicroseconds();
		auto time = mRoot->getTimer()->getMicroseconds();


		double timeSinceLast = time / 1000000.0;
		timeSinceLast = std::min(1.0, timeSinceLast); //Prevent from going haywire.

	//	m_GUIRenderer._t_update(timeSinceLast);

		mAccumTimeSinceLastLogicFrame = timeSinceLast;
		
		_isRenderThreadFinished = true;
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