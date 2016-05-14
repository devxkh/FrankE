#ifndef __FREELOOKCAMERACONTROLLER_HPP__
#define __FREELOOKCAMERACONTROLLER_HPP__

#include <XESystem/Entityx/System.h>
#include <XESystem/TransportData.hpp>

#include <XEngine/Components/CameraFree.hpp>


namespace XE {

	class Scene;
	class QueueManager;
	class GraphicsManager;
	class CameraRenderable;

	////////////////////////////////////////////////////////////
	/// \brief FreeLookCameraSystem class that can be controlled by a controller
	///
	////////////////////////////////////////////////////////////
	class FreeLookCameraSystem : public entityx::System < FreeLookCameraSystem > 
	{	
		public:
			FreeLookCameraSystem(Scene& scene);

			void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

		private:
			void updateCamera(CameraFreeComponent* camera, entityx::TimeDelta dt);

			Scene& m_Scene;
		};

	} // namespace XE

#endif //__CAMERACONTROLLER_HPP__