#pragma once

namespace Ogre
{
	class Item;
	class Node;
	class Light;
	//class SceneManager;
	class SceneNode;
		
	class InstantRadiosity;
	class Vector3;
}

namespace XE
{
	class GraphicsManager;
	class Scene;
	class CLightVisualHelper;

	struct LightRenderable
	{
		LightRenderable(GraphicsManager& gmanager, Scene& scene, const void* fbData);
		
		~LightRenderable();

		void setLightData(const void* fbData);

		void setPosition(const Ogre::Vector3& pos);

	private:

		void _setLightData(const void* fbData);

		Ogre::SceneNode* _t_OgreEntitySceneNodePtr;
		GraphicsManager& m_GraphicsManager;

		Ogre::InstantRadiosity          *mInstantRadiosity;

		Ogre::Light* m_light;
		Ogre::SceneNode* m_LightAxisNode;
		Scene& m_Scene;

		CLightVisualHelper* mCLightVisualHelper;
	};

}