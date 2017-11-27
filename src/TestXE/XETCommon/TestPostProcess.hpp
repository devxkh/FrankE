#pragma once

#include <Ogre/OgreMain/include/OgreStringVector.h>

namespace Ogre {
	class CompositorWorkspace;
	struct IdString;
}

namespace XE
{
	class XEngine;
	class CameraRenderable;
}

namespace XET
{

	class TestPostProcess
	{
	public:
		TestPostProcess(XE::XEngine& engine, XE::CameraRenderable& cameraRenderable);
		void createCustomTextures();
		void togglePostprocess(Ogre::IdString nodeName);
		Ogre::CompositorWorkspace* setupCompositor();
		void createExtraEffectsFromCode();

		Ogre::StringVector          mCompositorNames;

		Ogre::CompositorWorkspace *m_workspace;

	private:
		XE::XEngine& m_engine;
		XE::CameraRenderable& m_cameraRenderable;
	};
}