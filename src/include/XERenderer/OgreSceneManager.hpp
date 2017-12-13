#ifndef __OGRESCENEMANAGER_HPP__
#define __OGRESCENEMANAGER_HPP__

//#include <Ogre/OgreMain/include/OgreMesh.h>
#include <sfml/Config.hpp>
//#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <Ogre/OgreMain/include/OgreQuaternion.h>
#include <Ogre/OgreMain/include/OgreNode.h>
//#include <Ogre/OgreMain/include/OgreColourValue.h>

namespace Ogre
{
	class Camera;
	class SceneManager;
	class SceneNode;
	class TerrainGroup;
}

namespace XE {

	class GraphicsManager;
	class Scene;

	class OgreSceneManager
	{
	public:

		OgreSceneManager(GraphicsManager& gmanager);
		
		void create();
		void destroy();
		void clearItems();

		//change only  in Renderthread!!! needed for createworkspace
		Ogre::SceneManager *__OgreSceneMgrPtr;

		
	private:

		Ogre::SceneNode* __lRootSceneNode; //	lRootSceneNode = mSceneMgr->getRootSceneNode(); 
		Ogre::TerrainGroup* mTerrainGrp;
	
		GraphicsManager& mGraphicsManager;
				
		//-------------------------------
		//todo updated from Renderer!!
		//Ogre::Vector3 mDirection;
	//	Ogre::Quaternion m_worldOrientation;
	//	Ogre::Matrix4 m_transform;
		//-------------------------------
	};

}


#endif //__OGRESCENEMANAGER_HPP__