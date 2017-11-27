#include <XERenderer/Editor/UIState/GizmoUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/Editor/ImGuizmo.h>
#include <XERenderer/GraphicsManager.hpp>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>

namespace XE {

	GizmoUIState::GizmoUIState(GraphicsManager& graphicsMgr, Ogre::Camera* camera)
	: m_camera (camera)
		,m_graphicsMgr(graphicsMgr)
	{

	}


	void GizmoUIState::render()
	{
		EditTransform();
	}

	void GizmoUIState::EditTransform()
	{
		const Ogre::Matrix4& currentOrigin_ = m_graphicsMgr.getGUIRenderer()._t_CurrentGizmoOrigin;

		static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
		static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
		if (ImGui::IsKeyPressed(90))
			mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
		if (ImGui::IsKeyPressed(69))
			mCurrentGizmoOperation = ImGuizmo::ROTATE;
		if (ImGui::IsKeyPressed(82)) // r Key
			mCurrentGizmoOperation = ImGuizmo::SCALE;
		if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
			mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
		ImGui::SameLine();
		if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
			mCurrentGizmoOperation = ImGuizmo::ROTATE;
		ImGui::SameLine();
		if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
			mCurrentGizmoOperation = ImGuizmo::SCALE;

		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(currentOrigin_[0], matrixTranslation, matrixRotation, matrixScale);
		ImGui::InputFloat3("Tr", matrixTranslation, 3);
		ImGui::InputFloat3("Rt", matrixRotation, 3);
		ImGui::InputFloat3("Sc", matrixScale, 3);
		//	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, currentOrigin_[0]);

		if (mCurrentGizmoOperation != ImGuizmo::SCALE)
		{
			if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
				mCurrentGizmoMode = ImGuizmo::LOCAL;
			ImGui::SameLine();
			if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
				mCurrentGizmoMode = ImGuizmo::WORLD;
		}
		static bool useSnap(false);
		if (ImGui::IsKeyPressed(83))
			useSnap = !useSnap;
		ImGui::Checkbox("", &useSnap);
		ImGui::SameLine();

		Ogre::Vector3 snap;
		switch (mCurrentGizmoOperation)
		{
		case ImGuizmo::TRANSLATE:
			//	snap = config.mSnapTranslation;
			ImGui::InputFloat3("Snap", &snap.x);
			break;
		case ImGuizmo::ROTATE:
			//	snap = config.mSnapRotation;
			ImGui::InputFloat("Angle Snap", &snap.x);
			break;
		case ImGuizmo::SCALE:
			//	snap = config.mSnapScale;
			ImGui::InputFloat("Scale Snap", &snap.x);
			break;
		}

		Ogre::Matrix4 view = m_camera->getViewMatrix().transpose();
		Ogre::Matrix4 proj = m_camera->getProjectionMatrix().transpose();
		Ogre::Matrix4 tran = currentOrigin_.transpose();
		Ogre::Matrix4 delta;

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		ImGuizmo::Manipulate(view[0], proj[0]
			, mCurrentGizmoOperation, mCurrentGizmoMode, tran[0], delta[0], nullptr); // useSnap ? &snap.x : NULL);

																					  //move to engine level!
																					  //if (ImGuizmo::IsUsing())
																					  //{
																					  //	tran = tran.transpose();
																					  //	delta = delta.transpose();

																					  //	currentOrigin_ = Ogre::Matrix4(tran);

																					  //	for (const auto& node : nodes)
																					  //	{
																					  //		if (node == nullptr)
																					  //		{
																					  //		//	URHO3D_LOGERROR("Gizmo received null pointer of node.");
																					  //			continue;
																					  //		}

																					  //		if (operation_ == GIZMOOP_SCALE)
																					  //		{
																					  //			// A workaround for ImGuizmo bug where delta matrix returns absolute scale value.
																					  //			if (!nodeScaleStart_.Contains(node))
																					  //				nodeScaleStart_[node] = node->GetScale();
																					  //			node->SetScale(nodeScaleStart_[node] * delta.Scale());
																					  //		}
																					  //		else
																					  //		{
																					  //			// Delta matrix is always in world-space.
																					  //			if (operation_ == GIZMOOP_ROTATE)
																					  //				node->RotateAround(currentOrigin_.Translation(), -delta.Rotation(), TS_WORLD);
																					  //			else
																					  //				node->Translate(delta.Translation(), TS_WORLD);
																					  //		}
																					  //	}

																					  //	return true;
																					  //}
																					  //else if (operation_ == GIZMOOP_SCALE && !nodeScaleStart_.Empty())
																					  //	nodeScaleStart_.Clear();
																					  //return false;
	}
}