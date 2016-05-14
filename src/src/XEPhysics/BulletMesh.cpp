#include <XEPhysics/BulletMesh.hpp>
#include <XEPhysics/Util/gkMathUtils.hpp>
//#include <XEEntity/Scene.hpp>

//#include <XEPhysics/gkDynamicsWorld.h>

#include <bullet/BulletDynamics/Dynamics/btDynamicsWorld.h>

namespace OgreDecal {

	//class DebugDrawcallback : public btTriangleCallback, public btInternalTriangleIndexCallback
	//{
	//	btIDebugDraw*	m_debugDrawer;
	//	btVector3	m_color;
	//	btTransform	m_worldTrans;
	//	BulletMesh& mBulletMesh;

	//public:

	//	DebugDrawcallback(BulletMesh& bulletMesh, btIDebugDraw*	debugDrawer, const btTransform& worldTrans, const btVector3& color) :
	//		mBulletMesh(bulletMesh),
	//		m_debugDrawer(debugDrawer),
	//		m_color(color),
	//		m_worldTrans(worldTrans)
	//	{
	//	}

	//	virtual void internalProcessTriangleIndex(btVector3* triangle, int partId, int  triangleIndex)
	//	{
	//		processTriangle(triangle, partId, triangleIndex);
	//	}

	//	virtual void processTriangle(btVector3* triangle, int partId, int triangleIndex)
	//	{
	//		(void)partId;
	//		(void)triangleIndex;

	//		btVector3 wv0, wv1, wv2;
	//		wv0 = m_worldTrans*triangle[0];
	//		wv1 = m_worldTrans*triangle[1];
	//		wv2 = m_worldTrans*triangle[2];
	//		btVector3 center = (wv0 + wv1 + wv2)*btScalar(1. / 3.);

	//		if (m_debugDrawer->getDebugMode() & btIDebugDraw::DBG_DrawNormals)
	//		{
	//			btVector3 normal = (wv1 - wv0).cross(wv2 - wv0);
	//			normal.normalize();
	//			btVector3 normalColor(1, 1, 0);
	//			m_debugDrawer->drawLine(center, center + normal, normalColor);
	//		}
	//		m_debugDrawer->drawLine(wv0, wv1, m_color);
	//		m_debugDrawer->drawLine(wv1, wv2, m_color);
	//		m_debugDrawer->drawLine(wv2, wv0, m_color);

	//		mTriangles->push_back(t);
	//	}
	//};

BulletMesh::BulletMesh(XE::Scene* scene)
	: m_debugDrawer(nullptr)
{
	//mMesh = 0;
	mTriangles = 0;

	mScene = scene;//;	scene->getDynamicsWorld()->getBulletWorld();
}

//void BulletMesh::init(btIDebugDraw* debugDrawer)
//{
//	m_debugDrawer = mScene->getDynamicsWorld()->getBulletWorld()->getDebugDrawer();
//}
//BulletMesh::BulletMesh(btConcaveShape* mesh)
//{
//	addShape(mesh);
//	mTriangles = 0;
//}

//void BulletMesh::setMesh(btConcaveShape* mesh)
//{
//	mMesh = mesh;
//}

void BulletMesh::addShape(btCollisionObject* mesh)
{
	mMeshVector.push_back(mesh);
}

void BulletMesh::processTriangle(btVector3* triangle, int partId, int triangleIndex)
{
	(void)partId;
	(void)triangleIndex;

	btVector3 wv0, wv1, wv2;
	wv0 = m_worldTrans*triangle[0];
	wv1 = m_worldTrans*triangle[1];
	wv2 = m_worldTrans*triangle[2];
	btVector3 center = (wv0 + wv1 + wv2)*btScalar(1. / 3.);

	if (m_debugDrawer->getDebugMode() & btIDebugDraw::DBG_DrawNormals)
	{
		btVector3 normal = (wv1 - wv0).cross(wv2 - wv0);
		normal.normalize();
		btVector3 normalColor(1, 1, 0);
		m_debugDrawer->drawLine(center, center + normal, normalColor);
	}
	m_debugDrawer->drawLine(wv0, wv1, m_color);
	m_debugDrawer->drawLine(wv1, wv2, m_color);
	m_debugDrawer->drawLine(wv2, wv0, m_color);

//todo	XE::Triangle t(MathUtils::get(wv0), MathUtils::get(wv1), MathUtils::get(wv2));
//todo	mTriangles->push_back(t);
}
//void BulletMesh::processTriangle(btVector3* triangle, int partId, int triangleIndex)
//{
//	//(void)partId;
//	//(void)triangleIndex;
//	//m_worldTrans
//	////btVector3 wv0, wv1, wv2;
//	//wv0 = m_worldTrans*triangle[0];
//	//wv1 = m_worldTrans*triangle[1];
//	//wv2 = m_worldTrans*triangle[2];
//	//btVector3 center = (wv0 + wv1 + wv2)*btScalar(1. / 3.);
//
//	//if (m_debugDrawer->getDebugMode() & btIDebugDraw::DBG_DrawNormals)
//	//{
//	//	btVector3 normal = (wv1 - wv0).cross(wv2 - wv0);
//	//	normal.normalize();
//	//	btVector3 normalColor(1, 1, 0);
//	//	m_debugDrawer->drawLine(center, center + normal, normalColor);
//	//}
//	//m_debugDrawer->drawLine(wv0, wv1, m_color);
//	//m_debugDrawer->drawLine(wv1, wv2, m_color);
//	//m_debugDrawer->drawLine(wv2, wv0, m_color);
//
//
//	/// Convert Bullet vectors to Ogre vectors
//	Ogre::Vector3 v1(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
//	Ogre::Vector3 v2(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
//	Ogre::Vector3 v3(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
//
//	OgreDecal::Triangle t(v1, v2, v3);
//
//	/// Check for false-positive
//	if (OgreDecal::collide_triangle_exact(mAABBMin, mAABBMax, t))
//		mTriangles->push_back(t);
//}

void BulletMesh::findTrianglesInAABB(const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, std::vector< XE::Triangle >& triangles)
{
	mTriangles = &triangles;
	mTriangles->clear();

	mAABBMin = aabbMin;
	mAABBMax = aabbMax;

	//colObj->getWorldTransform()
	
//	concaveMesh->processAllTriangles(&drawCallback, aabbMin, aabbMax);

	mMeshIt = mMeshVector.begin();
	for (; mMeshIt != mMeshVector.end(); ++mMeshIt)
	{

		m_worldTrans = (*mMeshIt)->getWorldTransform();
	//	DebugDrawcallback drawCallback(mScene->getDynamicsWorld()->getBulletWorld()->getDebugDrawer(), 
	//		(*mMeshIt)->getWorldTransform(), btVector3(0, 0, 0));
		static_cast<btConcaveShape*>((*mMeshIt)->getCollisionShape())->processAllTriangles(this, MathUtils::get(aabbMin), MathUtils::get(aabbMax));
		//static_cast<btConcaveShape*>((*mMeshIt)->getCollisionShape())->processAllTriangles(&drawCallback, MathUtils::get(aabbMin), MathUtils::get(aabbMax));
	}
	
	/*for (mMesh.begin();)
	{
		mMesh->processAllTriangles(this, MathUtils::get(aabbMin), MathUtils::get(aabbMax));
	}*/
	/// We no longer need to point to the triangle list
	mTriangles = 0;
}

} // ns OgreDecal