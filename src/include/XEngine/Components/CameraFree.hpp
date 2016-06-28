#pragma once

#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>

namespace XE
{
	struct BodyComponent;
	class CameraRenderable;

	struct XE_API CameraFreeComponent  {

	public:
		CameraFreeComponent(CameraRenderable& cameraRenderable, BodyComponent& bodyComponent);
		
		~CameraFreeComponent();
	
		void rotate(float x, float y);

		BodyComponent&	getCameraNode(){ return _cameraBodyNode; }

		bool getSpeedModifier() { return m_SpeedModifier; }

		CameraRenderable& getRenderable() {	return _cameraRenderable; }

		void IsDirty(bool isDirty);
		bool IsDirty();
		
		float m_CameraYaw;
		float m_CameraPitch;

	private:
		bool _isDirty;

		CameraRenderable&	_cameraRenderable;
		BodyComponent&		_cameraBodyNode;


		bool AutoTracking;
		bool FixedYawAxis;
		float m_deltaZoom;


		bool m_SpeedModifier;
		float mTopSpeed;
		bool mFastMove;
	};
}