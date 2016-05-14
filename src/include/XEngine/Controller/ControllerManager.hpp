#ifndef __CONTROLLERMANAGER_HPP__
#define __CONTROLLERMANAGER_HPP__

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <XEngine/Controller/WindowManager.hpp>

#include <memory>
#include <vector>

namespace sf
{
	class Window;
}


namespace Ogre
{
	class RenderWindow;
}
namespace XE {

	class XEngine;
	class Controller;

	typedef std::vector<std::unique_ptr<Controller>>::iterator ControllerIt;
	typedef std::vector<std::unique_ptr<Controller>> ControllerVector;

	class ControllerManager //: public Ogre::GeneralAllocatedObject
	{
	public:

		ControllerManager();

		//Controller&  createController(Ogre::uint16 id, XEngine* engine, sf::Window* window);

		Controller& getController(Ogre::uint16 controllerID);

		void update(Ogre::Real timeSinceLastUpdate);

		void updateRenderWindow();

		void addController(std::unique_ptr<Controller>  controller);
		//void windowResized(XE::RenderWindow* rw)
		//{
		//	for (std::vector<Controller*>::iterator it = mControllerList.begin();  it!=mControllerList.end(); ++it)
		//	{
		//		(*it)->windowResized(rw); 
		//	}
		//}

		//void frameRenderingQueued(const FrameEvent& evt)
		//{
		//	//Controller Camera
		//	for (std::vector<Controller*>::iterator it = mControllerList.begin();  it!=mControllerList.end(); ++it)
		//	{
		//		(*it)->getCamera()->update(evt.timeSinceLastFrame);
		//	}
		//}

		ControllerVector& getList() { return mControllerList; }
	//	WindowManager& getWindowManager() { return mWindowManager; }
	private:
	
		//WindowManager	mWindowManager;
		ControllerIt		mControllerIt;
		ControllerVector	mControllerList;                     ///< Queue of available events
	};

} // namespace XE

#endif //__CONTROLLER_HPP__