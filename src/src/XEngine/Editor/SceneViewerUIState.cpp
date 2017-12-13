#include <XEngine/Editor/SceneViewerUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>
#include <XEngine/Components/Body.hpp>


namespace XE {

	SceneViewerUIState::SceneViewerUIState(GraphicsManager& graphicsMgr, Scene& scene)
	: m_graphicsMgr(graphicsMgr)
	, m_scene(scene)
		, m_selected(0)
	{

	}
	

	void SceneViewerUIState::render() {
		
		ImGui::Begin("Entities");

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