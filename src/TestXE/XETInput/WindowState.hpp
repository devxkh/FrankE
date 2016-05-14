#ifndef __WindowSTATE_HPP__
#define __WindowSTATE_HPP__

#include <XEngine.hpp>

class WindowState : public XE::XEState
{
public:

	WindowState(XE::XEngine& engine, bool replace = true);
	~WindowState();

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

	//virtual void windowResized(XE::RenderWindow* rw)
	//{
	//	//	mScene->getCamera()->setAspectRatio((Float)mViewport->getActualWidth() / (Float)mViewport->getActualHeight());
	//	//	mStateData. mControllerManager->windowResized(rw);
	//}

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
	
};

// namespace XG

#endif // __WindowSTATE_HPP__