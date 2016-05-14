#ifndef BulletMesh_h
#define BulletMesh_h

#include <XEEffect/Decal/OgreDecal.hpp>
#include <bullet/btBulletCollisionCommon.h>

#include <Ogre/OgreMain/include/OgreVector3.h>

namespace XE { class Scene; }

namespace OgreDecal {

class BulletMesh : public XE::TriangleMesh, public btTriangleCallback
{
public:

	BulletMesh(XE::Scene* scene);

	void setDebugDrawer(btIDebugDraw* debugDrawer) { m_debugDrawer = debugDrawer; }

	//void init();
//	inline void setMesh(btConcaveShape* mesh);

	void processTriangle(btVector3* triangle, int partId, int triangleIndex);

	void findTrianglesInAABB(const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, std::vector< XE::Triangle >& triangles);

	void addShape(btCollisionObject* meshPtr);

private:
	typedef std::vector<btCollisionObject*> MeshVector;
	typedef std::vector<btCollisionObject*>::iterator MeshVectorIt;

	Ogre::Vector3 mAABBMin, mAABBMax;
	std::vector< XE::Triangle >* mTriangles;
	
	btTransform m_worldTrans;
	MeshVector mMeshVector;
	MeshVectorIt mMeshIt;
	XE::Scene* mScene;
	btVector3 m_color;
	btIDebugDraw* m_debugDrawer;
};

} // ns OgreDecal

#endif