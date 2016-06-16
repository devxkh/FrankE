#ifndef __TestMenuState_HPP__
#define __TestMenuState_HPP__

#include <XEngine.hpp>

class TestMenuState : public XE::XEState
{
public:

	TestMenuState(XE::XEngine& engine, bool replace = true);
	~TestMenuState();

	void pause() { return; };
	void resume() { return; };
	void draw() { return; };

	void SetResource();

	void update(float deltaTime);

	void cleanup();

}; // namespace XE

#endif // __WindowSTATE_HPP__