/*
TecnoFreak Animation System
http://sourceforge.net/projects/tecnofreakanima/

Copyright (c) 2008 Pau Novau Lebrato

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

/*

Code from Game Programming Gems Volume 4

1.10 Critically Damed Ease-In/Ease-Out Smoothing by Thomas Lowe

*/

#include <XEngine/Animation/Helper/SmoothValue.h>
#include <XEngine/Animation/Helper/Clamp.h>

namespace XE {

	float helper::smoothValue(const float from, const float to, float& vel, const float smoothTime, const float timeDelta)
	{
		float omega = 2.f / smoothTime;
		float x = omega * timeDelta;
		float exp = 1.f / (1.f + x + 0.48f * x * x + 0.235f * x * x * x);
		float change = from - to;
		float temp = (vel + omega * change) * timeDelta;
		vel = (vel - omega * temp) * exp;
		return to + (change + temp) * exp;
	}

	float helper::smoothValue(const float from, const float to, float& vel, const float smoothTime, const float timeDelta, const float maxSpeed)
	{
		float omega = 2.f / smoothTime;
		float x = omega * timeDelta;
		float exp = 1.f / (1.f + x + 0.48f * x * x + 0.235f * x * x * x);
		float change = from - to;
		float maxChange = maxSpeed * smoothTime;
		change = helper::clamp< float >(change, -maxChange, maxChange);
		float temp = (vel + omega * change) * timeDelta;
		vel = (vel - omega * temp) * exp;
		return to + (change + temp) * exp;
	}

}