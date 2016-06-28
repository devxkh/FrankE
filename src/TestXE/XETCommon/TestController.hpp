#pragma once

#include <XEngine.hpp>

namespace XET
{
	struct  TestControllerComponent : public XE::ControllerComponent
	{
		TestControllerComponent(XE::Uint16 id, XE::XEngine& engine, SDL_Window* window, bool defaultCtrl = false);

		void setActionMap(XE::ControllerComponent& controller);
	};

} // ns XET
