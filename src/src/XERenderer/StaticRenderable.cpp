#include <XERenderer/StaticRenderable.hpp>


#include <XERenderer/GraphicsManager.hpp>

#include <XEDAL/Objects/FBEngineTypes_generated.h>



#include <Ogre/OgreMain/include/OgreMeshManager.h>
#include <Ogre/OgreMain/include/OgreMeshManager2.h>
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/OgreMain/include/OgreMesh2.h>



#include <XEngine/Scene.hpp>
#include <Ogre/OgreMain/include/OgreSceneManager.h>


namespace XE
{
	StaticRenderable::StaticRenderable(sf::Uint16 id, GraphicsManager& gmanager, Scene& scene, const void* fbData)
		: Renderable(id, gmanager, scene)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]()
		{
			Ogre::LogManager::getSingleton().logMessage("RQ -> StaticRenderable::StaticRenderable");

			Ogre::uint16 idTmp = getID();

			auto gameEntObj = flatbuffers::GetRoot<XFBType::RenderableComponent>(fbData);
			auto entbase = gameEntObj->entitybase();
			auto meshes = entbase->meshes();

			//------------------------------------------------------------------------------
			//------------------- create all meshes for this entity -----------------------
			//------------------------------------------------------------------------------
			if (meshes)
			{
				for (auto var : *meshes)
				{
					//std::cout << "meshes:" << var->Name()->c_str() << std::endl;
					if (var->plane())
					{

					}
				}
			}

			//------------------- OGRE PLANE MESH -----------------------
			Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(std::to_string(idTmp), "General",
				Ogre::Plane(Ogre::Vector3::UNIT_Y, 1), 250, 250, 25, 25, true, 1, 15, 15, Ogre::Vector3::UNIT_Z,
				Ogre::v1::HardwareBuffer::HBU_STATIC,
				Ogre::v1::HardwareBuffer::HBU_STATIC); //without Ogre::v1::HardwareBuffer::HBU_STATIC crash in planeMesh->importV1???

			// create a floor entity, give it a material, and place it at the origin
			//---------------------------
			Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createManual(
				"Plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			planeMesh->importV1(planeMeshV1.get(), true, true, true);

			Ogre::Item* floor = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(planeMesh, Ogre::SCENE_DYNAMIC);
			floor->setDatablock("Marble");
			//floor->setMaterialName("Examples/Rockwall", "General");
			//floor->setCastShadows(false);
			_t_OgreEntitySceneNodePtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode()->createChildSceneNode();
			_t_OgreEntitySceneNodePtr->attachObject(floor);

			//	m_ogreEntity._t_OgreEntitySceneNodePtr->setPosition(0, -50, 0); //done in scene gameEntity->setTransform(tvs);

			delete fbData;
		});
		//KH	GameEntity::setEntity(floor);
		//------------------- OGRE PLANE MESH -----------------------
	}





} // ns XE