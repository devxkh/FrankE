#pragma once

#include <XERenderer/Editor/IEditorUIState.hpp>

namespace Ogre {
	class Camera;
}

namespace XE {

	class GraphicsManager;
	class Scene;

	///lives in Rendererthread
	class GizmoUIState : public IEditorUIState {

	public:
		GizmoUIState(Scene& scene, GraphicsManager& graphicsMgr, Ogre::Camera* camera);

		void render();

		Ogre::Camera* m_camera; 
		GraphicsManager& m_graphicsMgr;
		Scene& m_scene;

	private:


		void EditTransform();

	};
}