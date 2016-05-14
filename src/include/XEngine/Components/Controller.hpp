#ifndef __CONTROLLERCOMPONENT_HPP__
#define __CONTROLLERCOMPONENT_HPP__

#include <Thor/Input/EventSystem.hpp>
#include <Thor/Input/ActionMap.hpp>

namespace sf { class Window; }

namespace XE
{
	class XEngine;

	typedef thor::ActionContext<std::size_t> ActionContext;

	struct WindowState
	{
	public:
		sf::Uint32 width;
		sf::Uint32 height;
		bool isDirty;
	};

	// Controller Device Type
	enum DeviceType
	{
		DT_unknown,
		DT_KeyMouse,
		DT_Joy,
		DT_Gamepad,

		DT_count
	};

	struct  ControllerComponent
	{
		ControllerComponent(sf::Uint16 id, XEngine& engine, sf::Window* window, bool defaultCtrl = false);

		DeviceType m_deviceType;
		thor::ActionMap<std::size_t>::CallbackSystem system;
		thor::ActionMap<std::size_t> actionmap;
		bool isActive;
		sf::Window* m_window;
		sf::Uint16 mID;

		WindowState _windowState;
		XEngine& engine;

	};

} // ns XE

#endif // __CONTROLLERCOMPONENT_HPP__