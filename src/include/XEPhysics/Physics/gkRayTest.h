/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Nestor Silveira.

    Contributor(s): Thomas Trocha(dertom)
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
#ifndef _gkRayTest_h_
#define _gkRayTest_h_

//#include "gkCommon.h"
//#include "MathUtils.h"
#include "btBulletDynamicsCommon.h"
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XESystem/Entityx/Entity.h>

class btCollisionObject;
class gkDynamicsWorld;

namespace entityx { class Entity; }

namespace Ogre { class Ray; }

namespace XE {
	class Scene;
	class Ray;
}

class gkRayTest
{
public:
	
	struct gkRayTestFilter : public btCollisionWorld::RayResultCallback
	{
		virtual bool filterFunc(btCollisionObject* ob) const {return true;}
		
		// taken from ClosestRayResultCallback
		btVector3	m_hitNormalWorld;
		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace);
	};
	
	gkRayTest(gkDynamicsWorld* physicsWorld);

	~gkRayTest();

	bool collides(const Ogre::Ray& ray);
        
	// rayCallback is a struct for filtering objects that will be ray tested;
	// gkRayTestFilter.filterFunc is called with each colliding objects
	// until it returns true.
	bool collides(const Ogre::Vector3& from, const Ogre::Vector3& to,gkRayTestFilter& rayCallback);

	const Ogre::Vector3& getHitPoint() const { return m_hitPointWorld; }

	const Ogre::Vector3& getHitNormal() const { return m_hitNormalWorld; }

	const btCollisionObject* getCollisionObject() const { return m_collisionObject; }

	entityx::Entity getObject() const;

	float getHitFraction() const {return m_hitFraction;}

private:

	Ogre::Vector3 m_hitPointWorld;

	Ogre::Vector3 m_hitNormalWorld;

	const btCollisionObject* m_collisionObject;

	float m_hitFraction;

	gkDynamicsWorld* m_physicsWorld;
};


struct notMeFilter : gkRayTest::gkRayTestFilter
{
	notMeFilter(entityx::Entity self)
	:m_self(self) {}
	
	entityx::Entity m_self;
		
	virtual bool filterFunc(btCollisionObject* ob) const;
};


struct xrayFilter : gkRayTest::gkRayTestFilter
{
	xrayFilter(entityx::Entity self, const std::string& prop, const std::string& material)
	:m_self(self), m_prop(prop), m_material(material) {}
	
	entityx::Entity m_self;
	std::string m_prop, m_material;
		
	virtual bool filterFunc(btCollisionObject* ob) const;
};

/*
// C style callback
struct gkRayTestCStyleFilter : gkRayTest::gkRayTestFilter
{
	gkRayTestCStyleFilter(bool (*filterFunc)(btCollisionObject*, void *),
				void *filterFuncData)
	:m_filterFunc(filterFunc),
	m_filterFuncData(filterFuncData)
	{}
		
	bool (*m_filterFunc)(btCollisionObject*, void *);
	void *m_filterFuncData;

	virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
};
*/

#endif//_gkRayTest_h_
