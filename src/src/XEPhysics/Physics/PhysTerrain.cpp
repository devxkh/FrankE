#include <XEPhysics/Physics/PhysTerrain.h>
#include <XEPhysics/Physics/gkDynamicsWorld.h>
//#include <XEEntity/GameEntity.hpp> 
//#include <XEEntity/Scene.hpp> 
//#include "gkEntity.h"
//#include "gkMesh.h"
#include <XEPhysics/Physics/gkRigidBody.h>
#include "btBulletDynamicsCommon.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
//#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <XEPhysics/HeightfieldTerrainShape.h>

//KH #### #include <Ogre/Components/Terrain/include/OgreTerrain.h>
//KH #### #include <Ogre/Components/Terrain/include/OgreTerrainGroup.h>

//#include <Ogre/OgreMain/include/OgreLogManager.h>

using namespace Ogre;

PhysTerrain::PhysTerrain(gkDynamicsWorld* owner)
	: gkPhysicsController( owner), mTerrain(nullptr)
{
}




PhysTerrain::~PhysTerrain()
{
	delete mTerrain;
	mTerrain = 0;

	delete m_collisionObject;
	m_collisionObject = 0;
}




//void PhysTerrain::create(void)
//{
//	if (mTerrain || m_collisionObject)
//		return;
//
//
//	assert(m_object);// && m_object->isInstanced() && m_object->isInActiveLayer());
//
//	// use the most up to date transform.
//	//const TransformState& trans = m_object->getTransformState();
//
//
//	//createShape();
//
//
//	//if (!m_shape)
//	//	return;
//
//
//	//btPairCachingGhostObject* ghost = new btPairCachingGhostObject();
//	//ghost->setCollisionShape(m_shape);
//
//	//m_collisionObject = ghost;
//
//	//// basic material properties
//	//ghost->setFriction(m_props.m_friction);
//	//ghost->setRestitution(m_props.m_restitution);
//
//	//ghost->setWorldTransform(trans.toTransform());
//
//	//// intertwine
//	//ghost->setUserPointer(this);
//
//	//btDynamicsWorld* dyn = getOwner();
//	//
//	//btCollisionShape* pShape = ghost->getCollisionShape();
//
//	//gkPhysicsProperties& physProps = m_object->getProperties().m_physics;
//
//	//float stepHeight = physProps.m_charStepHeight == -1
//	//	? getAabb().getSize().z / 1.5f
//	//	: physProps.m_charStepHeight;
//
//	//mTerrain->setJumpSpeed(physProps.m_charJumpSpeed);
//	//mTerrain->setFallSpeed(physProps.m_charFallSpeed);
//
//	//mTerrain->setUpAxis(1);   //KH Changed!!!!! y = up axis not z (blender is Z)
//
//	//	dyn->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter);
//
//
//	//Flags sau wichtig für static collision!!!
//	///only collide with static for now (no interaction with dynamic objects)
//	//dyn->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter); //physProps.m_colGroupMask, physProps.m_colMask);
//
//	//dyn->addAction(this);
//
//	//Reset from bullet demo
//	//	dyn->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(ghost->getBroadphaseHandle(), dyn->getDispatcher());
//	//	mTerrain->reset(dyn);
//	///WTF
//	//	mTerrain->warp(btVector3(10.210001, -2.0306311, 16.576973));
//}

/*! enum. HeightFieldTesselation
desc.
Tesselation mode for Quads in HeightFields
enums.
HeightFieldTesselation_NE_SW -- NorthEast (TopRight) to SouthWest (BottomLeft).
HeightFieldTesselation_NW_SE -- NorthWest (TopLeft) to SouthEast (BottomRight).
*/
enum HeightFieldTesselation
{
	HeightFieldTesselation_NE_SW = 0,
	HeightFieldTesselation_NW_SE = 1
};

void PhysTerrain::putTerrainData(int size, float* data,
	const float& minHeight,
	const float& maxHeight,
	const Ogre::Vector3& position,
	const float& scale)
{


//	float height = data[(size * z) + x];
//	short sample = (short)(((height - minHeight) / (maxHeight - minHeight)) * (normMax - normMin) + normMin);
	//float normMin = -32768.0f;
	//float normMax = 32767.0f;

	//// Sample the data to the manual heightfield
	//	for (int x = 0; x < size; ++x)
	//	{
	//		HeightFieldTesselation tess = HeightFieldTesselation_NW_SE;
	//		for (int z = size - 1; z >= 0; --z)
	//		{
	//			float height = data[(size * z) + x];
	//			short sample = (short)(((height - minHeight) / (maxHeight - minHeight)) * (normMax - normMin) + normMin);
	//		
	//			
	//			memcpy(mTerrainHeights + sample, //target
	//				data + size * (size - x - 1), //source
	//				sizeof(float)* size); //size

	//			//mhf.sample(sample, 0, 0, tess);
	//			
	//			if (tess == HeightFieldTesselation_NE_SW)
	//				tess = HeightFieldTesselation_NW_SE;
	//			else
	//				tess = HeightFieldTesselation_NE_SW;
	//		}
	//	}

	// Convert height data in a format suitable for the physics engine
	float* mTerrainHeights = new float[size * size];
	assert(mTerrainHeights != 0);

	for (int i = 0; i < size; i++)
		memcpy(mTerrainHeights + size * i, //target
		data + size * (size - i - 1), //source
		sizeof(float)* size); //size


	btScalar heightScale = 1.f;
	btVector3 localScaling(scale, heightScale, scale);

	HeightfieldTerrainShape* mTerrainShape = new HeightfieldTerrainShape(
		size, size, mTerrainHeights, 1 /*ignore*/, minHeight, maxHeight, 1, PHY_FLOAT, false);
//	mTerrainShape->setUseDiamondSubdivision(true);
	mTerrainShape->setUseZigzagSubdivision(true);
	mTerrainShape->setLocalScaling(localScaling);

//	mTerrainShape->setMargin(0.5);
	//mCollisionShapes.push_back(mTerrainShape);
	Ogre::Quaternion rot = Ogre::Quaternion::IDENTITY;

	btDefaultMotionState *groundState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(0.0f, 0.0f, 0.0f)));


	btRigidBody* mGroundBody = new btRigidBody(0, groundState, mTerrainShape);

	mGroundBody->setGravity(btVector3(0,9.81,0));
	mGroundBody->setFriction(0.8f); // m_props.m_friction
	mGroundBody->setHitFraction(0.8f);
	mGroundBody->setRestitution(0.6f);// m_props.m_restitution

	//mGroundBody->getWorldTransform().setOrigin(btVector3(position.x,position.y,position.z) + btVector3(0, heightScale, 0));
	mGroundBody->getWorldTransform().setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	
	mGroundBody->getWorldTransform().setOrigin(btVector3(position.x, position.y + (maxHeight - minHeight) / 2, position.z));

	mGroundBody->setCollisionFlags(mGroundBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

	btDynamicsWorld* dyn = getOwner();
	mGroundBody->setUserPointer(this);

	m_shape = mTerrainShape; // for physics controller
	m_collisionObject = mGroundBody;
	// Add the body to dynamics world
	dyn->addRigidBody(mGroundBody);
}

bool PhysTerrain::create(Ogre::TerrainGroup* group, Ogre::Page* page, Ogre::PagedWorldSection* section)
{
	if (mTerrain || m_collisionObject)
		return false;

	//http://www.ogre3d.org/forums/viewtopic.php?f=2&t=60354
//	assert(m_object);

	// Get terrain group
	/*XE::WRLD::TerrainPagedWorldSection* worldSection =
	static_cast<XE::WRLD::TerrainPagedWorldSection*>(section);
	if (!worldSection)
	return false;*/
	//Ogre::TerrainGroup* group = mTerrainGroup; // worldSection->getTerrainGroup();
	assert(group);

	// Find terrain X,Y coordinates
	long pageX, pageY;
	//page->getID() ---- 0
	//KH #### group->unpackIndex(0, &pageX, &pageY);
	if (!(pageX == 0 && pageY == 0))
		return true;

	// Get terrain at X,Y coordinates
	//KH #### 	Ogre::Terrain* terrain = group->getTerrain(pageX, pageY);
	//KH #### 	if (!terrain)
	//KH #### 		return false;

	// Get terrain height data
	//KH #### 	float* data = terrain->getHeightData();
	//KH #### 	if (!data)
	//KH #### 		return false;
	// Calculate world scale
	//KH #### 	float scale = terrain->getWorldSize() / (terrain->getSize() - 1);

	//KH #### 	LogManager::getSingleton().logMessage(std::string("[World::Terrain]")
		//KH #### 		+ " pageX " + StringConverter::toString(pageX)
		//KH #### 		+ " pageY " + StringConverter::toString(pageY)
		//KH #### 		+ "; minHeight=" + StringConverter::toString(terrain->getMinHeight())
		//KH #### 		+ "; maxHeight=" + StringConverter::toString(terrain->getMaxHeight())
		//KH #### 		+ "; worldSize=" + StringConverter::toString(terrain->getWorldSize())
		//KH #### 		+ "; size=" + StringConverter::toString(terrain->getSize())
		//KH #### 		+ "; scale=" + StringConverter::toString(scale)
		//KH #### 		+ "; position=" + StringConverter::toString(terrain->getPosition()));

	// Now feed the physics engine
	/*Physics::PhysicsManager::getSingleton().putTerrainData(
	terrain->getSize(), data,
	terrain->getMinHeight(), terrain->getMaxHeight(),
	terrain->getPosition(), scale);*/
	//KH #### 	putTerrainData(
	//KH #### 		terrain->getSize(), data,
	//KH #### 		terrain->getMinHeight(), terrain->getMaxHeight(),
	//KH #### 		terrain->getPosition(), scale);

	return true;
}

//btPairCachingGhostObject* PhysTerrain::getGhostObject() const
//{
//	assert(m_collisionObject);
//	return static_cast<btPairCachingGhostObject*>(m_collisionObject);
//}



void PhysTerrain::destroy(void)
{
	//assert(m_object);

	if (m_collisionObject)
	{
		// intertwine
		m_collisionObject->setUserPointer(0);

		//	assert(m_object->isInActiveLayer());

		//m_owner->getBulletWorld()->removeAction(mTerrain);
		m_owner->getBulletWorld()->removeCollisionObject(m_collisionObject);

		delete m_shape;

		m_shape = 0;

		delete mTerrain;

		mTerrain = 0;

		delete m_collisionObject;

		m_collisionObject = 0;
	}
}


void PhysTerrain::setWorldTransform(const btTransform& worldTrans)
{
	if (!mTerrain || !m_collisionObject)
		return;

	gkPhysicsController::setTransform(worldTrans);

}