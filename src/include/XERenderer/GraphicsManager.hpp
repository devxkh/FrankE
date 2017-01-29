#ifndef __GRAPHICSMANAGER_HPP__
#define __GRAPHICSMANAGER_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XEngine/Controller/Export.hpp>

#include <XESystem/QueueManager.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>

#include <XEngine/Controller/WindowManager.hpp>

#include <XEngine/OgreLogListener.hpp>

#include <ThirdParty/sfml/include/sfml/System/Clock.hpp>

#include <mutex>
#include <thread>

#include <SDL.h>

namespace sol { class state; }

namespace Ogre
{
	class Root;
	class RenderWindow;
}

#define UseRenderThread 1 // 1 = use renderthread, 0 = dont use renderthread

namespace XE
{
	class Renderable;
	class XEngine;
	class OgreWorkspace;

	enum RenderTaskID
	{
		DebugLines,
		AnimationTimes,
		AnimationAddTimes,
		RenderBody,
		RenderGUI,
		Camera,
	};


	struct RenderTask
	{
	public:
		RenderTask(RenderTaskID id, bool isDone = true) : taskId(id), isDone(isDone){}

		RenderTaskID taskId;
		bool isDone;
	};


	class GraphicsManager 
	{
	public:
		struct FrameStats
		{
			float Fps;
			float AvgFps;
			float BestTime;
			float WorstTime;
		};

		GraphicsManager(XE::XEngine* engine);
		~GraphicsManager();

		void registerObject(sol::state& lua);

		//Ogre::TexturePtr createTextureRenderTarget(int width, int height);
		void setRenderSystem();
		
		void resizeRenderWindow(size_t w, size_t h);
		void createRenderWindow(const std::string& title);
		
		void registerHlms(void);

		QueueManager& getFromRendererQueue() { return my_FromRSQueueManager; }
		QueueManager& getIntoRendererQueue() { return my_QueueManager; }

		void updateRenderer();

		void setShadowMappingUseBackFaces(bool useBackFaces);


		GUIRenderer& getGUIRenderer() { return m_GUIRenderer; }

		inline Ogre::Root*	 getRoot() { return mRoot; }

		inline FrameStats& getFrameStats() { return  m_FrameStats; }
		

		void setFullScreen(SDL_Window* wnd, bool fullscreen);

		float getAccumTimeSinceLastLogicFrame();

		Ogre::RenderWindow* _t_getRenderWindow(XE::Uint16 id){ return _t_RenderWindow; }

//		WindowManager& getWindowManager() { return mWindowManager; }
		SDL_Window* getWindow();

		RenderTask& GetRenderTask(RenderTaskID id);

		std::vector<Renderable*> _t_Renderables;

	protected:
		void createRenderer();

	private:

		float mAccumTimeSinceLastLogicFrame;
		
		sf::Clock m_clock;

		OgreLogListener m_ogreLog;

		SDL_Window* m_SdlWindow;

		void RenderThread(GraphicsManager* graphicsMgr, XE::XEngine* engine);

		std::vector<RenderTask> _renderTasks;

	//	WindowManager	mWindowManager;

		Ogre::RenderWindow*  _t_RenderWindow;
		//todo multiple workspaces!
		OgreWorkspace*			_t_OgreWorkspace;
		
		//initialization order!
		Ogre::Root*			mRoot;

		GUIRenderer m_GUIRenderer;
		
		FrameStats m_FrameStats;

		XE::XEngine*		mEngine;
		QueueManager		my_QueueManager;
		QueueManager		my_FromRSQueueManager;
		std::mutex			mRenderMutex;// protects mRenderThread
		std::thread*		mRenderThread;
	};


} // namespace XE

#endif //__GRAPHICSMANAGER_HPP__