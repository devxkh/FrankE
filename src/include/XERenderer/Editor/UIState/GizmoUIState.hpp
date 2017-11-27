#pragma once

#include <XERenderer/Editor/IEditorUIState.hpp>


namespace Ogre {
	class Camera;
}

namespace XE {

	class GraphicsManager;

	///lives in Rendererthread
	class GizmoUIState : public IEditorUIState {

	public:
		GizmoUIState(GraphicsManager& graphicsMgr, Ogre::Camera* camera);

		void render();

		Ogre::Camera* m_camera; 
		GraphicsManager& m_graphicsMgr;

	private:

		void EditTransform();

	};
}