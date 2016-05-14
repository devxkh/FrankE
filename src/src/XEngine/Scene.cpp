#include <XEngine/Scene.hpp>

#include <XEDAL/IDAL.hpp>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <XEngine/Components/PhysicsComponents.hpp>
#include <XEngine/Components/SpawnPoint.hpp>

#include <XEngine/Systems/RenderBodySystem.hpp>
#include <XEngine/Systems/PhysicsSystem.hpp>
#include <XEngine/Systems/FreeLookCameraSystem.hpp>
#include <XEngine/Systems/EntityRenderSystem.hpp>
#include <XEngine/Systems/SpawnSystem.hpp>
#include <XEngine/Systems/UISystem.hpp>

#include <XERenderer/StaticRenderable.hpp>

#include <XEUI/UIStateManager.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XEngine.hpp>

namespace XE {


	Scene::Scene(XEngine& engine, IDAL& idal, GraphicsManager& gmanager) :
		m_sceneID(0),
		m_IDAL(idal),
		m_engine(engine)
		//KH	mTerrainGrp ( nullptr),
		, mDecalGenerator(),
		mGraphicsManager(gmanager)
		, _renderableCount(0)
		, m_OgreSceneManager(engine.getOgreSceneManager())
	{
		registerObject(engine.getLua().state);
	}

	Scene::~Scene()
	{
		m_OgreSceneManager.clearItems();
	}

	void Scene::registerObject(sol::state& lua)
	{
		lua.new_usertype<Scene>("Scene",

			//properties
		//	"create", sol::property(&XEngine::getGraphicsManager),

			//functions
			"create", &Scene::create
			);

		auto stateView = lua.set("Scene", this); //set object instance
	}

	//void Scene::initDecalGenerator(btCollisionObject* meshPtr)
	//{
	//	/// This is the mesh object that we will pass to the decal generator.
	//	/// Do not create any more than one OgreMesh per mesh, even if you have multiple instances of the same mesh in your scene.
	////	OgreDecal::OgreMesh worldMesh;
	//	//mWorldMesh.init();
	//
	//	/// This method will extract all of the triangles from the mesh to be used later. Only should be called once.
	//	/// If you scale your mesh at all, pass it in here.
	//	mWorldMesh.addShape(meshPtr); // .initialize(meshPtr, Ogre::Vector3(1.0, 1.0, 1.0));
	//
	//	/// Get the DecalGenerator singleton and initialize it
	//	//OgreDecal::DecalGenerator& generator = OgreDecal::DecalGenerator::getSingleton();
	//	mDecalGenerator.initialize(m_OgreSceneManager);
	//
	////	mDecalGenerator.turnDebugOn();
	//}

	void Scene::addListener(std::unique_ptr<SceneListener> obs) {
		_listenerVector.push_back(std::move(obs));
	}

	void Scene::removeListener(std::unique_ptr<SceneListener> obs) {
		//todo _listenerVector.remove(std::move(obs));
	}

	Ogre::uint16 Scene::nextRenderableID()
	{
		return _renderableCount++;
	}


	void Scene::create(XE::Uint16 sceneID, char* fbData)
	{
		m_sceneID = sceneID;


		//	systems.add<XE::ControllerSystem>(0, m_engine);
		systems.add<PhysicsSystem>(*this);
		systems.add<FreeLookCameraSystem>(*this);// 0, mGraphicsManager, this);
		systems.add<RenderBodySystem>(m_engine.getGraphicsManager());
		systems.add<EntityRenderSystem>();
		systems.add<AnimationControllerSystem>(m_engine.getGraphicsManager(), *this);
		//systems.add<UIStateManager>(); // UISystem
		//	XE::SpawnSystem* spawnSysten = scene->systems.add<XE::SpawnSystem>();
		systems.configure();

		//load scene from datasource
		{
			if (!fbData) //no flatbufferdata available -> then load from DAL
				fbData = m_IDAL.getScene(m_sceneID);

			if (fbData)
			{
				auto sceneObj = flatbuffers::GetRoot<XFBType::Scene>(fbData);

				if (sceneObj->colourAmbient())
				{
					ambientColor = Ogre::ColourValue(sceneObj->colourAmbient()->r(), sceneObj->colourAmbient()->g(), sceneObj->colourAmbient()->b(), sceneObj->colourAmbient()->a());
					m_OgreSceneManager.setAmbientLight(ambientColor);
				}
				delete fbData;
			}
		}

		//SceneNode Data
		m_IDAL.getSceneNodes(*this, m_sceneID, callbackNewNode);

		//--------------------------------------------------------
		//------------------ Light -------------------------------
		//--------------------------------------------------------
		mGraphicsManager.getIntoRendererQueue().push([this]() {
			Ogre::Light *light = m_OgreSceneManager.__OgreSceneMgrPtr->createLight();
			Ogre::SceneNode *rootNode = m_OgreSceneManager.__OgreSceneMgrPtr->getRootSceneNode();

			Ogre::SceneNode *lightNode = rootNode->createChildSceneNode();
			lightNode->attachObject(light);
			light->setPowerScale(1.0f);
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

		});
	}

	void Scene::reload(char* fbData)
	{
	}

	void Scene::createEntity(XE::Int32 entityID, char* entityData, bool replicateEntity)
	{
		auto entity = entities.create();

		bool deleteBufferInRenderThread = createEntity(entity, m_engine, m_sceneID, entityID, entityData, replicateEntity);

		if (deleteBufferInRenderThread)
		{
			m_engine.getGraphicsManager().getIntoRendererQueue().push([entityData]()
			{
				if (entityData)
				{
					delete entityData;
					//	entityData = nullptr;
				}
			});
		}
		else
		{
			//	delete protoData;
			if (entityData)
			{
				delete entityData;
				entityData = nullptr;
			}
		}
	}

	int Scene::callbackNewNode(Scene& scenePointer, XE::Int32 entityID, char* entityData, bool replicateEntity)
	{
		std::cout << "callbackNewNode entID:" << entityID << std::endl;// << gameEntity.getName();

		scenePointer.createEntity(entityID, entityData, replicateEntity);

		return 0;
	}

	void Scene::update(float deltaTime)
	{
		systems.update_all(deltaTime);
	}

	void Scene::collision()
	{
	}

	bool Scene::createEntity(entityx::Entity entity, XE::XEngine& engine, XE::Uint16 sceneID, XE::Uint32 entityID, char* entityData, bool replicateEntity)
	{
		if (replicateEntity && !entity.has_component<XE::NetIdComponent>())
		{
			auto netID = entity.assign<XE::NetIdComponent>();
			netID->entityID = entityID;
		}

		return createEntityType(entity, entityData);
	}

	void Scene::createSoundComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{

	}

	void Scene::updateSoundComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{

	}


	void Scene::createPhysicsComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::PhysicsComponent* fbPhysicsComponent = (const XFBType::PhysicsComponent*)fbData;

		auto physics = fbPhysicsComponent->physics();
		if (physics)
		{
			entityx::ComponentHandle<XE::PhysicsComponent> physicsComponent = entity.assign<XE::PhysicsComponent>();

			for (auto physicObject : *physics)
			{
				if (physicObject->type() == XFBType::PhysicsType::PhysicsType_PT_CHARACTER)
				{
					auto rigidbody = std::unique_ptr<XE::CharacterPhysics>(new XE::CharacterPhysics);
					rigidbody->create(systems.system<XE::PhysicsSystem>()->getDynamicsWorld(), physicObject);

					//set data
					rigidbody->Id = physicObject->id();

					rigidbody->character->enableContactProcessing(true); //todo per fb settings

					physicsComponent->objects.push_back(std::move(rigidbody));
				}
				else// if(physicObject->type() == XFBType::PhysicsType::PhysicsType_PT_RIGID)
				{
					auto rigidbody = std::unique_ptr<XE::RigidBody>(new XE::RigidBody);
					rigidbody->create(systems.system<XE::PhysicsSystem>()->getDynamicsWorld(), physicObject);

					//set data
					rigidbody->Id = physicObject->id();

					physicsComponent->objects.push_back(std::move(rigidbody));
				}
			}

			//set body for phyiscs
			if (entity.has_component<XE::BodyComponent>())
			{
				auto body = entity.component<XE::BodyComponent>();

				for each (auto& physicsObj in physicsComponent->objects)
				{
					physicsObj->setEntityWithBody(entity);

					for (int i = 0; i < physicsComponent->objects.size(); i++)
					{
						TransformState tState(body->getPosition(), body->getOrientation(), body->getScale());
						physicsComponent->objects[i]->setTransformState(tState);
					}

				}
			}
		}
	}

	void Scene::updatePhysicsComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::PhysicsComponent* fbPhysicsComponent = (const XFBType::PhysicsComponent*)fbData;

		auto physics = fbPhysicsComponent->physics();
		if (physics)
		{
			entityx::ComponentHandle<XE::PhysicsComponent> physicsComponent = entity.assign<XE::PhysicsComponent>();

			for (auto fbPhysicObject : *physics)
			{
				//find the corresponding physicsobject
				for each (auto& physicsObj in physicsComponent->objects)
				{
					if (physicsObj->Id == fbPhysicObject->id())
					{
						if (fbPhysicObject->type() == XFBType::PhysicsType::PhysicsType_PT_CHARACTER)
						{
							auto rigidBody = static_cast<XE::RigidBody*>(physicsObj.get());

							//todo change without destroy!
							rigidBody->rigidBody->destroy(); // destroy
							rigidBody->create(systems.system<XE::PhysicsSystem>()->getDynamicsWorld(), fbPhysicObject); //create
						}

						break; //found
					}
				}
			}
		}
	}

	void Scene::createRenderableComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::RenderableComponent* staticRenderableItem = (const XFBType::RenderableComponent*)fbData;

		auto entbase = staticRenderableItem->entitybase();

		auto renderable = entity.assign<XE::Renderable>(engine.getGraphicsManager(), engine.getScene(), fbData);
		auto netID = entity.component<XE::NetIdComponent>();
		netID->id = engine.getNetworkManager().newNetID();

		if (entity.has_component<XE::AnimationComponent>())
		{
			auto animationComponent = entity.component<XE::AnimationComponent>();
			renderable->createAnimations(*animationComponent.get());
		}
	}

	void Scene::updateRenderableComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::RenderableComponent* staticRenderableItem = (const XFBType::RenderableComponent*)fbData;

		auto renderable = entity.component<XE::Renderable>(); //(entbase->entityId(), engine.getGraphicsManager(), scene, fbData->data());#
		renderable->update(fbData);
	}

	void Scene::createBodyComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::Node* node = (const XFBType::Node*)fbData;

		entityx::ComponentHandle<XE::BodyComponent> body = entity.assign<XE::BodyComponent>(node->transform());// , scene->getNodeMemoryMgr());
		auto netID = entity.component<XE::NetIdComponent>();
		netID->id = engine.getNetworkManager().newNetID();

		//set body for physics
		if (entity.has_component<XE::PhysicsComponent>())
		{
			auto physicsComponent = entity.component<XE::PhysicsComponent>();
			for each (auto& physicsObj in physicsComponent->objects)
			{
				physicsObj->setEntityWithBody(entity);

				for (int i = 0; i < physicsComponent->objects.size(); i++)
				{
					TransformState tState(body->getPosition(), body->getOrientation(), body->getScale());
					physicsComponent->objects[i]->setTransformState(tState);
				}
			}
		}
		//	std::cout << netID->id;
	}

	void Scene::updateBodyComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::Node* node = (const XFBType::Node*)fbData;
		entity.component<XE::BodyComponent>()->setPosition(node->transform()->loc()->x(), node->transform()->loc()->y(), node->transform()->loc()->z());
	}

	void Scene::createScene(XE::XEngine& engine, const void* fbData)
	{
		if (fbData)
		{
			const XFBType::Scene* sceneData = (const XFBType::Scene*)fbData;
			engine.getLua().loadScene(sceneData->sceneid());
		}
		else
			LOG(WARNING) << "fbData paremeter is null! in createScene";
	}

	void Scene::updateScene(XE::XEngine& engine, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::Scene* sceneData = (const XFBType::Scene*)fbData;

		if (sceneData->colourAmbient())
		{
			ambientColor = Ogre::ColourValue(sceneData->colourAmbient()->r(), sceneData->colourAmbient()->g(), sceneData->colourAmbient()->b(), sceneData->colourAmbient()->a());
			m_OgreSceneManager.setAmbientLight(ambientColor);
		}
	}

	void Scene::createSpawnPointComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::SpawnPointComponent* fbSPoint = (const XFBType::SpawnPointComponent*)fbData;

		auto sp = entity.assign<XE::SpawnPointComponent>();
		sp->id = fbSPoint->id();
		sp->m_group = fbSPoint->SPGroup();
	}

	void Scene::updateSpawnPointComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::SpawnPointComponent* fbSPoint = (const XFBType::SpawnPointComponent*)fbData;
		auto sp = entity.component<XE::SpawnPointComponent>();
		sp->id = fbSPoint->id();
		sp->m_group = fbSPoint->SPGroup();
	}

	void Scene::createLightComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData)
	{
		const XFBType::Light* characterComp = (const XFBType::Light*)fbData;

		entity.assign<XE::LightRenderable>(engine.getGraphicsManager(), engine.getScene(), fbData);
	}

	void Scene::updateLightComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::Light* characterComp = (const XFBType::Light*)fbData;
		//	entity.component<XE::LightComponent>()->setTransform(node->transform());
	}

	void Scene::createAnimationComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::AnimationComponent* animationComp = (const XFBType::AnimationComponent*)fbData;

		auto animationComponent = entity.assign<XE::AnimationComponent>(engine.getGraphicsManager(), entity);

		animationComponent->initialize(animationComp);

		//animationComponent->animationSystem.loadAnimationTree("D:/Projekte/Src Game/Data/Data_Tests/XETCharacter/simpleOrgeDanceTree.xml");
		//animationComponent->animationSystem.loadAnimationInfo("D:/Projekte/Src Game/Data/Data_Tests/XETCharacter/animation_info.xml");

		if (entity.has_component<XE::Renderable>())
		{
			auto renderable = entity.component<XE::Renderable>();
			renderable->createAnimations(*animationComponent.get());
		}
	}

	void Scene::updateAnimationComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData)
	{
		const XFBType::AnimationComponent* animationComp = (const XFBType::AnimationComponent*)fbData;
		//	entity.component<XE::LightComponent>()->setTransform(node->transform());
	}

} // namespace XE
