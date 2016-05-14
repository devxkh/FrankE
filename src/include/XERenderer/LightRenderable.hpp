#pragma once

namespace Ogre
{
	class Item;
	class Node;
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

	private:
		Ogre::SceneNode* _t_OgreEntitySceneNodePtr;
		GraphicsManager& m_GraphicsManager;

		Scene& m_Scene;
	};

}