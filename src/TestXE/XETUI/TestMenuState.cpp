#include "TestMenuState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

#include "UIState_1.h"

#include <memory>
#include <iostream>

TestMenuState::TestMenuState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	LOG(plog::info) << "InitState - Initialization";

	auto ctrlSystem = engine.getScene().systems.add<XET::TestControllerSystem>(engine);
	
	engine.getScene().create(1);

	if (!engine.getGraphicsManager().getGUIRenderer().loadAtlas("dbData/UI/TestAtlas.fbbin"))
		return;
	
	//create an empty entity for free style camera
	entityx::Entity entity = engine.getScene().entities.create();
	XE::BodyComponent* body = entity.assign<XE::BodyComponent>().get();
	XE::CameraRenderable* camRenderable = entity.assign<XE::CameraRenderable>(0, engine.getGraphicsManager(), engine.getScene()).get();
	XE::CameraFreeComponent* camera = entity.assign<XE::CameraFreeComponent>(*camRenderable, *body).get();
	
	body->setPosition(0,10,0);

	XET::TestControllerComponent* ctrl = entity.assign<XET::TestControllerComponent>(0,engine,  engine.getGraphicsManager().getWindow(), true).get();

	XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindow()).get(); //createScreen(); //workspace needed for screen
	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIDebug>(11, entity, true));
//	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

//	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <UIState_1>(1, entity, true));//ctrl.createConsole();

	//XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindowManager().getWindow(0)).get(); //createScreen(); //workspace needed for screen

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	LOG(XE::info) << "InitState - Initialized";
}

TestMenuState::~TestMenuState()
{

}

void TestMenuState::update(float deltaTime)
{

}

void TestMenuState::cleanup()
{

}

