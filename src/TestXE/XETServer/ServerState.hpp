#pragma once

#include <XEngine.hpp>

class ServerState : public XE::XEState
{
public:

	ServerState(XE::XEngine& engine, bool replace = true);
	~ServerState();

	void pause(){ return; };
	void resume(){ return; };
	void draw(){ return; };

	void update(float deltaTime);

	void cleanup();

protected:

};