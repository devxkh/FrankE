#pragma once

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