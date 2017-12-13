#include <XERenderer/OgreWorkspace.hpp>

#include <XEngine.hpp>

#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbs.h>
#include <Ogre/OgreMain/include/OgreDepthBuffer.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorManager2.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspaceDef.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorNodeDef.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorShadowNodeDef.h>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorCommon.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPass.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPassDef.h>
#include <Ogre/OgreMain/include/Compositor/Pass/PassClear/OgreCompositorPassClear.h>
#include <Ogre/OgreMain/include/Compositor/Pass/PassScene/OgreCompositorPassScene.h>


#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspace.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspaceDef.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorNode.h>
#include <Ogre/OgreMain/include/Compositor/OgreCompositorNodeDef.h>


#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspace.h>
#include <Ogre/OgreMain/include/OgreCamera.h>

#include <SDL_syswm.h>

#include <XERenderer/Editor/ImgGuiRenderable.hpp>
#include <ThirdParty/imgui/imgui.h>

namespace XE {

	ImGuiCompositorWorkspaceListener::ImGuiCompositorWorkspaceListener() :m_ImgGuiRenderable(0) {}

	ImGuiCompositorWorkspaceListener::ImGuiCompositorWorkspaceListener(Ogre::Camera* camera)
		:m_ImgGuiRenderable(0) {
		m_camera = camera;
	}

	void ImGuiCompositorWorkspaceListener::passPreExecute(Ogre::CompositorPass *pass) {

		if (pass->getDefinition()->mIdentifier == 10010)
		{
			ImGuiIO& io = ImGui::GetIO();

			//Needed later
		//	Ogre::Viewport *vp = m_camera->getSceneManager()->getCurrentViewport();

			Ogre::Matrix4 projMatrix(2.0f / io.DisplaySize.x, 0.0f, 0.0f, -1.0f,
									0.0f, -2.0f / io.DisplaySize.y, 0.0f, 1.0f,
									0.0f, 0.0f, -1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f);

			m_camera->setCustomProjectionMatrix(true, projMatrix);
			
			//render the object
		/*	if(m_ImgGuiRenderable)
			{
				m_ImgGuiRenderable->m_sceneNodeLines->setPosition(m_camera->getPosition());
				m_ImgGuiRenderable->m_sceneNodeLines->setOrientation(m_camera->getOrientation());
			}*/
		}
		else
		{
			m_camera->setCustomProjectionMatrix(false);
		}
	}

	//Ogre::IdString OgreCompositorPassProvider::mPassId = Ogre::IdString("ImGui");

	//ImGuiPass::ImGuiPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
	//	Ogre::CompositorNode *parentNode, GraphicsManager& graphicsMgr)
	//	: Ogre::CompositorPass(definition, target, parentNode) ,m_GraphicsManager(graphicsMgr)
	//{

	//}

	//void ImGuiPass::execute(const Ogre::Camera *lodCameraconst)
	//{
	////-----------------------------	m_GraphicsManager.getGUIRenderer()._t_update();
	////todo!	static_cast<MyGUI::OgreRenderManager*>(MyGUI::RenderManager::getInstancePtr())->render();
	//}

Ogre::IdString OgreCompositorPassProvider::mPassId = Ogre::IdString("MYGUI");

MyGUIPass::MyGUIPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
	Ogre::CompositorNode *parentNode, GraphicsManager& graphicsMgr, Ogre::Camera* camera)
	: Ogre::CompositorPass(definition, target, parentNode) 
	,m_GraphicsManager(graphicsMgr),
	m_camera(camera)
{

}

void MyGUIPass::execute(const Ogre::Camera *lodCameraconst)
{
	ImGuiIO& io = ImGui::GetIO();

	Ogre::Matrix4 projMatrix(2.0f / io.DisplaySize.x, 0.0f, 0.0f, -1.0f,
		0.0f, -2.0f / io.DisplaySize.y, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	m_camera->setCustomProjectionMatrix(true, projMatrix);

//-----------------------------	m_GraphicsManager.getGUIRenderer()._t_update();
//todo!	static_cast<MyGUI::OgreRenderManager*>(MyGUI::RenderManager::getInstancePtr())->render();
}

	OgreWorkspace::OgreWorkspace(GraphicsManager& graphicsMgr, Ogre::SceneManager* sceneMgr) :
		mGraphicsManager(graphicsMgr),
		m_imguilistener(),
		_t_compositorWorkspace(nullptr),
		//	mRenderWindow(nullptr),
		//	mWindow(nullptr),
		_t_sceneMgr(sceneMgr)
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
				LOG(plog::error) << "Couldn't get WM Info! (SDL2) - GraphicsSystem::initialize";

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
		//	params.insert(std::make_pair("FSAA", "4"));
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

	//http://www.ogre3d.org/forums/viewtopic.php?f=25&t=84734
	void setShadowMapping(Ogre::CompositorNodeDef *nodeDef, bool shadowsEnabled, uint32 numShadowCastingLights,
		uint32 resolution = 2048,
		bool usePssm = true, uint32 numPssmSplits = 3,
		Ogre::HlmsPbs::ShadowFilter shadowFilter = Ogre::HlmsPbs::PCF_3x3)
	{
		size_t numShadowMaps = numShadowCastingLights + (usePssm ? (numPssmSplits - 1) : 0);
		size_t split = 0;
		size_t lightIdx = 0;

		CompositorManager2 *compositorManager = Root::getSingleton().getCompositorManager2();
		//	compositorManager->removeAllShadowNodeDefinitions();

		CompositorShadowNodeDef *shadowNodeDef = compositorManager->addShadowNodeDefinition("myShadowNode");

		shadowNodeDef->setNumLocalTextureDefinitions(numShadowMaps);

		shadowNodeDef->setDefaultTechnique(SHADOWMAP_PSSM);

		/*for (size_t i = 0; i<numShadowMaps; ++i)
		{
			ShadowTextureDefinition *shadowTexDef =shadowNodeDef->addShadowTextureDefinition(lightIdx, split,StringConverter::toString(i), false);

			shadowTexDef->width = resolution;
			shadowTexDef->height = resolution;
			shadowTexDef->formatList.push_back(PF_D32_FLOAT);
			shadowTexDef->depthBufferId = Ogre::DepthBuffer::POOL_NON_SHAREABLE;

			if (usePssm && i < numPssmSplits)
			{
				shadowTexDef->shadowMapTechnique = SHADOWMAP_PSSM;
				shadowTexDef->pssmLambda = 0.95f;
				shadowTexDef->numSplits = 3;
				++split;

				if (split >= numPssmSplits)
				{
					split = 0;
					++lightIdx;
				}
			}
			else
			{
				shadowNodeDef->setDefaultTechnique(SHADOWMAP_FOCUSED);
				shadowTexDef->shadowMapTechnique = SHADOWMAP_FOCUSED;
				split = 0;
				++lightIdx;
			}
		}*/

		shadowNodeDef->setNumTargetPass(numShadowMaps);

		for (size_t i = 0; i < numShadowMaps; ++i)
		{
			CompositorTargetDef *targetPassDef = shadowNodeDef->addTargetPass(StringConverter::toString(i));
			targetPassDef->setNumPasses(2);

			{
				CompositorPassClearDef *pass = static_cast<CompositorPassClearDef*>(targetPassDef->addPass(PASS_CLEAR));
				pass->mClearBufferFlags = FBT_DEPTH | FBT_STENCIL;
				pass->mShadowMapIdx = i;
				pass->mIncludeOverlays = false;
			}

			{
				CompositorPassSceneDef *pass = static_cast<CompositorPassSceneDef*>(targetPassDef->addPass(PASS_SCENE));
				pass->mVisibilityMask = 0x00000001;
				pass->mShadowMapIdx = i;
				pass->mIncludeOverlays = false;
			}
		}

		//	CompositorNodeDef *nodeDef = compositorManager->getNodeDefinitionNonConst("DefaultNode");

			//for (size_t i = 0; i<nodeDef->getNumTargetPasses(); ++i)
			//{
			//	CompositorTargetDef *targetDef = nodeDef->getTargetPass(i);

			//	const CompositorPassDefVec &passDefs = targetDef->getCompositorPasses();
			//	CompositorPassDefVec::const_iterator itor = passDefs.begin();
			//	CompositorPassDefVec::const_iterator end = passDefs.end();

			//	while (itor != end)
			//	{
			//		CompositorPassDef *passDef = *itor;

			//		//if (passDef->mIdentifier == 1000) //We actually flag which passes use a shadow node with an identifier
			//		//{
			//		if (passDef->getType() == Ogre::PASS_SCENE) {
			//		//	assert(passDef->getType() == PASS_SCENE);
			//			CompositorPassSceneDef *passSceneDef = static_cast<CompositorPassSceneDef*>(passDef);
			//			passSceneDef->mShadowNode = shadowsEnabled ? IdString("myShadowNode") : IdString();
			//		}
			//		/*else
			//		{
			//			assert(passDef->getType() != PASS_SCENE);
			//		}*/

			//		++itor;
			//	}
			//}

		Ogre::Root *root = Root::getSingletonPtr();
		Ogre::HlmsManager *hlmsManager = root->getHlmsManager();
		Ogre::Hlms *hlms = hlmsManager->getHlms(Ogre::HLMS_PBS);

		Ogre::HlmsPbs *hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlms);
		hlmsPbs->setShadowSettings(shadowFilter);
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

			//##### mPassProvider.reset(new OgreCompositorPassProvider(mGraphicsManager, camera));

		_t_ImGUIPassProvider.reset(new ImGUICompositorPassProvider());
	//	Ogre::CompositorManager2* pCompositorManager = Ogre::Root::getSingleton().getCompositorManager2();

		// don't overwrite a custom pass provider that the user may have registered already
		if (!m_compositorManager->getCompositorPassProvider())
		{
			m_compositorManager->setCompositorPassProvider(_t_ImGUIPassProvider.get());
		}
		else
		{
			/*	MYGUI_PLATFORM_LOG(Warning, "A custom pass provider is already installed." <<
			"MyGui passes will not work unless the registered provider can create MyGui passes");*/
		}

			// don't overwrite a custom pass provider that the user may have registered already
	//KH	
		//##### if (!m_compositorManager->getCompositorPassProvider())
		//##### 	m_compositorManager->setCompositorPassProvider(mPassProvider.get());


		//if (!m_compositorManager->hasWorkspaceDefinition("MyOwnWorkspace"))
		//{
		//	//funtzt ->>>
		//	//	m_compositorManager->createBasicWorkspaceDef("MyOwnWorkspace", ColourValue(0.6f, 0.0f, 0.6f));

		//	Ogre::CompositorNodeDef *nodeDef = m_compositorManager->addNodeDefinition("AutoGen " + (Ogre::IdString("MyOwnWorkspace") + Ogre::IdString("/Node")).getReleaseText());

		//	//Input texture
		//	nodeDef->addTextureSourceName("WindowRT", 0, Ogre::TextureDefinitionBase::TEXTURE_INPUT);

		//	Ogre::CompositorPassSceneDef *passScene;

		//	nodeDef->setNumTargetPass(1);
		//	{
		//		Ogre::CompositorTargetDef *targetDef = nodeDef->addTargetPass("WindowRT");
		//		targetDef->setNumPasses(2);
		//		{
		//			{
		//				Ogre::CompositorPassClearDef *passClear = static_cast<Ogre::CompositorPassClearDef*> (targetDef->addPass(Ogre::PASS_CLEAR));
		//				passClear->mColourValue = Ogre::ColourValue(0.6f, 0.0f, 0.6f);
		//			}
		//			{
		//				passScene = static_cast<Ogre::CompositorPassSceneDef*> (targetDef->addPass(Ogre::PASS_SCENE));
		//				//passScene->mShadowNode = IdString("myShadowNode"); // Ogre::IdString();
		//				//passScene->mShadowNode = IdString("ShadowMapDebuggingEsmShadowNodeCompute");
		//				passScene->mVpWidth = 1.0;
		//				passScene->mVpHeight = 1.0;
		//				passScene->mVpLeft = 0.0f;
		//				passScene->mCameraName = camera->getName(); // "LeftCamera";
		//			//	passScene->mFirstRQ = 0;
		//		//		passScene->mLastRQ = 250;
		//				// For the MyGUI pass
		//			//	targetDef->addPass(Ogre::PASS_CUSTOM, OgreCompositorPassProvider::mPassId);

		//			}
		//			//{
		//			//	passScene = static_cast<Ogre::CompositorPassSceneDef*> (targetDef->addPass(Ogre::PASS_SCENE));
		//			//	passScene->mVpWidth = 1.0;
		//			//	passScene->mVpHeight = 1.0;
		//			//	passScene->mVpLeft = 0.0f;
		//			//	passScene->mCameraName = camera->getName(); // "LeftCamera";
		//			//	passScene->mFirstRQ = 250;
		//			//	passScene->mLastRQ = 255;
		//			//	passScene->mIdentifier = 10010;
		//			//	//targetDef->addPass(Ogre::PASS_CUSTOM, OgreCompositorPassProvider::mPassId);
		//			//}

		//			//{
		//			//	Ogre::CompositorPassSceneDef *passScene = static_cast<Ogre::CompositorPassSceneDef*>
		//			//		(targetDef->addPass(Ogre::PASS_SCENE));
		//			//	passScene->mShadowNode = Ogre::IdString();
		//			//	passScene->mVpWidth = 0.5;
		//			//	passScene->mVpHeight = 0.5;
		//			//	passScene->mVpLeft = 0.5f;
		//			//	passScene->mCameraName = "RightCamera";
		//			//}
		//		}
		//	}
		//	//----	nodeDef->getTargetPass(0)->getCompositorPasses()->
		//	//passScene->

			Ogre::CompositorWorkspaceDef *workDef = m_compositorManager->addWorkspaceDefinition(std::string("MyOwnWorkspace"));
		//	//workDef->connectOutput(nodeDef->getName(), 0);
		//	//##############	workDef->connectExternal(0, nodeDef->getName(), 0);

		//	//	this->mGraphicsManager.getRoot()->getHlmsManager()->setShadowMappingUseBackFaces(false);

		//	//	setShadowMapping(nodeDef, true, 1 , 2048, true);
		//		//todo!	controller.getControllerView().getCameraController()._t_getOgreCamera();
		////##############	_t_compositorWorkspace = m_compositorManager->addWorkspace(mEngine.getOgreSceneManager().__OgreSceneMgrPtr, renderWindow, camera, "MyOwnWorkspace", true, 0);


			//////////CompositorNodeDef *nodeDef = m_compositorManager->addNodeDefinition("AutoGen " + IdString(std::string("MyOwnWorkspace") +
			//////////	"/Node").getReleaseText());

			////////////Input texture
			//////////nodeDef->addTextureSourceName("WindowRT", 0, TextureDefinitionBase::TEXTURE_INPUT);

			//////////nodeDef->setNumTargetPass(1);
			//////////{
			//////////	CompositorTargetDef *targetDef = nodeDef->addTargetPass("WindowRT");
			//////////	targetDef->setNumPasses(2);
			//////////	{
			//////////		{
			//////////			CompositorPassClearDef *passClear = static_cast<CompositorPassClearDef*>
			//////////				(targetDef->addPass(PASS_CLEAR));
			//////////			passClear->mColourValue = Ogre::ColourValue(0.6f, 0.0f, 0.6f);
			//////////		}
			//////////		{
			//////////			CompositorPassSceneDef *passScene = static_cast<CompositorPassSceneDef*>
			//////////				(targetDef->addPass(PASS_SCENE));
			//////////			
			//////////			passScene->mFirstRQ = 254;
			//////////			passScene->mLastRQ = 255;
			//////////			targetDef->addPass(Ogre::PASS_CUSTOM, ImGUICompositorPassProvider::mPassId);
			//////////		//	passScene->mShadowNode = shadowNodeName;
			//////////		}
			//////////	}
			//////////}
			//////////workDef->connectExternal(0, nodeDef->getName(), 0);
			//////////_t_compositorWorkspace = m_compositorManager->addWorkspace(mEngine.getOgreSceneManager().__OgreSceneMgrPtr, renderWindow, camera, "MyOwnWorkspace", true, 0);


			//	myworkspace->recreateAllNodes();
			//	myworkspace->reconnectAllNodes();
			//	myworkspace->validateAllObjects();

				//passScene->
				//myworkspace->getListener();
			//	CompositorPass * test;
		//	m_imguilistener.m_camera = camera;
		//	mGraphicsManager.getGUIRenderer()._t_initimgui(&mEngine.getOgreSceneManager().__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), mEngine.getOgreSceneManager().__OgreSceneMgrPtr, camera);
		//	m_imguilistener.m_ImgGuiRenderable = mGraphicsManager.getGUIRenderer()._t_ImgGuiRenderable;
		//	myworkspace->setListener(&m_imguilistener);


		//}
		//	});

				//Ogre::CompositorWorkspace*  workspace = m_compositorManager->addWorkspace(mEngine.getOgreSceneManager().__OgreSceneMgrPtr, renderWindow, camera, "MyOwnWorkspace", true);

				//CompositorNode *node = workspace->findNode("Bloom");
				//node->setEnabled(!node->getEnabled());

				////The workspace instance can't return a non-const version of
				////its definition, so we perform the lookup this way.
				//CompositorWorkspaceDef *workspaceDef = m_compositorManager->getWorkspaceDefinition("MyOwnWorkspace");

				////workspaceDef->clearAllInterNodeConnections();

				//IdString finalCompositionId = "FinalComposition";
				//const CompositorNodeVec &nodes = workspace->getNodeSequence();

				//IdString lastInNode;
				//CompositorNodeVec::const_iterator it = nodes.begin();
				//CompositorNodeVec::const_iterator en = nodes.end();

				//while (it != en)
				//{
				//	CompositorNode *outNode = *it;

				//	if (outNode->getEnabled() && outNode->getName() != finalCompositionId)
				//	{
				//		//Look for the next enabled node we can connect to
				//		CompositorNodeVec::const_iterator it2 = it + 1;
				//		while (it2 != en && (!(*it2)->getEnabled() || (*it2)->getName() == finalCompositionId))
				//			++it2;

				//		if (it2 != en)
				//		{
				//			lastInNode = (*it2)->getName();
				//			workspaceDef->connect(outNode->getName(), lastInNode);
				//		}

				//		it = it2 - 1;
				//	}

				//	++it;
				//}

				//if (lastInNode == IdString())
				//	lastInNode = "PostprocessingSampleStdRenderer";

				//workspaceDef->connect(lastInNode, 0, "FinalComposition", 1);


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
