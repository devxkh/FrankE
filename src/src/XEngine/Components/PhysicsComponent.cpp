#include <XEngine/Components/PhysicsComponents.hpp>

#include <XEngine/Components/NetId.hpp>

namespace XE
{

	PhysicsComponent::~PhysicsComponent()
	{
	}

	RigidBody::RigidBody()
		: rigidBody(nullptr)
		, m_dynWorld(nullptr)
	{

	}

	RigidBody::~RigidBody()
	{
		m_dynWorld->destroyObject(rigidBody);
	}

	void RigidBody::setOrientation(const Ogre::Quaternion& orientation)
	{
		//todo ?
	}

	void RigidBody::rotate(const Ogre::Vector3& axis, float scalar)
	{
		//todo ?
	}

	void RigidBody::setTransformState(const TransformState& state)
	{
		rigidBody->forceWorldTransform(state.toTransform());
	}

	void RigidBody::setEntityWithBody(entityx::Entity object)
	{
		rigidBody->setEntityWithBody(object);
	}

	void RigidBody::create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
	{
		m_dynWorld = &dynWorld;
		rigidBody = dynWorld.createRigidBody(physicObject);
	}

	void RigidBody::collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
	{

	}



	Ghost::Ghost()
		: ghost(nullptr)
		, m_dynWorld(nullptr)
	{

	}

	Ghost::~Ghost()
	{
		m_dynWorld->destroyObject(ghost);
	}

	void Ghost::setOrientation(const Ogre::Quaternion& orientation)
	{
		//todo ?
	}

	void Ghost::rotate(const Ogre::Vector3& axis, float scalar)
	{
		//todo ?
	}

	void Ghost::setTransformState(const TransformState& state)
	{
		ghost->setTransformState(state);
	}

	void Ghost::setEntityWithBody(entityx::Entity object)
	{
		ghost->setEntityWithBody(object);
	}

	void Ghost::create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
	{
		m_dynWorld = &dynWorld;
		ghost = dynWorld.createGhost(physicObject);
	}

	void Ghost::collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
	{

	}


	CharacterPhysics::CharacterPhysics() :
		character(nullptr)
		, m_dynWorld(nullptr)
	{

	}

	CharacterPhysics::~CharacterPhysics()
	{
		m_dynWorld->destroyObject(character);
	}

	void CharacterPhysics::setTransformState(const TransformState& state)
	{
		character->setGhostTranformState(state); // setTransformState(state);
	}

	void CharacterPhysics::setEntityWithBody(entityx::Entity object)
	{
		character->setEntityWithBody(object);
	}

	void CharacterPhysics::setOrientation(const Ogre::Quaternion& orientation)
	{
		character->setOrientation(orientation);
	}

	void CharacterPhysics::rotate(const Ogre::Vector3& axis, float scalar)
	{
		character->rotate(axis, scalar);
	}

	void CharacterPhysics::collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
	{
		auto netid = collider.component<NetIdComponent>();
		auto test2 = netid.get();

		auto body = collider.component<BodyComponent>();
		auto test = body.get();

		if (test2->entityID > 1)
		{
			//	 std::cout << test2->entityID;

		}
	}

	void CharacterPhysics::create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
	{
		m_dynWorld = &dynWorld;
		character = dynWorld.createCharacter(physicObject);
	}
}