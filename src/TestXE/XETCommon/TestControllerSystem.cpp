#include "TestControllerSystem.hpp"

#include <XEngine.hpp>

#include <XEngine/Controller/UI/UI_Console.hpp>
#include <XEngine/Controller/UI/UIFrameStatState.hpp>

#include <XEngine/Components/CameraFree.hpp>
#include <XEngine/Components/Controller.hpp>
#include <XEPhysics/Physics/gkRayTest.h>


#include "Controllers_generated.h"


#include <functional>

namespace XET {

	void TestControllerSystem::onQuit()
	{
		mEngine.quit();
	}

	void TestControllerSystem::setBasicInputEvents(TestControllerComponent& controller)
	{
		controller.system.connect0(ControllerSettings::ActionType_Quit, [this]() { onQuit(); });

		////Interface
		//controller.system.connect(ActionType_NavRight, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });  //std::bind(&TestControllerSystem::menuNav, std::placeholders::_1, ControllerSettings::ActionType_NavRight));
		//controller.system.connect(ActionType_NavLeft, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavUp, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavDown, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavEnter, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });

		controller.system.connect(ControllerSettings::ActionType_Resized, [this](XE::ActionContext context) { onResized(context); });


		controller.system.connect(ControllerSettings::ActionType_KeyPressed, [this](XE::ActionContext context) { onKeyPressed(context); });
		controller.system.connect(ControllerSettings::ActionType_TextEntered, [this](XE::ActionContext context) { onTextEntered(context); });

		//mouse only events
		controller.system.connect(ControllerSettings::ActionType_PointSelectStart, [this](XE::ActionContext context) { onPointSelectStart(context); });
		controller.system.connect(ControllerSettings::ActionType_PointSelectEnd, [this](XE::ActionContext context) { onPointSelectEnd(context); });
		controller.system.connect(ControllerSettings::ActionType_PointMoved, [this](XE::ActionContext context) { onPointMoved(context); });
	}


	TestControllerSystem::TestControllerSystem(XE::XEngine& engine)
		: mEngine(engine)
		, mDecalDestroy(false)
		, _lastMousePos(0, 0)
		, _mousePressed(false)
		, moveDirection(0, 0, 0)
		//, _windowState()

		, _turn_speed(0)
		, _zoom_speed(0)
	{
		//	mCamera.getCamera()->setNearClipDistance(0.7);
		/*	Ogre::uint16 fd = 5;
			CameraController test(engine->getGraphicsManager(), engine->getScene());*/

			//	settingActionMap();

				//engine->getGraphicsManager().createWorkspace(window);

				//engine->getGraphicsManager().addFrameListener(this);

				//mRayScnQuery = mEngine->getCurrentState()->getStateData()->mScene->getSceneMgr()->createRayQuery(Ogre::Ray());
	}

	TestControllerSystem::~TestControllerSystem()
	{

	}

	/// needed for sfgui mouse clicked events!!
	void TestControllerSystem::onPointMoved(XE::ActionContext context)
	{
		//if (mConsole)
		//	mConsole->onKeyPressed(event.key.code);

		sf::Vector2i mousePosition = sf::Vector2i(context.event->mouseMove.x, context.event->mouseMove.y);//;sf::Mouse::getPosition(*controller.m_window);

		std::cout << "onPointMoved! x:" << mousePosition.x << ",y:" << mousePosition.y << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->HandleEvent(*context.event);

			sf::Vector2i pos = sf::Mouse::getPosition(*controller->m_window);


			sf::Vector2i delta;

			if (_mousePressed)
			{
				//Mouse bewegt?
				if (_lastMousePos != pos && _lastMousePos != sf::Vector2i(0, 0))
				{
					sf::Mouse::setPosition(_lastMousePos, *controller->m_window);
					delta = _lastMousePos - pos;

					//if (mGameEntity)
					//	mCameraController.updateCameraGoal(delta.x, delta.y, 0);
					//	else
					if (entity.has_component<XE::CameraFreeComponent>())
					{
						entity.component<XE::CameraFreeComponent>()->rotate(delta.x, delta.y);
					}

					std::cout << "onCameraMove   delta = (" << delta.x << ", " << delta.y << ")" << std::endl;
				}
			}
		}

	}

	void TestControllerSystem::onKeyPressed(XE::ActionContext context)
	{
		//if (mConsole)
		//	mConsole->onKeyPressed(event.key.code);

		std::cout << "onKeyPressed! " << context.event->key.code << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->HandleEvent(*context.event);
		}
	}

	void TestControllerSystem::onTextEntered(XE::ActionContext context)
	{
		//if (mConsole)
		//	mConsole->onTextEntered(event.key.code);

		std::cout << "onTextEntered! " << context.event->key.code << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->HandleEvent(*context.event);
		}
	}

	void TestControllerSystem::onPointSelectStart(XE::ActionContext context)
	{
		std::cout << "onPointSelectStart! " << context.event->key.code << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->HandleEvent(*context.event);
		}

		_lastMousePos = sf::Vector2i(context.event->mouseMove.x, context.event->mouseMove.y);
		_mousePressed = true;
	}

	void TestControllerSystem::onPointSelectEnd(XE::ActionContext context)
	{
		std::cout << "onPointSelectEnd! " << context.event->key.code << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->HandleEvent(*context.event);
		}
		_mousePressed = false;
	}

	void TestControllerSystem::onResized(XE::ActionContext context)
	{
		// The XE::Event member variable called type has always the value XE::Event::Resized, as specified in the XE::Action
		// constructor. Since the Resize action has been triggered by an XE::Event (and not by a XE::Keyboard, XE::Mouse or
		// XE::Joystick), we can also be sure that context.event is no null pointer.
		///	XE::Event event = *context.event;

		//	mUIScreen->setSize(m_window->getSize().x,m_window->getSize().y);

		//KH needed??		mView.mRenderWindow->resize(event.size.width, event.size.height);
		//	ogreCamera->setAspectRatio(Ogre::Real(event.size.width) / Ogre::Real(event.size.height));

		// context.Window is a pointer to the sf::Window passed to the thor::ActionMap constructor.It can
		// be used for mouse input relative to a window, as follows:
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
		//	std::cout << "Shoot: " << thor::toString(mousePosition) << std::endl;

		mEngine.getGraphicsManager().resizeRenderWindow(context.window->getSize().x, context.window->getSize().y);

		entityx::ComponentHandle<TestControllerComponent> controller;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller)) {

			controller->_windowState.width = context.event->size.width;
			controller->_windowState.height = context.event->size.height;
			controller->_windowState.isDirty = true;
		}

		//KH todo ---		mEngine->getUIMgr().windowResized(mView.mRenderWindow);

		std::cout << "Resized!   New size = (" << context.event->size.width << ", " << context.event->size.height << ")" << std::endl;
		std::cout << "Resized!   New Screensize = (x:" << context.window->getSize().x << ",y: " << context.window->getSize().y << ")" << std::endl;
	}

	void TestControllerSystem::menuNav(XE::ActionContext context, TestControllerComponent& controller)
	{
		//switch (context.actionId)
		//{
		//case InputCmd::NavRight:

		////todo	mEngine->getUIMgr().makeNextItemOver();
		//	std::cout << "menuNav (NavRight)" << std::endl;
		//	break;
		//case InputCmd::NavLeft:

		//	//todo	mEngine->getUIMgr().makePrevItemOver();
		//	std::cout << "menuNav (NavLeft)" << std::endl;
		//	break;
		//case InputCmd::NavDown:

		//	//todo	mEngine->getUIMgr().selectOveredItem();
		//	std::cout << "menuNav (NavDown)" << std::endl;
		//	break;
		//
		//case InputCmd::NavUp:

		//		//todo	mEngine->getUIMgr().selectOveredItem();
		//		std::cout << "menuNav (NavUp)" << std::endl;
		//		break;
		//case InputCmd::NavEnter:

		//	//todo	mEngine->getUIMgr().selectOveredItem();
		//	std::cout << "menuNav (NavEnter)" << std::endl;
		//	break;
		//}

		//	MyEvent( 5 );
	}

	void TestControllerSystem::move(entityx::Entity entity)
	{
		entityx::ComponentHandle<XE::BodyComponent> body = entity.component<XE::BodyComponent>();
		entityx::ComponentHandle<TestControllerComponent> controller = entity.component<TestControllerComponent>();

		if (controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft))
			moveDirection.x = -1.0f;//left

		if (controller->actionmap.isActive(ControllerSettings::ActionType_Forward))
			moveDirection.z = 1.0f;//forward

		if (controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
			moveDirection.x = 1.0f; //right

		if (controller->actionmap.isActive(ControllerSettings::ActionType_Backward))
			moveDirection.z = -1.0f;//backward

		if (controller->actionmap.isActive(ControllerSettings::ActionType_TurnLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
		{
			if (entity.has_component<XE::BodyComponent>())
				entity.component<XE::BodyComponent>()->rotate(XE::Vector3::UNIT_Y, XE::Radian(_turn_speed));
			else // camera
				moveDirection.x = -1.0f;//left
		}
		else if (controller->actionmap.isActive(ControllerSettings::ActionType_TurnRight) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
		{
			if (entity.has_component<XE::BodyComponent>())
				entity.component<XE::BodyComponent>()->rotate(XE::Vector3::UNIT_Y, XE::Radian(-_turn_speed));
			else // camera
				moveDirection.x = 1.0f; //right
		}
	}

	void TestControllerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<TestControllerComponent> controller;

		for (entityx::Entity entity : es.entities_with_components(controller)) {

			if (controller->m_window)
				controller->actionmap.update(*controller->m_window); //clears events !!


			// Forward actions to callbacks: Invokes onResize() in case of Event::Resized events
			controller->actionmap.invokeCallbacks(controller->system, controller->m_window);

			move(entity);

			////only camera
			if (moveDirection != XE::Vector3::ZERO && entity.has_component<XE::CameraFreeComponent>())
			{
				entityx::ComponentHandle<XE::CameraFreeComponent> camera = entity.component<XE::CameraFreeComponent>();
				moveDirection.normalise();
				camera->getCameraNode().translate(moveDirection * 0.5);

				//	else
				//		LOG(INFO) << "camposx:" << camera->getCameraNode().getPosition().x << "camposy:" << camera->getCameraNode().getPosition().y << "camposz:" << camera->getCameraNode().getPosition().z;
			}


			moveDirection = XE::Vector3(0, 0, 0);

			//	moveDirection = Vector3(0,0,0);

				//if (mConsole)
				//	mConsole->update();

			if (entity.has_component<XE::ScreenComponent>())
			{
				if (controller->_windowState.isDirty)
				{
					controller->_windowState.isDirty = false;
					entity.component<XE::ScreenComponent>()->setSize(controller->_windowState.width, controller->_windowState.height);
				}

				entity.component<XE::ScreenComponent>()->mUIStateManager.update(dt);
				entity.component<XE::ScreenComponent>()->m_Desktop->Update(dt);
			}
		}
	}

} // namespace XE
