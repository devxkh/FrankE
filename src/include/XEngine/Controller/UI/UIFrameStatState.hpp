#ifndef __UI_DEBUG_STATE_HPP__
#define __UI_DEBUG_STATE_HPP__

#include <XEUI/UIState.hpp>
#include <XEUI/widgets/Label.hpp>
#include <XEUI/Alignment.hpp>
#include <XEUI/Box.hpp>
#include <XEUI/Alignment.hpp>
#include <XESystem/Entityx/Entity.h>

namespace entityx
{
	class Entity;
}

namespace XE {

	class ControllerComponent;
	class MenuItem;

	class UIDebug : public XE::UIState
	{
	public:

		UIDebug(const Uint16& id, entityx::Entity entity, bool replace);
		~UIDebug();

		void pause();
		void resume();

		void draw();

		bool running() { return m_running; }
		void quit() { m_running = false; }

		void create(const char* fbdata);
		void reload(const char* fbdata);

		void update(float delta);

	protected:

		//initialization order!
		Label::Ptr m_FpsRendererThread;
		Label::Ptr m_FpsAvqThread;
		Label::Ptr m_FpsMainThread;
		Label::Ptr m_BatchCount;
		Box::Ptr  m_Box;
		Alignment::Ptr  m_alignment;

		entityx::Entity m_entity;

		MenuItem* mMenuitem;
		bool m_running;
		bool m_resume;
	};

} // namespace XE

#endif // __UI_DEBUG_STATE_HPP__