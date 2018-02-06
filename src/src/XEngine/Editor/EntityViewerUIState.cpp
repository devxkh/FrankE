#include <XEngine/Editor/EntityViewerUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>
#include <XEngine/Components/Body.hpp>

#include <XERenderer/LightRenderable.hpp>

#include <Ogre/OgreMain/include/OgreLight.h>

//#include <ThirdParty/plog/Log.h>


namespace XE {

	EntityViewerUIState::EntityViewerUIState(GraphicsManager& graphicsMgr, Scene& scene)
	: m_graphicsMgr(graphicsMgr)
		, m_scene(scene)
	{

	}
	

	static float power = 0;
	//static Ogre::Light::LightTypes lightType = Ogre::Light::LightTypes::LT_SPOTLIGHT;
	static int listbox_item_current = -1;

	static float innerAngle, outerAngle = 0;
	static float falloff = 0;
	static bool castShadows = true;
	static Ogre::ColourValue lightColor;
	static Ogre::ColourValue lightSpecularColor;
	static float latt_Range, latt_Constant, latt_Linear, latt_Quadratic;


	void EntityViewerUIState::render() {
		
		ImGui::Begin("Entity");

		for each (auto& component in components)
		{
			if (component->renderableType == RenderableType::RT_LightRenderable)
			{
				if (component->_t_light)
				{
					power = component->_t_light->getPowerScale();
					listbox_item_current = component->_t_light->getType();

					if (ImGui::InputFloat("power", &power))
					{
						component->_t_light->setPowerScale(power);
					}
					/*if (ImGui::InputFloat("type", &lightType))
					{
						component->_t_light->setType(lightType);
					}*/

					/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
					//LT_DIRECTIONAL = 0,
						/// Point light sources give off light equally in all directions, so require only position not direction
					//	LT_POINT = 1,
						/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
					//	LT_SPOTLIGHT = 2,
						/// Virtual point lights, used for Instant Radiosity (Global Illumination fake / approximation)
					//	LT_VPL = 3,

					const char* listbox_items[] = { "LT_DIRECTIONAL", "LT_POINT", "LT_SPOTLIGHT", "LT_VPL" };

					ImGui::ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

					component->_t_light->setType((Ogre::Light::LightTypes)listbox_item_current);

					if ((Ogre::Light::LightTypes)listbox_item_current == Ogre::Light::LightTypes::LT_SPOTLIGHT)
					{
						ImGui::Text("Spotlight Range:");
						
						if (ImGui::InputFloat("inner (degree)", &innerAngle))
						{
							component->_t_light->setSpotlightInnerAngle(Ogre::Degree(innerAngle)); // setSpotlightRange(Ogre::Degree(80), Ogre::Degree(90), 0);
						}
						if (ImGui::InputFloat("outer (degree)", &outerAngle))
						{
							component->_t_light->setSpotlightInnerAngle(Ogre::Degree(outerAngle));
						}

						if (ImGui::InputFloat("falloff", &falloff))
						{
							component->_t_light->setSpotlightFalloff(falloff);
						}
					
					}

					if (ImGui::Checkbox("Cast shdaows", &castShadows))
						component->_t_light->setCastShadows(castShadows);

					lightColor = component->_t_light->getDiffuseColour();
					if (ImGui::ColorEdit4("Diffuse Color", (float*)&lightColor))
						component->_t_light->setDiffuseColour(lightColor);

					lightSpecularColor = component->_t_light->getSpecularColour();
					if (ImGui::ColorEdit4("Specular Color", (float*)&lightSpecularColor))
						component->_t_light->setSpecularColour(lightSpecularColor);

					latt_Constant = component->_t_light->getAttenuationConstant();
					latt_Quadratic = component->_t_light->getAttenuationQuadric();
					latt_Linear = component->_t_light->getAttenuationLinear();
					latt_Range = component->_t_light->getAttenuationRange();

					ImGui::Text("Attenuation:");
					if (ImGui::InputFloat("Range", &latt_Range))
						component->_t_light->setAttenuation(latt_Range, latt_Constant, latt_Linear, latt_Quadratic);
					if (ImGui::InputFloat("Constant", &latt_Constant))
						component->_t_light->setAttenuation(latt_Range, latt_Constant, latt_Linear, latt_Quadratic);
					if (ImGui::InputFloat("Linear", &latt_Linear))
						component->_t_light->setAttenuation(latt_Range, latt_Constant, latt_Linear, latt_Quadratic);
					if (ImGui::InputFloat("Quadratic", &latt_Quadratic))
						component->_t_light->setAttenuation(latt_Range, latt_Constant, latt_Linear, latt_Quadratic);

				}
			}
		}


		/*if (m_entity.has_component<LightRenderable>())
		{
			auto lightRenderable = m_entity.component<LightRenderable>();

			static float test = lightRenderable->_t_light->getPowerScale();

			if (ImGui::InputFloat("power", &test))
			{
			}
		}*/

			//if (ImGui::TreeNode(displayEntity->displayInformation->name.c_str()))
			//{
			//	static int clicked = 0;
			//	if (ImGui::Button("Button"))
			//		clicked++;
			//	if (clicked & 1)
			//	{
			//		ImGui::SameLine();
			//		ImGui::Text("Thanks for clicking me!");
			//	}

			//	ImGui::Text("Num Slots");
			//	ImGui::Text("Num Slots");
			//	ImGui::Text("Num Slots");
			//	ImGui::Text("Num Slots");
			//	//if (ImGui::TreeNode("Base"))
			//	//{
			//	//	ImGui::Indent();
			//	//	ImGui::Text("Num Slots");
			//	//	ImGui::Text("Count");
			//	//	ImGui::Unindent();
			//	//	ImGui::TreePop();
			//	//}
			//	//if (ImGui::TreeNode("Slots"))
			//	//{
			//	//	ImGui::TreePop();
			//	//}
			//	ImGui::TreePop();
			//}
		

		
		/*if (ImGui::TreeNode("floor"))
		{
			ImGui::Text("Num Slots");
			ImGui::TreePop();
		}*/
		//ImGui::Indent();
		//ImGui::Text("Previous Modifications");
		//ImGui::Text("Debug Ticks");
		//ImGui::Unindent();
		
		ImGui::End();

	}
}