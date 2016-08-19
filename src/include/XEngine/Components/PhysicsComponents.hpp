#pragma once

#include <XEPhysics/Physics/gkDynamicsWorld.h>
#include <XEPhysics/Physics/gkRigidBody.h>
#include <XEPhysics/Physics/gkCharacter.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

namespace XE
{
	struct IPhysicsObject
	{
	public:
		virtual ~IPhysicsObject() { }

		virtual void setEntityWithBody(entityx::Entity object) = 0;
		
		virtual void setTransformState(const TransformState& state) = 0;

		virtual void setOrientation(const Ogre::Quaternion& orientation) = 0;
		
		virtual void rotate(const Ogre::Vector3& axis, float scalar) = 0;
	
		virtual void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse) = 0;

		sf::Uint16 Id;
	};

	struct PhysicsComponent
	{
		~PhysicsComponent();

		std::vector<std::unique_ptr<IPhysicsObject>> objects;
	};


	struct CharacterPhysics : IPhysicsObject
	{
		explicit CharacterPhysics();

		~CharacterPhysics();

		void setTransformState(const TransformState& state);

		void setEntityWithBody(entityx::Entity object);
				
		void setOrientation(const Ogre::Quaternion& orientation);

		void rotate(const Ogre::Vector3& axis, float scalar);

		void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse);

		void create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject);

		gkCharacter*      character;

	private:
		gkDynamicsWorld* m_dynWorld;
	};

	struct RigidBody : IPhysicsObject {

		explicit RigidBody();

		~RigidBody();

		void setOrientation(const Ogre::Quaternion& orientation);

		void rotate(const Ogre::Vector3& axis, float scalar);

		void setTransformState(const TransformState& state);
		
		void setEntityWithBody(entityx::Entity object);

		void create(gkDynamicsWorld& dynWorld, const XFBType::PhysicsObject* physicObject);

		void collided(entityx::Entity collider, const Ogre::Vector3& positionWorldOnB, const Ogre::Vector3& normalWorldOnB, float distance1, float appliedImpulse);

		gkRigidBody*      rigidBody;

	private:
		gkDynamicsWorld* m_dynWorld;
	};
}