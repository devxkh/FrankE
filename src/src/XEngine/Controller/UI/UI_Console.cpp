////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <XEngine/Controller/UI/UI_Console.hpp>

#include <XEUI/UIManager.hpp>

#include <XEngine/Components/Controller.hpp>
//#include <XEUI/UISerializer.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h>
//#include <XEUI/UIPanel.hpp>
//#include <XEUI/PanelContainer.hpp>
//#include <XEUI/UIScreen.hpp>

//#include <States/UIStates/UI_Controller.hpp>
//#include <States/UIStates/UI_Character.hpp>
//#include <States/UIStates/UI_Controls.hpp>
//#include <States/UIStates/UI_Games.hpp>
//#include <States/UIStates/UI_GameStart.hpp>
//#include <States/UIStates/UI_Scene.hpp>
//#include <States/UIStates/UI_Team.hpp>

#include <XERenderer/GraphicsManager.hpp>
#include <XESystem/Entityx/Entity.h>
#include <XEngine/Components/ScreenComponent.hpp>
#include <XERenderer/CameraRenderable.hpp>


namespace XE {

	UIConsole::UIConsole(const Ogre::uint16& id, entityx::Entity entity, bool replace = true)
		: UIState(id, replace),
		m_entity(entity)
	
	//---	, m_ConsolePanel(UIPanel::Create(entity.component<CameraRenderable>()->getGraphicsManager().getGUIRenderer(), entity.component<ScreenComponent>()->getDesktop()))
//------		, m_Ogreconsole(OgreConsole::Create(entity.component<CameraRenderable>()->getGraphicsManager().getGUIRenderer(), m_ConsolePanel->getLayer(0)))

	{
		XE::WLayer& layer = entity.component<XE::ScreenComponent>()->wLayer;
	//	m_Box = XE::Box::Create(layer, XE::Box::Orientation::VERTICAL, 10.f);

		m_Ogreconsole = OgreConsole::Create(layer);
	//	std::cout << "UIConsole Init" << std::endl;
		 
//		controller->getConsole();
	//-->>	m_ConsolePanel->SetAlignment(sf::Vector2f(0.0f, 1.0f));//todo from style
	//-->>	m_ConsolePanel->Put(m_Ogreconsole,sf::Vector2f(0,0));

		//absturtz!!
	//	controller->getStateData()->mRoot->addFrameListener(this);

		//###controller->getEngine()->getUIMgr().getGUIRenderer().addAtlas("completeGUIDemo", "General");// group);

	//##	Ogre::DataStreamPtr filstream = Ogre::ResourceGroupManager::getSingleton().openResource("console.xfb_ui", "General");
		//read
		//##	const XFB_UI::Panel2D* panel2DElement = flatbuffers::GetRoot<XFB_UI::Panel2D>(filstream->getAsString().c_str());


		//KH todo		XE::UISerializer serializer(&controller->getEngine()->getUIMgr(),
		//KH todo			&controller->getUIStateMgr(),
		//KH todo			controller->getID());

		//serializer.addCallback("onPlay",this, &UIConsole::onPlay);
		//serializer.addCallback("onSelectExit",this, &UIConsole::onSelectExit);
		//serializer.addCallback("onItemChanged",this, &UIConsole::onNavItemChanged); //Navigation selection Changed

//		const XFB_UI::Console* consoleElement = new XFB_UI::Console();
	//	consoleElement->base()->height();
		//const XFB_UI::Style* consoleStyle;

		//flatbuffers::FlatBufferBuilder fbb;
		//XFB_UI::Vec2f* test = new XFB_UI::Vec2f(0, 0);
		//flatbuffers::Offset<XFB_UI::Element>  tmp = XFB_UI::CreateElement(fbb, 'kk', 'tt', 0, 0, 0, 50, 50, 0, test, 't', 't', 0);
		//XFB_UI::CreateConsole(fbb, tmp);
		//todo destroy
//###		WLayer& layer = m_ConsolePanel.getGUILayer();//.createLayer();
	///	m_Ogreconsole = new OgreConsole(&controller->getEngine()->getUIMgr(), &layer);
		//mController->getView().mUIScreen = serializer.loadScreenTheme(mController->getView().mViewport,"screenTheme.xml" , "General");
//KH todo			Screen* screen = serializer.loadScreenTheme(controller->getView().mViewport, "screenTheme.xml", "General");
		//KH todo		ScreenPanel* consolePanel = serializer.loadPanel2D("panelConsole", "General");
		//KH todo		OgreConsole* console = static_cast<OgreConsole*>(consolePanel->getItem("consoleMain"));
//KH todo			console->init(screen);
		//Menu* menu = static_cast<Menu*>(debugPanel->getItem("menuConsole"));
		//mMenuitem = static_cast<MenuItem*>(menu->getItemPID(3));
		//XE::UI::Navigation* nav = mController->getStateData()->mUIStateManager.getNav( 0 );
		//if(nav)
		//{
		//	XE::UI::NavItem* navItem = nav->addItem("NI_controller",2,"Controller");
		//	nav->addItem("NI_controls",3,"Controls");
		//	
		//	XE::UI::NavItem* navSettings = nav->addItem("NI_settings",4,"Settings");

		//	nav->addItem("NI_games",5,"Game");
		//	nav->addItem("NI_team",6,"Team")->_enabled = false;
		//	nav->addItem("NI_character",7,"Character")->_enabled = false;
		//	nav->addItem("NI_scene",8,"Scene")->_enabled = false;
		//	nav->addItem("NI_gameStart",9,"Play")->_enabled = false;

		//	mController->getStateData()->mUIStateManager.stepTo( 
		//			0, mController->getStateData()->mUIStateManager.build <UIController>( UISI_Games, mController, true ) );
		//}
		//else
		//mUIPanel = serializer.loadPanel2D("panelController", "General");
	}

	UIConsole::~UIConsole()
	{

	}



	void UIConsole::create(const char* fbdata)
	{

	}
	void UIConsole::reload(const char* fbdata)		{

	}
	//bool UIConsole::frameRenderingQueued(const Ogre::FrameEvent& evt)
	//{
	//	std::stringstream fps;
	//	//todo KH	fps << mController->getView().mRenderWindow->getLastFPS();

	//	//mMenuitem->setText(fps.str());

	//	return true;
	//}

	//bool UIConsole::onNavItemChanged( XE::UI::PanelElement* e )
	//{
	//	XE::UI::Navigation* nav = static_cast<XE::UI::Navigation*>(e);

	//	XE::UI::NavItem* niSelected = nav->getSelectedItem();
	//	String navItemName = niSelected->getName();

	//	if(mSubPanel)
	//	{	
	//		mSubPanel->_destroy = true;
	//		mSubPanel = nullptr;
	//	}
	//		//nav->getPanelContainer()->getXEUI()->destroyUIPanel( "panelSetChoice" );

	//	XE::UI::UIStateManager& uiSM = mController->getStateData()->mUIStateManager;

	//	if(navItemName == "NI_controller") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UIController>( UI::UISI_Controller, mController, true ) );
	//	else if(navItemName == "NI_controls") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UIControls>( UI::UISI_Controls, mController, true ) );
	//	else if(navItemName == "NI_settings")
	//	{
	//		//mController->stepTo ( PN_settings );	
	//		
	//		nav->removeActualPanel();
	//		
	//		uiSM.destroyUIState( nav->getLastStateID() );

	//		//XE::UI::UISerializer serializer( &mController->getStateData()->mUIManager, mController->getID() );
	//		//serializer.addCallback("onItemChanged",this, &UIConsole::onSubNavItemChanged); //Navigation selection Changed

	//		//float x = niSelected->_pos.x;
	//		//float y = niSelected->_pos.y + niSelected->_size.y;

	//		//mSubPanel = new XE::UI::ScreenPanel(
	//		//							nav->getPanelContainer()->getXEUI(), 
	//		//							mController->getView().mUIScreen,
	//		//							"notUsed", 
	//		//							"panelSetChoice",
	//		//							0 );
	//		//nav->getPanelContainer()->getXEUI()->addUIPanel(mSubPanel);
	//		//
	//		//XE::UI::ElementStyle* style = mSubPanel->getStyle( XE::UI::S_Panel2D );
	//		//style->width = 400;
	//		//style->height = 50;
	//		//	
	//		//mSubPanel->setStyle( style );
	//		//mSubPanel->setPosition(XE::Vector3f( x, y, 0));
	//		//XE::UI::Navigation* navSettings = mSubPanel->makeNavigation( "navSetChoice", 0, 0, 400, 50, 6 );
	//		//
	//		//navSettings->addItem("NI_setGraphic",1,"Graphic");
	//		//navSettings->addItem("NI_setGame",2,"Game");
	//		//navSettings->addItem("NI_setNetwork",3,"Network");
	//		//navSettings->addItem("NI_setUI",4,"Interface");

	//		//Jump to Graphic Settings
	//		//mController->stepTo( mController->build <UI_SetGraphic>( "panelSetGraphic", true ) );
	//
	//	}
	//	else if(navItemName == "NI_games") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UIGames>( UI::UISI_Games, mController, true ) );
	//	else if(navItemName == "NI_team") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UITeam>( UI::UISI_Team, mController, true ) );
	//	else if(navItemName == "NI_character") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UICharacter>( UI::UISI_Character, mController, true ) );
	//	else if(navItemName == "NI_scene") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UIScene>( UI::UISI_Scene, mController, true ) );
	//	else if(navItemName == "NI_gameStart") 
	//		uiSM.stepTo( 0, uiSM.build <UI::UIGameStart>( UI::UISI_GameStart, mController, true ) );
	//	else
	//	{
	//		//Fehler
	//	}

	//	std::cout << "onNavItemChanged:" << nav->getValue() << std::endl;
	//	return true;
	//}

	//bool UIConsole::onPlay( XE::UI::PanelElement* e )
	//{
	//	std::cout << "onPlay" << std::endl;
	//
	//	m_running = false;

	//	//std::find(vector.begin(), vector.end(), item)!=vector.end()
	//	// serializer.loadPanel2D("menuGames", "General"));
	////	mController->uiAdd
	////	mController->uiStepTo( mController->build <UI::UIGames>( "menuGames", mUIManager, mRoot, mController , true ) );
	////	mController->uiDestroyLast();
	//	

	////	callnextPanelThread();
	//	//Kann erst gelöscht werden wenn funktzion fertig da callback in pressend aufgerufen wird... sonst objekt gelöscht bevor fertig!
	//	//mXEUI.destroyUIPanel("mainPanel");

	//	return true;
	//}


	//void UIConsole::createFrameListener(void)
	// {

	// }

	void UIConsole::resume()
	{
		// let the state update the game
		//	m_states.top()->update();
	}
	void UIConsole::pause()
	{
		// let the state update the game
		//	m_states.top()->update();
	}

	void UIConsole::update(float delta)
	{

		m_Ogreconsole->update();

		// let the state update the game
		//	m_states.top()->update();
	}

	void UIConsole::draw()
	{
		// let the state draw the screen
		//	m_states.top()->draw();
	}
} // namespace XE
