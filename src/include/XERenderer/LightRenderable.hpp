#pragma once

namespace Ogre
{
	class Item;
	class Node;
	class Light;
	//class SceneManager;
	class SceneNode;
}

namespace XE
{
	class GraphicsManager;
	class Scene;

	struct LightRenderable
	{
		LightRenderable(GraphicsManager& gmanager, Scene& scene, const void* fbData);
		
		void setLightData(const void* fbData);

	private:

		void _setLightData(const void* fbData);

		Ogre::SceneNode* _t_OgreEntitySceneNodePtr;
		GraphicsManager& m_GraphicsManager;

		Ogre::Light* m_light;
		Ogre::SceneNode* m_LightAxisNode;
		Scene& m_Scene;
	};

}