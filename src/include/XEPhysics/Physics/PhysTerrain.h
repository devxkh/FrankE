#ifndef _PTERRAIN_h_
#define _PTERRAIN_h_


//#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include "gkPhysicsController.h"

#include <Ogre/OgreMain/include/OgreVector3.h>

class btDynamicsWorld;
//class btPairCachingGhostObject;
class btHeightfieldTerrainShape;
//class btTriangleMesh;
class gkDynamicsWorld;

namespace Ogre{
	class Page;
	class PagedWorldSection;
	class TerrainGroup;
}

class PhysTerrain : public gkPhysicsController
{
public:

	PhysTerrain(gkDynamicsWorld* owner);
	virtual ~PhysTerrain();

//	btPairCachingGhostObject* getGhostObject() const;
	btHeightfieldTerrainShape* getTerrain() const { return mTerrain; }

//	void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTime);
	
	bool create(Ogre::TerrainGroup* group, Ogre::Page* page, Ogre::PagedWorldSection* section);
	void debugDraw(btIDebugDraw* debugDrawer) {}

//	void setGravity(float gravity);

	//void setRotation(const XE::Vector3& axis, float scalar);

	//void setJumpSpeed(float jumpSpeed);
	//void setFallSpeed(float fallSpeed);

	//void jump(void);

	//bool isOnGround(void);

	//void create(void);
	void destroy(void);

protected:

	void putTerrainData(int size, float* data,
		const float& minHeight,
		const float& maxHeight,
		const Ogre::Vector3& position,
		const float& scale);

	void setWorldTransform(const btTransform& worldTrans);

	btHeightfieldTerrainShape* mTerrain;
};

#endif//_gkCharacter_h_
