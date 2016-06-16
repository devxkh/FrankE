#ifndef __TESTCONTROLLERCOMPONENT_HPP__
#define __TESTCONTROLLERCOMPONENT_HPP__

#include <XEngine.hpp>

#include "Netmsg_generated.h"

namespace XET
{
	struct  TestControllerComponent : public XE::ControllerComponent
	{
		TestControllerComponent(XE::Uint16 id, XE::XEngine& engine, SDL_Window* window, bool defaultCtrl = false);

		void setActionMap(XE::ControllerComponent& controller);
	};

} // ns XET

#endif // __CONTROLLERCOMPONENT_HPP__