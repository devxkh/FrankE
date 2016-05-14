#include <XERenderer/LightRenderable.hpp>


#include <XERenderer/OgreSceneManager.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>

namespace XE
{
	LightRenderable::LightRenderable(GraphicsManager& gmanager, Scene& scene, const void* fbData) 
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]() {
			Ogre::Light *light = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createLight();
			Ogre::SceneNode *rootNode = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode();

			Ogre::SceneNode *lightNode = rootNode->createChildSceneNode();
			lightNode->attachObject(light);
			light->setPowerScale(1.0f);
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
		});
	}
}