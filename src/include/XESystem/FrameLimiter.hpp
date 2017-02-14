#pragma once

#include <XESystem/SystemConfig.hpp>
#include <vector>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

namespace sf {
	class Time;
}

namespace XE
{
	class FrameLimiter
	{
	public:
		FrameLimiter();

		void ApplyFrameLimit(sf::Time& elapsedTime, float wanted_fps = 120.0f);

	private:

		Uint16 m_timeStepSmoothing;
		std::vector<size_t> m_lastTimeSteps;
		Uint16 m_minFps;
		Uint16  m_maxFps;
		Uint16  m_maxInactiveFps;

	};
}