#ifndef __UI_CONSOLE_STATE_HPP__
#define __UI_CONSOLE_STATE_HPP__

#include <XEUI/UIState.hpp>
#include <XESystem/Entityx/Entity.h>
#include <XEUI/widgets/OgreConsoleForGorilla.hpp>

namespace entityx
{
	class Entity;
}

namespace XE {

	class ControllerComponent;
	class ScreenPanel;

	class UIConsole : public XE::UIState
	{
	public:

		UIConsole(const Ogre::uint16& id, entityx::Entity entity, bool replace);
		~UIConsole();

		void pause();
		void resume();

		void draw();

		bool running() { return m_running; }
		void quit() { m_running = false; }

		void create(const char* fbdata);
		void reload(const char* fbdata);

		void update(float delta);

	protected:
		//UIPanel::Ptr m_ConsolePanel;
		OgreConsole::Ptr m_Ogreconsole;
		entityx::Entity m_entity;

		bool m_running;
		bool m_resume;
	};

} // namespace XE

#endif // __UI_CONSOLE_STATE_HPP__