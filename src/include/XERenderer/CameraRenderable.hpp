#ifndef __OGRECAMERA_HPP__
#define __OGRECAMERA_HPP__

//#include <Ogre/OgreMain/include/OgreMesh.h>
#include <XESystem/SystemConfig.hpp>
//#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <Ogre/OgreMain/include/OgreQuaternion.h>
//#include <Ogre/OgreMain/include/OgreNode.h>
#include <Ogre/OgreMain/include/OgreRay.h>

#include <XERenderer/Renderable.hpp>

#include <XESystem/TransportData.hpp>

namespace Ogre
{
	class Camera;
	//class SceneManager;
	class SceneNode;
	class OgreWorkspace;
	class Vector3;
	class Vector2;
}

namespace XE {

	class OgreWorkspace;
	class GraphicsManager;
	class Scene;

	class CameraRenderable
	{
	public:

		CameraRenderable(XE::Uint16 id, GraphicsManager& gmanager, Scene& scene);

		void destroy();
	
		inline GraphicsManager& getGraphicsManager() { return m_GraphicsManager; }

		void moveToTarget(Ogre::Real elapsedTime, Ogre::Vector3& targetPosition, float speed);

		void setFixedYawAxis(bool fixedYawAxis);
		void updateTransform(const Ogre::Vector3& position, const Ogre::Quaternion& rotation);
		void updateLookAt(const Ogre::Vector3& position, const Ogre::Vector3& lookAt);

		bool IsSettingDirty() { return m_settingIsDirty; }

		void setAutoTracking(bool autotracking, Renderable* target);// { m_autoTracking = autotracking;  m_settingIsDirty = true; }
		void setNearClipDistance(float nearClipDistance);// { m_nearClipDistance = nearClipDistance; m_settingIsDirty = true; }
		void setFarClipDistance(float farClipDistance) { m_farClipDistance = farClipDistance; m_settingIsDirty = true; }

		float getNearClipDistance() { return m_nearClipDistance; }
		float getFarClipDistance() { return  m_farClipDistance; }
		bool getAutoAspectRatio() { return  m_autoAspectRatio; }

		void setPosition(const  Ogre::Vector3& position);

		const Ogre::Ray& getScreenPointRay()  { return m_screenPointRay; }

		void _t_updateRayFromPoint(const Ogre::Vector2& screenpoint);


		Ogre::Camera* _t_OgreCameraPtr;

	private:


		Ogre::Vector3 _t_LastPosition;
		Ogre::Vector3 _t_CurrentPosition;

		Ogre::Ray m_screenPointRay;

		GraphicsManager& m_GraphicsManager;
		XE::Uint16 m_ID;
		Scene& m_Scene;

		XE::OgreWorkspace*			_t_OgreWorkspace;

		
		bool m_settingIsDirty;

		//camera settings
		float m_nearClipDistance;
		float m_farClipDistance;
		bool m_autoAspectRatio;
		bool m_autoTracking;
	};

}


#endif //__OGRECAMERA_HPP__