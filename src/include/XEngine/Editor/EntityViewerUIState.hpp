#pragma once

#include <XESystem/SystemConfig.hpp>
#include <XERenderer/Editor/IEditorUIState.hpp>
#include <Ogre/OgreMain/include/OgreString.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <memory>

namespace XE {

	class Scene;
	class GraphicsManager;

	enum RenderableType {
		RT_None,
		RT_Renderable,
		RT_LightRenderable,
		RT_DebugDrawer
	};

	struct RenderableComponent
	{
		RenderableComponent()
		: _t_light(nullptr)
		, _t_OgreItemPtr(nullptr) {}

		RenderableType renderableType;

		Ogre::Light* _t_light;
		Ogre::Item* _t_OgreItemPtr;
	};

	class EntityViewerUIState : public IEditorUIState {

	public:
		EntityViewerUIState(GraphicsManager& graphicsMgr, Scene& scene);

		void render();

		std::vector<std::unique_ptr<RenderableComponent>> components;

	private:



		GraphicsManager& m_graphicsMgr;
		Scene& m_scene;
	};
}