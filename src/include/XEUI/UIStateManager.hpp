#ifndef XEUISTATE_MANAGER_HPP
#define XEUISTATE_MANAGER_HPP

#include <XESystem/SystemConfig.hpp>
#include <XESystem/Entityx/System.h>
//#include <XEUI/Widgets/Navigation.hpp>
#include <XEUI/UIState.hpp>

#include <memory>

namespace entityx { class Entity; }

namespace XE {

	typedef std::unordered_map<Uint16 , std::unique_ptr< UIState > > UIStateMap;
	typedef std::unordered_map<Uint16, std::unique_ptr< UIState > >::iterator UIStateIt;

	class UIStateManager
	{
	public:
		~UIStateManager();
		
		template < typename T >
		std::unique_ptr< T > build( const Uint16& id, entityx::Entity entity, bool replace = true );

		void stepTo( const Uint16& navID, std::unique_ptr<  UIState > state );

		void update(const float deltaTime);
		void uiDestroy( const Uint16& id );
		void addUIStateNavItem( const Uint16& navID, std::unique_ptr< UIState > state );
		void addUIState( std::unique_ptr< UIState > state );
		void uiDestroyLast();

		void destroyUIState( const Uint16& id );

	private:

		Uint16 mLastStateID;

		// the stack of states
		UIStateIt mStateIt;
		UIStateMap m_states;
	};

	//templates cannot be implemented in source files 
	template <typename T>
	std::unique_ptr<T> UIStateManager::build(const Uint16& id, entityx::Entity entity, bool replace)
	{
		return std::move(std::unique_ptr<T>(new T(id, entity, replace)));
	}

} //namespace XE

#endif//XEUISTATE_MANAGER_HPP