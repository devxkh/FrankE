#pragma once

#include <XEngine.hpp>


#ifdef CompileEditor	
namespace XE {
	class EntityViewerUIState;
}
#endif

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

#ifdef CompileEditor	
	XE::EntityViewerUIState* m_EntityViewerUIState;
#endif

};

// namespace XG