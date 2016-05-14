#include "TestScene.hpp"

#include "TestControllerSystem.hpp"

#include  <XEngine.hpp>

//#include "../Systems/CharacterCameraSystem.hpp"
//#include "../Components/Character.hpp"
#include "Netmsg_generated.h"
//#include "../Systems/ServerSystem.hpp"
//#include "../DAL/DALHelper.hpp"

namespace XET {

TestScene::TestScene( XE::XEngine& engine)
	: XE::Scene(engine, engine.getIDAL(), engine.getGraphicsManager())
	, m_engine(engine)
{
	//XE::LuaEngine::loadFile(_state, "Scene/1_Scene.lua");
}

bool TestScene::createEntityType(entityx::Entity entity, char* entityData)
{
	bool deleteBufferInRenderThread = false;

	XE::Uint16 sceneID = 0; //TODO use as section ?? for large world

	const NetMsg::Entity* ent = flatbuffers::GetRoot< NetMsg::Entity>(entityData);
	//const NetMsg::Entity* ent = (const NetMsg::Entity*)entityData;
	for each (auto var in *ent->components())
	{
		auto test = var->comp_type();

		if (var->comp_type() == NetMsg::UComponent::UComponent_RenderableComponent) //message: editor -> server
		{
			//	std::cout << "XFBType::RenderableComponent -> netid: " << entityData->netid() << std::endl;

			if (entity.has_component<XE::Renderable>())
				updateRenderableComponent(m_engine, entity, sceneID, var->comp());
			else
				createRenderableComponent(m_engine, entity, sceneID, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_PhysicsComponent)  // messages: client <->server
		{
			const XFBType::PhysicsComponent* nodeMsg = (const XFBType::PhysicsComponent*)var->comp();
			//std::cout << "x: " << nodeMsg->transform()->loc()->x() << std::endl;

			if (entity.has_component<XE::PhysicsComponent>())
				updatePhysicsComponent(m_engine, entity, sceneID, var->comp());
			else
				createPhysicsComponent(m_engine, entity, sceneID, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_Node)  // messages: client <->server
		{
			const XFBType::Node* nodeMsg = (const XFBType::Node*)var->comp();
			std::cout << "x: " << nodeMsg->transform()->loc()->x() << std::endl;

			if (entity.has_component<XE::BodyComponent>())
				updateBodyComponent(m_engine, entity, var->comp());
			else
				createBodyComponent(m_engine, entity, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_SpawnPointComponent)  // messages: client <->server
		{
			const XFBType::SpawnPointComponent* nodeMsg = (const XFBType::SpawnPointComponent*)var->comp();

			if (entity.has_component<XE::SpawnPointComponent>())
				updateSpawnPointComponent(m_engine, entity, var->comp());
			else
				createSpawnPointComponent(m_engine, entity, var->comp());
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_Light)  // messages: client <->server
		{
			const XFBType::Light* light = (const XFBType::Light*)var->comp();

			if (entity.has_component<XE::LightRenderable>())
				updateLightComponent(m_engine, entity, var->comp());
			else
				createLightComponent(m_engine, entity, sceneID, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_AnimationComponent)  // messages: client <->server
		{
			const XFBType::AnimationComponent* animation = (const XFBType::AnimationComponent*)var->comp();

			if (entity.has_component<XE::AnimationComponent>())
				updateAnimationComponent(m_engine, entity, var->comp());
			else
				createAnimationComponent(m_engine, entity, var->comp());
		}
	}

	return deleteBufferInRenderThread;
}

void TestScene::update(float deltaTime)
{
	XE::Scene::update(deltaTime);
}

} // namespace XET
