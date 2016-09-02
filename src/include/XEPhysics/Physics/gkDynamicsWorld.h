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
#ifndef _gkDynamicsWorld_h_
#define _gkDynamicsWorld_h_


//#include "gkCommon.h"
//#include "MathUtils.h"
#include <bullet/LinearMath/btScalar.h>
#include "gkGhost.h"

#include <XEDAL/Objects/FBEngineTypes_generated.h>

namespace entityx { class Entity; }
namespace XE { class Camera; class Scene; class PhysicsDebugDrawer; }
namespace Ogre { class PagedWorldSection; class Page; class TerrainGroup; }


class btDynamicsWorld;
class btCollisionConfiguration;
class btBroadphaseInterface;
class btDispatcher;
class btConstraintSolver;
class btRigidBody;
class btTypedConstraint;
class gkRigidBody;
class gkCharacter;
class btTriangleMesh;
class btCollisionShape;
class btGhostPairCallback;
class gkPhysicsDebug;
class gkDbvt;
//class gkPhysicsConstraintProperties;

class PhysTerrain;

typedef utArray<gkPhysicsController*>				gkPhysicsControllers;

class gkDynamicsWorld
{
public:

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void presubtick(float rate) = 0;
		virtual void subtick(float rate) = 0;
	};

	typedef utArray<Listener*> Listeners;


protected:


	XE::Scene&                    m_scene;
	btDynamicsWorld*            m_dynamicsWorld;
	btCollisionConfiguration*   m_collisionConfiguration;;
	btBroadphaseInterface*      m_pairCache;
	btGhostPairCallback*        m_ghostPairCallback;
	btDispatcher*               m_dispatcher;
	btConstraintSolver*         m_constraintSolver;
	gkPhysicsControllers        m_objects;
	XE::PhysicsDebugDrawer*             m_debug;
	bool                        m_handleContacts;
	//gkDbvt*                     m_dbvt;
	Listeners                   m_listeners;


	// drawing all but static wireframes
	void localDrawObject(gkPhysicsController* phyCon);

	void createInstanceImpl(void);
	void destroyInstanceImpl(void);

	static void substepCallback(btDynamicsWorld* dyn, btScalar tick);
	static void presubstepCallback(btDynamicsWorld *dyn, btScalar tick);

public:
	gkDynamicsWorld(const std::string& name, XE::Scene& scene);
	virtual ~gkDynamicsWorld();

	// Do one full physics step
	void step(float tick);
	void presubstep(float tick);
	void substep(float tick);

	void EnableContacts(bool enable) { m_handleContacts = enable; }

	btRigidBody* getFixedBody();
	btTypedConstraint* createConstraint(btRigidBody* rbA, btRigidBody* rbB, const XFBType::PhysicsConstraint* constraintprops);

	gkRigidBody* createRigidBody(const  XFBType::PhysicsObject* physobject);
	PhysTerrain* createTerrain( Ogre::TerrainGroup* group, Ogre::Page* page, Ogre::PagedWorldSection* section);
	gkCharacter* createCharacter( const  XFBType::PhysicsObject* physobject);
	gkGhost* createGhost( const  XFBType::PhysicsObject* physobject);
	void destroyObject(gkPhysicsController* cont);

	inline btDynamicsWorld* getBulletWorld(void) {assert(m_dynamicsWorld); return m_dynamicsWorld;}
	inline XE::Scene& getScene(void)               { return m_scene;}

	void enableDebugPhysics(bool enable, bool debugAabb);

	void resetContacts();

	//void handleDbvt(XE::Camera* cam);

	XE::PhysicsDebugDrawer* getDebug() const { return m_debug; }

	void DrawDebug();
	
	//gkVariable* getDBVTInfo(void);

	void exportBullet(const std::string& fileName);
	
	void addListener(Listener *listener);
	void removeListener(Listener *listener);

private:
	/// Simulation substeps per second.
	unsigned m_fps;
	
	/// Maximum number of simulation substeps per frame. 0 (default) unlimited, or negative values for adaptive timestep.
	int m_maxSubSteps;

	/// Time accumulator for non-interpolated mode.
	float m_timeAcc;

	/// Interpolation flag.
	bool m_interpolation;

	/// Simulating flag.
	bool m_simulating;

};


#endif//_gkDynamicsWorld_h_
