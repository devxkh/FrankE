#pragma once

#include <XEUI/UIState.hpp>
#include <memory>

namespace entityx
{
	class Entity;
}

namespace XE {

	class Label;
	class Box;
	class Alignment;

	class ScreenComponent;
	class ControllerComponent;
	class MenuItem;
	class CameraRenderable;

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
		ScreenComponent*			m_screen;
		CameraRenderable*			m_cameraRenderable;
	//	ControllerComponent*		m_controller;

		std::shared_ptr<Label>		m_FpsRendererThread;
		std::shared_ptr<Label>		m_FpsAvqThread;
		std::shared_ptr<Label>		m_FpsMainThread;
		std::shared_ptr<Label>		m_BatchCount;
		std::shared_ptr<Box>		m_Box;
		std::shared_ptr<Alignment>	m_alignment;

		MenuItem*					mMenuitem;
		bool						m_running;
		bool						m_resume;
	};

} // namespace XE