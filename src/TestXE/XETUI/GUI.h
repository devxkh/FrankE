#include <XEngine.hpp>

#include "UIState_1.h"
#include "UIState_2.h"
//#include < "MenuStates/UIStateManager.hpp"

//#include "DemoPanelColors.h"
//
//#include <XEUI/Panel2D.hpp>
////#include <XEUI/UIPrerequisites.hpp>
//#include <XEUI/Widgets/UIItemBar.hpp>
//#include <XEUI/Widgets/UIItemBox.hpp>
////#include <XEUI/UIScreen.hpp>
//
//#include <XEUI/Widgets/Menu.hpp>
//#include <XEUI/Widgets/MIButton.hpp>

//
//#include <XEMath/Vectors/Vector2.hpp>
//#include <XEGraphics/Gorilla.h>
//
//#include <XEUI/PanelElement.hpp>
//#include <XEUI/Widgets/UIComboBox.hpp>

class MyLinkedPanel : public XE::Panel3D
{
public:
	//
	MyLinkedPanel(XE::UIManager* gui,
		Ogre::SceneManager* sceneMgr,
		const XE::Vector3f& position,
		const XE::Vector2f& size,
		Ogre::String atlasName,
		Ogre::String name)
		: XE::Panel3D(gui, sceneMgr, 10, atlasName, name),
		next(nullptr), previous(nullptr)
	{}

	~MyLinkedPanel()
	{}

	// Link the panels
	MyLinkedPanel* next;
	MyLinkedPanel* previous;
};


//#include "MenuStates/MS_Controller.hpp"
class GUI : public XE::FrameListener, public XE::WindowEventListener
{

public:

	GUI(XE::XEngine& engine, XE::RenderWindow *renderWindow) : mXEUI() //, mUIStateMgr(engine)
	{
		XE::WindowEventUtilities::addWindowEventListener(renderWindow, this);	
	}

	
	bool onSelectExit(XE::PanelElement* e)
	{

		std::cout << "onExit" << std::endl;
		return true;
	}

	bool onContinue( XE::PanelElement* e )
	{
		std::cout << "onContinue" << std::endl;
		return true;
	}
	
	bool onAddController( XE::PanelElement* e )
	{
		std::cout << "onAddController" << std::endl;


		return true;
	}	
	
	bool onDeviceSelected( XE::PanelElement* e )
	{
		std::cout << "onDeviceSelected" << std::endl;
		return true;
	}

	bool onRemoveController( XE::PanelElement* e )
	{
		std::cout << "onRemoveController" << std::endl;

		mCtrlDevicePanel->_destroy = true;

		return true;
	}

	bool makeNextItemOver()
	{
		return navi->makeNextItemOver();
	}

	bool makePrevItemOver()
	{
		return navi->makePrevItemOver();
	}

	bool onControllerSelected( XE::PanelElement* e )
	{
		XE::Menu* menu = static_cast<XE::Menu*>(e);

	//	if(menu->getID() == 0)
	//	{
			//Menu(Uint32 id, Float x,  Float y,   size_t width,   size_t height, unsigned int nbDisplayedElements, PanelContainer* parentContainer);
			//Uint32 id, Uint16 idx,   const String text, Menu* owner
			//ScreenPanel(UIManager* gui,  Screen* screen,  const String& atlasName,  const String& name, const Uint16& grp = 0);
		{
		XE::UISerializer serializer( &mXEUI, &mUIStateMgr );

		serializer.addCallback("onRemoveController", this, &GUI::onRemoveController);
		serializer.addCallback("onDeviceSelected", this, &GUI::onDeviceSelected);
				
		serializer.setScreen( mXEUI.getScreen("WorldState") );	
		
		mCtrlDevicePanel = serializer.loadPanel2D("panelCtrlDevice", "General");

		Ogre::Vector3 submenuPos = menu->getSubMenuPosition();
		mCtrlDevicePanel->setPosition( submenuPos );

		XE::Menu* subMenu = static_cast<XE::Menu*>(mCtrlDevicePanel->getItem("menuCtrlDevice"));
		subMenu->setPosition( submenuPos.x, submenuPos.y );
					XE::MIButton* device1 = OGRE_NEW XE::MIButton("",0,"GamePad1",subMenu);
			subMenu->addItem(device1);
			XE::MIButton* device2 = OGRE_NEW XE::MIButton("", 1, "Joy 1", subMenu);
			subMenu->addItem(device2);
			XE::MIButton* device3 = OGRE_NEW XE::MIButton("", 2, "Keyboard/Mouse", subMenu);
			subMenu->addItem(device3);
			XE::MIButton* device4 = OGRE_NEW XE::MIButton("", 3, "GamePad2", subMenu);
			subMenu->addItem(device4);
		//	XE::MIButton* miRemoveDevice = XE_NEW XE::MIButton("",3,"Remove",subMenu);
		//	subMenu->addItem(miRemoveDevice);
		}
		//-----------------------------------------


			//XE::Vector3f submenuPos =  menu->getSubMenuPosition();
			//Float x = submenuPos.x; //wieso kann ich &vector nicht direkt übergeben?
			//Float y = submenuPos.y;

			//XE::ScreenPanel* subContainer = new XE::ScreenPanel(&mXEUI, mXEUI.getScreen("WorldState"),"completeGUIDemo.gorilla","DevicePanel");
			//XE::ElementStyle* style = subContainer->getStyle( XE::S_Panel2D );

			//mXEUI.addUIPanel(subContainer);
			//style->width = 200;
			//style->height = 300;

			//style->align.unitvert = XE::Unit_AlignCenter; 
			//style->align.unithorz = XE::Unit_AlignCenter;

			//subContainer->setStyle( style );

			//subContainer->setPosition( submenuPos );

			//XE::Menu* subMenu = subContainer->makeMenu( 1,0,0,200,500,5);



			//miRemoveDevice->setPressedCallback(this, &GonRemoveController);
			//menu->setValueChangedCallback(this, &GonDeviceSelected);
	//	}

		std::cout << "onControllerSelected:" << menu->getValue() << std::endl;
		return true;
	}

	bool onItemChanged( XE::PanelElement* e )
	{
		XE::Navigation* nav = static_cast<XE::Navigation*>(e);

		XE::NavItem* niSelected = nav->getSelectedItem();
		Ogre::String navItemName = niSelected->getName();

		XE::UIStateManager& uiSM = mUIStateMgr;

		if(navItemName == "NI_controller")
			mUIStateMgr.stepTo( 0, mUIStateMgr.build < XG::UI::UIInitGame>( 1, nullptr, true ) );
		//else if(nav->getValue() == "3") mController->stepTo ( PN_controls );
		else if(navItemName == "NI_settings")
		{
			//mController->stepTo ( PN_settings );	
			
			mUIStateMgr.stepTo(0, mUIStateMgr.build < XG::UI::UISetting>(5, nullptr, true));

		}
		//else if(nav->getValue() == "5") mController->stepTo ( PN_games );		
		//else if(nav->getValue() == "6") mController->stepTo ( PN_team );	
		//else if(nav->getValue() == "7") mController->stepTo ( PN_character );	
		//else if(nav->getValue() == "8") mController->stepTo ( PN_scene );
		//else if(nav->getValue() == "9") mController->stepTo ( PN_gameStart );
		//else
		//{
		//	//Fehler
		//}

		
		
		//if(nav->getValue() == "0")
		//{
		//	XE::UISerializer serializer( &mXEUI );

		//	serializer.addCallback("onSelectChar",this, &GonSelectChar);
		//	serializer.addCallback("onSelectExit",this, &GonSelectExit);
		//	serializer.addCallback("onItemChanged",this, &GonItemChanged);

		//	serializer.setScreen( mXEUI.getScreen( "WorldState" ) );
		//	//mXEUI.getNav()->setActualPanel( serializer, "menuStart", "General");

		////XE::NavItem* navItem = new XE::NavItem(2,1,"blub", mXEUI.getNav()->getPanelContainer());
		//
		//	//mXEUI.getNav()->addItem(navItem);
		//	serializer.addCallback("onItemChanged",this, &GonItemChanged);

		//	/*XE::Menu* menuController = mXEUI.getUIPanel("panelController")->getElement("menuController");
		//	XE::MenuItem* menuItem = menuController->addItem(2,0,"Controller 2", mXEUI.getNav()->getPanelContainer());
		//	XE::MenuItem* menuItem = menuController->addItem(3,1,"Controller 3", mXEUI.getNav()->getPanelContainer());
		//	XE::MenuItem* menuItem = menuController->addItem(4,2,"Controller 4", mXEUI.getNav()->getPanelContainer());*/
		//}

		std::cout << "onItemChanged:" << nav->getTabIdx() << std::endl;
		return true;
	}

	bool onSelectChar( XE::PanelElement* e )
	{
		std::cout << "onSelectChar" << std::endl;

		XE::UISerializer serializer( &mXEUI, &mUIStateMgr );

		serializer.addCallback("onContinue", this, &GUI::onContinue);
		serializer.addCallback("onSelectExit", this, &GUI::onSelectExit);
			
		serializer.setScreen( mXEUI.getScreen( "WorldState" ) );
//		mXEUI.getNav()->stepTo( serializer, "menuChar", "General" );
	


	//	callnextPanelThread();
		//Kann erst gelöscht werden wenn funktzion fertig da callback in pressend aufgerufen wird... sonst objekt gelöscht bevor fertig!
		//mXEUI.destroyUIPanel("mainPanel");

		return true;
	}

	void windowResized(XE::RenderWindow* rw)
	{
		mXEUI.windowResized(rw);
	}
	
	void create(XE::SceneManager* sceneMgr, XE::Viewport* vp)
	{
		mViewPort = vp;


		//MenuState starting
		//mUIStateMgr.run( mUIStateMgr.build<XG::MS_Controller>( true ) );

		//if(mUIStateMgr.running())
		//{
		//	//update menustate
		//	mUIStateMgr.update();
		//}

		////quit menustate
		//mUIStateMgr.quit();
		XE::MemoryTracker::get().setReportToStdOut( true);

		XE::uint16 test =	XE::MemoryTracker::get().getTotalMemoryAllocated();
		std::cout << "Memory used:" << test << std::endl; 
		{
			//--------------------------------------------
			XE::UISerializer serializer(&mXEUI, &mUIStateMgr);

			serializer.addCallback("onSelectChar", this, &GUI::onSelectChar);
			serializer.addCallback("onSelectExit", this, &GUI::onSelectExit);
			serializer.addCallback("onItemChanged", this, &GUI::onItemChanged); //Navigation selection Changed

			mUIScreen = serializer.loadScreenTheme(vp,"screenTheme.xml" , "General");
			serializer.loadScreenElements("screenInit.xml" , "General");
			
			//
			if(navi = dynamic_cast<XE::Navigation*>(mXEUI.getUIPanel("navPanel")->getItem("navMain")))
			{
				XE::NavItem* navItem = navi->addItem("",2,"Controller");
				navi->addItem("",3,"Controls");
				navi->addItem("",4,"Settings");
				navi->addItem("",5,"Game");
				navi->addItem("",6,"Team")->_enabled = false;
				navi->addItem("",7,"Character")->_enabled = false;
				navi->addItem("",8,"Scene")->_enabled = false;
				navi->addItem("",9,"Play")->_enabled = false;

				//	mController->stepTo( PN_controller );
			}

			XE::uint16 id = 5;
		//	XE::UIStateController* controller;
			bool replace ;

			//	mUIStateMgr.build <XG::UIInitGame>( id, controller,replace );

			//mUIStateMgr.stepTo( 0, mUIStateMgr.build <XG::UIInitGame>( id, controller,replace ) );
			//		
			//		//-------------------------------- TEST ------------------
			//		//serializer.addCallback("onSelectExit",this, &GonSelectExit);
			//		serializer.addCallback("onAddController",this, &GonAddController);
			//serializer.addCallback("onControllerSelected",this, &GonControllerSelected);
			////		serializer.addCallback("onItemChanged",this, &UIController::onNavItemChanged); //Navigation selection Changed
			//				
			//		serializer.setScreen(mUIScreen);
		//	mUIPanel = serializer.loadPanel2D("panelController", "General");
			//	serializer.loadPanel2D("panelController", "General");
		}

		//	mXEUI.destroyScreen("WorldState");
		//	mXEUI.destroyStyles();

		
		Ogre::MemoryTracker::get().setReportToStdOut( true);
		test = Ogre::MemoryTracker::get().getTotalMemoryAllocated();
		std::cout << "Memory used after:" << test << std::endl; 

		//Controller List
	/*	XE::Menu* menuCtrl = static_cast<XE::Menu*>(mUIPanel->getItem("menuController"));

		XE::MIButton* miFoundDevice = XE_NEW XE::MIButton( "Menuitem", 0, "P1", menuCtrl);
		miFoundDevice->setImage("inlineselectorNextButtonNotOvered", XE::Vector2f( 30,30));
		menuCtrl->addItem(miFoundDevice);

		XE::MIButton* miFoundDevice2 = XE_NEW XE::MIButton( "Menuitem2", 0, "P2", menuCtrl);
		miFoundDevice2->setImage("inlineselectorPreviousButtonNotOvered", XE::Vector2f( 30,30));
		menuCtrl->addItem(miFoundDevice2);*/
		//--------------------------------------------------
		//		mXEUI.getNav()->stepTo( serializer, "menuStart", "General");

		/*XE::NavItem* navItem = mXEUI.getNav()->addItem(2,2,"Controller", mXEUI.getNav()->getPanelContainer());
		mXEUI.getNav()->addItem(3,3,"Controls", mXEUI.getNav()->getPanelContainer())->_enabled = false;
		mXEUI.getNav()->addItem(4,4,"Settings", mXEUI.getNav()->getPanelContainer())->_enabled = true;
		mXEUI.getNav()->addItem(5,5,"Game", mXEUI.getNav()->getPanelContainer())->_enabled = false;
		mXEUI.getNav()->addItem(6,6,"Team", mXEUI.getNav()->getPanelContainer())->_enabled = false;
		mXEUI.getNav()->addItem(7,7,"Character", mXEUI.getNav()->getPanelContainer())->_enabled = false;
		mXEUI.getNav()->addItem(8,8,"Scene", mXEUI.getNav()->getPanelContainer())->_enabled = false;
		mXEUI.getNav()->addItem(9,9,"Play", mXEUI.getNav()->getPanelContainer())->_enabled = false;*/

		//		serializer.loadPanel2D();
		//	serializer.loadPanel3D();
		//--------------------------------------------

		//	mXEUI.loadAtlas("world.gorilla");

		/*MyLinkedPanel* panel = new MyLinkedPanel(
		&mXEUI, sceneMgr, XE::Vector2f(400, 340), "completeGUIDemo.gorilla", "panelResolution");*/

		//-------------- 3D --------------------------
		//mPanel = new XE::Panel(
		//&mXEUI, sceneMgr, XE::Vector2f(400, 340),10, "completeGUIDemo.gorilla", "panelResolution");
		//// nur bei 3D !!! 
		//	 mPanel->mNode->setPosition(0, 0, -5);
		//-----------------------------------------
		//-------------- 2D
		/* XE::ScreenPanel* mPanel = new XE::ScreenPanel(
		&mXEUI, mXEUI.getScreen("WorldState"), 
		XE::Vector2f(400, 240),
		XE::Vector2f(300, 300),
		"completeGUIDemo.gorilla", 
		"panelResolution");*/
		/*
		mPanel->makeCaption(0, 5, -30, 390, 30, "Resolution Panel");

		XE::Menu* menuTest = mPanel->makeMenu(2, 10, 10, 280, 280, 4);

		XE::MIButton* ControllerMenuBtn = new XE::MIButton(10,0,mPanel);
		ControllerMenuBtn->setPressedCallback(this, &GmenuControllerPCallback);

		String test = "haha";
		ControllerMenuBtn->setPressedCallback(this, &GmenuControllerPCallback);

		menuTest->addItem(ControllerMenuBtn);
		menuTest->addItem(new XE::MIButton(11,1,mPanel));

		menuTest->setValueChangedCallback(this, &GmenuChangedCallback);*/


		/*panel->makeCaption(1, 5, 10, 390, 30, "Choose your prefered resolution", XE::TextAlign_Centre);

		std::vector<String> mAvailableResolutions;

		mAvailableResolutions.push_back("800x600 16bits");
		mAvailableResolutions.push_back("1024x700 16bits");
		mAvailableResolutions.push_back("1366x700 16bits");
		mAvailableResolutions.push_back("1600x900 16bits");
		mAvailableResolutions.push_back("800x600 32bits");
		mAvailableResolutions.push_back("1024x700 32bits");

		XE::Combobox* comboboxResolution = 
		panel->makeCombobox(2, 0, 15, 300, 210, mAvailableResolutions, 4);
		comboboxResolution->setValueChangedCallback(this, &GresolutionChangedCallback);
		comboboxResolution->setCurrentValue(mAvailableResolutions[2]);*/

		/* panel->makeButton(10, 300, 180, 30, "Back")
		->setPressedCallback(this, &DemoLinkedPanels::goPreviousPanel);
		panel->makeButton(200, 300, 180, 30, "Next")
		->setPressedCallback(this, &DemoLinkedPanels::goNextPanel);*/

		//Style
		//mNormalizedMousePosition = XE::Vector2f(0.5, 0.5);
		//mMousePointerLayer = mGui3D->getScreen("mainScreen")->createLayer();
		//mMousePointer = mMousePointerLayer->createRectangle(
		//	vp->getActualWidth() / 2, 
		//	vp->getActualHeight() / 2 , 
		//	12,
		//	18);
		//mMousePointer->background_image("mousepointer");

		//XE::Panel* panel = new XE::Panel(
		//	mGui3D, sceneMgr, XE::Vector2f(400, 600), 10, "completeGUIDemo.gorilla", "test_panel");

		//	XE::Button* btn = panel->makeButton(100,100,200,50,"haha");
		//  btn->setActive(true);

		//#### mGui3D->createScreen(vp2, "simpleDemo.gorilla", "mainScreen2");

		//####  XE::Panel* panel2 = new XE::Panel(
		//####	  mGui3D, sceneMgr, XE::Vector2f(400, 600), 10, "simpleDemo.gorilla", "test_panel");

		// panel->makeButton(100,100,200,50,"haha");
		//------panel->makeCaption(5, -30, 390, 30, "Simple Demo Panel");

		/*mPanel = panel;
		mPanel->mNode->setPosition(0, 0, -8);*/



		//Main ItemBar
		//--------------------------------------------
		//m_pItemBar = new XE::ItemBar(mGui3D,XE::Vector2f(0, mScreen->getHeight() - 300)); 
		//		
		////Event wenn Menu auswahl fertig und zum nächsten Schritt
		//m_pItemBar->GetSignal( XE::ItemBar::OnContinue ).Connect( &GOnContinue, this );
		//m_pItemBar->GetSignal( XE::ItemBar::OnBack ).Connect( &GOnBack, this );
		//m_pItemBar->GetSignal( XE::ItemBar::OnExit ).Connect( &GOnExit, this );
		//m_pItemBar->GetSignal( XE::ItemBar::OnClose ).Connect( &GOnClose, this );
		//m_pItemBar->GetSignal( XE::AddItem ).Connect( &GOnAddItem, this ); //innerhalb itembox handeln!
		//	m_pItemBar->GetSignal( XE::RemoveController ).Connect( &GOnRemoveController, this );
		//	m_pItemBar->GetSignal( XE::ChangeEvent ).Connect( &GOnChangeEvent, this ); //innerhalb itembox handeln!

		//
		//subobx von main itembar mit SubItemBar
		//XE::ItemBox* iBoxSub = new XE::ItemBox(mGui3D,  XE::ITEM_ID::BALL, "Exit", "item_ball", "item_ball_hover");
		//iBoxSub->GetSignal( XE::ItemBox::OnTriggered ).Connect( &GOnExit, this );
		//	//	iBoxSub->connect(&onClickItemBoxSub);

		////Itemboxes für Main Itembar
		//m_pItemBar->addItem(iBoxSub);

		//XE::ItemBox* iBoxSubNext = new XE::ItemBox(mGui3D,  XE::ITEM_ID::SMALLBALL, "Weiter", "item_smallball", "item_smallball_hover");
		//iBoxSubNext->GetSignal( XE::ItemBox::OnTriggered ).Connect( &GOnNext, this );
		//m_pItemBar->addItem(iBoxSubNext);

		//XE::ItemBox* iBoxSubController1 = new XE::ItemBox(mGui3D,  XE::ITEM_ID::SMALLBALL, "Controller 1", "item_smallball", "item_smallball_hover");
		//iBoxSubController1->GetSignal( XE::ItemBox::OnTriggered ).Connect( &GOnController, this );
		//m_pItemBar->addItem(iBoxSubController1);

		//XE::ItemBox* iBoxSubAddController = new XE::ItemBox(mGui3D,  XE::ITEM_ID::UNKNOWN, "Add Controller", "item_unknown", "item_unknown_hover");
		//iBoxSubAddController->GetSignal( XE::ItemBox::OnTriggered ).Connect( &GOnAddController, this );
		//m_pItemBar->addItem(iBoxSubAddController);

		//Where BALL is the ITEM_ID, 25 is its capacity, and "item_ball" and "item_ball_hover" are the images for the two states.
		//	m_pItemBar->addItem(new XE::ItemBox(mGui3D, XE::ITEM_ID::BALL, 25, "item_ball", "item_ball_hover"));

		//MyLinkedPanel* panel = (this->*(panels[i].createMethod))();
		//          panel->mNode->setPosition(panels[i].position);
		//          panel->mNode->yaw(panels[i].rotation);
		//          panel->previous = lastCreatedPanel;
		//          // Next will be set on next loop
		//          panel->next = nullptr;

		//          // First panel created ? Setup things
		//          if (lastCreatedPanel == nullptr)
		//          {
		//              mCameraNode->setPosition(panel->mPanelCameraNode->_getDerivedPosition());

		// This will be the actual panel
		//   mActualPanel-> = mPanel;
		//}
		//else
		//{
		//    panel->getGUILayer()->hide();
		//    // Chain it with previous panels
		//    lastCreatedPanel->next = panel;
		//}

		//lastCreatedPanel = panel;

		//####  mPanel2 = panel2;
		//####  mPanel2->mNode->setPosition(0, 0, -8);

		//_------------------------------------
	}

	void OnReload() 
	{	
		//mXEUI.destroyScreen(mUIScreen);
	//	mXEUI.destroyUIPanel("mainPanel");

		std::cout << "OnReload" << std::endl; 

		XE::UISerializer serializer(&mXEUI, &mUIStateMgr );
		
		serializer.addCallback("onSelectChar", this, &GUI::onSelectChar);
		serializer.addCallback("onSelectExit", this, &GUI::onSelectExit);

		serializer.loadScreenTheme(mViewPort,"mainScreenTheme.xml" , "General");
		serializer.loadScreenElements("mainScreenElements.xml" , "General");
//		serializer.loadPanel2D();
		serializer.loadPanel3D();

	}

	void OnController() 
	{	
		std::cout << "OnAddController" << std::endl; 

		//Sub ItemBar
		/*XE::ItemBar* m_pItemBarSub = new XE::ItemBar(mGui3D,XE::Vector2f(0, mScreen->getHeight() - 600)); 

		m_pItemBarSub->addItem(new XE::ItemBox(mGui3D,  XE::ITEM_ID::SMALLBALL, "Keyboard/Mouse", "item_smallball", "item_smallball_hover"));
		m_pItemBarSub->addItem(new XE::ItemBox(mGui3D,  XE::ITEM_ID::SMALLBALL, "Joustick 1", "item_smallball", "item_smallball_hover"));
		m_pItemBarSub->addItem(new XE::ItemBox(mGui3D,  XE::ITEM_ID::SMALLBALL, "Gamepad 1", "item_smallball", "item_smallball_hover"));*/

	}

	void OnNext() 
	{	
		std::cout << "OnNext" << std::endl; 

		//	delete m_pItemBar;

	}

	void OnAddController() 
	{	
		std::cout << "OnAddController" << std::endl; 

		//	m_pItemBar->addItem(new XE::ItemBox(mGui3D,  XE::ITEM_ID::UNKNOWN, "Neuer Controller", "item_unknown", "item_unknown_hover"));

	}

	void OnContinue() {	
		std::cout << "OnContinue" << std::endl; 

		//	m_pItemBar->addItem(new XE::ItemBox(mGui3D,  XE::ITEM_ID::UNKNOWN, -1, "item_unknown", "item_unknown_hover"));

	}
	void OnBack() {	
		std::cout << "OnBack" << std::endl;  
	}
	void OnExit() {	
		std::cout << "OnExit" << std::endl;  
	}
	void OnClose() {	
		std::cout << "OnClose" << std::endl;  
	}



	/*void onClickItemBoxSub(XE::ItemBox* parent)
	{

		std::cout << "onClickItemBoxSub" << std::endl;
	}*/

	// Calculate and normalize the distance between the middle of the screen
	// and the mouse on both X and Y axis.
	// This is used for the smooth movement of the camera
	// when the mouse is moving.
	XE::Vector2f getScreenCenterMouseDistance()
	{
		double posX = (mMousePointer->position().x - vp1->getActualWidth())
			/ vp1->getActualWidth();
		double posY = (mMousePointer->position().y - vp1->getActualHeight())
			/ vp1->getActualHeight();

		return XE::Vector2f(posX + 0.5, posY + 0.5);
	}

	void setMouseMove(XE::Event& event)
	{
		XE::Vector2f point;
		point.x = event.mouseMove.x;
		point.y = event.mouseMove.y;

		//###m_pItemBar->mouseMoved(point.x,point.y);
			// Set the new camera smooth direction movement
		/*	XE::Vector2f distance(getScreenCenterMouseDistance());
			mCamera->setDirection(cameraDirection
				+ XE::Vector3f(distance.x, -distance.y, 0) / 30);*/

		/*	float xMove = static_cast<float>(event.mouseButton.x);
		float yMove = static_cast<float>(event.mouseButton.y);*/

			/*mNormalizedMousePosition.x += point.x / vp1->getActualWidth();
			mNormalizedMousePosition.y += point.y / vp1->getActualHeight();*/

			// Make sur the mouse isn't out of the screen
			/*mNormalizedMousePosition.x = std::min<Float>(
				std::max<Float>(mNormalizedMousePosition.x, 0), 1);
			mNormalizedMousePosition.y = std::min<Float>(
				std::max<Float>(mNormalizedMousePosition.y, 0), 1);
*/
			// Mouse position on the screen
			/*mMousePointer->position(
				mNormalizedMousePosition.x * vp1->getActualWidth(),
				mNormalizedMousePosition.y * vp1->getActualHeight());*/

		//	// Ray for the actual panel to know where the mouse is
//-----------------------------------
		mXEUI.injectMouseMoved(point.x,
				point.y);
//		mPanel->injectMouseMoved(point.x,
//				point.y);
//---------------------------------------------
		/*mPanel->injectMouseMoved(
				mCamera->getCameraToViewportRay(
				mNormalizedMousePosition.x, mNormalizedMousePosition.y));*/


	}

	void setCamera(Ogre::Camera* camera)
	{
		mCamera = camera;
	}

	void setPointSelectStart(XE::Event& event)
	{
		Ogre::Vector2 point;
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;

		//	m_pItemBar->mouseDown(point.x,point.y);
	//	mPanel->pointSelectStart(point);
		mXEUI.pointSelectStart(point);
	}

	void setPointSelectEnd(XE::Event& event)
	{
		Ogre::Vector2 point;
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;

		//m_pItemBar->mouseUp(point.x,point.y);
	//	mXEUI.pointSelectEnd(point);
 		mXEUI.pointSelectEnd(point);
	}

	bool countryVisitedChangedCallback(XE::PanelElement* e)
	{
		XE::Listbox* cb = (XE::Listbox*) e;
		//    mUserVisitedCountry = cb->getValues();
		//   String s("Visited country : ");
		/*    for (size_t i=0; i < mUserVisitedCountry.size(); i++)
		{
		s.append(mUserVisitedCountry[i].substr(0, 2));
		if (i != mUserVisitedCountry.size() - 1)
		s.append(",");
		}*/
		//  mVisitedCitySummary->text(s);
		return true;
	}

	/* Ogre::FrameListener */
	//	virtual bool frameStarted(const FrameEvent& evt);
	//virtual bool frameEnded(const FrameEvent& evt);

	virtual bool frameRenderingQueued(const XE::FrameEvent& evt)
	{
		//nur bei textbox benötigt
		//####	mPanel->injectTime(evt.timeSinceLastFrame);
		//####mPanel2->injectTime(evt.timeSinceLastFrame);
		mXEUI.frameRenderingQueued(evt);
		return true;//SdkSample::frameRenderingQueued(evt);
	}

	/* Ogre::WindowEventListener */
	//void windowResized(XE::RenderWindow* win);
	//void windowClosed(XE::RenderWindow* win);

private:
			XE::Navigation* navi;
	XE::UIPanel* mUIPanel;
		
	XE::ScreenPanel* mCtrlDevicePanel;

	XE::UIStateManager mUIStateMgr;//GUI StateManager
	XE::UIManager mXEUI;
	XE::Screen* mUIScreen;
	//XE::XEUI* mGui3D;

	// The panel that is actually focused
	MyLinkedPanel* mActualPanel;
	XE::ItemBar* m_pItemBar;

	Ogre::Camera* mCamera;
	// Base Direction for the camera
	Ogre::Vector3 cameraDirection;

	XE::Vector2f mNormalizedMousePosition;

	std::vector<Ogre::String> mUserVisitedCountry;
	XE::Viewport* vp1;

	XE::Viewport* mViewPort;
//	XE::Panel* mPanel;

//	XE::ScreenPanel* mPanel;


	XE::Layer* mMousePointerLayer;
	XE::Rectangle* mMousePointer;
//	MySimpleDemoPanelColors mMySimpleDemoPanelColors;

	//XE::Panel* mPanel2;
	XE::Layer* mMousePointerLayer2;
	XE::Rectangle* mMousePointer2;
};