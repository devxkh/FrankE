#pragma once

#include <XERenderer/Editor/IEditorUIState.hpp>

#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreQuaternion.h>
#include <map>

namespace Ogre {
	class Camera;
}

namespace XE {

	class GraphicsManager;
	class Scene;
	struct BodyComponent;

	///lives in Rendererthread
	class GizmoUIState : public IEditorUIState {

	public:
		GizmoUIState(Scene& scene, GraphicsManager& graphicsMgr, Ogre::Camera* camera);

		void render();

		Ogre::Camera* m_camera; 
		GraphicsManager& m_graphicsMgr;
		Scene& m_scene;

	private:

		Ogre::Vector3 m_snap;

		Ogre::Vector3 m_position;
		Ogre::Vector3 m_scale;
		Ogre::Quaternion m_orientation;
		
		Ogre::Matrix4 _delta;
		
		void EditTransform();

	};
}