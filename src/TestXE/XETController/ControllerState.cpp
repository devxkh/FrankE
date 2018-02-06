#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

#include "../XETCommon/TestPostProcess.hpp"

#include "../DAL/Netmsg_generated.h"

#include <XERenderer/Resource/XEMesh.hpp>
#include <XERenderer/Resource/gltfAsset.h>


//TODO remove!!
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

#ifdef CompileEditor
#include <XEngine/Editor/EntityViewerUIState.hpp>
#include <XEngine/Editor/SceneViewerUIState.hpp>
#include <XEngine/Editor/GizmoUIState.hpp>
#include "../XETCommon/EditorControllerSystem.hpp"
#include <XERenderer/Editor/CompositorUIState.hpp>
#endif

ControllerState::ControllerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)

#ifdef CompileEditor	
	, m_EntityViewerUIState(nullptr)
#endif

{
	LOG(XE::info) << "InitState - Initialization";

	auto ctrlSystem = engine.getScene().systems.add<XET::TestControllerSystem>(engine);
	auto spawnSystem = engine.getScene().systems.add<XE::SpawnSystem>(engine.getScene());

#ifdef CompileEditor	
	auto editorSystem = engine.getScene().systems.add<XET::EditorControllerSystem>(engine);
#endif

	engine.getScene().create(1);
	XE::FileResource fres;
	engine.getResourceMgr().getBufferFromFile("dbData/UI/TestAtlas.fbbin", fres);
	engine.getGraphicsManager().getGUIRenderer().loadAtlas(fres.buffer); // "dbData/UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

	//create an empty entity for free style camera
	entityx::Entity entity = engine.getScene().entities.create();
	XE::BodyComponent* body = entity.assign<XE::BodyComponent>().get();
	XE::CameraRenderable* camRenderable = entity.assign<XE::CameraRenderable>(0, engine.getGraphicsManager(), engine.getScene()).get();
	XE::CameraFreeComponent* camera = entity.assign<XE::CameraFreeComponent>(*camRenderable, *body).get();
	

	body->setPosition(0, 10, 20);

	XET::TestControllerComponent* ctrl = entity.assign<XET::TestControllerComponent>(0, engine, engine.getGraphicsManager().getWindow(), true).get();

	XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindow()).get(); //createScreen(); //workspace needed for screen
	screenComp->mUIStateManager.get()->addUIState(screenComp->mUIStateManager.get()->build <XE::UIDebug>(NetMsg::UIStateId_Stats, entity, true));
	//screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	//create helmet entity
	entityx::Entity entityHelmet = m_engine.getScene().entities.create();

	XE::EditorComponent* editorComponent = entityHelmet.assign<XE::EditorComponent>().get();
	XE::Renderable* renderable = entityHelmet.assign<XE::Renderable>(m_engine.getGraphicsManager(), m_engine.getScene(), nullptr).get();
	XE::BodyComponent* bodyHelmet = entityHelmet.assign<XE::BodyComponent>().get();
	bodyHelmet->setPosition(0, 10, 0);
//	bodyHelmet->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1, 0, 0)));
	bodyHelmet->isSelected = true;
	editorComponent->id = 999;
	editorComponent->name = "Helmet";

	m_engine.getGraphicsManager().getIntoRendererQueue().push([this,camRenderable, renderable]()
	{
		camRenderable->m_XECompositor.setup();

#ifdef CompileEditor	
		m_engine.getGraphicsManager().getGUIRenderer()._t_initEditorUIRenderer(camRenderable->_t_OgreCameraPtr);

		std::unique_ptr<XE::SceneViewerUIState> p1(new XE::SceneViewerUIState(m_engine.getGraphicsManager(), m_engine.getScene()));
		p1->ID = XE::EUSID::SceneHierarchy;
		m_engine.getGraphicsManager().getGUIRenderer()._t_EditorUIRenderer->createUIState(std::move(p1));
		
		//default Editor ui 
		std::unique_ptr<XE::GizmoUIState> p2(new XE::GizmoUIState(m_engine.getScene(), m_engine.getGraphicsManager(), camRenderable->_t_OgreCameraPtr));
		p2->ID = XE::EUSID::Gizmo;
		m_engine.getGraphicsManager().getGUIRenderer()._t_EditorUIRenderer->createUIState(std::move(p2));

		//Compositor Editor UI
		std::unique_ptr<XE::CompositorUIState> p3(new XE::CompositorUIState(m_engine.getGraphicsManager(), camRenderable->m_XECompositor));
		p3->ID = XE::EUSID::Compositor;
		m_engine.getGraphicsManager().getGUIRenderer()._t_EditorUIRenderer->createUIState(std::move(p3));


		//Entity Editor UI
		std::unique_ptr<XE::EntityViewerUIState> p4(new XE::EntityViewerUIState(m_engine.getGraphicsManager(), m_engine.getScene()));
		p4->ID = XE::EUSID::EntityObject;
		m_EntityViewerUIState = p4.get();
		m_engine.getGraphicsManager().getGUIRenderer()._t_EditorUIRenderer->createUIState(std::move(p4));

#endif

		//## 	XET::TestPostProcess pp(m_engine, *camRenderable);
	//	pp.createCustomTextures();
		

//		m_engine.getResourceMgr()._t_initResourceGroup("TestGrp"); //needed for xecompositor
		

		//## 	pp.setupCompositor();
//		pp.togglePostprocess("Bloom");

		//load gltf
	//	gltf::Asset asset;
	//	//gltf::load("F:/Projekte/coop/XGame/data/assets/Impact/impact_ground_1.gltf", asset);
	////gltf::load("F:/Projekte/coop/FrankE/data/assets/DamagedHelmet/DamagedHelmet.gltf", asset);
	//	gltf::load("F:/Projekte/coop/XGame/data/assets/Turricane/turicane_blendshapes.gltf", asset);
	//	//	gltf::load("F:/Projekte/coop/glTF-Sample-Models/2.0/AnimatedMorphCube/glTF/AnimatedMorphCube.gltf", asset);
	////gltf::load("F:/Projekte/coop/glTF-Sample-Models/2.0/DamagedHelmet/glTF/DamagedHelmet.gltf", asset);

	//	XE::XEMesh mesh;
	//	mesh.buildMesh(asset, m_engine.getGraphicsManager(), m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr);

		//{
		//	gltf::Asset assetEmissive;
		//	gltf::load("F:/Projekte/coop/XGame/_devFolder/Test/scene.gltf", assetEmissive);
		//		XE::XEMesh meshMaterialBall;
		//	meshMaterialBall.buildMesh(assetEmissive, "SHuman 1", m_engine.getGraphicsManager(), m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr);

		//	{
		//		Ogre::Item* item{ nullptr };
		//		item = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->createItem(meshMaterialBall.m_ogreMesh, Ogre::SCENE_DYNAMIC);
		//		auto m_sceneNode = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		//		m_sceneNode->attachObject(item);
		//		item->setCastShadows(true);
		//		//do it at last! here the texture baking happens! needed for normal maps etc.
		//		if (meshMaterialBall.m_datablock)
		//			item->setDatablock(meshMaterialBall.m_datablock);

		//		m_sceneNode->setPosition(0,110, 30);
		//		m_sceneNode->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(1, 0, 0))); // needed for blender exported meshes!
		//	}
		//}

		gltf::Asset assetEmissive;
		//gltf::load(m_engine.settings.resourceData.assetsFolder + "/DebugPack/material_ball/material_ball.gltf", assetEmissive);
		gltf::load(m_engine.settings.resourceData.assetsFolder + "/DamagedHelmet/DamagedHelmet.gltf", assetEmissive);
		XE::XEMesh meshMaterialBall;
		meshMaterialBall.buildMesh(assetEmissive, "Ball 1", m_engine.getGraphicsManager(), m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr);
		
		{
			renderable->_t_OgreItemPtr = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->createItem(meshMaterialBall.m_ogreMesh, Ogre::SCENE_DYNAMIC);
			renderable->_t_OgreItemPtr->setCastShadows(true);
			
			//do it at last! here the texture baking happens! needed for normal maps etc.
			if (meshMaterialBall.m_datablock)
				renderable->_t_OgreItemPtr->setDatablock(meshMaterialBall.m_datablock);
			
			renderable->_t_OgreEntitySceneNodePtr->attachObject(renderable->_t_OgreItemPtr);	

		//	renderable->setVisibility(true);
			//without setVisibilityFlags -> item is not visible in release mode!!??
			renderable->_t_OgreItemPtr->setVisibilityFlags(0x000000001); // 0x000000001);


		//	renderable->_t_OgreEntitySceneNodePtr->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1, 0, 0))); // needed for blender exported meshes!
		}

		//////{
		//////	Ogre::Item* item{ nullptr };
		//////	item = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->createItem(meshMaterialBall.m_ogreMesh, Ogre::SCENE_DYNAMIC);
		//////	auto m_sceneNode = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		//////	m_sceneNode->attachObject(item);
		//////	item->setCastShadows(true);
		//////	//do it at last! here the texture baking happens! needed for normal maps etc.

		//////	Ogre::HlmsManager *hlmsManager = m_engine.getGraphicsManager().getRoot()->getHlmsManager();
		//////	Ogre::HlmsUnlitDatablock* testdatablock = (Ogre::HlmsUnlitDatablock*)hlmsManager->getDatablock("BillBoardTest");
		//////	testdatablock->setUseColour(true);
		//////	testdatablock->setColour(Ogre::ColourValue(0, 1, 0, 1) * 1.5);

		//////	item->setDatablock(testdatablock);

		//////	m_sceneNode->setPosition(20, 10, 0);
		//////	m_sceneNode->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1, 0, 0))); // needed for blender exported meshes!
		//////}

	});

	LOG(XE::info) << "InitState - Initialized";
}

ControllerState::~ControllerState()
{

}

#ifdef CompileEditor	
static uint64_t lastSelected;
static Ogre::Light* selectedLight;
static XE::RenderableType selectedType;
#endif

void ControllerState::update(float deltaTime)
{

#ifdef CompileEditor	


	entityx::ComponentHandle<XE::BodyComponent> body;

	for (entityx::Entity entity : m_engine.getScene().entities.entities_with_components(body)) {

		auto debug = body->getPosition();
		if (body->isSelected && lastSelected != entity.id().id())
		{
			lastSelected = entity.id().id();
			selectedType = XE::RenderableType::RT_None;
			selectedLight = nullptr;

			if (entity.has_component<XE::LightRenderable>())
			{
				entityx::ComponentHandle<XE::LightRenderable> lightRenderable = entity.component<XE::LightRenderable>();
				selectedLight = lightRenderable->_t_light;
				selectedType = XE::RenderableType::RT_LightRenderable;
			}

			m_engine.getGraphicsManager().getIntoRendererQueue().push([this]()
			{
				if (m_EntityViewerUIState)
					m_EntityViewerUIState->components.clear();

				if (m_EntityViewerUIState && selectedType == XE::RenderableType::RT_LightRenderable)
				{
					std::unique_ptr<XE::RenderableComponent> p1(new XE::RenderableComponent);
					p1->renderableType = XE::RenderableType::RT_LightRenderable;
					p1->_t_light = selectedLight;
					m_EntityViewerUIState->components.push_back(std::move(p1));
				}
			});
		}
	};
#endif

}

void ControllerState::cleanup()
{
}

