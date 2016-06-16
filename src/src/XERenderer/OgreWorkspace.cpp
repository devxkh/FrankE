#include <XERenderer/OgreWorkspace.hpp>

#include <XEngine.hpp>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorManager2.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspaceDef.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorNodeDef.h>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorCommon.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPass.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPassDef.h>
#include <Ogre/OgreMain/include/Compositor/Pass/PassClear/OgreCompositorPassClear.h>
#include <Ogre/OgreMain/include/Compositor/Pass/PassScene/OgreCompositorPassScene.h>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspaceListener.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspace.h>


#include <SDL_syswm.h>


namespace XE {

	Ogre::IdString OgreCompositorPassProvider::mPassId = Ogre::IdString("MYGUI");

	MyGUIPass::MyGUIPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
		Ogre::CompositorNode *parentNode, GraphicsManager& graphicsMgr)
		: Ogre::CompositorPass(definition, target, parentNode) ,m_GraphicsManager(graphicsMgr)
	{

	}

	void MyGUIPass::execute(const Ogre::Camera *lodCameraconst)
	{
	//-----------------------------	m_GraphicsManager.getGUIRenderer()._t_update();
	//todo!	static_cast<MyGUI::OgreRenderManager*>(MyGUI::RenderManager::getInstancePtr())->render();
	}

	OgreWorkspace::OgreWorkspace(XEngine& engine, GraphicsManager& graphicsMgr) :
		mGraphicsManager(graphicsMgr),
		//	mRenderWindow(nullptr),
		//	mWindow(nullptr),
		mEngine(engine)
	{
		//----------------------------------------------------------------
		//------------------ create window -------------------------------
		//need ogre root initialized
		//	if (!isEditor)//todo !Controller can select window
		//		mWindow = createWindow(sf::VideoMode(800, 600), "Ogre3D v2.0 and SFML v2.2", sf::Style::Default);
	}

	OgreWorkspace::~OgreWorkspace()
	{
		//geht nicht====???????
		//OGRE_DELETE_T(mWindow,sf::Window, Ogre::MEMCATEGORY_GEOMETRY);
	}

	Ogre::TexturePtr OgreWorkspace::createTextureRenderTarget(int width, int height)
	{
		return Ogre::TextureManager::getSingleton().createManual("RttTex",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, width, height, 0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);
	}

	Ogre::RenderTarget* OgreWorkspace::createRenderTarget(int width, int height, Ogre::RenderTarget* renderTarget)
	{
		//View& view = controller.getView();

		//todo hold list with all rendertargets

		//Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual("EyeTexture", "General", Ogre::TextureType::TEX_TYPE_2D, 1182 * 2, 1461, 0, Ogre::PixelFormat::PF_A8R8G8B8, Ogre::TU_RENDERTARGET);
		//todo KH	
		mRtt_texture = Ogre::TextureManager::getSingleton().createManual("RttTex",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, width, height, 0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);


		return nullptr; //todo KH view.mRenderTarget = mRtt_texture->getBuffer()->getRenderTarget();
	}

	Ogre::RenderWindow* OgreWorkspace::_t_createRenderWindow(void* window)
	{
		//View& view = controller.getView();

		//-------------------------------
		// Create Window

		Ogre::NameValuePairList params;

		//http://www.ogre3d.org/forums/viewtopic.php?f=1&t=79384

		if (window)
		{
			//Get the native whnd
			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);

			if (SDL_GetWindowWMInfo((SDL_Window*)window, &wmInfo) == SDL_FALSE)
				LOG(ERROR) << "Couldn't get WM Info! (SDL2) - GraphicsSystem::initialize";

			Ogre::String winHandle;

			switch (wmInfo.subsystem)
			{
#ifdef WIN32
			case SDL_SYSWM_WINDOWS:
				// Windows code
				winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.win.window);
				break;
#elif __MACOSX__
			case SDL_SYSWM_COCOA:
				//required to make OGRE play nice with our window
				params.insert(std::make_pair("macAPI", "cocoa"));
				params.insert(std::make_pair("macAPICocoaUseNSView", "true"));

				winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
				break;
#else
			case SDL_SYSWM_X11:
				winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.x11.window);
				break;
#endif
			default:
				OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
					"Unexpected WM! (SDL2)",
					"GraphicsSystem::initialize");
				break;
			}

			//params.insert(std::make_pair("title", windowTitle));
			params.insert(std::make_pair("gamma", "true"));
		//	params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
		//	params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			params.insert(std::make_pair("externalWindowHandle", winHandle));
#else
			params.insert(std::make_pair("parentWindowHandle", winHandle));
#endif


		//	unsigned long winHandle = reinterpret_cast<unsigned long>(window->getSystemHandle());
			//unsigned long winGlContext = reinterpret_cast<unsigned long>(wglGetCurrentContext());

		//	misc["externalWindowHandle"] = Ogre::StringConverter::toString(winHandle);
		}
		else
		{
			params["hidden"] = Ogre::String("True");
		}
		//	misc["externalGLContext"] = XE::StringConverter::toString(winGlContext);
		//	misc["externalGLControl"] = Ogre::String("True");
//#else
//		misc["currentGLContext"] = String("True");
//#endif

		//--------------------------------
	
			Ogre::RenderWindow* renderWindow = Ogre::Root::getSingleton().createRenderWindow("Main", 0, 0, false, &params);
		//	}

		//	view.mWindow = mWindow;
		//über graphics controller!!!!	controller.setRenderWindow(mRenderWindow);
		//view.mRenderWindow = mRenderWindow;

	//	sf::WindowHandle mHwnd = 0;
		//renderWindow->getCustomAttribute("WINDOW", &mHwnd);
	//	renderWindow->setActive(true);
		//todo KH	view.mRenderWindow->setAutoUpdated(false);



		//	Ogre::WindowEventUtilities::addWindowEventListener(view.mRenderWindow, controller);
		return renderWindow;
	}

	void OgreWorkspace::_t_createWorkspace(Ogre::RenderWindow* renderWindow, Ogre::Camera* camera)
	{

	//	mGraphicsManager.getIntoRendererQueue().push([this, renderWindow, camera](){

			//create Camera
			//wird in controller constructor gemacht	controller.setCamera(OGRE_NEW Camera(controller.getID(), &mEngine->getScene()));

			//std::stringstream camName;
			//camName << "Cam" << controller.getID(); // camera wird in controller constructor erstellt

			//view.mCamera->getCamera()->setNearClipDistance(0.7);
			//view.mCamera->getCamera()->setAutoAspectRatio(true);



			//new create compositor
			//rendersystem intialize needed for compositor
			//window needed for HardwareBufferManager!
			// Create the compositor after the first RenderWindow has been created (D3D9 complains)
			//KH ?????  mGraphicsManager->getRoot()->initialiseCompositor();

		Ogre::CompositorManager2* m_compositorManager = this->mGraphicsManager.getRoot()->getCompositorManager2();

			mPassProvider.reset(new OgreCompositorPassProvider(mGraphicsManager));

			// don't overwrite a custom pass provider that the user may have registered already
	//KH		if (!m_compositorManager->getCompositorPassProvider())
				m_compositorManager->setCompositorPassProvider(mPassProvider.get());


			if (!m_compositorManager->hasWorkspaceDefinition("MyOwnWorkspace"))
			{
				//funtzt ->>>
				//	m_compositorManager->createBasicWorkspaceDef("MyOwnWorkspace", ColourValue(0.6f, 0.0f, 0.6f));

				Ogre::CompositorNodeDef *nodeDef = m_compositorManager->addNodeDefinition("AutoGen " + (Ogre::IdString("MyOwnWorkspace") + Ogre::IdString("/Node")).getReleaseText());

				//Input texture
				nodeDef->addTextureSourceName("WindowRT", 0, Ogre::TextureDefinitionBase::TEXTURE_INPUT);

				Ogre::CompositorPassSceneDef *passScene;

				nodeDef->setNumTargetPass(1);
				{
					Ogre::CompositorTargetDef *targetDef = nodeDef->addTargetPass("WindowRT");
					targetDef->setNumPasses(3);
					{
						{
							Ogre::CompositorPassClearDef *passClear = static_cast<Ogre::CompositorPassClearDef*> (targetDef->addPass(Ogre::PASS_CLEAR));
							passClear->mColourValue = Ogre::ColourValue(0.6f, 0.0f, 0.6f);
						}
						{
							passScene = static_cast<Ogre::CompositorPassSceneDef*> (targetDef->addPass(Ogre::PASS_SCENE));
							passScene->mShadowNode = Ogre::IdString();
							passScene->mVpWidth = 1.0;
							passScene->mVpHeight = 1.0;
							passScene->mVpLeft = 0.0f;
							passScene->mCameraName = camera->getName(); // "LeftCamera";

							// For the MyGUI pass
							targetDef->addPass(Ogre::PASS_CUSTOM, OgreCompositorPassProvider::mPassId);
							
						}


						//{
						//	Ogre::CompositorPassSceneDef *passScene = static_cast<Ogre::CompositorPassSceneDef*>
						//		(targetDef->addPass(Ogre::PASS_SCENE));
						//	passScene->mShadowNode = Ogre::IdString();
						//	passScene->mVpWidth = 0.5;
						//	passScene->mVpHeight = 0.5;
						//	passScene->mVpLeft = 0.5f;
						//	passScene->mCameraName = "RightCamera";
						//}
					}
				}
				//----	nodeDef->getTargetPass(0)->getCompositorPasses()->
				//passScene->
				Ogre::CompositorWorkspaceDef *workDef = m_compositorManager->addWorkspaceDefinition(std::string("MyOwnWorkspace"));
				workDef->connectOutput(nodeDef->getName(), 0);

				//todo!	controller.getControllerView().getCameraController()._t_getOgreCamera();
				Ogre::CompositorWorkspace*  myworkspace = m_compositorManager->addWorkspace(mEngine.getOgreSceneManager().__OgreSceneMgrPtr, renderWindow, camera, "MyOwnWorkspace", true);

				//passScene->
				//myworkspace->getListener();
				//CompositorPass * test;
				//CompositorWorkspaceListener listener(test);
				//myworkspace->setListener(&listener);

			}
	//	});


		//TEST Ogre::CompositorNodeDef *nodeDef = m_compositorManager->addNodeDefinition("AutoGen " + (Ogre::IdString("MyOwnWorkspace") +	Ogre::IdString("/Node")).getReleaseText());

		//needs node def!!
		//TESTOgre::CompositorWorkspaceDef *workDef = m_compositorManager->addWorkspaceDefinition(std::string("MyOwnWorkspace"));
		//TESTworkDef->connectOutput(nodeDef->getName(), 0);

		//needs initialiseCompositor !!
		//needs  workDef!! e.g. MyOwnWorkspace
		//TESTm_compositorManager->addWorkspace(mEngine->getScene().getSceneMgr(), mRenderWindow, view.mCamera->getCamera(), "MyOwnWorkspace", true);

	}

	//void OgreWorkspace::createViewport(Controller& controller, Ogre::RenderWindow* renderWindow, Ogre::RenderTarget* renderTarget)
	//{
	//	ControllerVector& controllers = mEngine->getCtrlMgr().getList();
	//	Ogre::uint16 controllerQty = controllers.size();
	////	View& view = controller.getView();
	//
	//	//----------------- Viewport -----------------
	//	float lViewportWidth = 1.0f;
	//	float lViewportHeight = 1.0f;
	//	float lViewportLeft = 0;
	//	float lViewportTop = 0;
	//	unsigned short lMainViewportZOrder = 100 * controller.getID();
	//
	//	// more than 2 controller
	//	if (controllerQty > 2 && controller.getID() != 0)
	//	{
	//		lViewportHeight = 0.5f;// 2 Viewports vertical, 2 vp horizontal
	//	}
	//	// more than one controller
	//	else if (controllerQty > 1)
	//	{
	//		lViewportWidth = 0.5f;  // 2 Viewports horizontal, 1 vertical
	//
	//		if (controller.getID() != 0)
	//			lViewportLeft = 0.5f;
	//	}
	//	// just one controller
	//	else
	//	{
	//		//Full Screen = One Viewport
	//		lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
	//		lViewportTop = (1.0f - lViewportHeight) * 0.5f;
	//	}
	//
	//	//Viewport
	//	//todo need to know how much vieport are set in the renderwindow
	//	if (renderWindow)
	//	{
	//		//todo KHview.mViewport = mRenderWindow->addViewport(view.mCamera->getCamera(), lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);
	//		//todo KHview.mViewport->setAutoUpdated(true);
	//	
	//		mWindow->setVerticalSyncEnabled(false); //not used!
	//		mRenderWindow->setVSyncEnabled(false);
	//	}
	//	else if (renderTarget)
	//	{
	//		//todo KH	view.mViewport = renderTarget->addViewport(view.mCamera->getCamera(), 50, 0, 0, 1.0f, 1.0f);
	//	}
	//
	////todo??	view.mCamera->getCamera()->setAspectRatio((float)view.mViewport->getActualWidth() / (float)view.mViewport->getActualHeight());
	//
	//	//todo KHif (controller.getID() == 0)
	//		//todo KH	view.mViewport->setBackgroundColour(Ogre::ColourValue(1, 0, 1));
	//		//todo KHelse
	//	//todo KH	view.mViewport->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
	//}

	void OgreWorkspace::UpdateViews()
	{
		return;

		//ControllerVector& controllers = mEngine.getCtrlMgr().getList();

		//Ogre::uint16 controllerQty = controllers.size();

		//for (ControllerVector::iterator it = controllers.begin(); it != controllers.end(); it++)
		//{
		//	//	View& view = (*it)->getView();

		//	//----------------- Viewport -----------------
		//	float lViewportWidth = 1.0f;
		//	float lViewportHeight = 1.0f;
		//	float lViewportLeft = 0;
		//	float lViewportTop = 0;
		//	unsigned short lMainViewportZOrder = 100 * (*it)->getID();

		//	// more than 2 controller
		//	if (controllerQty > 2 && (*it)->getID() != 0)
		//	{
		//		lViewportHeight = 0.5f;// 2 Viewports vertical, 2 vp horizontal
		//	}
		//	// more than one controller
		//	else if (controllerQty > 1)
		//	{
		//		lViewportWidth = 0.5f;  // 2 Viewports horizontal, 1 vertical

		//		if ((*it)->getID() != 0)
		//			lViewportLeft = 0.5f;
		//	}
		//	// just one controller
		//	else
		//	{
		//		//Full Screen = One Viewport
		//		lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
		//		lViewportTop = (1.0f - lViewportHeight) * 0.5f;
		//	}

		//	/*	view.mViewport->setDimensions( lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);

		//		view.mCamera->getCamera()->setAspectRatio((float)view.mViewport->getActualWidth() / (float)view.mViewport->getActualHeight());*/
		//}
	}

} // namespace XE
