/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
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
#ifndef _gkRigidBody_h_
#define _gkRigidBody_h_

#include "gkPhysicsController.h"
#include "LinearMath/btMotionState.h"


#include <XEngine/Components/Body.hpp>

namespace entityx { class Entity; }

class btDynamicsWorld;
class btRigidBody;
class btTriangleMesh;
class btCollisionShape;
class gkDynamicsWorld;




// gkRigidBody handles:
// dynamic (no angular velocity), rigid, and static bodies
class gkRigidBody : public gkPhysicsController, public btMotionState
{
public:
	gkRigidBody(gkDynamicsWorld* owner);
	virtual ~gkRigidBody();

	void        applyTorque(const Ogre::Vector3& t, int tspace = TRANSFORM_PARENT);
	void        applyForce(const Ogre::Vector3& f, int tspace = TRANSFORM_PARENT);


	void        setLinearVelocity(const Ogre::Vector3& linv, int tspace = TRANSFORM_PARENT);
	void        setAngularVelocity(const Ogre::Vector3& angv, int tspace = TRANSFORM_PARENT);
	Ogre::Vector3   getLinearVelocity(void);
	Ogre::Vector3   getAngularVelocity(void);

	inline int setActivationState(int newActivationState)
	{
		int oldState = m_oldActivationState;

		m_oldActivationState = newActivationState;

		return oldState;
	}

	btRigidBody* getBody(void);

	void addConstraint(btTypedConstraint* constraint, bool disableLinkedCollision = false);
	void removeConstraint(btTypedConstraint* constraint);

	inline UTsize getConstraintCount(void)				{ return m_constraints.size(); }
	inline btTypedConstraint* getConstraint(UTsize i)	{ return m_constraints[i];     }

	void update(const XFBType::PhysicsObject* physobject);
	void create(const XFBType::PhysicsObject* physobject);
	void destroy(void);

	void createConstraints(const XFBType::PhysicsObject* physobject);
	void removeConstaints(void);

	void recalLocalInertia(void);

	/// force physics position of the rigidbody
	void forceWorldTransform(const btTransform& worldTrans);

private:

	void getWorldTransform(btTransform& worldTrans) const;
	void setWorldTransform(const btTransform& worldTrans);

	btRigidBody* m_rigidBody;
	utArray<btTypedConstraint*> m_constraints;

	entityx::ComponentHandle<XE::BodyComponent> m_body;

	int m_oldActivationState;
};

#endif//_gkRigidBody_h_
