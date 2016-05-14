#ifndef __EDITORSTATE_HPP__
#define __EDITORSTATE_HPP__

#include <XEngine.hpp>

	class EditorState : public XE::XEState
	{
	public:

		EditorState(XE::XEngine& engine, bool replace = true);
		~EditorState();

		void pause(){ return; };
		void resume(){ return; };
		void draw(){ return; };

		bool frameStarted(const XE::FrameEvent& evt)
		{
			//update physics 
		//	mStateData->mScene->getDynamicsWorld()->step(evt.timeSinceLastFrame);
			
			//mStateData->mScene->getDynamicsWorld()->DrawDebug();
			//mStateData->mScene->getDebugger()-> flush();

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

		//XE::StateData* getStateData() { return mStateData.get(); }

	protected:

		virtual void createFrameListener(void);
		virtual bool frameRenderingQueued(const XE::FrameEvent& evt)
		{
			//mStateData->mScene->update(evt.timeSinceLastFrame);

			//	mScene->update(evt.timeSinceLastFrame);
			//	mEditorManager->frameRenderingQueued(evt);
			return true;//SdkSample::frameRenderingQueued(evt);
		}

		//std::unique_ptr<XE::StateData> mStateData;
		Ogre::String lNameOfResourceGroup;

		Ogre::TerrainGroup* mTerrainGroup;
	};

// namespace XG

#endif // __INITSTATE_HPP__