#include <XEngine/Editor/SceneViewerUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>
#include <XEngine/Components/Body.hpp>

#include <XERenderer/OgreSceneManager.hpp>
#include <Ogre/Components/Hlms/Pbs/include/InstantRadiosity/OgreInstantRadiosity.h>
#include "OgreForward3D.h"

namespace XE {

	SceneViewerUIState::SceneViewerUIState(GraphicsManager& graphicsMgr, Scene& scene)
	: m_graphicsMgr(graphicsMgr)
	, m_scene(scene)
		, mInstantRadiosity(0)
		, m_selected(0)
	{

	}
	

	static bool useInstantRadiosity = false;

	void SceneViewerUIState::enableIR(bool enable) {

		if (enable)
		{
			if (!mInstantRadiosity)
			{
				Ogre::HlmsManager *hlmsManager = m_scene.getGraphicsManager().getRoot()->getHlmsManager();
				mInstantRadiosity = new Ogre::InstantRadiosity(m_scene.getOgreSceneManager().__OgreSceneMgrPtr, hlmsManager);
				mInstantRadiosity->mVplThreshold = 0.0005f;

				//Guide where to shoot the rays for directional lights the 3 windows + the
				//hole in the ceiling). We use a sphere radius of 30 to ensure when the directional
				//light's dir is towards -X, we actually hit walls (instead of going through these
				//walls and generating incorrect results).
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-0.746887f, 7.543859f, 5.499001f),
						Ogre::Vector3(2.876101f, 2.716137f, 6.059607f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, 6.628003f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, 3.083399f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, -0.415852f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));

				mInstantRadiosity->build();

				m_scene.getOgreSceneManager().__OgreSceneMgrPtr->setForwardClustered(true, 16, 8, 24, 96, 2, 50);
				//Required by InstantRadiosity
				m_scene.getOgreSceneManager().__OgreSceneMgrPtr->getForwardPlus()->setEnableVpls(true);
			}
			else
			{
				mInstantRadiosity->mVplThreshold = 1.0f;//lightData->IRVplThreshold();
			}
		}
		else {
			m_scene.getOgreSceneManager().__OgreSceneMgrPtr->getForwardPlus()->setEnableVpls(false);
			m_scene.getOgreSceneManager().__OgreSceneMgrPtr->setForwardClustered(false, 16, 8, 24, 96, 2, 50);
			delete mInstantRadiosity;
			mInstantRadiosity = 0;
		}
	}
	
	void SceneViewerUIState::render() {
		
		ImGui::Begin("Entities");

		if (ImGui::Checkbox("Use Instant Radiosity", &useInstantRadiosity))
			enableIR(useInstantRadiosity);

		for each (auto& displayEntity in _t_displayedEntities)
		{
			if (ImGui::Button(displayEntity->displayInformation->name.c_str()))
			{
				if (m_selected == displayEntity->id) // already selected?
					continue;

				m_selected = displayEntity->id;

				m_graphicsMgr.getFromRendererQueue().push([this]() { //executed in mainthread		
					
					entityx::ComponentHandle<BodyComponent> body;
					entityx::ComponentHandle<EditorComponent> editorComponent;

					for (entityx::Entity entity : m_scene.entities.entities_with_components(body, editorComponent)) {

						body->isSelected = editorComponent->id == m_selected;
					}
				//	m_graphicsMgr.getGUIRenderer().selectedID = m_selected;
				
				});
				//ImGui::SameLine();
				//ImGui::Text("Thanks for clicking me!");
			}


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
		}
		
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