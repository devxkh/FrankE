#include <XEngine/Components/PhysicsComponents.hpp>

#include <XEngine/Components/NetId.hpp>

namespace XE
{
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

	void CharacterPhysics::setRotation(const Ogre::Vector3& axis, float scalar)
	{
		character->setRotation(axis, scalar);
	}
	
	void CharacterPhysics::collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse)
	{
		auto netid = collider.component<NetIdComponent>();
		auto test2 = netid.get();

		auto body = collider.component<BodyComponent>();
		auto test = body.get();

		if (test2->entityID > 1)
		 {
			 std::cout << test2->entityID;

		}
	}

	void CharacterPhysics::create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject)
	{
		m_dynWorld = &dynWorld;
		character = dynWorld.createCharacter(physicObject);
	}
}