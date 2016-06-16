#include <XERenderer/Renderable.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XEDAL/Objects/FBEngineTypes_generated.h>


#include <Ogre/OgreMain/include/OgreNode.h>
#include <Ogre/OgreMain/include/OgreMeshManager.h>
#include <Ogre/OgreMain/include/OgreMeshManager2.h>
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/OgreMain/include/OgreMesh2.h>
#include <Ogre/OgreMain/include/OgreSceneManager.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonInstance.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimationDef.h>

#include <Ogre/OgreMain/include//OgreHlmsManager.h>


#include <XERenderer/OgreSceneManager.hpp>

#include <XEngine/Components/AnimationComponent.hpp>
#include <XESystem/Logging.hpp>
#include <XEngine/Scene.hpp>

namespace XE
{
	Renderable::Renderable(GraphicsManager& gmanager, Scene& scene, const void* fbData)
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
		, m_ID(m_Scene.nextRenderableID())
		, _t_OgreEntitySceneNodePtr(0)
		, isDirty(false)
		//, m_worldPosition(0,0,0)
		, m_position(0, 0, 0)
		//, m_worldScale(1, 1, 1)
		//, m_scale(1, 1, 1)

		, m_rotation(1 ,0, 0, 0)
		//, m_worldOrientation(1 , 0, 0, 0)*/
		//,m_transform(0, 0, 0)
		//,m_worldTransform(0, 0, 0)
	{
		m_GraphicsManager._t_Renderables.push_back(this);

		m_GraphicsManager.getIntoRendererQueue().push([this,fbData]()
		{
			Ogre::LogManager::getSingleton().logMessage("RQ -> Renderable::StaticRenderable");

			_t_OgreEntitySceneNodePtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode()->createChildSceneNode();
				
			_t_createItem(fbData);
		});
	}

	Renderable::~Renderable()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]()
		{
			m_GraphicsManager._t_Renderables.erase(std::find(m_GraphicsManager._t_Renderables.begin(), m_GraphicsManager._t_Renderables.end(), this));
		});
	}

	void Renderable::_t_update()
	{
		_t_OgreEntitySceneNodePtr->setPosition(m_position);
		_t_OgreEntitySceneNodePtr->setOrientation(m_rotation);
		isDirty = false;
	}

	void Renderable::setWorldPosition(const Ogre::Vector3& pos)
	{
		m_position = pos;
		isDirty = true;
	}

	void Renderable::setOrientation(const Ogre::Quaternion& rot)
	{
		m_rotation = rot;
		isDirty = true;
	}

	//void Renderable::setBlendmode()// Ogre::v1::Entity* _t_entity)
	//{
	//	m_GraphicsManager.getIntoRendererQueue().push([this]() {
	//		//	assert(_t_entity);

	//		//	m_t_animations = ogreEntity._t_getEntPtr()->getAllAnimationStates();

	//		bool entityIsAnimated = (_t_OgreItemPtr->getSkeletonInstance()->getAnimations() != NULL);
	//		assert(entityIsAnimated);

	//		Ogre::SkeletonInstance* skeleton = _t_OgreItemPtr->getSkeletonInstance();
	//		skeleton->setBlendMode(Ogre::v1::ANIMBLEND_CUMULATIVE);
	//	});
	//}

	void Renderable::_t_createItem(const void* fbData)
	{
		const XFBType::RenderableComponent* renderable = (const XFBType::RenderableComponent*)fbData;

	//	auto renderable = flatbuffers::GetRoot<XFBType::RenderableComponent>(fbData);
		auto meshes = renderable->meshes();

		//------------------------------------------------------------------------------
		//------------------- create all meshes for this entity -----------------------
		//------------------------------------------------------------------------------
		if (meshes)
		{
			for (auto var : *meshes)
			{
				Ogre::v1::MeshPtr meshV1;
				Ogre::Item* newItem;
				//std::cout << "meshes:" << var->Name()->c_str() << std::endl;
				LOG(INFO) << "Renderable:_t_createItem";
				LOG(INFO) << "mesh_type:" << EnumNameUMesh(var->mesh_type());

				if (var->mesh_type() == XFBType::UMesh::UMesh_MeshPlane)
				{
					//------------------- OGRE PLANE MESH -----------------------
					meshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
						std::to_string(m_ID),
						"General",
						Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 250, 250, 25, 25, true, 1, 15, 15, Ogre::Vector3::UNIT_Z,
						Ogre::v1::HardwareBuffer::HBU_STATIC,
						Ogre::v1::HardwareBuffer::HBU_STATIC); //without Ogre::v1::HardwareBuffer::HBU_STATIC crash in planeMesh->importV1???

															   // create a floor entity, give it a material, and place it at the origin
															   //--------------------------- todo import v2 directly
					Ogre::MeshPtr manual = Ogre::MeshManager::getSingleton().createManual(
						"Plane",//var->Name()->c_str(), //"Plane",
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
					manual->importV1(meshV1.get(), true, true, true);
					//We don't need the v1 mesh. Free CPU memory, get it out of the GPU.
					//Leave it loaded if you want to use athene with v1 Entity.
					meshV1->unload();

					newItem = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(manual, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC); //renderable->memType()); //Ogre::SCENE_DYNAMIC);
					
					Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
					Ogre::HlmsDatablock *datablock = hlmsManager->getDatablock("HlmsUnlit1");
					newItem->setDatablock(datablock); //todo multiple materials per mesh	
												   //floor->setMaterialName("Examples/Rockwall", "General");
												   //floor->setCastShadows(false);
					newItem->setCastShadows(true);
			

					_t_OgreEntitySceneNodePtr->attachObject(newItem);
				}
				else if (var->mesh_type() == XFBType::UMesh::UMesh_MeshCube)
				{

				}

				else if (var->mesh_type() == XFBType::UMesh::UMesh_MeshFile)
				{
					bool halfPosition = true;
					bool halfUVs = true;
					bool useQtangents = true;

					auto v1Mesh = Ogre::v1::MeshManager::getSingleton().load(
						"Sinbad.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
						Ogre::v1::HardwareBuffer::HBU_STATIC, Ogre::v1::HardwareBuffer::HBU_STATIC);
					//Create a v2 mesh to import to, with a different name.
					auto v2Mesh = Ogre::MeshManager::getSingleton().createManual(
						"Barrel Imported", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

					v2Mesh->importV1(v1Mesh.get(), halfPosition, halfUVs, useQtangents);
					v1Mesh->unload();

					_t_OgreItemPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(v2Mesh, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC);
					_t_OgreItemPtr->setCastShadows(true);
				//	_t_OgreItemPtr->setDatablock("BaseWhite");
					//meshV1 = tmp->getMesh();
					//Ogre::MeshPtr manual = Ogre::MeshManager::getSingleton().createManual(
					//	"sindbad",//var->Name()->c_str(), //"Plane",
					//	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
					//manual->importV1(meshV1.get(), true, true, true);
					////We don't need the v1 mesh. Free CPU memory, get it out of the GPU.
					////Leave it loaded if you want to use athene with v1 Entity.
					//meshV1->unload();

				//	newItem = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(manual, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC); //renderable->memType()); //Ogre::SCENE_DYNAMIC);
				//	newItem->setDatablock("Marble"); //todo multiple materials per mesh	
													 //floor->setMaterialName("Examples/Rockwall", "General");
													 //floor->setCastShadows(false);
					_t_OgreEntitySceneNodePtr->attachObject(_t_OgreItemPtr);
				}

				
				
			}
		}

		//	m_ogreEntity._t_OgreEntitySceneNodePtr->setPosition(0, -50, 0); //done in scene gameEntity->setTransform(tvs);

	/*	if (deleteThisBuffer)
		{
			delete deleteThisBuffer;
			deleteThisBuffer = nullptr;
		}*/
	}

	void Renderable::createAnimations(AnimationComponent& animationComponent)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, &animationComponent]()
		{
			assert(_t_OgreItemPtr->hasSkeleton());

			auto animations = _t_OgreItemPtr->getSkeletonInstance()->getAnimations();

			Ogre::SkeletonAnimationVec::iterator it = animations.begin();
			while (it != animations.end())
			{
			//	auto animationPtr = &*it;
				float duration = it->getDuration();
				std::string name = it->getDefinition()->getNameStr();
				
				Ogre::SkeletonAnimation* skeletonAnimationPtr = &*it;

				//attention!! delete in mainthread 
				std::vector< float* >* boneWeightPtrs = new std::vector< float* >();
				std::vector< float >* boneWeightList = new std::vector< float >();

				for (int i = 0; i < skeletonAnimationPtr->mOwner->getNumBones(); i++)
				{
					Ogre::String boneName = skeletonAnimationPtr->mOwner->getBone(i)->getName();
					Ogre::Real* weight = skeletonAnimationPtr->getBoneWeightPtr(Ogre::IdString(boneName));
					if (weight != 0)
					{
						boneWeightPtrs->push_back(weight);
						boneWeightList->push_back(*boneWeightPtrs->back());
					}
					else
					{
						boneWeightPtrs->push_back(0);
						boneWeightList->push_back(0);
					}
				}

				//do not use the iterator!!
				Ogre::SkeletonAnimation* test = _t_OgreItemPtr->getSkeletonInstance()->getAnimation(name);
		//		m_GraphicsManager.getFromRendererQueue().push([test, name, duration, &animationComponent, boneWeightPtrs, boneWeightList]() {
			
					animationComponent._MT_setAnimationStatePtr(test, name, duration, boneWeightPtrs, boneWeightList);

				//	m_t_animation = test;
		//		});
				it++;
			}
		});
	}

	void Renderable::destoyItems()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]()
		{
			_t_OgreEntitySceneNodePtr->detachAllObjects();

			auto objIt = _t_OgreEntitySceneNodePtr->getAttachedObjectIterator();
			while (objIt.hasMoreElements())
			{
				m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroyItem(static_cast<Ogre::Item*>(objIt.getNext()));
			}

			_t_OgreEntitySceneNodePtr->removeAndDestroyAllChildren();
		});
	}

	void Renderable::update(const void* fbData)
	{
		destoyItems(); //mainthread !

		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]()
		{
			Ogre::LogManager::getSingleton().logMessage("RQ -> Renderable::update");
			
			_t_createItem(fbData);

		//	delete deleteThisBuffer;
		});
	}


	//void Renderable::scale(const Ogre::Vector3& scale){
	//	m_scale = scale;
	//	m_GraphicsManager.getIntoRendererQueue().push([this, scale]()
	//	{
	//		_t_OgreEntitySceneNodePtr->setScale(scale);
	//	});
	//}	


	void Renderable::destroy()
	{
		//todo	//todo in renderthread
		//(*rIter)->getSceneNode()->detachAllObjects();
		//(*rIter)->getSceneNode()->removeAndDestroyAllChildren();
		//mScene->getSceneMgr()->destroyEntity((*rIter)->getEntity());
		//mScene->getSceneMgr()->destroySceneNode((*rIter)->getSceneNode());
	}

} // namespace XE