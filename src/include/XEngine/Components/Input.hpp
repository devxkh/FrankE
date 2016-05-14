#ifndef __INPUTCOMPONENT_HPP__
#define __INPUTCOMPONENT_HPP__

#include <sfml/System/Vector3.hpp>
#include <XESystem/TransportData.hpp>

#include <XESystem/Entity/entityx.h>


#include <Thor/Input/EventSystem.hpp>
#include <Thor/Input/ActionMap.hpp>

#include <XEngine/Controller/InputCmd.hpp>

namespace XE
{
	struct InputComponent {

		InputComponent(bool defaultCtrl = false);

		void InputComponent::loadControllerFile();

		thor::ActionMap<std::size_t>::CallbackSystem system;
		thor::ActionMap<std::size_t> actionmap;

	};

}

#endif //__INPUTCOMPONENT_HPP__