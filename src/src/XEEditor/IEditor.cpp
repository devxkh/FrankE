#include  <XEEditor/IEditor.hpp>

//#include <EditorI/SelectionRectangle.h>
//#include "E:/Projekte/Src Game/_Engine/XEngine/TestXE/XETUI/GUI.h"


//#include <EditorI/TFViewport.h>
#include <XEEditor/Editor.hpp>


namespace EI {


	EI::Editor* gEditor = nullptr;

	//LNK2005 error Because you enabled STATIC_STD_LIBS (which is not recommended unless you know what you do), you must set the same option in your project, which is /MTd.
	//http://en.sfml-dev.org/forums/index.php?topic=7071.0

	//struct ImplData
	//{
	//	Ogre::Root* pRoot;
	//	Ogre::SceneManager* pSceneManager;
	//	Ogre::Camera* pCamera;
	//	Ogre::Viewport* pViewport;
	//	Ogre::RenderWindow* pRenderWindow;
	//	Ogre::RenderSystem* pRenderSystem;

	//	Ogre::SceneNode* pSceneNode;
	//	Ogre::Entity* pEntity;

	//	//	CameraNodes* pCameraNodes;

	//	//	AnimationSystem* pAnimationSystem;


	//	SelectionRectangle* pSelectionRect;
	//	Ogre::PlaneBoundedVolumeListSceneQuery* pVolumeQuery;
	//	bool mouseBoneSelectionModeEnabled;

	//	//	std::vector< BoneInfo > boneInfoList;
	//	//	std::vector< BoneDisplayInfo > boneDisplayInfoList;

	//	bool boneSelectionChangedSinceLastCall;

	//	ImplData()
	//		: pRoot(NULL)
	//		, pSceneManager(NULL)
	//		, pCamera(NULL)
	//		, pViewport(NULL)
	//		, pRenderWindow(NULL)
	//		, pRenderSystem(NULL)
	//		, pSceneNode(NULL)
	//		, pEntity(NULL)
	//		//	, pCameraNodes(NULL)
	//		//	, pAnimationSystem(NULL)
	//		, pSelectionRect(NULL)
	//		, pVolumeQuery(NULL)
	//		, mouseBoneSelectionModeEnabled(false)
	//		, boneSelectionChangedSinceLastCall(true)
	//	{
	//	}
	//};

	//void CreateResourceGroups()
	//{
	//	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("TecnoFreak.data", "Zip", "TecnoFreak");
	//}

	//XE::XEngine* engine;
	//XE::OgreConsole* console;

	//EI::Editor* gEditor = nullptr;



	void getStates(char* statesinfo)
	{
		//std::cout << "getStates";

	//	statesinfo->size = 9;
		//Ogre::String test("hmmm");
	//	statesinfo = "xxx";

		strncpy(statesinfo, "xxx\0", 5);
		std::cout << "getStates:" << statesinfo;
		//char temp[51];
		//if (strlen(word)>50)
		//	return false;
		

	//	statesinfo[0] = test.c_str();
	//	statesinfo->buffer[1] = "1";

	//	for (int i = 0; i < statesinfo->size; i++)
	//		statesinfo->buffer[i] = "h";

		//Ogre::String str(statesinfo->buffer);
		//Ogre::String* states = new Ogre::String[5];
		//str = "asdasd";
		//states[0] = "State1";
	//	states[1] = "State2";
		//states[2] = "State3";
		//states[3] = "State4";

		//statesinfo->buffer = states->c_str();
	}

	unsigned char* command(const char* command, unsigned char* data, int len)
	{
		std::cout << "command";
		
		if (gEditor)
			return gEditor->consoleCmd(command, data, len);

		return 0;
	}

	bool moveToState(const char* stateName)
	{
		std::cout << "moveToState";

		if (gEditor)
		{
			gEditor->moveToState(stateName);

			return true;
		}

		return false;
	}

	void renderTargetSize(const char* rtName, Ogre::Real x, Ogre::Real y)
	{
		gEditor->renderTargetSize(rtName, x, y);
	}

	int pushEvent(sfEvent pushEvent)
	{
		//std::cout << "pushEvent";
	
	//	return pushEvent.key.code;
		int test = 0;

		if (gEditor)
		{
			test = gEditor->pushEvent(pushEvent);
			return test;
		}
		
		/*if (pushEvent.key.code == 23)
			return true;
		else*/
			return -1;

	}

	void* renderOnceTexturePtr(const char* stateName, int width, int height)
	{
		void* bbSurface;

		if (gEditor)
		{
			if (gEditor->getEngine()->running())
			{
				gEditor->getEngine()->update();

				//Ogre::WindowEventUtilities::messagePump();

			}
		}

		return bbSurface;
	}

	//LPVOID stateInit(sf::WindowHandle hwnd, const char* stateName)
	void* stateInit(const char* stateName, int width, int height)
	{
		std::cout << "initState";

		void* bbSurface;

		if (!gEditor)
		{
			gEditor = new EI::Editor();
			bbSurface = gEditor->InitState(stateName, width, height);

			std::cout << "initState OK";

			/*bool running = true;
			while (running)
			{
				EI::stateUpdate();

			}*/
			return bbSurface;
		}

		return bbSurface;
		//	std::thread t1(hello);
		//		t1.join();




		//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		//XE::LogManager::getSingleton().logMessage("TecnoFreak: Initialising scene manger");
		//g_data.pSceneManager = g_data.pRoot->createSceneManager(Ogre::ST_GENERIC);
		//g_data.pCamera = g_data.pSceneManager->createCamera("Default");
		//g_data.pCamera->setNearClipDistance(0.1f);
		//g_data.pCamera->setAutoAspectRatio(true);
		//g_data.pViewport = g_data.pRenderWindow->addViewport(g_data.pCamera);

		//g_data.pViewport->setBackgroundColour(Ogre::ColourValue::Red);

		//Ogre::SceneNode* pRootSceneNode = g_data.pSceneManager->getRootSceneNode();

		////	g_data.pCameraNodes = new CameraNodes(pRootSceneNode, g_data.pCamera);

		//g_data.pSelectionRect = new SelectionRectangle("Selection SelectionRectangle");
		//pRootSceneNode->attachObject(g_data.pSelectionRect);

		//g_data.pVolumeQuery = g_data.pSceneManager->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());

		//XE::LogManager::getSingleton().logMessage("TecnoFreak: Finished initialising Ogre viewport");
	}

	bool stateUpdate()
	{
		if (gEditor)
		{
			if (gEditor->getEngine()->running())
			{
				gEditor->getEngine()->update();

				//Ogre::WindowEventUtilities::messagePump();

				return true;
			}
		}

		return false;
		//if (g_data.pRoot == NULL)
		//{
		//	return;
		//}

		//if (g_data.pRenderWindow == NULL)
		//{
		//	return;
		//}

		///*if (g_data.pCameraNodes == NULL)
		//{
		//return;
		//}*/

		//static Ogre::Timer s_frameTimer;
		//const unsigned long elapsedMilliseconds = s_frameTimer.getMilliseconds();
		//const float elapsedSeconds = static_cast< float >(elapsedMilliseconds) / 1000.f;
		//s_frameTimer.reset();

		//g_data.pRenderWindow->windowMovedOrResized();
		//g_data.pRoot->renderOneFrame();
		//g_data.pCameraNodes->Update();
		//UpdateBoneColours();

		//if (g_data.pAnimationSystem != NULL)
		//{
		//	g_data.pAnimationSystem->update(elapsedSeconds);
		//}
	}

	void quit()
	{
		if (gEditor)
		{
			gEditor->getEngine()->quit();

			delete gEditor;
		}
		//ImplData tmp = g_data;
		//g_data = ImplData();

		////delete tmp.pAnimationSystem;
		////delete tmp.pCameraNodes;
		//delete tmp.pSelectionRect;
		//delete tmp.pRoot;
	}

	//sf::WindowHandle 
	//	bool startState(sf::WindowHandle hwnd)
	//	{
	//		//	sf::WindowHandle winHandle = reinterpret_cast<sf::WindowHandle>(hwnd);
	//		
	//		sf::Window* window = new sf::Window(hwnd);
	//
	//		// Create the window
	//		//sfWindow* window = new sfWindow;
	//		//window->This.create(videoMode, title, style, params);
	//
	//		//sf::Window mWindow(sf::VideoMode(800, 600), "My window");
	//		
	//		unsigned long winHandle = reinterpret_cast<unsigned long>(window->getSystemHandle());
	//
	//	
	//
	//
	//		// initialise root
	//		Ogre::NameValuePairList misc;
	//		misc["externalWindowHandle"] = Ogre::StringConverter::toString(winHandle);
	//		//	misc["externalGLContext"] = XE::StringConverter::toString(winGlContext);
	//		//	misc["externalGLControl"] = Ogre::String("True");
	////#else
	////misc["currentGLContext"] = String("True");
	////#endif
	//
	////		XE::RenderWindow *renderWindow = root->createRenderWindow("Main", 820, 440, false, &misc);
	//
	//		return true;
	//	}

} // ns EI

