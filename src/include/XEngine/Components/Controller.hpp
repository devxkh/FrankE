#pragma once

#include <XESystem/SystemConfig.hpp>
#include <Thor/Input/EventSystem.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <XESystem/Entityx/Entity.h>

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

	struct  ControllerData
	{
		ControllerData(Uint16 id, XEngine& engine, SDL_Window* window, bool defaultCtrl = false);

		void destroy();

		DeviceType m_deviceType;
		thor::ActionMap<std::size_t>::CallbackSystem system;
		thor::ActionMap<std::size_t> actionmap;
		bool isActive;
		SDL_Window* m_window;
		Uint16 mID;


		std::vector<entityx::Entity> selectedEntities;
		WindowState _windowState;
		XEngine& engine;

	};

	struct  ControllerComponent
	{
		ControllerComponent();
		~ControllerComponent();
		ControllerData* get();

		ControllerData* m_ControllerData;
	};

} // ns XE