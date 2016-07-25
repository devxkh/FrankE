#pragma once

#include <XEngine.hpp>

namespace NetMsg
{
	enum PlayerState;
}


namespace XET
{
	struct  TestControllerComponent : public XE::ControllerComponent
	{
		TestControllerComponent(XE::Uint16 id, XE::XEngine& engine, SDL_Window* window, bool defaultCtrl = false);

		void setActionMap(XE::ControllerComponent& controller);


		NetMsg::PlayerState state;
	};

} // ns XET
