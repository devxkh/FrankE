#include <XERenderer/Editor/CompositorUIState.hpp>

#ifdef CompileEditor	

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/Compositor/Compositor.hpp>

#include <XERenderer/OgreWorkspace.hpp>

#include <Ogre/OgreMain/include/OgreSceneManager.h>

namespace XE {

	CompositorUIState::CompositorUIState(GraphicsManager& graphicsMgr, XECompositor& compositor)
		: m_graphicsMgr(graphicsMgr)
		, m_compositor(compositor)
		, minThreshold(0.0f), fullColourThreshold(1.0f)
		, envmapScale(1.0f)
		, mPreset(5)
		, hemisphereDir(Ogre::Vector3::NEGATIVE_UNIT_Y)
	{

	}

	void CompositorUIState::preset(Int32 id)
	{
		const XECompositor::CompositorProperties c_presets[] =
		{
			{
				"Bright, sunny day",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f)  * 60.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 4.5f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 2.925f,
				97.0f,              //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -1.0f, 2.5f,  //Exposure
				5.0f,               //Bloom
				16.0f               //Env. map scale
			},
			{
				"Average, slightly hazy day",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f) * 32.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 3.15f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 2.0475f,
				48.0f, //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -2.0f, 2.5f,  //Exposure
				5.0f,               //Bloom
				8.0f                //Env. map scale
			},
			{
				"Heavy overcast day",
				Ogre::ColourValue(0.4f, 0.4f, 0.4f) * 4.5f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.5f) * 0.4f,
				Ogre::ColourValue(0.5f, 0.5f, 0.5f) * 0.365625f,
				6.0625f,            //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -2.5f, 1.0f,  //Exposure
				5.0f,               //Bloom
				0.5f                //Env. map scale
			},
			{
				"Gibbous moon night",
				Ogre::ColourValue(0.27f, 0.3f, 0.6f) * 0.01831072f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.50f) * 0.003f,
				Ogre::ColourValue(0.4f, 0.5f, 0.65f) * 0.00274222f,
				0.0009251f,         //Sun power
				1.5f, 1.5f,         //Lights
				0.65f, -2.5f, 3.0f, //Exposure
				5.0f,               //Bloom
				0.0152587890625f    //Env. map scale
			},
			{
				"Gibbous moon night w/ powerful spotlights",
				Ogre::ColourValue(0.27f, 0.3f, 0.6f) * 0.01831072f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.50f) * 0.003f,
				Ogre::ColourValue(0.4f, 0.5f, 0.65f) * 0.00274222f,
				0.0009251f,         //Sun power
				6.5f, 6.5f,         //Lights
				0.65f, -2.5f, 3.0f, //Exposure
				5.0f,               //Bloom
				0.0152587890625f    //Env. map scale
			},
			{
				"JJ Abrams style",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f)  * 6.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 0.1125f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.073125f,
				4.0f,               //Sun power
				17.05f, 17.05f,     //Lights
				0.5f, 1.0f, 2.5f,   //Exposure
				3.0f,               //Bloom
				1.0f,               //Env. map scale
			},
		};

		const XECompositor::CompositorProperties &preset = c_presets[id];

		exposure = preset.exposure;
		minAutoExposure = preset.minAutoExposure;
		maxAutoExposure = preset.maxAutoExposure;
		minThreshold = Ogre::max(preset.bloomThreshold - 2.0f, 0.0f);
		fullColourThreshold = Ogre::max(preset.bloomThreshold, 0.01f);
		upperHemisphere = preset.ambUpperHemisphere;
		lowerHemisphere = preset.ambLowerHemisphere;
		envmapScale = preset.envmapScale;
	}

	void CompositorUIState::render() {

		
		ImGui::Begin("Compositor");

		ImGui::InputInt("preset", &mPreset);
		if(mPreset >= 0 && mPreset < 6)
			preset(mPreset);


		ImGui::InputFloat("exposure", &exposure);
		ImGui::InputFloat("minAutoExposure", &minAutoExposure);
		ImGui::InputFloat("maxAutoExposure", &maxAutoExposure);

		m_compositor.setExposure(exposure, minAutoExposure, maxAutoExposure);

		ImGui::InputFloat("minThreshold", &minThreshold);
		ImGui::InputFloat("fullColourThreshold", &fullColourThreshold);

		m_compositor.setBloomThreshold(minThreshold, fullColourThreshold);

		hemisphereDir = m_compositor._t_OgreWorkspace->_t_sceneMgr->getAmbientLightHemisphereDir();
		upperHemisphere = m_compositor._t_OgreWorkspace->_t_sceneMgr->getAmbientLightUpperHemisphere();
		lowerHemisphere = m_compositor._t_OgreWorkspace->_t_sceneMgr->getAmbientLightLowerHemisphere();

		ImGui::Text("Ambient light");
		ImGui::ColorEdit4("UpperHemisphere Color", upperHemisphere.ptr());
		ImGui::ColorEdit4("LowerHemisphere Color", lowerHemisphere.ptr());		
		ImGui::InputFloat3("hemisphereDir", hemisphereDir.ptr());
		ImGui::InputFloat("envmapScale", &envmapScale);

		m_compositor.setAmbientLight(lowerHemisphere, upperHemisphere, hemisphereDir, envmapScale);

		ImGui::End();

	}
}

#endif