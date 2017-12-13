#pragma once

#include <XESystem/SystemConfig.hpp>

#ifdef CompileEditor	

#include <XERenderer/Editor/IEditorUIState.hpp>
#include <Ogre/OgreMain/include/OgreString.h>
#include <Ogre/OgreMain/include/OgreVector3.h>

#include <memory>

namespace XE {

	class XECompositor;
	class GraphicsManager;

	class CompositorUIState : public IEditorUIState {

	public:
		CompositorUIState(GraphicsManager& graphicsMgr, XECompositor& compositor);

		void render();


	private:
		XECompositor& m_compositor;
		GraphicsManager& m_graphicsMgr;
	};
}

#endif