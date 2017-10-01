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

	void _t_createCustomTextures(Root *root, Ogre::RenderWindow* renderWindow)
	{
		TexturePtr tex = TextureManager::getSingleton().createManual(
			"HalftoneVolume",
			"General",
			TEX_TYPE_3D,
			64, 64, 64,
			0,
			PF_L8,
			TU_DYNAMIC_WRITE_ONLY
		);

		if (!tex.isNull())
		{
			v1::HardwarePixelBufferSharedPtr ptr = tex->getBuffer(0, 0);
			ptr->lock(v1::HardwareBuffer::HBL_DISCARD);
			const PixelBox &pb = ptr->getCurrentLock();
			Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);

			size_t height = pb.getHeight();
			size_t width = pb.getWidth();
			size_t depth = pb.getDepth();
			size_t rowPitch = pb.rowPitch;
			size_t slicePitch = pb.slicePitch;

			for (size_t z = 0; z < depth; ++z)
			{
				for (size_t y = 0; y < height; ++y)
				{
					for (size_t x = 0; x < width; ++x)
					{
						float fx = 32 - (float)x + 0.5f;
						float fy = 32 - (float)y + 0.5f;
						float fz = 32 - ((float)z) / 3 + 0.5f;
						float distanceSquare = fx*fx + fy*fy + fz*fz;
						data[slicePitch*z + rowPitch*y + x] = 0x00;
						if (distanceSquare < 1024.0f)
							data[slicePitch*z + rowPitch*y + x] += 0xFF;
					}
				}
			}
			ptr->unlock();
		}

		TexturePtr tex2 = TextureManager::getSingleton().createManual(
			"DitherTex",
			"General",
			TEX_TYPE_2D,
			renderWindow->getWidth(), renderWindow->getHeight(), 1,
			0,
			PF_L8,
			TU_DYNAMIC_WRITE_ONLY
		);

		v1::HardwarePixelBufferSharedPtr ptr2 = tex2->getBuffer(0, 0);
		ptr2->lock(v1::HardwareBuffer::HBL_DISCARD);
		const PixelBox &pb2 = ptr2->getCurrentLock();
		Ogre::uint8 *data2 = static_cast<Ogre::uint8*>(pb2.data);

		size_t height2 = pb2.getHeight();
		size_t width2 = pb2.getWidth();
		size_t rowPitch2 = pb2.rowPitch;

		for (size_t y = 0; y < height2; ++y)
		{
			for (size_t x = 0; x < width2; ++x)
			{
				data2[rowPitch2*y + x] = Ogre::Math::RangeRandom(64.0, 192);
			}
		}

		ptr2->unlock();
	}

	void _t_createExtraEffectsFromCode(Root *root)
	{
		CompositorManager2 *compositorManager = root->getCompositorManager2();

		// Bloom compositor is loaded from script but here is the hard coded equivalent
		if (!compositorManager->hasNodeDefinition("Bloom"))
		{
			CompositorNodeDef *bloomDef = compositorManager->addNodeDefinition("Bloom");

			//Input channels
			bloomDef->addTextureSourceName("rt_input", 0, Ogre::TextureDefinitionBase::TEXTURE_INPUT);
			bloomDef->addTextureSourceName("rt_output", 1, Ogre::TextureDefinitionBase::TEXTURE_INPUT);

			bloomDef->mCustomIdentifier = "Ogre/Postprocess";

			//Local textures
			bloomDef->setNumLocalTextureDefinitions(2);
			{
				TextureDefinitionBase::TextureDefinition *texDef = bloomDef->addTextureDefinition("rt0");
				texDef->widthFactor = 0.25f;
				texDef->heightFactor = 0.25f;
				texDef->formatList.push_back(Ogre::PF_R8G8B8);

				texDef = bloomDef->addTextureDefinition("rt1");
				texDef->widthFactor = 0.25f;
				texDef->heightFactor = 0.25f;
				texDef->formatList.push_back(Ogre::PF_R8G8B8);
			}

			bloomDef->setNumTargetPass(4);

			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt0");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BrightPass2";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt1");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BlurV";
					passQuad->addQuadTextureSource(0, "rt0", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt0");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BluH";
					passQuad->addQuadTextureSource(0, "rt1", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt_output");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BloomBlend2";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
					passQuad->addQuadTextureSource(1, "rt0", 0);
				}
			}

			//Output channels
			bloomDef->setNumOutputChannels(2);
			bloomDef->mapOutputChannel(0, "rt_output");
			bloomDef->mapOutputChannel(1, "rt_input");
		}

		//Glass compositor is loaded from script but here is the hard coded equivalent
		//if (!compositorManager->hasNodeDefinition("Glass"))
		//{
		//	CompositorNodeDef *glassDef = compositorManager->addNodeDefinition("Glass");

		//	//Input channels
		//	glassDef->addTextureSourceName("rt_input", 0, TextureDefinitionBase::TEXTURE_INPUT);
		//	glassDef->addTextureSourceName("rt_output", 1, TextureDefinitionBase::TEXTURE_INPUT);

		//	glassDef->mCustomIdentifier = "Ogre/Postprocess";

		//	glassDef->setNumTargetPass(1);

		//	{
		//		CompositorTargetDef *targetDef = glassDef->addTargetPass("rt_output");

		//		{
		//			CompositorPassQuadDef *passQuad;
		//			passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
		//			passQuad->mMaterialName = "Postprocess/Glass";
		//			passQuad->addQuadTextureSource(0, "rt_input", 0);
		//		}
		//	}

		//	//Output channels
		//	glassDef->setNumOutputChannels(2);
		//	glassDef->mapOutputChannel(0, "rt_output");
		//	glassDef->mapOutputChannel(1, "rt_input");
		//}

		//if (!compositorManager->hasNodeDefinition("Motion Blur"))
		//{
		//	/// Motion blur effect
		//	CompositorNodeDef *motionBlurDef = compositorManager->addNodeDefinition("Motion Blur");

		//	//Input channels
		//	motionBlurDef->addTextureSourceName("rt_input", 0, TextureDefinitionBase::TEXTURE_INPUT);
		//	motionBlurDef->addTextureSourceName("rt_output", 1, TextureDefinitionBase::TEXTURE_INPUT);

		//	motionBlurDef->mCustomIdentifier = "Ogre/Postprocess";

		//	//Local textures
		//	motionBlurDef->setNumLocalTextureDefinitions(1);
		//	{
		//		TextureDefinitionBase::TextureDefinition *texDef =
		//			motionBlurDef->addTextureDefinition("sum");
		//		texDef->width = 0;
		//		texDef->height = 0;
		//		texDef->formatList.push_back(Ogre::PF_R8G8B8);
		//	}

		//	motionBlurDef->setNumTargetPass(3);

		//	/// Initialisation pass for sum texture
		//	{
		//		CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("sum");
		//		{
		//			CompositorPassQuadDef *passQuad;
		//			passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
		//			passQuad->mNumInitialPasses = 1;
		//			passQuad->mMaterialName = "Ogre/Copy/4xFP32";
		//			passQuad->addQuadTextureSource(0, "rt_input", 0);
		//		}
		//	}
		//	/// Do the motion blur
		//	{
		//		CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("rt_output");

		//		{
		//			CompositorPassQuadDef *passQuad;
		//			passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
		//			passQuad->mMaterialName = "Postprocess/Combine";
		//			passQuad->addQuadTextureSource(0, "rt_input", 0);
		//			passQuad->addQuadTextureSource(1, "sum", 0);
		//		}
		//	}
		//	/// Copy back sum texture for the next frame
		//	{
		//		CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("sum");

		//		{
		//			CompositorPassQuadDef *passQuad;
		//			passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
		//			passQuad->mMaterialName = "Ogre/Copy/4xFP32";
		//			passQuad->addQuadTextureSource(0, "rt_output", 0);
		//		}
		//	}

		//	//Output channels
		//	motionBlurDef->setNumOutputChannels(2);
		//	motionBlurDef->mapOutputChannel(0, "rt_output");
		//	motionBlurDef->mapOutputChannel(1, "rt_input");
		//}
	}

	//#define GRAPHICS_THREAD 1  //compile with graphics render thread

	GraphicsManager::GraphicsManager(XE::XEngine* engine) :
		mRoot(0)

		//	, mWindowManager()
		, _t_OgreWorkspace(nullptr) //creates window in mainthread
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

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			LOG(plog::error) << "Cannot initialize SDL2! - GraphicsSystem::initialize";

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
	//FIXME crash?	delete mRenderThread;
		delete _t_OgreWorkspace;

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

			Ogre::String dataFolder = mEngine->settings.dataRootFolder + "/Hlms";

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

			Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Common/Any","FileSystem", true);
			Ogre::Archive *archivePbsLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "/Pbs/Any","FileSystem", true);
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


			//loading
			//GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
			//DataStreamPtr shaderCacheFile = mRoot->openFileStream("F:/Projekte/coop/XGame/data/MyCache.cache");
			//GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);

			_t_createCustomTextures(mRoot, _t_RenderWindow);
			_t_createExtraEffectsFromCode(mRoot);


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

		mAccumTimeSinceLastLogicFrame = timeSinceLast;
		
		
		m_GUIRenderer._t_update(timeSinceLast);
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