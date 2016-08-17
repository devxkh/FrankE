/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Nestor Silveira.

    Contributor(s): none yet.
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
#ifndef _gkCharacter_h_
#define _gkCharacter_h_

#include "gkPhysicsController.h"

namespace entityx { class Entity; }

class btDynamicsWorld;
class btPairCachingGhostObject;
class btKinematicCharacterController;
class btTriangleMesh;
class gkDynamicsWorld;


class gkCharacter : public gkPhysicsController, public btActionInterface
{
public:

	gkCharacter(gkDynamicsWorld* owner);
	virtual ~gkCharacter();

	void setWalkDirection(const Ogre::Vector3& wd, float walkSpeed);
	void setVelocity(const Ogre::Vector3& v, float timeInterval);
	void setLinearVelocity(float forward, float backward, float rightward, float leftward, float timeInterval);

	void setGhostTranformState(const TransformState& trans);

	btPairCachingGhostObject* getGhostObject() const;
	btKinematicCharacterController* getCharacterController() const { return m_character; }

	void updateAction( btCollisionWorld* collisionWorld, btScalar deltaTime);
	
	void debugDraw(btIDebugDraw* debugDrawer) {}

	void setGravity(float gravity);

	void setOrientation(const Ogre::Quaternion& orientation);
	void rotate(const Ogre::Vector3& axis, float scalar);

	void setJumpSpeed(float jumpSpeed);
	void setFallSpeed(float fallSpeed);

	void jump(void);

	bool isOnGround(void);

	void create(const XFBType::PhysicsObject* physData);
	void destroy(void);

protected:

	void setWorldTransform(const btTransform& worldTrans);

	btKinematicCharacterController* m_character;
};

#endif//_gkCharacter_h_
