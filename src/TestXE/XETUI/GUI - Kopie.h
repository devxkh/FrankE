#include <XEngine.hpp>

#include <XEUI/XEUI.hpp>

#include "DemoPanelColors.h"
#include <XEUI/XEUIPanel.hpp>
#include <XEUI/UIPrerequisites.hpp>
#include <XEUI/Widgets/UIItemBar.hpp>
#include <XEUI/Widgets/UIItemBox.hpp>

#include <XEUI/UISerializer.hpp>

class MyLinkedPanel : public XE::UI::Panel
{
public:
	//
	MyLinkedPanel(XE::UI::XEUI* gui, 
		XE::SM::SceneManager* sceneMgr, 
		const XE::Math::Vector2f& size,
		XE::SYS::String atlasName,
		XE::SYS::String name)
		: XE::UI::Panel(gui, sceneMgr, size, 10, atlasName, name), 
		next(nullptr), previous(nullptr)
	{}

	~MyLinkedPanel()
	{}

	// Link the panels
	MyLinkedPanel* next;
	MyLinkedPanel* previous;
};

class GUI : public XE::SYS::FrameListener, public XE::IPT::WindowEventListener
{
public:

	void create(XE::SM::SceneManager* sceneMgr, XE::RS::Viewport* vp)
	{

		// The main panel
		vp1 = vp;

		mGui3D = new XE::UI::XEUI(&mMySimpleDemoPanelColors);
		mScreen = mGui3D->createScreen(vp, "world.gorilla", "WorldState");

		//mNormalizedMousePosition = XE::Math::Vector2f(0.5, 0.5);
		//mMousePointerLayer = mGui3D->getScreen("mainScreen")->createLayer();
		//mMousePointer = mMousePointerLayer->createRectangle(
		//	vp->getActualWidth() / 2, 
		//	vp->getActualHeight() / 2 , 
		//	12,
		//	18);
		//mMousePointer->background_image("mousepointer");

		//XE::UI::Panel* panel = new XE::UI::Panel(
		//	mGui3D, sceneMgr, XE::Math::Vector2f(400, 600), 10, "completeGUIDemo.gorilla", "test_panel");

	//	XE::UI::Button* btn = panel->makeButton(100,100,200,50,"haha");
		//  btn->setActive(true);



		//#### mGui3D->createScreen(vp2, "simpleDemo.gorilla", "mainScreen2");

		//####  XE::UI::Panel* panel2 = new XE::UI::Panel(
		//####	  mGui3D, sceneMgr, XE::Math::Vector2f(400, 600), 10, "simpleDemo.gorilla", "test_panel");

		// panel->makeButton(100,100,200,50,"haha");
		//------panel->makeCaption(5, -30, 390, 30, "Simple Demo Panel");

		//panel->makeButton(100, 10, 200, 30, "click me!")->setPressedCallback(this, &SimpleDemo::buttonPressed);
		// panel->makeCaption(10, 60, 100, 30, "check it ! ");
		// panel->makeCheckbox(110, 60, 30, 30)->setSelecteStateChangedCallback(this, &SimpleDemo::checkboxChecked);

		//std::vector<XE::SYS::String> mCountry;
		//mCountry.push_back("Canada");
		//mCountry.push_back("England");
		//mCountry.push_back("Europe");
		//mCountry.push_back("France");
		//mCountry.push_back("USA");
		//mCountry.push_back("Mexico");
		//mCountry.push_back("South America");
		//mCountry.push_back("Others");

		//// The user has already visited some country..
		//mUserVisitedCountry.push_back(mCountry[0]);
		//mUserVisitedCountry.push_back(mCountry[1]);
		//mUserVisitedCountry.push_back(mCountry[5]);

		//XE::UI::Listbox* listBox = panel->makeListbox(50, 60, 300, 210, mCountry, 4);//->setValueChangedCallback(&comboboxValueChanged);
		//listBox->getRectangleDesign()->background_colour(XE::XE_G::rgb(255, 0, 0));

		//listBox->setValueChangedCallback(this, &GUI::countryVisitedChangedCallback);
		//listBox->setCurrentValues(mUserVisitedCountry);

		//listBox->setPosition(50,0);
		//listBox->setSize(350, 100);
		//listBox->setPosition(150,0);
		//  captionButton = panel->makeCaption(10, 250, 380, 30, "The button hasn't been clicked yet");
		//  captionChecked = panel->makeCaption(10, 300, 380, 30, "The checkbox hasn't been checked");
		//  captionCombobox = panel->makeCaption(10, 350, 380, 30, "No selected values yet");
		//  
		/*mPanel = panel;
		mPanel->mNode->setPosition(0, 0, -8);*/


		XE::UI::ElementMap elementMap;
		//-------------------------------------------
		XE::UI::CUISerializer serializer(&elementMap);
		serializer.Import("MenuInit.xml" , "General");
		//_--------------------------------------------
		//Main ItemBar
		//--------------------------------------------
		m_pItemBar = new XE::UI::ItemBar(mGui3D,XE::Math::Vector2f(0, mScreen->getHeight() - 300)); 
				
		//Event wenn Menu auswahl fertig und zum nächsten Schritt
		m_pItemBar->GetSignal( XE::UI::ItemBar::OnContinue ).Connect( &GUI::OnContinue, this );
		m_pItemBar->GetSignal( XE::UI::ItemBar::OnBack ).Connect( &GUI::OnBack, this );
		m_pItemBar->GetSignal( XE::UI::ItemBar::OnExit ).Connect( &GUI::OnExit, this );
		m_pItemBar->GetSignal( XE::UI::ItemBar::OnClose ).Connect( &GUI::OnClose, this );
		//m_pItemBar->GetSignal( XE::UI::AddItem ).Connect( &GUI::OnAddItem, this ); //innerhalb itembox handeln!
	//	m_pItemBar->GetSignal( XE::UI::RemoveController ).Connect( &GUI::OnRemoveController, this );
	//	m_pItemBar->GetSignal( XE::UI::ChangeEvent ).Connect( &GUI::OnChangeEvent, this ); //innerhalb itembox handeln!
		
		//
		//subobx von main itembar mit SubItemBar
		XE::UI::ItemBox* iBoxSub = new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::BALL, "Exit", "item_ball", "item_ball_hover");
		iBoxSub->GetSignal( XE::UI::ItemBox::OnTriggered ).Connect( &GUI::OnExit, this );
			//	iBoxSub->connect(&onClickItemBoxSub);

		//Itemboxes für Main Itembar
		m_pItemBar->addItem(iBoxSub);

		XE::UI::ItemBox* iBoxSubNext = new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::SMALLBALL, "Weiter", "item_smallball", "item_smallball_hover");
		iBoxSubNext->GetSignal( XE::UI::ItemBox::OnTriggered ).Connect( &GUI::OnNext, this );
		m_pItemBar->addItem(iBoxSubNext);

		XE::UI::ItemBox* iBoxSubController1 = new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::SMALLBALL, "Controller 1", "item_smallball", "item_smallball_hover");
		iBoxSubController1->GetSignal( XE::UI::ItemBox::OnTriggered ).Connect( &GUI::OnController, this );
		m_pItemBar->addItem(iBoxSubController1);

		XE::UI::ItemBox* iBoxSubAddController = new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::UNKNOWN, "Add Controller", "item_unknown", "item_unknown_hover");
		iBoxSubAddController->GetSignal( XE::UI::ItemBox::OnTriggered ).Connect( &GUI::OnAddController, this );
		m_pItemBar->addItem(iBoxSubAddController);
	
		//Where BALL is the ITEM_ID, 25 is its capacity, and "item_ball" and "item_ball_hover" are the images for the two states.
	//	m_pItemBar->addItem(new XE::UI::ItemBox(mGui3D, XE::UI::ITEM_ID::BALL, 25, "item_ball", "item_ball_hover"));

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

	void OnController() 
	{	
		std::cout << "OnAddController" << std::endl; 
			
		//Sub ItemBar
		XE::UI::ItemBar* m_pItemBarSub = new XE::UI::ItemBar(mGui3D,XE::Math::Vector2f(0, mScreen->getHeight() - 600)); 

		m_pItemBarSub->addItem(new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::SMALLBALL, "Keyboard/Mouse", "item_smallball", "item_smallball_hover"));
		m_pItemBarSub->addItem(new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::SMALLBALL, "Joustick 1", "item_smallball", "item_smallball_hover"));
		m_pItemBarSub->addItem(new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::SMALLBALL, "Gamepad 1", "item_smallball", "item_smallball_hover"));
		
	}

	void OnNext() 
	{	
		std::cout << "OnNext" << std::endl; 
			
	//	delete m_pItemBar;
	
	}

	void OnAddController() 
	{	
		std::cout << "OnAddController" << std::endl; 
			
		m_pItemBar->addItem(new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::UNKNOWN, "Neuer Controller", "item_unknown", "item_unknown_hover"));
	
	}

	void OnContinue() {	
		std::cout << "OnContinue" << std::endl; 
			
	//	m_pItemBar->addItem(new XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::UNKNOWN, -1, "item_unknown", "item_unknown_hover"));
	
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

	void onClickItemBoxSub(XE::UI::ItemBox* parent)
	{

		std::cout << "onClickItemBoxSub" << std::endl;
	}

	// Calculate and normalize the distance between the middle of the screen
	// and the mouse on both X and Y axis.
	// This is used for the smooth movement of the camera
	// when the mouse is moving.
	XE::Math::Vector2f getScreenCenterMouseDistance()
	{
		double posX = (mMousePointer->position().x - vp1->getActualWidth())
			/ vp1->getActualWidth();
		double posY = (mMousePointer->position().y - vp1->getActualHeight())
			/ vp1->getActualHeight();

		return XE::Math::Vector2f(posX + 0.5, posY + 0.5);
	}

	void setMouseMove(XE::IPT::Event& event)
	{
		XE::Math::Vector2f point;
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;

		m_pItemBar->mouseMoved(point.x,point.y);
	//	// Set the new camera smooth direction movement
	//	XE::Math::Vector2f distance(getScreenCenterMouseDistance());
	///*	mCamera->setDirection(cameraDirection
	//		+ XE::Math::Vector3f(distance.x, -distance.y, 0) / 30);*/

	//	float xMove = static_cast<float>(event.mouseButton.x);
	//	float yMove = static_cast<float>(event.mouseButton.y);

	//	mNormalizedMousePosition.x += xMove / vp1->getActualWidth();
	//	mNormalizedMousePosition.y += yMove / vp1->getActualHeight();

	//	// Make sur the mouse isn't out of the screen
	//	mNormalizedMousePosition.x = std::min<XE::Float>(
	//		std::max<XE::Float>(mNormalizedMousePosition.x, 0), 1);
	//	mNormalizedMousePosition.y = std::min<XE::Float>(
	//		std::max<XE::Float>(mNormalizedMousePosition.y, 0), 1);

	//	// Mouse position on the screen
	//	mMousePointer->position(
	//		mNormalizedMousePosition.x * vp1->getActualWidth(),
	//		mNormalizedMousePosition.y * vp1->getActualHeight());

	//	// Ray for the actual panel to know where the mouse is
	//	mPanel->injectMouseMoved(
	//		mCamera->getCameraToViewportRay(
	//		mNormalizedMousePosition.x, mNormalizedMousePosition.y));


	}

	void setCamera(XE::OBJ::Camera* camera)
	{
		mCamera = camera;
	}

	void setPointSelectStart(XE::IPT::Event& event)
	{
		XE::Math::Vector2f point;
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;

		m_pItemBar->mouseDown(point.x,point.y);
	//------	mPanel->pointSelectStart(point);
	}

	void setPointSelectEnd(XE::IPT::Event& event)
	{
		XE::Math::Vector2f point;
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;

		m_pItemBar->mouseUp(point.x,point.y);
	//------	mPanel->pointSelectEnd(point);
	}

	bool countryVisitedChangedCallback(XE::UI::PanelElement* e)
	{
		XE::UI::Listbox* cb = (XE::UI::Listbox*) e;
		//    mUserVisitedCountry = cb->getValues();
		//   XE::SYS::String s("Visited country : ");
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
	//	virtual bool frameStarted(const XE::SYS::FrameEvent& evt);
	//virtual bool frameEnded(const SYS::FrameEvent& evt);

	virtual bool frameRenderingQueued(const XE::SYS::FrameEvent& evt)
	{
		//nur bei textbox benötigt
		//####	mPanel->injectTime(evt.timeSinceLastFrame);
		//####mPanel2->injectTime(evt.timeSinceLastFrame);

		return true;//SdkSample::frameRenderingQueued(evt);
	}

	/* Ogre::WindowEventListener */
	//void windowResized(XE::RS::RenderWindow* win);
	//void windowClosed(XE::RS::RenderWindow* win);

private:
	XE::XE_G::Screen* mScreen;
	XE::UI::XEUI* mGui3D;

	// The panel that is actually focused
	MyLinkedPanel* mActualPanel;
	XE::UI::ItemBar* m_pItemBar;

	XE::OBJ::Camera* mCamera;
	// Base Direction for the camera
	XE::Math::Vector3f cameraDirection;

	XE::Math::Vector2f mNormalizedMousePosition;

	std::vector<XE::SYS::String> mUserVisitedCountry;
	XE::RS::Viewport* vp1;
	XE::UI::Panel* mPanel;
	XE::XE_G::Layer* mMousePointerLayer;
	XE::XE_G::Rectangle* mMousePointer;
	MySimpleDemoPanelColors mMySimpleDemoPanelColors;

	XE::UI::Panel* mPanel2;
	XE::XE_G::Layer* mMousePointerLayer2;
	XE::XE_G::Rectangle* mMousePointer2;
};