#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

ControllerState::ControllerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	LOG(XE::info) << "InitState - Initialization";

	auto ctrlSystem = engine.getScene().systems.add<XET::TestControllerSystem>(engine);

	engine.getScene().create(1);

	engine.getGraphicsManager().getGUIRenderer().loadAtlas("dbData/UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

	//create an empty entity for free style camera
	entityx::Entity entity = engine.getScene().entities.create();
	XE::BodyComponent* body = entity.assign<XE::BodyComponent>().get();
	XE::CameraRenderable* camRenderable = entity.assign<XE::CameraRenderable>(0, engine.getGraphicsManager(), engine.getScene()).get();
	XE::CameraFreeComponent* camera = entity.assign<XE::CameraFreeComponent>(*camRenderable, *body).get();

	XET::TestControllerComponent* ctrl = entity.assign<XET::TestControllerComponent>(0, engine, engine.getGraphicsManager().getWindow(), true).get();

	XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindow()).get(); //createScreen(); //workspace needed for screen
	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIDebug>(11, entity, true));
	//screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	LOG(XE::info) << "InitState - Initialized";
}

ControllerState::~ControllerState()
{

}

void ControllerState::update(float deltaTime)
{

}

void ControllerState::cleanup()
{
}

