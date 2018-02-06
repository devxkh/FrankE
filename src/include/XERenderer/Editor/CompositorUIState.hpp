#pragma once

#include <XESystem/SystemConfig.hpp>

#ifdef CompileEditor	

#include <XERenderer/Editor/IEditorUIState.hpp>
#include <Ogre/OgreMain/include/OgreString.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>

#include <memory>

namespace XE {

	class XECompositor;
	class GraphicsManager;

	class CompositorUIState : public IEditorUIState {

	public:
		CompositorUIState(GraphicsManager& graphicsMgr, XECompositor& compositor);

		void render();

		void preset(Int32 id);

	private:
		XECompositor& m_compositor;
		GraphicsManager& m_graphicsMgr;

		Int32 mPreset;
		float exposure, minAutoExposure, maxAutoExposure;
		float minThreshold, fullColourThreshold;
		Ogre::ColourValue upperHemisphere;
		Ogre::ColourValue lowerHemisphere;
		Ogre::Vector3 hemisphereDir;
		Ogre::Real envmapScale;

	};
}

#endif