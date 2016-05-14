
#ifndef XE_HEIGHTFIELD_TERRAIN_SHAPE_H
#define XE_HEIGHTFIELD_TERRAIN_SHAPE_H

#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <XEPhysics/Export.hpp>

class XEPHYSICS_API HeightfieldTerrainShape : public btHeightfieldTerrainShape
{

public:
	/// preferred constructor
	/**
	This constructor supports a range of heightfield
	data types, and allows for a non-zero minimum height value.
	heightScale is needed for any integer-based heightfield data types.
	*/
	HeightfieldTerrainShape(int heightStickWidth, int heightStickLength,
		const void* heightfieldData, btScalar heightScale,
		btScalar minHeight, btScalar maxHeight,
		int upAxis, PHY_ScalarType heightDataType,
		bool flipQuadEdges);

	void processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

protected:
	

	/// this returns the vertex in bullet-local coordinates
	void getVertex(int x, int y, btVector3& vertex) const;
};

#endif // XE_HEIGHTFIELD_TERRAIN_SHAPE_H