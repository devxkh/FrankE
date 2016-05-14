#ifndef __SERVERSTATE_HPP__
#define __SERVERSTATE_HPP__

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

// namespace XG

#endif // __INITSTATE_HPP__