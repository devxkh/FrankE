#ifndef __TestMenuState_HPP__
#define __TestMenuState_HPP__

#include <XEngine.hpp>

class TestMenuState : public XE::XEState
{
public:

	TestMenuState(XE::XEngine& engine, bool replace = true);
	~TestMenuState();

	void pause(){ return; };
	void resume(){ return; };
	void draw(){ return; };

	bool frameStarted(const XE::FrameEvent& evt)
	{
		/*if (mWindow->isClosed())
		return false;

		mEventListener->process();
		if (mEventListener->mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;*/

		return true;
	}

	//void setNext(Uint16 state);

	void SetResource();

	void update(float deltaTime);

	void cleanup();



protected:

	virtual void createFrameListener(void);
	virtual bool frameRenderingQueued(const XE::FrameEvent& evt)
	{
		//	mScene->update(evt.timeSinceLastFrame);
		//	mControllerManager->frameRenderingQueued(evt);
		return true;//SdkSample::frameRenderingQueued(evt);
	}


	Ogre::String lNameOfResourceGroup;
private:
	
}; // namespace XE

#endif // __WindowSTATE_HPP__