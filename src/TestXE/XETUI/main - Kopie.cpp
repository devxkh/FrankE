
#include <XEngine.hpp>

#include "GUI.h"

// Enumeration for user-defined actions
enum MyAction
{
	None,
	//Steuerung
	Forward,                ///< move forward
	ForwardLeft,            ///< move ForwardLeft
	ForwardRight,           ///< move ForwardRight
	Backward,               ///< move backward
	BackwardLeft,           ///< move BackwardLeft
	BackwardRight,          ///< move BackwardRight
	TurnLeft,               ///< TurnLeft
	TurnRight,              ///< TurnRight
	StrafeLeft,             ///< StrafeLeft
	StrafeRight,            ///< StrafeRight
	Jump,					///< Jump
	Run,					///< Run
	Walk,					///< Walk
	NextTarget,				///< Next Target
	PrevTarget,				///< Preview Target
	Punch1,					///< Punch1
	Kick1,					///< Kick1

	//Camera
	ZoomIn,					///< ZoomIn
	ZoomOut,				///< ZoomOut
	CamRotate,				///< Rotate Camera
	PointSelect,			///< Point selection
	PointSelectStart,
	PointSelectEnd,
	MouseMoved,

	//Ohne Combos
	Spell1,					///< Spell 1
	Spell2,					///< Spell 2
	Spell3,					///< Spell 3

	Action1,				///< Aktion 1
	Action2,				///< Aktion 2

	//Menu 
	NavUp,					///< Menu NavigationUP 
	NavDown,				///< Menu NavigationDown 
	NavLeft,				///< Menu NavigationLeft 
	NavRight,				///< Menu NavigationRight 
	NavSelect,				///< Menu Navigation selection
	NavEnter,

	Shoot,
	Resize,
	Quit,
	UIReload,

	Count                   ///< Keep last -- the total number of Commands
};

GUI* guiclass;

// Callback function for Resize events
void onPointSelectStart(XE::ActionContext<MyAction> context);

// Callback function for Shoot (mouse click) events
void onPointSelectEnd(XE::ActionContext<MyAction> context);

 void onMenuNav(MyAction move);

void onMouseMove(XE::ActionContext<MyAction> context);

void onUIReload(XE::ActionContext<MyAction> context);

int main()
{
	XE::ActionMap<MyAction> map;
	using XE::Action;

	std::cout << "start" << std::endl;

	//XE::XERectangleShape rectangle;
	//rectangle.setPosition(30, 30);
	//rectangle.setSize(XE::Vector2f(50, 30));

	//rectangle.setFillColor(XE::XEColor::Yellow);
	//rectangle.setOutlineColor(XE::XEColor::Blue);
	//rectangle.setOutlineThickness(3);
	map[MouseMoved] = Action(XE::Event::MouseMoved);

	map[PointSelectStart] = Action(XE::Mouse::Left, Action::PressOnce);
	map[PointSelectEnd] = Action(XE::Mouse::Left, Action::ReleaseOnce);
	map[UIReload] = Action(XE::Keyboard::R, Action::PressOnce);

	map[Quit] = XE::Action(XE::Keyboard::Escape, XE::Action::PressOnce);
	map[NavLeft] = XE::Action(XE::Keyboard::Left, XE::Action::PressOnce);
	map[NavRight] = XE::Action(XE::Keyboard::Right, XE::Action::PressOnce);
	map[NavUp] = XE::Action(XE::Keyboard::Up, XE::Action::PressOnce);
	map[NavDown] = XE::Action(XE::Keyboard::Down, XE::Action::PressOnce);

	XE::ActionMap<MyAction>::CallbackSystem system;
	//system.connect(MouseMove, &onResize);

	system.connect(PointSelectStart, &onPointSelectStart);
	system.connect(PointSelectEnd, &onPointSelectEnd);
	system.connect(MouseMoved, &onMouseMove);
	system.connect(UIReload, &onUIReload);

	system.connect(NavRight, std::bind(&onMenuNav,  NavRight));
		system.connect(NavLeft, std::bind(&onMenuNav,  NavLeft));
		system.connect(NavUp, std::bind(&onMenuNav,  NavUp));
		system.connect(NavDown, std::bind(&onMenuNav,  NavDown));
	

	XE::Root *root = new XE::Root();

	// choose renderer
	//root->saveConfig();
	root->installPlugin(new Ogre::GLPlugin());

	root->showConfigDialog();

	// initialise root
	root->initialise(false);

	XE::RenderWindow *renderWindow = root->createRenderWindow("Main",820,440,false);

	XE::XEngine engine;
	guiclass = new GUI(engine,renderWindow);
	root->addFrameListener(guiclass);
	// create main window
//	XE::RenderWindow *renderWindow2 = root->createRenderWindow("Main2",420,440,false);

	// create the scene
	XE::SceneManager *sceneMgr = root->createSceneManager(XE::ST_GENERIC, "MyFirstSceneManager");

	// The 'root SceneNode' is the only scenenode at the beginning in the SceneManager.
	// The SceneNodes can be seen as 'transformation' containers <=> it contains scale/position/rotation
	// of the objects. There is only 1 root scenenode, and all other scenenode are 
	// its direct or indirect children.
	XE::SceneNode* lRootSceneNode = sceneMgr->getRootSceneNode();

	//// add a camera
	Ogre::Camera *mCamera = sceneMgr->createCamera("MainCam");
	guiclass->setCamera(mCamera);

	Ogre::Camera *mCamera2 = sceneMgr->createCamera("MainCam2");
	// I attach the camera to a new SceneNode. It will be easier then to move it in the scene.
	XE::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("MyFirstCameraNode");
	lCameraNode->attachObject(mCamera);
	XE::SceneNode* lCameraNode2 = lRootSceneNode->createChildSceneNode("MyFirstCameraNode2");
	lCameraNode2->attachObject(mCamera2);

	XE::WindowHandle hWnd = 0;
	renderWindow->getCustomAttribute("WINDOW", &hWnd);

//	XE::WindowOSHandle hWnd2 = 0;
//	renderWindow2->getCustomAttribute("WINDOW", &hWnd2);

	 mCamera->setNearClipDistance(0.05f);
     mCamera->setFarClipDistance(1000);
 
	 mCamera2->setNearClipDistance(0.05f);
     mCamera2->setFarClipDistance(1000);

	renderWindow->setActive(true);
	renderWindow->setAutoUpdated(true);
//	renderWindow2->setActive(true);
//	renderWindow2->setAutoUpdated(false);
	root->clearEventTimes();

	XE::ResourceGroupManager* rgm = XE::ResourceGroupManager::getSingletonPtr();
  	rgm->addResourceLocation("D:/Projekte/Src Game/_Engine/XEngine/resources/XETUI", "FileSystem");
    rgm->addResourceLocation("D:/Projekte/Src Game/_Game/resource/UI", "FileSystem");
	rgm->addResourceLocation("D:/Projekte/Src Game/_Game/resource/UI", "FileSystem");
	
	// Initialise the resource groups:
	XE::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	float lViewportWidth = 1.0f;
	float lViewportHeight = 1.0f;
	float lViewportLeft	= (1.0f - lViewportWidth);
	float lViewportTop = (1.0f - lViewportHeight);
	unsigned short lMainViewportZOrder = 100;
	XE::Viewport * vp = renderWindow->addViewport(mCamera, lMainViewportZOrder, 0, 0, lViewportWidth, lViewportHeight);

	/*XE::Viewport * vp2 = renderWindow->addViewport(mCamera2, 200,0, 0, lViewportWidth, lViewportHeight);
	vp2->setBackgroundColour(XE::ColourValue(180./255, 115./255, 175./255, .5f));*/
 
//	XE::Viewport * vp2 = renderWindow2->addViewport(mCamera2);
//	vp2->setBackgroundColour(XE::ColourValue(180./255, 115./255, 175./255, .5f));
 
	guiclass->create(sceneMgr,vp);
	// I want the viewport to draw the scene automatically
	// when I will call lWindow->update();
	vp->setAutoUpdated(true);
	// I choose a color for this viewport. 
	// I prefer to have a bright color, to detect holes in geometry etc...
	vp->setBackgroundColour(XE::ColourValue(1,0,1));
//vp2->setBackgroundColour(XE::ColourValue(0,0,1));

	/*XE::Silverback*    mSilverback;
	XE::Screen*        mScreen;
	XE::Layer*         mLayer;

	XE::Polygon* poly;
	XE::LineList*       list;
	XE::Caption*        caption;
	XE::Rectangle*      rect;
	XE::QuadList*       quads;
	XE::MarkupText*     markup;*/
	
	

	// Create Silverback and load in dejavu
	//mSilverback = new XE::Silverback();
	//mSilverback->loadAtlas("dejavu.gorilla","General");
	//mScreen = mSilverback->createScreen(vp, "dejavu.gorilla");
	////  mScreen->setOrientation(XE::OR_DEGREE_270);
	//Float vpW = mScreen->getWidth(), vpH = mScreen->getHeight();

	// Create our drawing layer
	/*mLayer = mScreen->createLayer(0);
	rect = mLayer->createRectangle(0,0, vpW, vpH);
	rect->background_gradient(XE::Gradient_Diagonal, XE::rgb(98,0,63), XE::rgb(255,180,174));*/

	//markup = mLayer->createMarkupText(9,5,5, "%@24%A Haiku\n%@14%Written by Betajaen%@9%\nSo many to choose from\nPretty typefaces on Ogre screen\nTime to update Git");

	//caption = mLayer->createCaption(9, vpW - 55, 5, "9");
	//caption->width(50);
	//caption->align(XE::TextAlign_Right);

	//caption = mLayer->createCaption(14, vpW - 55, 18, "14");
	//caption->width(50);
	//caption->align(XE::TextAlign_Right);

	//caption = mLayer->createCaption(24, vpW - 55, 33, "24");
	//caption->width(50);
	//caption->align(XE::TextAlign_Right);

	//_---------------------------------
	
	//// Here I choose a name for a resource group. Then I create it.
	//// Often, a resourcegroup is a good way to store the data corresponding
	//// to a level in a game.
	//String lNameOfResourceGroup = "Mission 1 : Deliver Tom";
	//{
	//	XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();
	//	lRgMgr.createResourceGroup(lNameOfResourceGroup);
 //
	//	// We say which directories will be loaded by this resourcegroup.
	//	// I can add many directories, which will be loaded in same the ORDER.
	//	// This ORDER is extremely important : if a material is loaded <i>after</i> a mesh using this material,
	//	// this mesh won't be able to find the material during its loading!
	//	// I advise you not to use a recursive load (which load the full directory tree). 
	//	// Seriously, 'recursive loading' often leads to problems.
	////	String lDirectoryToLoad = "D:/Projekte/Src Game/_Engine/XEngine/resources";
	//	bool lIsRecursive = false;
	////	lRgMgr.addResourceLocation("$(ProjectDir)\..\..\..\..\resources\materials\textures", "FileSystem", lNameOfResourceGroup);
	////	lRgMgr.addResourceLocation("D:/Projekte/Src Game/_Engine/XEngine/resources/materials/programs", "FileSystem", lNameOfResourceGroup, lIsRecursive); //place for textures
	//	lRgMgr.addResourceLocation("D:/Projekte/Src Game/_Engine/XEngine/resources/XETScence/materials/textures", "FileSystem", lNameOfResourceGroup, lIsRecursive); //place for textures
	//	lRgMgr.addResourceLocation("D:/Projekte/Src Game/_Engine/XEngine/resources/XETScence/materials/scripts", "FileSystem", lNameOfResourceGroup, lIsRecursive);//place for .material files
	//	lRgMgr.addResourceLocation("D:/Projekte/Src Game/_Engine/XEngine/resources/XETScence/models", "FileSystem", lNameOfResourceGroup, lIsRecursive); //, lIsRecursive);
 //	
	//	// The function 'initialiseResourceGroup' parses scripts if any in the locations.
	//	lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
 //
	//	// Files that can be loaded are loaded.
	//	lRgMgr.loadResourceGroup(lNameOfResourceGroup);
 //	
	//	// Now the loaded Mesh is available from its ResourceGroup,
	//	// as well as from the Ogre::MeshManager. A shared pointer to
	//	// it can be accessed by : Ogre::MeshManager::getSingleton().getByName(name_of_the_mesh);
	////	lRgMgr.initialiseAllResourceGroups();
	//	

	//	int lNumberOfEntities = 1;
	//	/*for(int iter = 0; iter < lNumberOfEntities; ++iter)
	//	{*/
	//		XE::Entity* lEntity = sceneMgr->createEntity("EN_OgreHead","ogrehead.mesh",lNameOfResourceGroup);
	////		lEntity->setMaterialName("Ogre.material",lNameOfResourceGroup);
	//		
	//		// Now I attach it to a scenenode, so that it becomes present in the scene.
	//		XE::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
	//		lNode->attachObject(lEntity);
	//		// I move the SceneNode so that it is visible to the camera.
	//		//float lPositionOffset = float(1+ iter * 2) - (float(lNumberOfEntities));
	//	//	lPositionOffset = lPositionOffset * 20;
	//	//	lNode->translate(lPositionOffset, lPositionOffset, -200.0f);
	//		lNode->translate(0, -5,  -80.0f);
	//		// The loaded mesh will be white. This is normal.

	//		XE::Light *light = sceneMgr->createLight("MainLight");
	//		light->setPosition(20.0f, 90.0f, 50.0f);
	////	}
	//	
	//	//	XE::DataStreamPtr ds = lRgMgr.openResource("D:/Projekte/Src Game/_Engine/XEngine/resources/materials/scripts/Ogre.material", lNameOfResourceGroup, true);
	//	//XE::MaterialManager::getSingleton().parseScript(ds, lNameOfResourceGroup);

	//
	//	XE::ResourceManager::ResourceMapIterator materialIterator = XE::MaterialManager::getSingleton().getResourceIterator();
	//	while (materialIterator.hasMoreElements())
	//	{
	//		std::cout << "MaterialLoaded:" << (static_cast<XE::MaterialPtr>(materialIterator.peekNextValue()))->getName() << std::endl;
	//		materialIterator.moveNext();
	//	} 

	//}

	root->clearEventTimes();

	XE::Event event;
	while(!renderWindow->isClosed())
	{
		/*while (renderWindow->pollEvent(event))
		{	
			std::cout << "Event: type:" << event.type << "size.height:" << event.size.height << std::endl;
			switch (event.type) {

				 Cerrar ventana: salir
			case XE::Event::MouseMoved:

				std::cout << "Event: type:" << event.type << "x:" << event.mouseMove.x << ",y:" << event.mouseMove.y << std::endl;
				break;
			}
		}*/

		// Generate new actions (calls window.pollEvent(...))
		//map.update(renderWindow);
	
		//map.update(renderWindow2);

		// Check which actions are currently in effect, react correspondingly
		if (map.isActive(Run))
			std::cout << "Run!" << std::endl;
		if (map.isActive(Quit))
			return 0;

		// Forward actions to callbacks: Invokes onResize() in case of XE::Event::Resized events
		//map.invokeCallbacks(system, renderWindow);
		//	window.pushGLStates();
		//		//  window.draw(rectangle);
		////window.draw(text);
		//window.popGLStates();

		// Finally, display the rendered frame on screen
		// window.display();

		// Drawings
		// the window update its content.
		// each viewport that is 'autoupdated' will be redrawn now,
		// in order given by its z-order.
		renderWindow->update(false);
 	
	//	renderWindow2->update(false);
 
		// The drawn surface is then shown on the screen
		// (google "double buffering" if you want more details).
		// I always use vertical synchro.
		//bool lVerticalSynchro = true;
		renderWindow->swapBuffers();
 
	//	renderWindow2->swapBuffers(lVerticalSynchro);
 
		// This update some internal counters and listeners.
		// Each render surface (window/rtt/mrt) that is 'auto-updated' has got its 'update' function called.
		root->renderOneFrame();
 
		//	XE::WindowEventUtilities::messagePump(); //dont use it or .net wrapper crash!

		XE::sleep(XE::milliseconds(10));
	}
 
	// Let's cleanup!
	{
		renderWindow->removeAllViewports();
			
	//	renderWindow2->removeAllViewports();
	}
	{
		sceneMgr->destroyAllCameras();
		sceneMgr->destroyAllManualObjects();
		sceneMgr->destroyAllEntities();
		lRootSceneNode->removeAndDestroyAllChildren();
	}
	{
		XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();
		lRgMgr.destroyResourceGroup("General");
	}
}


 bool comboboxValueChanged(XE::PanelElement* e)
    {
		XE::Listbox* cb = (XE::Listbox*) e;
       // mUserVisitedCountry = cb->getValues();
       Ogre::String s("Visited country : ");
     /*   for (size_t i=0; i < mUserVisitedCountry.size(); i++)
        {
            s.append(mUserVisitedCountry[i].substr(0, 2));
            if (i != mUserVisitedCountry.size() - 1)
                s.append(",");
        }*/
      //  mVisitedCitySummary->text(s);
        return true;
    }
 
 void onUIReload(XE::ActionContext<MyAction> context)
{
	guiclass->OnReload();
 }

 void onMenuNav(MyAction move)
 {
	 switch(move)
	 {
	 case NavRight:

		 guiclass->makeNextItemOver();
		 std::cout << "onMenuNav (NavRight)" << std::endl;
		 break;
	 case NavLeft:
		  guiclass->makePrevItemOver();
		std::cout << "onMenuNav (NavLeft)" << std::endl;
		 break;
	 case NavUp:

		 //guiclass->makeNextItemOver();
		 std::cout << "onMenuNav (NavUP)" << std::endl;
		 break;
	 case NavDown:
		 //guiclass->makePrevItemOver();
		 std::cout << "onMenuNav (NavDown)" << std::endl;
		 break;
	 }
	 //	MyEvent( 5 );
 }

void onMouseMove(XE::ActionContext<MyAction> context)
{
	// The XE::Event member variable called type has always the value XE::Event::Resized, as specified in the XE::Action
	// constructor. Since the Resize action has been triggered by an XE::Event (and not by a XE::Keyboard, XE::Mouse or
	// XE::Joystick), we can also be sure that context.event is no null pointer.
	XE::Event event = *context.event;
	
	guiclass->setMouseMove(event);

	std::cout << "onMouseMove!    (" << event.mouseMove.x << ", " << event.mouseMove.y << ")" << std::endl;
}

 void onPointSelectStart(XE::ActionContext<MyAction> context)
{
	// The XE::Event member variable called type has always the value XE::Event::Resized, as specified in the XE::Action
	// constructor. Since the Resize action has been triggered by an XE::Event (and not by a XE::Keyboard, XE::Mouse or
	// XE::Joystick), we can also be sure that context.event is no null pointer.
	XE::Event event = *context.event;
	
	guiclass->setPointSelectStart(event);

	std::cout << "onPointSelectStart!    (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
}

void onPointSelectEnd(XE::ActionContext<MyAction> context)
{
	// The XE::Event member variable called type has always the value XE::Event::Resized, as specified in the XE::Action
	// constructor. Since the Resize action has been triggered by an XE::Event (and not by a XE::Keyboard, XE::Mouse or
	// XE::Joystick), we can also be sure that context.event is no null pointer.
	XE::Event event = *context.event;
	
	guiclass->setPointSelectEnd(event);

	std::cout << "onPointSelectEnd!    (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
}


//void onResize(XE::ActionContext<MyAction> context)
//{
//	// The XE::Event member variable called type has always the value XE::Event::Resized, as specified in the XE::Action
//	// constructor. Since the Resize action has been triggered by an XE::Event (and not by a XE::Keyboard, XE::Mouse or
//	// XE::Joystick), we can also be sure that context.event is no null pointer.
//	XE::Event event = *context.event;
//	std::cout << "Resized!   New size = (" << event.size.width << ", " << event.size.height << ")" << std::endl;
//}
//
//void onShoot(XE::ActionContext<MyAction> context)
//{
//	XE::WindowOSHandle hWnd = 0;
//	context.window->getCustomAttribute("WINDOW", &hWnd);
//
//	// context.Window is a pointer to the XE::Window passed to the XE::ActionMap constructor. It can
//	// be used for mouse input relative to a window, as follows:
//	XE::Vector2i mousePosition = XE::Mouse::getPosition(hWnd);
//	std::cout << "Shoot: " << mousePosition << std::endl;
//}