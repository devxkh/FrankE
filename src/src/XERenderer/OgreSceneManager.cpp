#include <XERenderer/OgreSceneManager.hpp>
#include <XERenderer/GraphicsManager.hpp>

//#include <Ogre/OgreMain/include/OgreCamera.h>
#include <XEngine/Scene.hpp>

namespace XE
{
	OgreSceneManager::OgreSceneManager(GraphicsManager& gmanager)
		: mGraphicsManager(gmanager)
		, __OgreSceneMgrPtr(nullptr)
		, __lRootSceneNode(nullptr)
	{
		//KH todo !!!! mSceneMgr = mEngine->getRoot()->createSceneManager(Ogre::ST_GENERIC,1,Ogre::InstancingTheadedCullingMethod::INSTANCING_CULLING_SINGLETHREAD, "MyFirstSceneManager");


	}

	void  OgreSceneManager::create()
	{
		mGraphicsManager.getIntoRendererQueue().push([this](){

			Ogre::LogManager::getSingleton().logMessage("RQ -> OgreSceneManager::create");


			__OgreSceneMgrPtr = mGraphicsManager.getRoot()->createSceneManager(Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD, "MyFirstSceneManager");


			//Set sane defaults for proper shadow mapping
			__OgreSceneMgrPtr->setShadowDirectionalLightExtrusionDistance(500.0f);
			__OgreSceneMgrPtr->setShadowFarDistance(500.0f);

			__lRootSceneNode = __OgreSceneMgrPtr->getRootSceneNode();
		});
	}

	void  OgreSceneManager::setAmbientLight(Ogre::ColourValue& colour)
	{
		mGraphicsManager.getIntoRendererQueue().push([this, &colour](){
		/*	__OgreSceneMgrPtr->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
				-light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);*/
		});
	}

	void OgreSceneManager::clearItems()
	{
		mGraphicsManager.getIntoRendererQueue().push([this]() {

			if (__OgreSceneMgrPtr)
			{
				__OgreSceneMgrPtr->destroyAllManualObjects();
				__OgreSceneMgrPtr->destroyAllEntities();
				__lRootSceneNode->removeAndDestroyAllChildren();
			}
		});
	}

	void OgreSceneManager::destroy()
	{
		mGraphicsManager.getIntoRendererQueue().push([this](){

			if (__OgreSceneMgrPtr)
			{
				__OgreSceneMgrPtr->destroyAllCameras();
				__OgreSceneMgrPtr->destroyAllManualObjects();
				__OgreSceneMgrPtr->destroyAllEntities();
				__lRootSceneNode->removeAndDestroyAllChildren();

				mGraphicsManager.getRoot()->destroySceneManager(__OgreSceneMgrPtr);
			}
		});

	}

} // namespace XE