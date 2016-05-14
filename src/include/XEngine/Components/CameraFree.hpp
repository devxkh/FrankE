#ifndef __CAMERAFREECOMPONENT_HPP__
#define __CAMERAFREECOMPONENT_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>
#include <XEngine/Components/Body.hpp>
#include <XERenderer/CameraRenderable.hpp>

namespace XE
{
	struct CameraFreeComponent  {

	public:
		CameraFreeComponent(CameraRenderable& cameraRenderable);
		
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

		CameraRenderable& _cameraRenderable;
		XE::BodyComponent _cameraBodyNode;


		bool AutoTracking;
		bool FixedYawAxis;
		float m_deltaZoom;


		bool m_SpeedModifier;
		float mTopSpeed;
		bool mFastMove;
	};
}

#endif // __CAMERAFREECOMPONENT_HPP__