#include <XEngine/Controller/ControllerManager.hpp>

#include <XEngine.hpp>

namespace XE {
	
	ControllerManager::ControllerManager()
		//: mWindowManager()
	{

	}

	void ControllerManager::addController(std::unique_ptr<Controller> controller)
	{
		mControllerList.push_back(std::move(controller));
	}


	//Controller& ControllerManager::createController(Ogre::uint16 id, XEngine* engine,sf::Window* window)
	//{
	//	//engine->getGraphicsManager().updateRenderer();
	//	//step 5 camera
	////	std::unique_ptr<Controller> controller = std::unique_ptr<Controller>(new Controller(id, engine, window)); //creates camera
	//	//controller->setWindow(window);

	//	////step 6 workspace
	//	//engine->getGraphicsManager().createWorkspace(0, &controller->getCameraController().getOgreCamera()); //camera needed for workspace
	//	//controller->createScreen(); //workspace needed for screen

	//	mControllerList.push_back(std::move(controller));

	//	for (ControllerIt it = mControllerList.begin(); it != mControllerList.end(); ++it)
	//	{
	//		if (it->get()->getID() == id)
	//			return *it->get();
	//	}
	//}

	Controller& ControllerManager::getController(Ogre::uint16 controllerID)
	{
		for (ControllerIt it = mControllerList.begin(); it != mControllerList.end(); ++it)
		{
			if (it->get()->getID() == controllerID)
				return *it->get();
		}


		//for (mControllerIt = mControllerList.begin() ; mControllerIt != mControllerList.end(); mControllerIt++)
		//	if (mControllerIt->get()->getID() == controllerID) 
		//		return mControllerIt->get();
	//todo exceotion ... controller not found
	}

	void ControllerManager::update(Ogre::Real timeSinceLastUpdate)
	{
		for (ControllerIt it = mControllerList.begin(); it != mControllerList.end(); ++it)
			it->get()->update(timeSinceLastUpdate);
	}

	void ControllerManager::updateRenderWindow()
	{
	//	for (ControllerIt it = mControllerList.begin(); it != mControllerList.end(); ++it)
	//		it->get()->updateRenderWindow();
	}

} // namespace XE
