#pragma once

#include <Ogre/OgreMain/include/OgreColourValue.h>
namespace Ogre {
	class Vector3;
}

namespace XE {

	class GraphicsManager;
	class CameraRenderable;
	class OgreWorkspace;
		

	class XECompositor {
	public:
		struct CompositorProperties
		{
			const char *name;
			Ogre::ColourValue skyColour;
			Ogre::ColourValue ambUpperHemisphere;
			Ogre::ColourValue ambLowerHemisphere;
			float lightPower[3];
			float exposure;
			float minAutoExposure;
			float maxAutoExposure;
			float bloomThreshold;
			float envmapScale;
		};

		XECompositor(GraphicsManager &graphicsMgr, CameraRenderable& cameraRenderable);


		void setExposure(float exposure, float minAutoExposure, float maxAutoExposure);

		void setSkyColour(const Ogre::ColourValue &colour, float multiplier);

		//-----------------------------------------------------------------------------------
		void setBloomThreshold(float minThreshold, float fullColourThreshold);

		void setAmbientLight(const Ogre::ColourValue& upperHemisphere, const Ogre::ColourValue& lowerHemisphere,const Ogre::Vector3 &hemisphereDir, Ogre::Real envmapScale = 1.0f);

		void setup();

		OgreWorkspace*			_t_OgreWorkspace;

	private:
		
		CompositorProperties m_CompositorProperties;

		GraphicsManager& m_graphicsMgr;
		CameraRenderable& m_cameraRenderable;

	};

}