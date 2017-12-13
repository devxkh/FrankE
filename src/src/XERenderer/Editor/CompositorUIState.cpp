#include <XERenderer/Editor/CompositorUIState.hpp>

#ifdef CompileEditor	

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/Compositor/Compositor.hpp>

namespace XE {

	CompositorUIState::CompositorUIState(GraphicsManager& graphicsMgr, XECompositor& compositor)
		: m_graphicsMgr(graphicsMgr)
		, m_compositor(compositor)
	{

	}

	void CompositorUIState::render() {

		ImGui::Begin("Compositor");

		static float exposure, minAutoExposure, maxAutoExposure;

		ImGui::InputFloat("exposure", &exposure);
		ImGui::InputFloat("minAutoExposure", &minAutoExposure);
		ImGui::InputFloat("maxAutoExposure", &maxAutoExposure);

		m_compositor.setExposure(exposure, minAutoExposure, maxAutoExposure);

		static float minThreshold = 0.0, fullColourThreshold = 1.0;
		ImGui::InputFloat("minThreshold", &minThreshold);
		ImGui::InputFloat("fullColourThreshold", &fullColourThreshold);

		m_compositor.setBloomThreshold(minThreshold, fullColourThreshold);

		static Ogre::ColourValue upperHemisphere;
		ImGui::InputFloat3("upperHemisphere", upperHemisphere.ptr());

		static Ogre::ColourValue lowerHemisphere;
		ImGui::InputFloat3("lowerHemisphere", lowerHemisphere.ptr());
		
		static Ogre::Vector3 hemisphereDir;
		ImGui::InputFloat3("hemisphereDir", hemisphereDir.ptr());
		static Ogre::Real envmapScale = 1.0f;
		ImGui::InputFloat("envmapScale", &envmapScale);

		m_compositor.setAmbientLight(lowerHemisphere, upperHemisphere, hemisphereDir, envmapScale);

		ImGui::End();

	}
}

#endif