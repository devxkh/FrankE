#ifndef __TestControllerSystem_HPP__
#define __TestControllerSystem_HPP__

#include <XEngine.hpp>

#include "TestController.hpp"

namespace XE
{
	class GraphicsManager;
	class OgreConsole;
	class XEngine;
}

namespace XET {

	//class ControllerComponent;


	class TestControllerSystem : public entityx::System < TestControllerSystem >
	{
	public:

		TestControllerSystem(XE::XEngine& engine);

		~TestControllerSystem();

		void createConsole();


		void setBasicInputEvents(TestControllerComponent& controller);

		virtual void onPointMoved(XE::ActionContext context);
		virtual void onPointSelectStart(XE::ActionContext context);
		virtual void onPointSelectEnd(XE::ActionContext context);
		virtual void onResized(XE::ActionContext context);
		virtual void onKeyPressed(XE::ActionContext context);
		virtual void onTextEntered(XE::ActionContext context);
		virtual void onQuit();	
		virtual void menuNav(XE::ActionContext context, TestControllerComponent& controller);

		//realtime action
		virtual void move(entityx::Entity entity);
	
		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

		inline XE::XEngine& getEngine() { return mEngine; }

		void createRayLine();

	private:

		const std::string m_atlasName = "XEngine";
		float _turn_speed;
		float _zoom_speed;
		XE::XEngine& mEngine;

		bool mDecalDestroy;
		sf::Vector2i mMousePos;

		sf::Vector2i _lastMousePos;
		bool _mousePressed;
		XE::Vector3 moveDirection; // pro Frame auf null setzen 
	};

} // namespace XE

#endif //__TestControllerSystem_HPP__

