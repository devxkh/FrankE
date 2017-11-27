#include "TestMenuState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestControllerSystem.hpp"
#include "../XETCommon/TestController.hpp"

#include "../DAL/Netmsg_generated.h"

#include "UIState_1.h"

#include <memory>
#include <iostream>


#include "../XETCommon/TestPostProcess.hpp"
#include <XERenderer/Resource/XEMesh.hpp>
#include <XERenderer/Resource/gltfAsset.h>


//TODO remove!!
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

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
	screenComp->mUIStateManager.get()->addUIState(screenComp->mUIStateManager.get()->build <XE::UIDebug>(NetMsg::UIStateId_Stats, entity, true));
//	screenComp->mUIStateManager.addUIState(screenComp->mUIStateManager.build <XE::UIConsole>(10, entity, true));//ctrl.createConsole();

	screenComp->mUIStateManager.get()->addUIState(screenComp->mUIStateManager.get()->build <UIState_1>(99, entity, true));//ctrl.createConsole();

	//XE::ScreenComponent* screenComp = entity.assign<XE::ScreenComponent>(*camRenderable, engine.getGraphicsManager().getWindowManager().getWindow(0)).get(); //createScreen(); //workspace needed for screen

	ctrlSystem->setBasicInputEvents(*ctrl);
	ctrl->setActionMap(*ctrl);

	m_engine.getGraphicsManager().getIntoRendererQueue().push([this, camRenderable]()
	{
		//XET::TestPostProcess pp(m_engine, *camRenderable);
		//	pp.createCustomTextures();

		m_engine.getResourceMgr()._t_initResourceGroup("TestGrp");

	//	pp.setupCompositor();
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

		gltf::Asset assetEmissive;
		gltf::load(m_engine.settings.resourceData.assetsFolder + "/DebugPack/material_ball/material_ball.gltf", assetEmissive);
		XE::XEMesh meshMaterialBall;
		meshMaterialBall.buildMesh(assetEmissive, "Ball 1", m_engine.getGraphicsManager(), m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr);

		{
			Ogre::Item* item{ nullptr };
			item = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->createItem(meshMaterialBall.m_ogreMesh, Ogre::SCENE_DYNAMIC);
			auto m_sceneNode = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			m_sceneNode->attachObject(item);
			item->setCastShadows(true);
			//do it at last! here the texture baking happens! needed for normal maps etc.
			if (meshMaterialBall.m_datablock)
				item->setDatablock(meshMaterialBall.m_datablock);

			m_sceneNode->setPosition(0, 10, 0);
			m_sceneNode->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1, 0, 0))); // needed for blender exported meshes!
		}

		{
			Ogre::Item* item{ nullptr };
			item = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->createItem(meshMaterialBall.m_ogreMesh, Ogre::SCENE_DYNAMIC);
			auto m_sceneNode = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			m_sceneNode->attachObject(item);
			item->setCastShadows(true);
			//do it at last! here the texture baking happens! needed for normal maps etc.

			Ogre::HlmsManager *hlmsManager = m_engine.getGraphicsManager().getRoot()->getHlmsManager();
			Ogre::HlmsUnlitDatablock* testdatablock = (Ogre::HlmsUnlitDatablock*)hlmsManager->getDatablock("BillBoardTest");
			testdatablock->setUseColour(true);
			testdatablock->setColour(Ogre::ColourValue(0, 1, 0, 1) * 1.5);

			item->setDatablock(testdatablock);

			m_sceneNode->setPosition(20, 10, 0);
			m_sceneNode->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1, 0, 0))); // needed for blender exported meshes!
		}

	});

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

