#include <XESystem/FrameLimiter.hpp>

#include <ThirdParty/sfml/include/sfml/System/Clock.hpp>
#include <ThirdParty/sfml/include/sfml/System/Sleep.hpp>

namespace XE {

	FrameLimiter::FrameLimiter() :
		m_minFps(10)
		, m_maxFps(60)
		, m_maxInactiveFps(10)
		, m_timeStepSmoothing(2)
	{

	}

	void FrameLimiter::ApplyFrameLimit(sf::Clock& clock, float wanted_fps)
	{
		//	float wanted_fps = (SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS) != 0 ? 1000.0f : 5.0f;


		if (clock.getElapsedTime().asMilliseconds() < 1 / wanted_fps)
		{
			sf::Time delayTime = sf::milliseconds(Int32(1000 / wanted_fps - clock.getElapsedTime().asMilliseconds() * 1000));
			sf::sleep(delayTime);
		}

		return;

	//	unsigned maxFps = m_maxFps;

	//	float elapsed = 0;
	//	float timeStep_ = 0.0f;
	//	//long long elapsed = 0;

	//	if (maxFps)
	//	{
	//		long long targetMax = 1000000.0 / maxFps;

	//		for (;;)
	//		{
	//			elapsed = clock.restart().asMicroseconds();
	//			if (elapsed >= targetMax)
	//				break;

	//			// Sleep if 1 ms or more off the frame limiting goal
	//			if (targetMax - elapsed >= 1000LL)
	//			{
	//				auto sleepTime = sf::microseconds((unsigned)((targetMax - elapsed) / 1000LL));
	//				sf::sleep(sleepTime);
	//			}
	//		}
	//	}

	//	elapsed = clock.restart().asMicroseconds(); // frameTimer_.GetUSec(true);
	////	return elapsed;

	//	// If FPS lower than minimum, clamp elapsed time
	//	if (m_minFps)
	//	{
	//		long long targetMin = 1000000LL / m_minFps;
	//		if (elapsed > targetMin)
	//			elapsed = targetMin;
	//	}

	//	// Perform timestep smoothing
	//	m_lastTimeSteps.push_back(elapsed);// / 1000000.0f);
	//	if (m_lastTimeSteps.size() > m_timeStepSmoothing)
	//	{
	//		// If the smoothing configuration was changed, ensure correct amount of samples
	//		m_lastTimeSteps.erase(m_lastTimeSteps.begin() + (m_lastTimeSteps.size() - m_timeStepSmoothing));
	//		for (unsigned i = 0; i < m_lastTimeSteps.size(); ++i)
	//			timeStep_ += m_lastTimeSteps[i];
	//		timeStep_ /= m_lastTimeSteps.size();
	//	}
	//	else
	//		timeStep_ = m_lastTimeSteps.back();

	//	return timeStep_;
	}

}