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
#ifndef _gkSweptTest_h_
#define _gkSweptTest_h_

//#include "gkCommon.h"
//#include "MathUtils.h"
#include <gamekit/utTypes.h>
#include <Ogre/OgreMain/include/OgreVector3.h>

namespace entityx { class Entity; }
namespace XE { class Ray; }

class btCollisionObject;

class gkSweptTest
{
public:
	typedef utArray<btCollisionObject*> AVOID_LIST;

	gkSweptTest(const AVOID_LIST& avoidList);

	~gkSweptTest();

	bool collides(const  XE::Ray& ray, float rayRadius);

	const Ogre::Vector3& getHitPoint() const { return m_hitPointWorld; }

	const Ogre::Vector3& getHitNormal() const { return m_hitNormalWorld; }

	const Ogre::Vector3& getReflection() const { return m_reflection; }

	const Ogre::Vector3& getSliding() const { return m_sliding; }

	const btCollisionObject* getCollisionObject() const { return m_collisionObject; }

	entityx::Entity getObject() const;

private:

	const AVOID_LIST& m_avoidList;

	Ogre::Vector3 m_hitPointWorld;

	const btCollisionObject* m_collisionObject;

	Ogre::Vector3 m_hitNormalWorld;

	// Reflection after hit
	Ogre::Vector3 m_reflection;

	// sliding vector along the plane(m_hitNormalWorld)
	// using the remaining component (after hit) of the ray direction component
	Ogre::Vector3 m_sliding;
};


#endif//_gkSweptTest_h_
