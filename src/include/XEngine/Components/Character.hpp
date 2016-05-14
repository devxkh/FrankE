#ifndef __CHARACTERCOMPONENT_HPP__
#define __CHARACTERCOMPONENT_HPP__

#include <sfml/System/Vector3.hpp>
#include <XESystem/TransportData.hpp>
#include <XESystem/Math/Quaternion.h>

namespace XE
{
	struct CharacterComponent {
		CharacterComponent()
			:
			bodyDirection(1, 0, 0, 0)
			, bodyGoalDirection(1, 0, 0, 0)

		{

		}

		Quaternion bodyDirection;      // player's local intended direction based on WASD keys
		Quaternion bodyGoalDirection;      // player's local intended direction based on WASD keys
	};

}

#endif //__CHARACTERCOMPONENT_HPP__