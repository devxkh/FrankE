#pragma once

#include <XESystem/Entityx/System.h>
#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>

namespace XE {

	struct CameraFreeComponent;
	class Scene;

	////////////////////////////////////////////////////////////
	/// \brief FreeLookCameraSystem class that can be controlled by a controller
	///
	////////////////////////////////////////////////////////////
	class XE_API FreeLookCameraSystem : public entityx::System < FreeLookCameraSystem >
	{
	public:
		FreeLookCameraSystem(Scene& scene);

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

	private:
		void updateCamera(CameraFreeComponent* camera, entityx::TimeDelta dt);

		Scene& m_Scene;
	};

} // namespace XE