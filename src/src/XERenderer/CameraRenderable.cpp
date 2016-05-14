#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/OgreSceneManager.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <XEngine/Scene.hpp>

#include <XERenderer/OgreWorkspace.hpp>
#include <XEngine/Components/Body.hpp>

#include <iostream>

namespace XE
{
	CameraRenderable::CameraRenderable(XE::Uint16 id, GraphicsManager& gmanager, Scene& scene)
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
		, m_ID(id)
		, __OgreCameraPtr(nullptr)
		, m_nearClipDistance(0.1f)
		, m_farClipDistance(1000.0f)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, id]() {

			Ogre::LogManager::getSingleton().logMessage("RQ -> CameraRenderable::CameraRenderable");

			std::stringstream camName;
			camName << "Cam" << id;
			__OgreCameraPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createCamera(camName.str());
			__OgreCameraPtr->lookAt(Ogre::Vector3(0, 0, 0));
			__OgreCameraPtr->setNearClipDistance(m_nearClipDistance); //0.2f);
			__OgreCameraPtr->setFarClipDistance(m_farClipDistance);// 1000.0f);
			__OgreCameraPtr->setAutoAspectRatio(m_autoAspectRatio); // true);

			//step 6 workspace
			//	engine->getGraphicsManager().createWorkspace(0, &mCameraController.getOgreCamera()); //camera needed for workspace
			//todo lock and stop render thread while adding renderwindow
//			_t_RenderWindow = OgreWorkspace::_t_createRenderWindow(window); //need window handle (else wnd is hidden), always a renderwindow is needed

			_t_OgreWorkspace = OGRE_NEW_T(OgreWorkspace, Ogre::MEMCATEGORY_GEOMETRY)(m_Scene.getEngine(), m_GraphicsManager);
			_t_OgreWorkspace->_t_createWorkspace(m_GraphicsManager._t_getRenderWindow(id), __OgreCameraPtr); //_t_RenderWindow only usable after initialization!
		});
	}

	void CameraRenderable::setSettings()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]() {
			//__OgreCameraPtr->setFixedYawAxis(camera.FixedYawAxis); still needed?
			//__OgreCameraPtr->setAutoTracking(camera.AutoTracking);
		});
	}

	void CameraRenderable::updateLookAt(const  Ogre::Vector3& position, const  Ogre::Vector3& lookAt)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, position, lookAt]() {

			__OgreCameraPtr->setPosition(position.x, position.y, position.z);
			__OgreCameraPtr->lookAt(Ogre::Vector3(lookAt.x, lookAt.y, lookAt.z));
		});
	}

	void CameraRenderable::updateTransform(const Ogre::Vector3& position, const Ogre::Quaternion& rotation)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, position, rotation]() {

			__OgreCameraPtr->setPosition(position.x, position.y, position.z);

			__OgreCameraPtr->setOrientation(Ogre::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));

		});
	}

	void CameraRenderable::destroy()
	{
		m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroyCamera(__OgreCameraPtr);
		OGRE_DELETE_T(_t_OgreWorkspace, OgreWorkspace, Ogre::MEMCATEGORY_GEOMETRY);
	}

} // namespace XE