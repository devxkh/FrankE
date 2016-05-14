#ifndef __PHYSICSCOMPONENTS_HPP__
#define __PHYSICSCOMPONENTS_HPP__

#include <XEPhysics/Physics/gkDynamicsWorld.h>
#include <XEPhysics/Physics/gkRigidBody.h>
#include <XEPhysics/Physics/gkCharacter.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

namespace XE
{
	struct IPhysicsObject
	{
	public:

		virtual void setEntityWithBody(entityx::Entity object) = 0;
		
		virtual void setTransformState(const TransformState& state) = 0;

		virtual void setRotation(const Ogre::Vector3& axis, float scalar) = 0;

		virtual void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse) = 0;

		sf::Uint16 Id;
	};

	struct PhysicsComponent
	{
		std::vector<std::unique_ptr<IPhysicsObject>> objects;
	};


	//struct CollisionShape : IPhysicsObject {
	//	explicit CollisionShape()
	//		: _gkPhysicsController(nullptr)
	//		, m_dynWorld(nullptr)
	//	{

	//	}

	//	~CollisionShape()
	//	{
	//		m_dynWorld->destroyObject(_gkPhysicsController);
	//	}

	//	void setRotation(const Ogre::Vector3& axis, float scalar)
	//	{
	//		//todo ?
	//	}

	//	void setTransformState(const TransformState& state)
	//	{
	//		_gkPhysicsController->setTransformState(state);
	//	}

	//	void setEntityWithBody(entityx::Entity object)
	//	{
	//		_gkPhysicsController->setEntityWithBody(object);
	//	}

	//	void create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
	//	{
	//		m_dynWorld = &dynWorld;
	//		_gkPhysicsController = dynWorld.createRigidBody(physicObject);
	//	}

	//	void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
	//	{

	//	}

	//	gkPhysicsController*      _gkPhysicsController;

	//private:
	//	gkDynamicsWorld* m_dynWorld;
	//};


	struct CharacterPhysics : IPhysicsObject
	{
		explicit CharacterPhysics();

		~CharacterPhysics();

		void setTransformState(const TransformState& state);

		void setEntityWithBody(entityx::Entity object);

		void setRotation(const Ogre::Vector3& axis, float scalar);

		void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse);
		void create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject);

		gkCharacter*      character;

	private:
		gkDynamicsWorld* m_dynWorld;
	};

	struct RigidBody : IPhysicsObject {
		explicit RigidBody( )
			: rigidBody(nullptr)
			, m_dynWorld(nullptr)
		{

		}

		~RigidBody()
		{
			m_dynWorld->destroyObject(rigidBody);
		}

		void setRotation(const Ogre::Vector3& axis, float scalar)
		{
			//todo ?
		}

		void setTransformState(const TransformState& state)
		{
			rigidBody->forceWorldTransform(state.toTransform());
		}

		void setEntityWithBody(entityx::Entity object)
		{
			rigidBody->setEntityWithBody(object);
		}

		void create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
		{
			m_dynWorld = &dynWorld;
			rigidBody = dynWorld.createRigidBody( physicObject);
		}

		void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
		{

		}


		gkRigidBody*      rigidBody;

	private:
		gkDynamicsWorld* m_dynWorld;
	};


}

#endif // __PHYSICSCOMPONENTS_HPP__