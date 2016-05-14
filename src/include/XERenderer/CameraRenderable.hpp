#ifndef __OGRECAMERA_HPP__
#define __OGRECAMERA_HPP__

//#include <Ogre/OgreMain/include/OgreMesh.h>
#include <XESystem/SystemConfig.hpp>
//#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <Ogre/OgreMain/include/OgreQuaternion.h>
//#include <Ogre/OgreMain/include/OgreNode.h>

#include <XERenderer/Renderable.hpp>

#include <XESystem/TransportData.hpp>

namespace Ogre
{
	class Camera;
	//class SceneManager;
	class SceneNode;
	class OgreWorkspace;
	class Vector3;
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

		//change only  in Renderthread!!! needed for createworkspace
		inline Ogre::Camera* getOgreCamera() { return __OgreCameraPtr;	}

		void setSettings();
		void updateTransform(const Ogre::Vector3& position, const Ogre::Quaternion& rotation);
		void updateLookAt(const Ogre::Vector3& position, const Ogre::Vector3& lookAt);

		bool IsSettingDirty() { return m_settingIsDirty; }

		void setAutoTracking(bool autotracking) { m_autoTracking = autotracking;  m_settingIsDirty = true; }
		void setNearClipDistance(float nearClipDistance) { m_nearClipDistance = nearClipDistance; m_settingIsDirty = true; }
		void setFarClipDistance(float farClipDistance) { m_farClipDistance = farClipDistance; m_settingIsDirty = true; }

		float getNearClipDistance() { return m_nearClipDistance; }
		float getFarClipDistance() { return  m_farClipDistance; }
		bool getAutoAspectRatio() { return  m_autoAspectRatio; }

	private:

		GraphicsManager& m_GraphicsManager;
		XE::Uint16 m_ID;
		Scene& m_Scene;

		Ogre::Camera* __OgreCameraPtr;
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