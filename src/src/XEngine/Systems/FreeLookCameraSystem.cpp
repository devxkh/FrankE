#include <XEngine/Systems/FreeLookCameraSystem.hpp>


#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <XEngine/Components/ScreenComponent.hpp>
#include <XEPhysics/Physics/gkDynamicsWorld.h>
#include <XESystem/QueueManager.hpp>
#include <XEngine/Scene.hpp>
#include <XEngine/Components/Body.hpp>
#include <XEngine/Components/CameraFree.hpp>
#include <XEPhysics/Util/gkMathUtils.hpp>

namespace XE {

	FreeLookCameraSystem::FreeLookCameraSystem(Scene& scene)
		: m_Scene(scene)
	{
	}

	void FreeLookCameraSystem::updateCamera(CameraFreeComponent* camera, entityx::TimeDelta dt)
	{


//			//-----------------------------------------
//			//Check for Collision
//			//-----------------------------------------
//			return;
//
//
//			//look at the vehicle
//
//			entityx::ComponentHandle<BodyComponent> body = camera->getTarget()->component<BodyComponent>();
//
//			btTransform characterWorldTrans; // = body->getWorldTransformState().toTransform();
//			characterWorldTrans.setIdentity();
//			characterWorldTrans.setOrigin(btVector3(body->getPosition().x, body->getPosition().y, body->getPosition().z));
//			characterWorldTrans.setRotation(btQuaternion(body->getOrientation().x, body->getOrientation().y, body->getOrientation().z, body->getOrientation().w));
//
//			btVector3 up = characterWorldTrans.getBasis()[1];
//			btVector3 backward = -characterWorldTrans.getBasis()[2];
//			up.normalize();
//			backward.normalize();
//
//			btVector3 m_cameraTargetPosition = characterWorldTrans.getOrigin();
//			btVector3 m_cameraPosition = MathUtils::get(body->getPosition());// m_cameraTargetPosition + up * 10.0 + backward * 12.0;
//
//			//use the convex sweep test to find a safe position for the camera (not blocked by static geometry)
//			btSphereShape cameraSphere(0.2f);
//			btTransform cameraFrom, cameraTo;
//			cameraFrom.setIdentity();
//			cameraFrom.setOrigin(characterWorldTrans.getOrigin());
//			cameraTo.setIdentity();
//			cameraTo.setOrigin(m_cameraPosition);
//
//			btCollisionWorld::ClosestConvexResultCallback cb(characterWorldTrans.getOrigin(), cameraTo.getOrigin());
//			cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
//
//			m_Scene.getDynamicsWorld().getBulletWorld()->convexSweepTest(&cameraSphere, cameraFrom, cameraTo, cb);
//			if (cb.hasHit())
//			{
//				btScalar minFraction = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
//				m_cameraPosition.setInterpolate3(cameraFrom.getOrigin(), cameraTo.getOrigin(), minFraction);
//
//				camera->getBody()->setPosition(MathUtils::get(m_cameraPosition));
//			}
//		}
		/* if (camera->getStyle() == CA_FREE)
		{*/

			//Vector3 camMovementDir = camera->getMove(); // (camMovementX, slideUpDown, camMovementZ);
			//camMovementDir.normalize();
			//camMovementDir *= dt * 10.0f * (1 + camera->getSpeedModifier() * 5);

			//camera->moveRelative(camMovementDir);
			//}

	}

	void FreeLookCameraSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<CameraFreeComponent> camera;

		for (entityx::Entity entity : es.entities_with_components(camera)) {

			if (camera->IsDirty())
			{
			//	updateCamera(camera.get(), dt);
				BodyComponent& camNode = camera->getCameraNode();

				auto debugCamera = camera.get();
				
				camNode.setOrientation(Ogre::Quaternion(1,0,0,0));
				camNode.yaw(Ogre::Radian(camera->m_CameraYaw), TransformSpace::TS_WORLD);
				camNode.pitch(Ogre::Radian(camera->m_CameraPitch));

				camera.get()->getRenderable().updateTransform(camNode.getPosition(), camNode.getOrientation());

			//	camera->m_CameraYaw = 0;
		//		camera->m_CameraPitch = 0;

				camera->IsDirty(false);
			}	  
		}
	}

} // namespace XE
