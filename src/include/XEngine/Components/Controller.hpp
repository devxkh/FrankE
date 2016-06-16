#ifndef __CONTROLLERCOMPONENT_HPP__
#define __CONTROLLERCOMPONENT_HPP__

#include <XESystem/SystemConfig.hpp>
#include <Thor/Input/EventSystem.hpp>
#include <Thor/Input/ActionMap.hpp>

class SDL_Window;

namespace XE
{
	class XEngine;

	typedef thor::ActionContext<std::size_t> ActionContext;

	struct WindowState
	{
	public:
		Int32 width;
		Int32 height;
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
		ControllerComponent(Uint16 id, XEngine& engine, SDL_Window* window, bool defaultCtrl = false);

		DeviceType m_deviceType;
		thor::ActionMap<std::size_t>::CallbackSystem system;
		thor::ActionMap<std::size_t> actionmap;
		bool isActive;
		SDL_Window* m_window;
		Uint16 mID;

		WindowState _windowState;
		XEngine& engine;

	};

} // ns XE

#endif // __CONTROLLERCOMPONENT_HPP__