/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

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
#ifndef _gkPhysicsController_h_
#define _gkPhysicsController_h_


#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>

//#include <XEEntity/GameEntity.hpp>
//#include <XEDAL/Serialize.hpp>
#include <XEPhysics/Util/TransformState.hpp>
#include <XESystem/Entityx/Entity.h>
#include <gamekit/utTypes.h>

namespace entityx { class Entity; }
namespace XE { struct AABB; }

class btDynamicsWorld;
class btTriangleMesh;
class gkDynamicsWorld;
class gkPhysicsController;

enum PhysicsObjectMode
{
	GK_GHOST = (1 << 0),  // gkCharacter controller
	GK_ACTOR = (1 << 1),  // Sensor listener
	GK_INVISIBLE = (1 << 2),  // Marked invisible
	GK_OCCLUDER = (1 << 3),  // Occluder
	GK_HAS_LOGIC = (1 << 4),  // Has game logic
	GK_IMMOVABLE = (1 << 5),  // Marked as an immovable object
	GK_STATIC_GEOM = (1 << 6)   // Is part of static batch geometry.
};


struct gkContactInfo
{
	gkPhysicsController* collider;
	btManifoldPoint      point;

	typedef utArray<gkContactInfo> Array;
	typedef utArrayIterator<Array> Iterator;
};

enum gkPhysicsMode
{
	GK_NO_SLEEP = (1 << 0),
	GK_CONTACT = (1 << 1),
	GK_LOCK_LINV_X = (1 << 2),
	GK_LOCK_LINV_Y = (1 << 3),
	GK_LOCK_LINV_Z = (1 << 4),
	GK_LOCK_ANGV_X = (1 << 5),
	GK_LOCK_ANGV_Y = (1 << 6),
	GK_LOCK_ANGV_Z = (1 << 7),
	GK_COMPOUND = (1 << 8),
	GK_COMPOUND_CHILD = (1 << 9)
};


///Base class for a physics object that gets updated along side a XE::GameEntity.
class gkPhysicsController
{
public:

	gkPhysicsController(gkDynamicsWorld* owner);
	virtual ~gkPhysicsController();


	virtual void setTransformState(const TransformState& state);

	void setEntityWithBody(entityx::Entity object);

	virtual void updateTransform(void);


	void suspend(bool v);
	bool isSuspended(void) {return m_suspend;}


	//gkPhysicsProperties& getProperties(void);

	void enableContactProcessing(bool v);

	gkContactInfo::Array&    getContacts(void);
	gkContactInfo::Iterator  getContactIterator(void);


	// Collision tests.

	bool collidesWith(entityx::Entity ob, gkContactInfo* cpy = 0);
	bool collidesWith(const std::string& name, gkContactInfo* cpy = 0, bool emptyFilter = true);

	// Sensor tests,
	// If prop is empty and material is empty, return any old collision.
	// If onlyActor is true, filter collision on actor settings (XE::GameEntityProperties).
	// If testAllMaterials is true, test all assigned opposed to only testing the first assigned.
//	bool sensorCollides(const std::string& prop, const std::string& material = "", bool onlyActor = false, bool testAllMaterials = false);
	bool sensorCollides(const std::string& prop, const std::string& material, bool onlyActor, bool testAllMaterials, utArray<entityx::Entity*>* list = NULL);
	static bool sensorTest(entityx::Entity ob, const std::string& prop, const std::string& material = "", bool onlyActor = false, bool testAllMaterials = false);

	static gkPhysicsController* castController(btCollisionObject* colObj);
	static gkPhysicsController* castController(const btCollisionObject* colObj);
	static gkPhysicsController* castController(void* colObj);
	static entityx::Entity castObject(btCollisionObject* colObj);
	static entityx::Entity castObject(const btCollisionObject* colObj);


	btCollisionObject* getCollisionObject(void);

	btCollisionShape* getShape(void);

	btDynamicsWorld* getOwner(void);

	entityx::Entity getObject(void);


	XE::AABB&  getAabb(void) const;

	void setShape(btCollisionShape* shape);


	virtual void create(const XFBType::PhysicsObject* physData)  {}
	virtual void destroy(void) {}

	virtual void _handleManifold(btPersistentManifold* manifold);
	void _resetContactInfo(void);
	bool _markDbvt(bool v);
	
	btCollisionShape* _createShape(const XFBType::PhysicsObject* physData);

	bool m_isGhost;
protected:

//	PhysicsObjectMode m_mode;

	int         m_type;
	int         m_mode;

	inline bool isRigidOrDynamic(void)     const { return m_type == XFBType::PhysicsType_PT_DYNAMIC || m_type == XFBType::PhysicsType_PT_RIGID; }
	inline bool isDosser(void)             const { return (m_mode & GK_NO_SLEEP) == 0; }
	inline bool isDynamic(void)            const { return m_type == XFBType::PhysicsType_PT_DYNAMIC; }
	inline bool isContactListener(void)    const { return (m_mode & GK_CONTACT) != 0; }

	void setTransform(const btTransform& worldTrans);


	void createShape(const XFBType::PhysicsObject* physData);
	void destroyShape(btCollisionShape* shape);

	gkContactInfo::Array m_localContacts;

	gkDynamicsWorld* m_owner;
	entityx::Entity m_object;

	btCollisionObject* m_collisionObject;

	btCollisionShape* m_shape;
	bool m_suspend;
	bool m_dbvtMark;

	Ogre::Vector3		m_renderOffset;
	//gkPhysicsProperties m_props;
};

#endif//_gkPhysicsController_h_
