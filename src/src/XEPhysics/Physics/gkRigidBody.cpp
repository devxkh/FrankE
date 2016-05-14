/*
-------------------------------------------------------------------------------
    This file is part of XEKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): Nestor Silveira.
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
#include <XEPhysics/Physics/gkDynamicsWorld.h>
//#include <XEEntity/GameEntity.hpp>
#include <XEPhysics/Physics/gkRigidBody.h>
//#include "XE::Scene.h"
//#include "XE::GameEntityInstance.h"
#include "btBulletDynamicsCommon.h"
#include <XESystem/TransportData.hpp>

#include <XESystem/Entityx/Entity.h>
#include <XESystem/Logging.hpp>


gkRigidBody::gkRigidBody(gkDynamicsWorld* owner)
	:    gkPhysicsController( owner),
			m_rigidBody(0)
	     , m_oldActivationState(-1)
{
	
}



gkRigidBody::~gkRigidBody()
{
	UTsize i;	
	for (i = 0; i < m_constraints.size(); i++)
	{		
		delete m_constraints[i];
	}
	m_constraints.clear();

	delete m_rigidBody;
	m_rigidBody = 0;

	m_collisionObject = 0;
}



btRigidBody* gkRigidBody::getBody(void)
{
	return m_rigidBody;
}


void gkRigidBody::update(const XFBType::PhysicsObject* physobject)
{


}

void gkRigidBody::create(const XFBType::PhysicsObject* physobject)
{
	if (m_rigidBody || m_collisionObject) //already created?
		return;

//	assert(m_object);// && m_object->isInstanced() && m_object->isInActiveLayer());

	createShape(physobject);
	if (!m_shape)
		return;


	/*const GameEntityProperties& props = m_object->getProperties();
	const gkPhysicsProperties& phy = props.m_physics;*/

	this->m_type = physobject->type();

	// use the most up to date transform.
	//const TransformState& tstate = m_object->getTransformState();
	//if (!m_object.component<XE::BodyComponent>())
	//{
	//	LOG(DEBUG) << "entity doesn't have a bodyComponent";
	//	return;
	//}
	//entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();

	//btTransform trans;
	//trans.setIdentity();
	//trans.setOrigin(btVector3(body->getPosition().x, body->getPosition().y, body->getPosition().z));
	//trans.setRotation(btQuaternion(body->getOrientation().x, body->getOrientation().y, body->getOrientation().z, body->getOrientation().w));

	if (this->isRigidOrDynamic())
	{
		btVector3 inertia;
		m_shape->calculateLocalInertia(physobject->mass(), inertia);

		m_rigidBody = new btRigidBody(physobject->mass(), this, m_shape, inertia);

		m_rigidBody->setLinearFactor(
		    btVector3(
			(physobject->mode() & GK_LOCK_LINV_X) ? 0.f : 1.f,
			(physobject->mode() & GK_LOCK_LINV_Y) ? 0.f : 1.f,
			(physobject->mode() & GK_LOCK_LINV_Z) ? 0.f : 1.f
		    ));

		if (this->isDynamic())
			m_rigidBody->setAngularFactor(0.f);
		else
		{
			m_rigidBody->setAngularFactor(
			    btVector3(
				(physobject->mode() & GK_LOCK_ANGV_X) ? 0.f : 1.f,
				(physobject->mode() & GK_LOCK_ANGV_Y) ? 0.f : 1.f,
				(physobject->mode() & GK_LOCK_ANGV_Z) ? 0.f : 1.f
			    ));
		}

		m_rigidBody->setDamping(physobject->linearDamp(), physobject->angularDamp());
	}
	else
	{
		m_rigidBody = new btRigidBody(0.f, 0, m_shape, btVector3(0, 0, 0));
		m_rigidBody->setDamping(0.f, 0.f);
		m_rigidBody->setAngularFactor(0.f);
	}

	btDynamicsWorld* dyn = getOwner();
	m_rigidBody->setUserPointer(this);

	m_rigidBody->setFriction(physobject->friction());
	m_rigidBody->setRestitution(physobject->restitution());
//	m_rigidBody->setWorldTransform(trans);// .toTransform());

	if (!this->isDosser())
		// No Sleep option in Blender
		m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	
	
	if (m_isGhost)
		m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	m_collisionObject = m_rigidBody;

	std::cout << "gkRigidBody - colgroupmask:" << physobject->colGroupMask() << std::endl;
	std::cout << "gkRigidBody - colmask:" << physobject->colMask() << std::endl;

	// both values have to be set
//	if (physobject->colMask() != -2 && physobject->colGroupMask() != -2)
		dyn->addRigidBody(m_rigidBody, physobject->colGroupMask(), physobject->colMask());
//	else
	//	dyn->addRigidBody(m_rigidBody);
}

void gkRigidBody::removeConstaints(void)
{
	btDynamicsWorld* dyn = getOwner();

	UTsize i;
	for (i = 0; i < m_constraints.size(); i++)
	{
		dyn->removeConstraint(m_constraints[i]);
		delete m_constraints[i];
	}
	m_constraints.clear();
}

void gkRigidBody::destroy(void)
{
	btDynamicsWorld* dyn = getOwner();

	removeConstaints();

	if (m_rigidBody)
	{
		// intertwine
		m_rigidBody->setUserPointer(0);
		m_rigidBody->setMotionState(0);

		if (!m_suspend)
			dyn->removeRigidBody(m_rigidBody);

		delete m_shape;
		m_shape = 0;

		delete m_rigidBody;
		m_rigidBody = 0;

		m_collisionObject = 0;
	}	
}

void gkRigidBody::addConstraint(btTypedConstraint* constraint, bool disableLinkedCollision)
{
	assert(constraint && m_constraints.find(constraint) == UT_NPOS);

	getOwner()->addConstraint(constraint, disableLinkedCollision);
	m_constraints.push_back(constraint);
}

void gkRigidBody::removeConstraint(btTypedConstraint* constraint)
{
	assert(constraint && m_constraints.find(constraint) != UT_NPOS);

	m_constraints.erase(m_constraints.find(constraint));
}


void gkRigidBody::createConstraints(const XFBType::PhysicsObject* physobject)
{
	entityx::Entity obj = getObject();
	//XE::Scene* scene = obj->getOwner();

	//GameEntityProperties&  props  = obj->getProperties();

	UTsize i;
	for (i = 0; i < physobject->physicsConstraints()->size(); i++)
	{
		const XFBType::PhysicsConstraint* cprops = physobject->physicsConstraints()->Get(i); //todo check obs geht??

		btRigidBody* rbA = getBody();
		btRigidBody* rbB = 0;

		if (!cprops->target())
		{
			//XE::GameEntity* target;
			//if (!obj->isGroupInstance())
			//	target = scene->findInstancedObject(cprops.m_target);
			//else
			//	target = obj->getGroupInstance()->getObject(cprops.m_target);

			//assert(target);// && target->getAttachedBody());

		//todo	rbB = target->getAttachedBody()->getBody();
		}

		btTypedConstraint* constraint = m_owner->createConstraint(rbA, rbB, cprops);

		if (constraint)
			addConstraint(constraint, cprops->disableLinkedCollision());

	}
}


void gkRigidBody::setLinearVelocity(const Ogre::Vector3& v, int tspace)
{
	if (m_suspend) // block
		return;

	if (!m_rigidBody)
		return;

	// only dynamic bodies
	if (m_rigidBody->isStaticOrKinematicObject())
		return;

	if (v.squaredLength() > GK_EPSILON * GK_EPSILON)
		m_rigidBody->activate();

	Ogre::Vector3 vel;
	switch (tspace)
	{
	case TRANSFORM_LOCAL:
		{
			btTransform trans = m_rigidBody->getCenterOfMassTransform();
			btQuaternion quat = trans.getRotation();
			vel = Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z())  * v;
		}
		break;
	case TRANSFORM_WORLD:
	case TRANSFORM_PARENT:
	default:
		vel = v;
		break;
	}

	btVector3 lf = m_rigidBody->getLinearFactor();
	if (gkFuzzy(lf.length2()))
		return;

	btVector3 nvel = btVector3(vel.x, vel.y, vel.z) * lf;
	if (gkFuzzy(nvel.length2()))
		return;

	m_rigidBody->setLinearVelocity(nvel);
}



void gkRigidBody::setAngularVelocity(const Ogre::Vector3& v, int tspace)
{
	if (m_suspend) // block
		return;

	if (!m_rigidBody)
		return;


	// only rigid bodies
	if (!(m_type == XFBType::PhysicsType_PT_RIGID))
		return;

	if (v.squaredLength() > GK_EPSILON * GK_EPSILON)
		m_rigidBody->activate();



	Ogre::Vector3 vel;
	switch (tspace)
	{
	case TRANSFORM_LOCAL:
		{
			btTransform trans = m_rigidBody->getCenterOfMassTransform();
			btQuaternion quat = trans.getRotation();
			vel = Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z())  * v;
		}
		break;
	case TRANSFORM_WORLD:
	case TRANSFORM_PARENT:
	default:
		vel = v;
		break;
	}


	btVector3 af = m_rigidBody->getAngularFactor();
	if (gkFuzzy(af.length2()))
		return;


	btVector3 nvel = btVector3(vel.x, vel.y, vel.z) * af;
	if (gkFuzzy(nvel.length2()))
		return;

	m_rigidBody->setAngularVelocity(nvel);
}



void gkRigidBody::applyTorque(const Ogre::Vector3& v, int tspace)
{
	if (m_suspend) // block
		return;

	if (!m_rigidBody)
		return;

	if (m_rigidBody->isStaticOrKinematicObject())
		return;

	if (v.squaredLength() > GK_EPSILON * GK_EPSILON) m_rigidBody->activate();

	Ogre::Vector3 vel;
	switch (tspace)
	{
	case TRANSFORM_LOCAL:
		{

			btTransform trans = m_rigidBody->getCenterOfMassTransform();
			btQuaternion quat = trans.getRotation();
			vel = Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z())  * v;
		}
		break;
	case TRANSFORM_WORLD:
	case TRANSFORM_PARENT:
	default:
		vel = v;
		break;
	}

	m_rigidBody->applyTorque(btVector3(vel.x, vel.y, vel.z));
}



void gkRigidBody::applyForce(const Ogre::Vector3& v, int tspace)
{
	if (m_suspend) // block
		return;

	if (!m_rigidBody)
		return;

	// only dynamic bodies
	if (m_rigidBody->isStaticOrKinematicObject())
		return;

	if (v.squaredLength() > GK_EPSILON * GK_EPSILON)
		m_rigidBody->activate();


	Ogre::Vector3 vel;

	switch (tspace)
	{
	case TRANSFORM_LOCAL:
		{

			btTransform trans = m_rigidBody->getCenterOfMassTransform();
			btQuaternion quat = trans.getRotation();
			vel = Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z())  * v;
		}
		break;
	case TRANSFORM_WORLD:
	case TRANSFORM_PARENT:
	default:
		vel = v;
		break;
	}

	m_rigidBody->applyCentralForce(btVector3(vel.x, vel.y, vel.z));
}



Ogre::Vector3 gkRigidBody::getLinearVelocity(void)
{
	if (m_suspend || m_rigidBody->isStaticOrKinematicObject() || !m_rigidBody)
		return Ogre::Vector3(0, 0, 0);

	return MathUtils::get(m_rigidBody->getLinearVelocity());
}


Ogre::Vector3 gkRigidBody::getAngularVelocity()
{
	// only rigid bodies
	if (m_suspend || !(m_type == XFBType::PhysicsType_PT_RIGID) || !m_rigidBody)
		return Ogre::Vector3(0, 0, 0);

	return MathUtils::get(m_rigidBody->getAngularVelocity());
}




void gkRigidBody::getWorldTransform(btTransform& worldTrans) const
{
	if (m_suspend  || !m_rigidBody)//|| !m_object->isInstanced() || !m_rigidBody)
		return;

	worldTrans.setIdentity();


	Ogre::Quaternion rot;
	Ogre::Vector3 loc;

	// see if we can benefit from cached transforms


	if (!m_body->getParent())
	{
		rot = m_body->_getDerivedOrientation();
		loc = m_body->_getDerivedPosition();
	}
	else
	{
		rot = m_body->getOrientation();
		loc = m_body->getPosition();
	}


	worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	worldTrans.setOrigin(btVector3(loc.x, loc.y, loc.z));
}

void gkRigidBody::forceWorldTransform(const btTransform& pWorldTrans)
{
	if (m_suspend || !m_rigidBody)// || !m_object->isInstanced() || !m_rigidBody)
		return;

	//m_rigidBody->setInterpolationWorldTransform(worldTrans);

		btTransform& worldTrans = m_rigidBody->getWorldTransform();
		worldTrans.setOrigin(pWorldTrans.getOrigin());
		setWorldTransform(pWorldTrans);
		//worldTrans.setOrigin(worldTrans)//ToBtVector3(position + ToQuaternion(worldTrans.getRotation()) * centerOfMass_));

		// When forcing the physics position, set also interpolated position so that there is no jitter
		// When not inside the simulation loop, this may lead to erratic movement of parented rigidbodies
		// so skip in that case. Exception made before first simulation tick so that interpolation position
		// of e.g. instantiated prefabs will be correct from the start
		/*if (!hasSimulated_ || physicsWorld_->IsSimulating())
		{*/
		/*	btTransform interpTrans = m_rigidBody->getInterpolationWorldTransform();
			interpTrans.setOrigin(worldTrans.getOrigin());
			m_rigidBody->setInterpolationWorldTransform(interpTrans);*/
		//}
}


void gkRigidBody::setWorldTransform(const btTransform& worldTrans)
{
	if (m_suspend || !m_rigidBody)// || !m_object->isInstanced() || !m_rigidBody)
		return;

	gkPhysicsController::setTransform(worldTrans);
}


void gkRigidBody::recalLocalInertia(void)
{
	assert(m_rigidBody && m_shape);
	if (!m_rigidBody || !m_shape) return;

	float mass = 1.f/ m_rigidBody->getInvMass();	

	btVector3 localInertia;
	m_shape->calculateLocalInertia(mass, localInertia);
	m_rigidBody->setMassProps(mass, localInertia);
}
