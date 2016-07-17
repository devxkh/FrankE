#include "TestScene.hpp"

#include "TestControllerSystem.hpp"

#include  <XEngine.hpp>
#include "Netmsg_generated.h"

namespace XET {

TestScene::TestScene( XE::XEngine& engine)
	: XE::Scene(engine, engine.getDAL(), engine.getGraphicsManager())
	, m_engine(engine)
{
	//m_engine.getLua().loadFile("Scene/1_Scene.lua");
}

bool TestScene::createEntityType(entityx::Entity entity, void* entityData)
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
			//	LOG(plog::info) << "XFBType::RenderableComponent -> netid: " << entityData->netid();

			if (entity.has_component<XE::Renderable>())
				updateRenderableComponent(entity, sceneID, var->comp());
			else
				createRenderableComponent(entity, sceneID, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_PhysicsComponent)  // messages: client <->server
		{
			const XFBType::PhysicsComponent* nodeMsg = (const XFBType::PhysicsComponent*)var->comp();
			
			//LOG(plog::info) << "x: " << nodeMsg->transform()->loc()->x();

			if (entity.has_component<XE::PhysicsComponent>())
				updatePhysicsComponent(entity, sceneID, var->comp());
			else
				createPhysicsComponent(entity, sceneID, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_BodyComponent)  // messages: client <->server
		{
			const XFBType::BodyComponent* nodeMsg = (const XFBType::BodyComponent*)var->comp();
			std::cout << "x: " << nodeMsg->position()->x() << std::endl;

			if (entity.has_component<XE::BodyComponent>())
				updateBodyComponent(entity, var->comp());
			else
				createBodyComponent(entity, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_SpawnPointComponent)  // messages: client <->server
		{
			const XFBType::SpawnPointComponent* nodeMsg = (const XFBType::SpawnPointComponent*)var->comp();

			if (entity.has_component<XE::SpawnPointComponent>())
				updateSpawnPointComponent(entity, var->comp());
			else
				createSpawnPointComponent(entity, var->comp());
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_Light)  // messages: client <->server
		{
			const XFBType::Light* light = (const XFBType::Light*)var->comp();

			if (entity.has_component<XE::LightRenderable>())
				updateLightComponent(entity, var->comp());
			else
				createLightComponent(entity, var->comp());

			deleteBufferInRenderThread = true;
		}
		else if (var->comp_type() == NetMsg::UComponent::UComponent_AnimationComponent)  // messages: client <->server
		{
			const XFBType::AnimationComponent* animation = (const XFBType::AnimationComponent*)var->comp();

			if (entity.has_component<XE::AnimationComponent>())
				updateAnimationComponent(entity, var->comp());
			else
				createAnimationComponent(entity, var->comp());
		}
	}

	return deleteBufferInRenderThread;
}

void TestScene::update(float deltaTime)
{
	XE::Scene::update(deltaTime);
}

} // namespace XET
