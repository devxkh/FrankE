#pragma once

#include <XEngine.hpp>

#include <XEUI/UIState.hpp>

class UIState_2 : public XE::UIState
{
public:

	UIState_2(const XE::uint16& id, entityx::Entity entity, bool replace);
	~UIState_2();

	void pause();
	void resume();

	void draw();

	bool running() { return m_running; }
	void quit() { m_running = false; }

	void create(const char* fbdata);
	void reload(const char* fbdata);

	void update(float delta);

	void ButtonClick();

private:

	entityx::Entity m_entity;

	//initialization order!
	XE::Button::Ptr m_btnTest;
	XE::Box::Ptr  m_Box;
	XE::Alignment::Ptr  m_alignment;

	bool m_running;
	bool m_resume;
};