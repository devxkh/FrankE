#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

#include "../DAL/Netmsg_generated.h"

#include <XERenderer/Resource/XEMesh.hpp>
#include <XERenderer/Resource/gltfAsset.h>

ControllerState::ControllerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	LOG(XE::info) << "InitState - Initialization";

	auto ctrlSystem = engine.getScene().systems.add<XET::TestControllerSystem>(engine);
	auto spawnSystem = engine.getScene().systems.add<XE::SpawnSystem>(engine.getScene());

	engine.getScene().create(1);

	engine.getGraphicsManager().getGUIRenderer().loadAtlas("dbData/UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

	//create an empty entity for free style camera
	entityx::Entity entity = engine.getScene().entities.create();
	XE::BodyComponent* body = entity.assign<XE::BodyComponent>().get();
	XE::CameraRenderable* camRenderable = entity.assign<XE::CameraRenderable>(0, engine.getGraphicsManager(), engine.getScene()).get();
	XE::CameraFreeComponent* camera = entity.assign<XE::CameraFreeComponent>(*camRenderable, *body).get();

	body->setPosition(0, 10, 0);

	XET::TestControllerComponent* ctrl = entity.assign<XET::TestControllerComponent>(0, engine, engine.getGraphicsManager().getWindow(), true).get();

	XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindow()).get(); //createScreen(); //workspace needed for screen
	screenComp->mUIStateManager.get()->addUIState(screenComp->mUIStateManager.get()->build <XE::UIDebug>(NetMsg::UIStateId_Stats, entity, true));
	//screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	m_engine.getGraphicsManager().getIntoRendererQueue().push([this]()
	{
		//load gltf
		gltf::Asset asset;
		gltf::load("F:/Projekte/coop/FrankE/data/assets/DamagedHelmet/DamagedHelmet.gltf", asset);
		//gltf::load("F:/Projekte/coop/glTF-Sample-Models/2.0/DamagedHelmet/glTF/DamagedHelmet.gltf", asset);

		XE::XEMesh mesh;
		mesh.buildMesh(asset, m_engine.getGraphicsManager(), m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr);



	});

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

