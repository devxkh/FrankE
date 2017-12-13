#include <XEngine/Editor/GizmoUIState.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/Editor/ImGuizmo.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/LightRenderable.hpp>
#include <XEngine/Scene.hpp>
#include <XEngine/Components/Body.hpp>

#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/OgreMain/include/OgreMath.h>

namespace XE {

	GizmoUIState::GizmoUIState(Scene& scene, GraphicsManager& graphicsMgr, Ogre::Camera* camera)
	: m_camera (camera)
		,m_graphicsMgr(graphicsMgr)
		, m_scene(scene)
		, m_snap(1.0f, 1.0f, 1.0f)
	{

	}

	void GizmoUIState::render()
	{
		EditTransform();
	}

	void GizmoUIState::EditTransform()
	{
		Ogre::Matrix4& currentOrigin_ = m_graphicsMgr.getGUIRenderer()._t_CurrentGizmoOrigin;


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

		Ogre::Vector3 position;
		Ogre::Vector3 scale;
		Ogre::Quaternion orientation;

		currentOrigin_.decomposition(position, scale, orientation);

		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(currentOrigin_[0], matrixTranslation, matrixRotation, matrixScale);
				
		matrixTranslation[0] = currentOrigin_[0][3];
		matrixTranslation[1] = currentOrigin_[1][3];
		matrixTranslation[2] = currentOrigin_[2][3];
		
	//	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, currentOrigin_[0]);

		if (ImGui::InputFloat3("Tr", matrixTranslation, 3))
		{
			Ogre::Vector3 position(Ogre::Vector3::ZERO);
			position.x = matrixTranslation[0];
			position.y = matrixTranslation[1];
			position.z = matrixTranslation[2];
						
			m_graphicsMgr.getFromRendererQueue().push([this, position]() { //executed in mainthread			

				entityx::ComponentHandle<BodyComponent> body;

				for (entityx::Entity entity : m_scene.entities.entities_with_components(body)) {
					if (body->isSelected)
						body->setPosition(position);
				}
			});
		}

		//float radianRotation[3];
		//radianRotation[0] = Ogre::Radian(orientation.x).valueDegrees();
		//radianRotation[1] = Ogre::Radian(orientation.y).valueDegrees();
		//radianRotation[2] = Ogre::Radian(orientation.z).valueDegrees();


		if (ImGui::InputFloat3("Rt", matrixRotation, 3))
		{
		//	Ogre::Matrix3 mx3(matrixRotation);
		//	Ogre::Quaternion orientation(Ogre::Degree(matrixRotation[0]), Ogre::Vector3(1, 1, 1));
		//	orientation.x = matrixRotation[0] * Ogre::Math::fDeg2Rad;
		
			//orientation.ToAngleAxis(Ogre::Degree(matrixRotation[0]), Ogre::Vector3(1, 0, 0));
			//Ogre::Radian fHalfAngle(0.5*matrixRotation[0]);
			//Ogre::Real fSin = Ogre::Math::Sin(fHalfAngle);
			//orientation.w = Ogre::Math::Cos(fHalfAngle);
			//orientation.x = fSin;//*rkAxis.x;

		//	orientation.y = Ogre::Degree(matrixRotation[1]).valueRadians();
		//	orientation.z = Ogre::Degree(matrixRotation[2]).valueRadians();
			//	orientation.FromAngleAxis(Ogre::Degree(matrixRotation[0]), Ogre::Vector3(1,0, 0));
		//	orientation.FromAngleAxis(Ogre::Degree(matrixRotation[1]), Ogre::Vector3(0, 1, 0));
	//		orientation.FromAngleAxis(Ogre::Degree(matrixRotation[2]), Ogre::Vector3(0, 0, 1));

			//	orientation.ToAngleAxis(Ogre::Degree(matrixRotation[1]), Ogre::Vector3(0, 1, 0));

			/*Ogre::Quaternion orientation(Ogre::Quaternion::IDENTITY);
			orientation.x = Ogre::Degree(radianRotation[0]).valueDegrees();
			orientation.y = Ogre::Degree(radianRotation[1]).valueDegrees();
			orientation.z = Ogre::Degree(radianRotation[2]).valueDegrees();*/

			m_graphicsMgr.getFromRendererQueue().push([this, matrixRotation]() { //executed in mainthread			

				entityx::ComponentHandle<BodyComponent> body;

				for (entityx::Entity entity : m_scene.entities.entities_with_components(body)) {

					if (body->isSelected)
					{
						body->setOrientation(Ogre::Quaternion::IDENTITY);
						body->pitch(Ogre::Degree(matrixRotation[0]));
						body->yaw(Ogre::Degree(matrixRotation[1]));
						body->roll(Ogre::Degree(matrixRotation[2]));
						//	body->setOrientation(orientation);
					}
				}
			});
		}

		if (ImGui::InputFloat3("Sc", matrixScale, 3))
		{
			Ogre::Vector3 scale(Ogre::Vector3::ZERO);
			scale.x = matrixScale[0];
			scale.y = matrixScale[1];
			scale.z = matrixScale[2];

			m_graphicsMgr.getFromRendererQueue().push([this, scale]() { //executed in mainthread			

				entityx::ComponentHandle<BodyComponent> body;

				for (entityx::Entity entity : m_scene.entities.entities_with_components(body)) {

					if (body->isSelected)
						body->setScale(scale);
				}
			});
		}

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

		switch (mCurrentGizmoOperation)
		{
		case ImGuizmo::TRANSLATE:
			ImGui::InputFloat3("Snap", &m_snap.x);
			break;
		case ImGuizmo::ROTATE:
			ImGui::InputFloat("Angle Snap", &m_snap.x);
			break;
		case ImGuizmo::SCALE:
			ImGui::InputFloat("Scale Snap", &m_snap.x);
			break;
		}

		Ogre::Matrix4 view = m_camera->getViewMatrix().transpose();
		Ogre::Matrix4 proj = m_camera->getProjectionMatrix().transpose();
		Ogre::Matrix4 tran = currentOrigin_.transpose();
		Ogre::Matrix4 delta;

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		ImGuizmo::Manipulate(view[0], proj[0], mCurrentGizmoOperation, mCurrentGizmoMode, tran[0], delta[0], useSnap ? &m_snap.x : NULL); 

		if (ImGuizmo::IsUsing())
		{
		//	tran = tran.transpose();
			delta = delta.transpose();

			m_graphicsMgr.getFromRendererQueue().push([this, delta]() { //executed in mainthread			

				Ogre::Vector3 position;
				Ogre::Vector3 scale;
				Ogre::Quaternion orientation;

				delta.decomposition(position, scale, orientation);

				entityx::ComponentHandle<BodyComponent> body;

				for (entityx::Entity entity : m_scene.entities.entities_with_components(body)) {

					if (body->isSelected)
					{
						if (mCurrentGizmoOperation == ImGuizmo::TRANSLATE)
						{
							body->translate(delta.getTrans()); 
						}
						else if (mCurrentGizmoOperation == ImGuizmo::ROTATE) {
							
							body->rotate(delta.extractQuaternion());
						}
						else if (mCurrentGizmoOperation == ImGuizmo::SCALE) {

							// A workaround for ImGuizmo bug where delta matrix returns absolute scale value.
							if (body->_t_nodeScaleStart == Ogre::Vector3::ZERO)
								body->_t_nodeScaleStart = body->getScale();

							body->setScale(body->_t_nodeScaleStart * scale);

							//	body->setScale(scale);
						}
					}
				}
			});
		}
		else if (mCurrentGizmoOperation == ImGuizmo::SCALE)
		{
			entityx::ComponentHandle<BodyComponent> body;

			// A workaround for ImGuizmo bug where delta matrix returns absolute scale value.
			for (entityx::Entity entity : m_scene.entities.entities_with_components(body)) {
				body->_t_nodeScaleStart = Ogre::Vector3::ZERO;
			}	
		}
	}
}