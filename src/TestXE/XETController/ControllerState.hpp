#ifndef __INITSTATE_HPP__
#define __INITSTATE_HPP__

#include <XEngine.hpp>

class ControllerState : public XE::XEState
{
public:

	ControllerState(XE::XEngine& engine, bool replace = true);
	~ControllerState();

	void pause(){ return; };
	void resume(){ return; };
	void draw(){ return; };

	void update(float deltaTime);

	void cleanup();
	
protected:

};

// namespace XG

#endif // __INITSTATE_HPP__