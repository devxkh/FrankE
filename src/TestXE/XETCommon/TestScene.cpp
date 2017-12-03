#include "TestScene.hpp"

#include "TestControllerSystem.hpp"

#include  <XEngine.hpp>
#include "Netmsg_generated.h"


#ifdef CompileEditor	
#include <XEngine/Editor/SceneViewerUIState.hpp>
#endif

namespace XET {

TestScene::TestScene( XE::XEngine& engine)
	: XE::Scene(engine, engine.getDAL(), engine.getGraphicsManager())
	, m_engine(engine)
{
	//m_engine.getLua().loadFile("Scene/1_Scene.lua");
}

void TestScene::loadRendererResources()
{
	//load all materials before scene load -> for ogre3D
	//TODO replace ogre resource loading with on demand async loading ....

	mGraphicsManager.getIntoRendererQueue().push([this]() {

		//	Ogre::ArchiveFactory *fac = new PhysFS::PhysFSArchiveFactory;
		//		Ogre::ArchiveManager::getSingleton().addArchiveFactory(fac);

		//------------------- basic stuff always needed ---------------------
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/2.0/scripts/Compositors", "General", true, true);
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/2.0/scripts/materials/Common", "General", true, true);
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/2.0/scripts/materials/Common/GLSL", "General", true, true);
		//debugging
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/DebugPack/material_ball", "General", true, true);

		// test 
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/DamagedHelmet", "General", true, true);
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/Test", "General", true, true);
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/TestTextures", "General", true, true);

		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/2.0/scripts/Postprocessing", "TestGrp", true, true);
		m_engine.getResourceMgr()._t_addLocationForRender(m_engine.settings.dataRootFolder + "/assets/Editor", "Editor", true, true);

		const char *c_locations[7] =
		{
			"/2.0/scripts/materials/TutorialSky_Postprocess",
			"/2.0/scripts/materials/Postprocessing",
			"/2.0/scripts/materials/Postprocessing/GLSL",
			//	"/2.0/scripts/materials/Postprocessing/HLSL",
			//	"/2.0/scripts/materials/Postprocessing/Metal",
			"/2.0/scripts/materials/Postprocessing/SceneAssets",

			"/2.0/scripts/materials/HDR",
			"/2.0/scripts/materials/HDR/GLSL",
			//"/2.0/scripts/materials/HDR/HLSL",
			//"/2.0/scripts/materials/HDR/Metal",
			"/2.0/scripts/materials/PbsMaterials"
		};


		for (size_t i = 0; i<7; ++i)
		{
			Ogre::String dataFolder = m_engine.settings.resourceData.assetsFolder + c_locations[i];
			m_engine.getResourceMgr()._t_addLocationForRender(dataFolder, "General");
		}

		m_engine.getResourceMgr()._t_initResourceGroup("General");
	});
}

bool TestScene::createEntityType(entityx::Entity entity, void* entityData)
{
	bool deleteBufferInRenderThread = false;

	XE::Uint16 sceneID = 0; //TODO use as section ?? for large world

	const NetMsg::Entity* ent = flatbuffers::GetRoot< NetMsg::Entity>(entityData);

	if (!ent->components())
		return false;

#ifdef CompileEditor	
	XE::EditorComponent* editorComponent;
	if (entity.has_component<XE::Renderable>())
		editorComponent = entity.component<XE::EditorComponent>().get();
	else
		editorComponent = entity.assign<XE::EditorComponent>().get();

	editorComponent->id = ent->entityID();
	editorComponent->name = ent->name()->c_str();
#endif

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
		else if (var->comp_type() == NetMsg::UComponent::UComponent_SpawnComponent)  // messages: client <->server
		{
			const XFBType::SpawnComponent* nodeMsg = (const XFBType::SpawnComponent*)var->comp();

			if (entity.has_component<XE::SpawnComponent>())
				updateSpawnComponent(entity, var->comp());
			else
				createSpawnComponent(entity, var->comp());
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
