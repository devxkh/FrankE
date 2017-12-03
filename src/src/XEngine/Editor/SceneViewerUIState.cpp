#include <XEngine/Editor/SceneViewerUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>

namespace XE {

	SceneViewerUIState::SceneViewerUIState(const GraphicsManager& graphicsMgr, const Scene& scene)
	: m_graphicsMgr(graphicsMgr)
	, m_scene(scene)
	{

	}
	

	void SceneViewerUIState::render() {
		
		ImGui::Begin("Entities");

		for each (auto& displayEntity in _t_displayedEntities)
		{
			if (ImGui::TreeNode(displayEntity->displayInformation->name.c_str()))
			{
				ImGui::Text("Num Slots");
				ImGui::Text("Num Slots");
				ImGui::Text("Num Slots");
				ImGui::Text("Num Slots");
				//if (ImGui::TreeNode("Base"))
				//{
				//	ImGui::Indent();
				//	ImGui::Text("Num Slots");
				//	ImGui::Text("Count");
				//	ImGui::Unindent();
				//	ImGui::TreePop();
				//}
				//if (ImGui::TreeNode("Slots"))
				//{
				//	ImGui::TreePop();
				//}
				ImGui::TreePop();
			}
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