#include <XEUI/UIStateManager.hpp>
#include <XEUI/UIState.hpp>


namespace XE {

	void UIStateManager::update(const float deltaTime)
	{
		for (auto &state : m_states)
		{
			state.second->update(deltaTime);
		}
	}

	void UIStateManager::stepTo(const Uint16& navID, std::unique_ptr<  UIState > state)
	{
		//		mNavigations[navID]->setActualPanel( state->getUIPanel() );
		destroyUIState(mLastStateID);
		mLastStateID = state->getID();
		//		mNavigations[navID]->setLastStateID( state->getID() );
		//		m_states.clear();
		m_states[state->getID()] = std::move(state);
		//mController->getNav()->getItemPID( 8 )->_enabled = true; //,8,"Scene"
		//mController->uiDestroyLast();
	}

	void UIStateManager::destroyUIState(const Uint16& id)
	{
		m_states.erase(id);
		//	mStateIt = m_states.begin();
		//	while (mStateIt != m_states.end())
		//	{
		//		if( (*mStateIt).second->getID() == id )
		//		{
		//			//OGRE_DELETE *
		//		//	mStateIt.get_deleter()(new int);

		//		
		//		//	*mStateIt = nullptr;
		//			mStateIt = m_states.erase( mStateIt );

		//	
		////			destroyLayer( "WorldState", (*mUIPanelVectorIt)->getName() );
		//		}
		//		else 
		//			++mStateIt;
		//	}
		//	mStateIt = m_states.begin();
		//
	}

	//void UIStateManager::stepTo( PanelName panelName )
	//{
	//	//switch(panelName){
	//	//case PN_controller: 
	//	//	mNavigation->getNavItem( "NI_controller" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UIController>( "panelController", true ) );
	//	//	break;
	//	//case PN_controls: 
	//	//	mNavigation->getNavItem( "NI_controls" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UIControls>( "panelControls", true ) );
	//	//	break;
	//	//case PN_settings: 
	//	////	mNavigation->getNavItem( "NI_settings" )->_enabled = true; //,8,"Scene"
	//	////	stepTo( build <UISettings>( "panelSettings", true ) );
	//	//	break;
	//	//case PN_games: 
	//	//	mNavigation->getNavItem( "NI_games" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UIGames>( "panelGames", true ) );
	//	//	break;
	//	//case PN_team: 
	//	//	mNavigation->getNavItem( "NI_team" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UITeam>( "panelTeam", true ) );
	//	//	break;
	//	//case PN_character: 
	//	//	mNavigation->getNavItem( "NI_character" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UICharacter>( "panelCharacter", true ) );
	//	//	break;
	//	//case PN_scene: 
	//	//	mNavigation->getNavItem( "NI_scene" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UIScene>( "panelScene", true ) );
	//	//	break;
	//	//case PN_gameStart: 
	//	//	mNavigation->getNavItem( "NI_gameStart" )->_enabled = true; //,8,"Scene"
	//	//	stepTo( build <UIGameStart>( "panelGameStart", true ) );
	//	//	break;
	//	//}

	//	//mController->uiDestroyLast();

	//}
	void UIStateManager::uiDestroy(const Uint16& id)
	{
		m_states.erase(id);
	}

	void UIStateManager::addUIStateNavItem(const Uint16& navID, std::unique_ptr< UIState > state)
	{
		//		mNavigations[navID]->setActualPanel(state->getUIPanel());

		m_states[state->getID()] = std::move(state);
	}

	void UIStateManager::addUIState(std::unique_ptr< UIState > state)
	{
		m_states[state->getID()] = std::move(state);
	}

	void UIStateManager::uiDestroyLast()
	{
	}


} //namespace XE