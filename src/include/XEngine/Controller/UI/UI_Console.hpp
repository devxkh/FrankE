#pragma once

#include <XEUI/UIState.hpp>
#include <XESystem/Entityx/Entity.h>
#include <XEUI/Alignment.hpp>
#include <XEUI/Widgets/Entry.hpp>
#include <XEUI/Widgets/Label.hpp>
#include <XEUI/Box.hpp>

//#include <XEUI/widgets/OgreConsoleForGorilla.hpp>

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
		//OgreConsole::Ptr m_Ogreconsole;

		std::vector<Label::Ptr> m_linesOfText;

		Box::Ptr  m_consoleWidgetContainer;
		Alignment::Ptr  m_alignment;
		Entry::Ptr m_entry;
		
		entityx::Entity m_entity;

		bool m_running;
		bool m_resume;
	};

} // namespace XE