/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Nestor Silveira.

    Contributor(s): Charlie C. Danil Ko.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include <XEPhysics/Physics/gkCharacter.h>
#include <XEPhysics/Physics/gkDynamicsWorld.h>
//#include  <XEEntity/GameEntity.hpp> //"XE::GameEntity.h"
//#include <XEEntity/Scene.hpp> //"XE::Scene.h"
//#include "gkEntity.h"
//#include "gkMesh.h"
#include <XEPhysics/Physics/gkRigidBody.h>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

#include <iostream>

gkCharacter::gkCharacter(gkDynamicsWorld* owner)
	: gkPhysicsController(owner), m_character(nullptr)
{
}




gkCharacter::~gkCharacter()
{
	delete m_character;
	m_character = 0;

	delete m_collisionObject;
	m_collisionObject = 0;
}

void gkCharacter::getGhostTranformState(TransformState& state)
{
	state.toTransform(m_collisionObject->getWorldTransform());
}

void gkCharacter::setGhostTranformState(const TransformState& trans)
{
	m_collisionObject->setWorldTransform(trans.toTransform());
}

void gkCharacter::create(const XFBType::PhysicsObject* physData)
{
	if (m_character || m_collisionObject)
		return;


	//assert(m_object);// && m_object->isInstanced() && m_object->isInActiveLayer());

	// use the most up to date transform.
	//const TransformState& trans = m_object->getTransformState();
	//entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();

	//btTransform trans;
	//trans.setIdentity();
	//trans.setOrigin(btVector3(body->getPosition().x, body->getPosition().y, body->getPosition().z));
	//trans.setRotation(btQuaternion(body->getOrientation().x, body->getOrientation().y, body->getOrientation().z, body->getOrientation().w));

	std::cout << "PhysObj - mass:" << physData->mass() << std::endl;

	std::cout << "PhysObj - friction:" << physData->friction() << std::endl;
	std::cout << "PhysObj - restitution:" << physData->restitution() << std::endl;
	std::cout << "PhysObj - charStepHeight:" << physData->charStepHeight() << std::endl;
	std::cout << "PhysObj - charJumpSpeed:" << physData->charJumpSpeed() << std::endl;
	std::cout << "PhysObj - mass:" << physData->mass() << std::endl;
	std::cout << "PhysObj - colgroupmask:" << physData->colGroupMask() << std::endl;
	std::cout << "PhysObj - colmask:" << physData->colMask() << std::endl;

	createShape(physData);


	if (!m_shape)
		return;


	btPairCachingGhostObject* ghost = new btPairCachingGhostObject();
	ghost->setCollisionShape(m_shape);

	//btOverlappingPairCallback* m_ghostPairCallback = new btGhostPairCallback();
	//m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(m_ghostPairCallback);

	m_collisionObject = ghost;

	// basic material properties
	ghost->setFriction(physData->friction());
	ghost->setRestitution(physData->restitution());



	//todo??ghost->setWorldTransform(trans);// .toTransform());

	// intertwine
	ghost->setUserPointer(this);

	btDynamicsWorld* dyn = getOwner();

	ghost->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	btCollisionShape* pShape = ghost->getCollisionShape();

	//todo getaab size
	/*float stepHeight = physData->charStepHeight() == -1
							? getAabb().getSize().z / 1.5f
							: physData->charStepHeight();*/
	float stepHeight =  physData->charStepHeight();

	m_character = new btKinematicCharacterController(
	    ghost, static_cast<btConvexShape*>(ghost->getCollisionShape()), stepHeight);


	m_character->setJumpSpeed(physData->charJumpSpeed());
	m_character->setFallSpeed(physData->charJumpSpeed());

	m_character->setUpAxis(1);   //KH Changed!!!!! y = up axis not z (blender is Z)

//	dyn->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter);


	//Flags sau wichtig für static collision!!!
	///only collide with static for now (no interaction with dynamic objects)
	dyn->addCollisionObject(ghost, physData->colGroupMask(), btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter); //physProps.m_colGroupMask, physProps.m_colMask);
	//dyn->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter); //physProps.m_colGroupMask, physProps.m_colMask);

	dyn->addAction(this);

	//Reset from bullet demo
//	dyn->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(ghost->getBroadphaseHandle(), dyn->getDispatcher());
//	m_character->reset(dyn);
	///WTF
//	m_character->warp(btVector3(10.210001, -2.0306311, 16.576973));
}



btPairCachingGhostObject* gkCharacter::getGhostObject() const
{
	assert(m_collisionObject);
	return static_cast<btPairCachingGhostObject*>(m_collisionObject);
}



void gkCharacter::destroy(void)
{
	//assert(m_object);

	if (m_collisionObject)
	{
		// intertwine
		m_collisionObject->setUserPointer(0);

	//	assert(m_object->isInActiveLayer());

		m_owner->getBulletWorld()->removeAction(this); // m_character);
		m_owner->getBulletWorld()->removeCollisionObject(m_collisionObject);

		delete m_shape;

		m_shape = 0;

		delete m_character;

		m_character = 0;

		delete m_collisionObject;

		m_collisionObject = 0;
	}
}


void gkCharacter::setWalkDirection(const Ogre::Vector3& wd, float timeInterval)
{


	///set walkDirection for our character
	btTransform ghostPos;
	ghostPos = getGhostObject()->getWorldTransform();
	btVector3 forwardDir = ghostPos.getBasis()[2];
	//	printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = ghostPos.getBasis()[1];
	btVector3 strafeDir = ghostPos.getBasis()[0];
	forwardDir.normalize();
	upDir.normalize();
	strafeDir.normalize();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	//btScalar walkVelocity = btScalar(1.1) * 4.0; // 4 km/h -> 1.1 m/s
	//btScalar walkSpeed = walkVelocity * dt;

	//if (gForward)
	//	walkDirection += forwardDir;

	//if (gBackward)
	//	walkDirection -= forwardDir;

		//m_character->setWalkDirection(walkDirection*walkSpeed);
	
	btTransform xform = getGhostObject()->getWorldTransform();
	Ogre::Vector3 result = MathUtils::get(xform.getRotation()) * wd; ///??????


	setVelocity(result, timeInterval);

//---------- m_character->setWalkDirection(MathUtils::get(result) * 0.001);//;walkSpeed);

	//m_character->setWalkDirection(btVector3(wd.x, wd.y, wd.z)*walkSpeed);
	
	//-----------------------------------------------------------------
	// calculate actuall goal direction in world based on player's key directions
	//mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
	//mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
	//mGoalDirection.y = 0;
	//mGoalDirection.normalise();

	//Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

	// calculate how much the character has to turn to face goal direction
	//Real yawToGoal = toGoal.getYaw().valueDegrees();
	// this is how much the character CAN turn this frame
	//Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;

	// turn as much as we can, but not more than we need to
	//if (yawToGoal < 0) yawToGoal = std::min<Real>(0, std::max<Real>(yawToGoal, yawAtSpeed));
	//else if (yawToGoal > 0) yawToGoal = std::max<Real>(0, std::min<Real>(yawToGoal, yawAtSpeed));

	//mBodyNode->yaw(Degree(yawToGoal));

	//m_character->setWalkDirection(btVector3(wd.x * direction, wd.y * direction, wd.z * direction)*walkSpeed);
	//mCCPlayer->setIsMoving(true);

	//----------------------------------------------------------------------
}

void gkCharacter::setVelocity(const Ogre::Vector3& v, float timeInterval)
{
	if (!m_character || !m_collisionObject)
		return;

	btVector3 velocity = btVector3(v.x, v.y, v.z);

	m_character->setVelocityForTimeInterval(velocity, timeInterval);
}

void gkCharacter::setLinearVelocity(float forward, float backward, float rightward, float leftward, float timeInterval)
{
	btTransform xform =  getGhostObject()->getWorldTransform();

	Ogre::Vector3 walkDirection(0.f, 0.f, 0.f);

	if (leftward != 0)
		walkDirection -= Ogre::Vector3(leftward, 0.f, 0.f);

	if (rightward != 0)
		walkDirection += Ogre::Vector3(rightward, 0.f, 0.f);

	if (forward != 0)
		walkDirection += Ogre::Vector3(0.f, 0.f, forward);

	if (backward != 0)
		walkDirection -= Ogre::Vector3(0.f, 0.f, backward);

	Ogre::Vector3 result = MathUtils::get(xform.getRotation()) * walkDirection;

	setVelocity(result, timeInterval); 
} 




void gkCharacter::setWorldTransform(const btTransform& worldTrans)
{
	if (!m_character || !m_collisionObject)
		return;

	gkPhysicsController::setTransform(worldTrans);

}




void gkCharacter::updateAction( btCollisionWorld* collisionWorld, btScalar deltaTime)
{
	if (!m_character || !m_collisionObject)
		return;

	m_character->updateAction(collisionWorld, deltaTime);

	setWorldTransform(m_collisionObject->getWorldTransform());
}



void gkCharacter::setGravity(float gravity)
{
	m_character->setGravity(btScalar(gravity));
}

void gkCharacter::setOrientation(const Ogre::Quaternion& orientation)
{
	m_character->getGhostObject()->getWorldTransform().setRotation(MathUtils::get(orientation));
}

void gkCharacter::rotate(const Ogre::Vector3& axis, float scalar)
{
	btMatrix3x3 orn = m_character->getGhostObject()->getWorldTransform().getBasis();
	orn *= btMatrix3x3(btQuaternion(MathUtils::get(axis), scalar));
	m_character->getGhostObject()->getWorldTransform().setBasis(orn);
}

void gkCharacter::setJumpSpeed(float jumpSpeed)
{
	m_character->setJumpSpeed(jumpSpeed);
}


void gkCharacter::setFallSpeed(float fallSpeed)
{
	m_character->setFallSpeed(fallSpeed);
}


void gkCharacter::jump(void)
{
	m_character->jump();
}

bool gkCharacter::isOnGround(void)
{
	return m_character->onGround();
}

