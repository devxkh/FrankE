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

			//PBS expects gamma correction, otherwise it won't look right.
			mGraphicsManager.getRoot()->getRenderSystem()->setConfigOption("sRGB Gamma Conversion", "Yes");

			//Set sane defaults for proper shadow mapping
			__OgreSceneMgrPtr->setShadowDirectionalLightExtrusionDistance(250.0f);
			__OgreSceneMgrPtr->setShadowFarDistance(250.0f);

			__lRootSceneNode = __OgreSceneMgrPtr->getRootSceneNode();
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