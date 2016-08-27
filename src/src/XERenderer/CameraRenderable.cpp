#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/OgreSceneManager.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
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
		, _t_OgreCameraPtr(nullptr)
		, m_nearClipDistance(0.1f)
		, m_farClipDistance(1000.0f)
		, m_screenPointRay()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, id]() {

			Ogre::LogManager::getSingleton().logMessage("RQ -> CameraRenderable::CameraRenderable");

			std::stringstream camName;
			camName << "Cam" << id;
			_t_OgreCameraPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createCamera(camName.str());
			_t_OgreCameraPtr->lookAt(Ogre::Vector3(0, 0, 0));
			_t_OgreCameraPtr->setNearClipDistance(m_nearClipDistance); //0.2f);
			_t_OgreCameraPtr->setFarClipDistance(m_farClipDistance);// 1000.0f);
			_t_OgreCameraPtr->setAutoAspectRatio(m_autoAspectRatio); // true);

			//step 6 workspace
			//	engine->getGraphicsManager().createWorkspace(0, &mCameraController.getOgreCamera()); //camera needed for workspace
			//todo lock and stop render thread while adding renderwindow
//			_t_RenderWindow = OgreWorkspace::_t_createRenderWindow(window); //need window handle (else wnd is hidden), always a renderwindow is needed

			_t_OgreWorkspace = OGRE_NEW_T(OgreWorkspace, Ogre::MEMCATEGORY_GEOMETRY)(m_Scene.getEngine(), m_GraphicsManager);
			_t_OgreWorkspace->_t_createWorkspace(m_GraphicsManager._t_getRenderWindow(id), _t_OgreCameraPtr); //_t_RenderWindow only usable after initialization!
		});
	}

	void CameraRenderable::_t_updateRayFromPoint(const Ogre::Vector2& screenpoint)
	{
		auto screenPointRay = _t_OgreCameraPtr->getCameraToViewportRay(screenpoint.x, screenpoint.y);

		m_GraphicsManager.getFromRendererQueue().push([this, screenPointRay]() {
			m_screenPointRay = screenPointRay;
		});
	}

	void CameraRenderable::setFixedYawAxis( bool fixedYawAxis)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, fixedYawAxis]() {
				_t_OgreCameraPtr->setFixedYawAxis(fixedYawAxis); 
		});
	}

	void CameraRenderable::moveToTarget(Ogre::Real elapsedTime, Ogre::Vector3& targetPosition,  float speed) {
	
		m_GraphicsManager.getIntoRendererQueue().push([this, targetPosition, speed]() {
			
			// Handle movement
			Ogre::Vector3 displacement;

			displacement = (targetPosition - _t_OgreCameraPtr->getPosition()) * speed;
			_t_OgreCameraPtr->getParentNode()->translate(displacement);

			/*displacement = (targetPosition - mTargetNode->getPosition()) * mTightness;
			mTargetNode->translate(displacement);*/
		});
	}

	
	void CameraRenderable::setPosition(const  Ogre::Vector3& position)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, position]() {
			
			_t_OgreCameraPtr->setPosition(position.x, position.y, position.z);

			m_GraphicsManager.getFromRendererQueue().push([this]() {
				m_GraphicsManager.GetRenderTask(RenderTaskID::Camera).isDone = true;
			});
		});
	}

	void CameraRenderable::updateLookAt(const  Ogre::Vector3& position, const  Ogre::Vector3& lookAt)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, position, lookAt]() {
			
			_t_OgreCameraPtr->setPosition(position.x, position.y, position.z);
			_t_OgreCameraPtr->lookAt(Ogre::Vector3(lookAt.x, lookAt.y, lookAt.z));
		});
	}

	void CameraRenderable::setAutoTracking(const bool autoTracking, Renderable* target)
	{
		m_nearClipDistance = autoTracking;

		m_GraphicsManager.getIntoRendererQueue().push([this, autoTracking, target]() {
			_t_OgreCameraPtr->setAutoTracking(autoTracking, target->_t_getNodePtr());
		});
	}

	void CameraRenderable::setNearClipDistance(const float nearClipDistance)
	{
		m_nearClipDistance = nearClipDistance;

		m_GraphicsManager.getIntoRendererQueue().push([this, nearClipDistance]() {

			_t_OgreCameraPtr->setNearClipDistance(nearClipDistance);
		});
	}

	void CameraRenderable::updateTransform(const Ogre::Vector3& position, const Ogre::Quaternion& rotation)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, position, rotation]() {
			
			_t_OgreCameraPtr->setPosition(position.x, position.y, position.z);

			_t_OgreCameraPtr->setOrientation(Ogre::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));

			m_GraphicsManager.getFromRendererQueue().push([this]() {
				m_GraphicsManager.GetRenderTask(RenderTaskID::Camera).isDone = true;
			});
		});
	}

	void CameraRenderable::destroy()
	{
		m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroyCamera(_t_OgreCameraPtr);
		OGRE_DELETE_T(_t_OgreWorkspace, OgreWorkspace, Ogre::MEMCATEGORY_GEOMETRY);
	}

} // namespace XE