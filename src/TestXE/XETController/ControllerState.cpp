#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

#include <memory>
#include <iostream>

#include "TestScene.h"

ControllerState::ControllerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	LOG(INFO) << "InitState - Initialization";

	auto ctrlSystem = engine.getScene().systems.add<XET::TestControllerSystem>(engine);

	engine.getLua().loadScene(1);

	engine.getGraphicsManager().getGUIRenderer().loadAtlas("UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

	//create an empty entity for free style camera
	entityx::Entity entity = engine.getScene().entities.create();
	XE::CameraRenderable* camRenderable = entity.assign<XE::CameraRenderable>(0, engine.getGraphicsManager(), engine.getScene()).get();
	XE::CameraFreeComponent* camera = entity.assign<XE::CameraFreeComponent>(*camRenderable).get();

	XET::TestControllerComponent* ctrl = entity.assign<XET::TestControllerComponent>(0, engine, engine.getGraphicsManager().getWindowManager().getWindow(0), true).get();

	auto wnd = engine.getGraphicsManager().getWindowManager().getWindow(0);
	XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, wnd->getSize().x, wnd->getSize().y).get(); //createScreen(); //workspace needed for screen
	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIDebug>(11, entity, true));
	//screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	LOG(INFO) << "InitState - Initialized";
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

