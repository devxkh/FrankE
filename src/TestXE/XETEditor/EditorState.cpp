#include "EditorState.hpp"


//#include <XEDebugger/UI/UIDebugState.h>

#include <memory>
#include <iostream>

void EditorState::createFrameListener(void)
{

}

EditorState::EditorState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	XE::LogManager::getSingleton().logMessage("InitState - Initialization");



	//--------------------------------------------------------
	//------------------ Light -------------------------------
	//--------------------------------------------------------
	//m_engine->getScene().getSceneMgr()->setAmbientLight(XE::ColourValue(0.5f, 0.5f, 0.5f));
	//XE::Light *light = m_engine->getScene().getSceneMgr()->createLight("MainLight");
	//light->setPosition(20.0f, 80.0f, 50.0f);

	//--------------------------------------------------------
	//--------------- CG Shader ------------------------
	//--------------------------------------------------------
	//XE::SHDR::CgProgramFactory* mCgProgramFactory;
	//// check for gles2 by the glsles factory (this plugin is not supported on embedded systems for now)
	//if (XE::HighLevelGpuProgramManager::getSingleton().isLanguageSupported("glsles") == false)
	//{
	//	// Create XE_NEW factory
	//	mCgProgramFactory = XE_NEW XE::SHDR::CgProgramFactory();
	//	// Register
	//	XE::HighLevelGpuProgramManager::getSingleton().addFactory(mCgProgramFactory);
	//	XE_NEW XE::SHDR::CgFxScriptLoader();
	//}
	//----------------- End CG Shader -------------------------------
	//SetResource();



	//--------------------------------------------------------
	//------------------ Controller -------------------------------
	//--------------------------------------------------------
	//XE::Controller& controller = m_engine->getCtrlMgr().getController(0);

//	m_engine->getScene().create(1); //test

//	XE::CharEntity*  charTest = new XE::CharEntity(1, m_engine->getGraphicsManager(), m_engine->getScene());
//	charTest->create(1);
	//controller->getUIStateMgr().addUIState(controller->getUIStateMgr().build <XE::UIDebug>(10, controller, true));

	//controller.createConsole();

	//--------------------------------------------------------
	//------------------ Controller -------------------------------
	//--------------------------------------------------------
//	XE::Controller* controller = m_engine->getCtrlMgr().getController(0);
	//mStateData->mUIStateManager.addUIState(mStateData->mUIStateManager.build <UI::UIInitGame>(UI::UISI_InitGame, controller, true));
//	controller->getUIStateMgr().addUIState(controller->getUIStateMgr().build <XE::UIDebug>(10, controller, true));
	//--------------------------------------------------------
	//------------------ Controller -------------------------------
	//--------------------------------------------------------
	//XE::Controller* controller = m_engine->getCtrlMgr().getController(0);
	//controller->getUIStateMgr().addUIState(controller->getUIStateMgr().build <XE::UIDebug>(10, controller, true));
	//controller->createConsole();


	//XE::CharEntity& entChar = (XE::CharEntity&)m_engine->getScene().getGameEntity(2);
	//controller->setCharEntity(entChar);
	//controller->getView().mCamera->setStyle(CA_CHARACTER);
	//controller->getView().mCamera->setTarget(entChar);

	//--------------------------------------------------------
	//Select Char
	//--------------------------------------------------------
	//XE::CharEntity* mChara = OGRE_NEW XE::CharEntity(1, &m_engine->getScene());
	//m_engine->getScene().addGameEntity(mChara);
	//controller->setCharEntity(*mChara);

	//controller->getView().mCamera->setStyle(CA_CHARACTER);
	//controller->getView().mCamera->setTarget(*mChara);

	//mChara->setPosition(Ogre::Vector3(0, 0, 70));

	//GameEntityProperties& props = mChara->getProperties();
	//props.m_physics.Object.shape() = SH_CAPSULE;
	//props.m_physics.Object.friction() = 1.0f;
	//props.m_physics.Object.restitution() = 0.0f; //for bouncing
	//props.m_physics.Object.colgroupmask() = btBroadphaseProxy::CharacterFilter;
	//props.m_physics.Object.colmask() = btBroadphaseProxy::DefaultFilter;
	//props.m_physics.Object.charjumpspeed() = 10;
	//props.m_physics.Object.charfallspeed() = 10;
	//props.m_physics.Object.charstepheight = 0.0f;
	////Attach physic Character
	////mStateData->mScene->getDynamicsWorld()->destroyObject(mChara->getPhysicsController());

	//gkCharacter* character = m_engine->getScene().getDynamicsWorld()->createCharacter(mChara);
	//mChara->attachCharacterPhysics(character);
	////	character->setGravity(-20);
	////	character->setFallSpeed(-10);
	//Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_NORMAL, "Attached Character Physics... ", true);

	//--------------------------------------------------------


	// create the builtin resource group
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(GK_BUILTIN_GROUP);

	//	controller->getView().mCamera->setPivotPosition(XE::Vector3f(0, 1, 0)); //fixed camera


	XE::LogManager::getSingleton().logMessage("InitState - Initialized");
}

EditorState::~EditorState()
	{

		//mStateData->mUIManager.des
	}

	void EditorState::SetResource(){

		XE::ConfigFile cf;
		cf.load("E:\\Projekte\\coop\\XEngine\\data\\Test\\XETController\\resources.cfg", "\t:=", true);

		XE::ConfigFile::SectionIterator seci = cf.getSectionIterator();
		Ogre::String secName, typeName, archName;
		Ogre::String sec, type, arch;

		// go through all specified resource groups
		while (seci.hasMoreElements())
		{
			sec = seci.peekNextKey();
			XE::ConfigFile::SettingsMultiMap* settings = seci.getNext();
			XE::ConfigFile::SettingsMultiMap::iterator i;

			// go through all resource paths
			for (i = settings->begin(); i != settings->end(); i++)
			{
				type = i->first;
				arch = i->second;

//#if XE_PLATFORM == XE_PLATFORM_APPLE || XE_PLATFORM == XE_PLATFORM_APPLE_IOS
//				// OS X does not set the working directory relative to the app,
//				// In order to make things portable on OS X we need to provide
//				// the loading with it's own bundle path location
//				if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
//					arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
//#endif
				XE::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}


		lNameOfResourceGroup = "General";
		{
			XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();

			lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
			lRgMgr.loadResourceGroup(lNameOfResourceGroup);

			// Create XE_NEW factory
			//XE::AL::SoundFactory* mOgreOggSoundFactory = XE_NEW_T(XE::AL::SoundFactory, MEMCATEGORY_GENERAL)();
			//mStateData->mRoot->addMovableObjectFactory(mOgreOggSoundFactory, true);

			//XE::AL::SoundManager* mOgreOggSoundManager = XE_NEW_T(XE::AL::SoundManager, MEMCATEGORY_GENERAL)();

			//if (XE::AL::SoundManager::getSingletonPtr()->init("",100,100,mStateData->mScene->getSceneMgr()))
			//{
			//	// Create a streamed sound, no looping, no prebuffering
			//	if (XE::AL::SoundManager::getSingletonPtr()->createSound("Sound1", "electricspark.ogg", false, false, false,mStateData->mScene->getSceneMgr()) )
			//	{
			//		
			//	}
			//}

			//geladene Materialien abfragen
			/*XE::ResourceManager::ResourceMapIterator materialIterator = XE::MaterialManager::getSingleton().getResourceIterator();
			while (materialIterator.hasMoreElements())
			{
			std::cout << "MaterialLoaded:" << (static_cast<XE::MaterialPtr>(materialIterator.peekNextValue()))->getName() << std::endl;
			materialIterator.moveNext();
			} */

			////bullet and heightmap
			////http://www.ogre3d.org/forums/viewtopic.php?f=2&t=60354

			////load mesh into bullet - example usage
			////http://www.ogre3d.org/forums/viewtopic.php?f=5&t=68588
			////http://www.ogre3d.org/tikiwiki/BulletMeshStrider

		}

		//_----------------------------------------
		//cube entity
		//------------------------------------------------------
		//XE::Entity* entity = mStateData->mScene->getSceneMgr()->createEntity("c_k", "Cube.mesh", "General");
		//XE::SceneNode *entNode = mStateData->mScene->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		//entNode->attachObject(entity);

		//entNode->setPosition(0,50,0);
		//XE::GameEntity* cubeEnt = new XE::GameEntity(5, mStateData->mScene);
		//cubeEnt->setEntity(entity);
		//cubeEnt->setSceneNode(entNode);

		//GameEntityProperties& props = cubeEnt->getProperties();
		//props.m_physics.Object.type = GK_RIGID;
		//props.m_physics.Object.shape = SH_BOX;
		//props.m_physics.Object.mass = 1;
		//props.m_physics.Object.friction = 0.6f;
		//props.m_physics.Object.restitution = 0.6f; //for bouncing

		//mStateData->mScene->getDynamicsWorld()->createRigidBody(cubeEnt); //->createRigidBody(test);
		//_----------------------------------------

		//collision plane
		lNameOfResourceGroup = "General";
		{
			//---------------------------------------------------
			//House
			//------------------------------------------------------
			//XE::Entity* test = mStateData->mScene->getSceneMgr()->createEntity("test", "Geoset_0_1_tex_1.mesh", lNameOfResourceGroup);
			//XE::SceneNode* lNode = mStateData->mScene->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
			//XE::GameEntity* staticHouseEnt = new XE::GameEntity(7, mStateData->mScene);
			//staticHouseEnt->setEntity(test);

			//lNode->attachObject(test);

			//lNode->scale(0.5, 0.5, 0.5);
			//XE::Quaternion rot(XE::Degree(90), Ogre::Vector3::UNIT_X);
			//lNode->rotate(rot);
			//staticHouseEnt->setSceneNode(lNode); //sonst collisionshape rot falsch!!

			//GameEntityProperties& props = staticHouseEnt->getProperties();
			//props.m_physics.m_type = GK_STATIC;
			//props.m_physics.m_shape = SH_GIMPACT_MESH;
			//props.m_physics.m_mass = 0;
			//props.m_physics.m_friction = 1.0f;
			//props.m_physics.m_restitution = 0.6f; //for bouncing
			//gkRigidBody* hRB = mStateData->mScene->getDynamicsWorld()->createRigidBody(staticHouseEnt);
			//---------------------------------------------------

			//_----------------------------------------
			// create a floor mesh resource
			//------------------------------------------------------
			//XE::MeshManager::getSingleton().createPlane("floor", lNameOfResourceGroup,
			//	XE::Plane(Ogre::Vector3::UNIT_Y, -1), 250, 250, 25, 25, true, 1, 15, 15, Ogre::Vector3::UNIT_Z);

			//// create a floor entity, give it a material, and place it at the origin
			//XE::Entity* floor = mStateData->mScene->getSceneMgr()->createEntity("Floor", "floor", lNameOfResourceGroup);
			//floor->setMaterialName("Examples/Rockwall", lNameOfResourceGroup);
			//floor->setCastShadows(false);
			//mStateData->mScene->getSceneMgr()->getRootSceneNode()->attachObject(floor);


			//XE::GameEntity* staticPlaneEnt = new XE::GameEntity(6, mStateData->mScene);
			//staticPlaneEnt->setEntity(floor);
			//GameEntityProperties& SPprops = staticPlaneEnt->getProperties();
			//SPprops.m_physics.m_type = GK_STATIC;
			//SPprops.m_physics.m_shape = SH_PLANE;
			//SPprops.m_physics.m_mass = 0;
			//SPprops.m_physics.m_friction = 1.0f;
			//SPprops.m_physics.m_restitution = 0.6f; //for bouncing
			//gkRigidBody* con = mStateData->mScene->getDynamicsWorld()->createRigidBody(staticPlaneEnt);
			//_----------------------------------------


			//------------------------------------------------------
			// Terrain
			//------------------------------------------------------
//KH todo ####			DotSceneLoader* mLoader = new DotSceneLoader();
		//	mLoader->parseDotScene("SampleScene3.scene", lNameOfResourceGroup, mStateData->mScene->getSceneMgr());//, attach);
			//KH todo ####				mLoader->parseDotScene("Map_1.scene", lNameOfResourceGroup, m_engine->getScene().getSceneMgr());//, attach);

			//mTerrainImported = true;

			//---------------------------------------------------------------------
			//KH Fix -> http://www.ogre3d.org/forums/viewtopic.php?f=5&t=58474
			//KH todo ####				mTerrainGroup = mLoader->getTerrainGroup();
			//KH todo ####				mTerrainGroup->setOrigin(Ogre::Vector3(0, -25, 0)); //old -175
			//-------------------------------------------------------------------
			//KH todo ####			if (!mTerrainGroup)
			//KH todo ####				std::cout << "##--TerrainGroup not found";


			//KH todo ####		m_engine->getScene().setTerrain(mTerrainGroup);

			//KH todo ####		PhysTerrain* resp = m_engine->getScene().getDynamicsWorld()->createTerrain(mTerrainGroup, nullptr, nullptr);
			//KH todo ####		gkPhysicsProperties& TPprops = resp->getProperties();
			//------------------------------------------------------

			//obj->attachRigidBody(con);
		}
		//cube collision hinzufügen
		/*btBoxShape *sceneCubeShape = new btBoxShape(btVector3(1, 1, 1));

		defaultBody->setShape(entNode, sceneCubeShape, gDynamicBodyRestitution, gDynamicBodyFriction,
		gDynamicBodyMass, XE::Vector3f(0, 50, 50), XE::Quaternion(0, 0, 0, 1));
		defaultBody->showDebugShape(true);*/


		//m_engine->getRoot()->clearEventTimes();
	}

	void EditorState::update(float deltaTime)
	{
		//window.setMouseCursorVisible(false); // Hide cursor
		//if (!m_breaked)
		//	m_engine->getCtrlMgr().update(); //update Controller

		//if (!m_breaked)
		//{
		//	//	if(mStateData->mUIStateMgr->running())
		//	//		mStateData->mUIStateMgr->update();//update UI States

		//	m_engine->getCtrlMgr().updateRenderWindow();

		//	m_engine->getRoot()->renderOneFrame();
		//	//	XE::WindowEventUtilities::messagePump(); //dont use it or .net wrapper crash!
		//}
	}

	void EditorState::cleanup()
	{
		// Let's cleanup!
		{
			//mStateData->mUIManager.destroyScreen("WorldState");

			//m_engine->getRoot()->removeFrameListener(this);


			//XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();
			//lRgMgr.destroyResourceGroup(lNameOfResourceGroup);
		}
	}

