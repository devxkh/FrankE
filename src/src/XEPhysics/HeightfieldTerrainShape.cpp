#include <XEPhysics/HeightfieldTerrainShape.h>


HeightfieldTerrainShape::HeightfieldTerrainShape
(
int heightStickWidth, int heightStickLength, const void* heightfieldData,
btScalar heightScale, btScalar minHeight, btScalar maxHeight, int upAxis,
PHY_ScalarType hdt, bool flipQuadEdges
)
: btHeightfieldTerrainShape(heightStickWidth, heightStickLength, heightfieldData,
		heightScale, minHeight, maxHeight, upAxis, hdt,
		flipQuadEdges)
{

}


/// process all triangles within the provided axis-aligned bounding box
/**
basic algorithm:
- convert input aabb to local coordinates (scale down and shift for local origin)
- convert input aabb to a range of heightfield grid points (quantize)
- iterate over all triangles in that subset of the grid
*/
void	HeightfieldTerrainShape::processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const
{
	// scale down the input aabb's so they are in local (non-scaled) coordinates
	btVector3	localAabbMin = aabbMin*btVector3(1.f / m_localScaling[0], 1.f / m_localScaling[1], 1.f / m_localScaling[2]);
	btVector3	localAabbMax = aabbMax*btVector3(1.f / m_localScaling[0], 1.f / m_localScaling[1], 1.f / m_localScaling[2]);

	// account for local origin
	localAabbMin += m_localOrigin;
	localAabbMax += m_localOrigin;

	//quantize the aabbMin and aabbMax, and adjust the start/end ranges
	int	quantizedAabbMin[3];
	int	quantizedAabbMax[3];
	quantizeWithClamp(quantizedAabbMin, localAabbMin, 0);
	quantizeWithClamp(quantizedAabbMax, localAabbMax, 1);

	// expand the min/max quantized values
	// this is to catch the case where the input aabb falls between grid points!
	for (int i = 0; i < 3; ++i) {
		quantizedAabbMin[i]--;
		quantizedAabbMax[i]++;
	}

	int startX = 0;
	int endX = m_heightStickWidth - 1;
	int startJ = 0;
	int endJ = m_heightStickLength - 1;

	switch (m_upAxis)
	{
	case 0:
	{
		if (quantizedAabbMin[1]>startX)
			startX = quantizedAabbMin[1];
		if (quantizedAabbMax[1]<endX)
			endX = quantizedAabbMax[1];
		if (quantizedAabbMin[2]>startJ)
			startJ = quantizedAabbMin[2];
		if (quantizedAabbMax[2]<endJ)
			endJ = quantizedAabbMax[2];
		break;
	}
	case 1:
	{
		if (quantizedAabbMin[0]>startX)
			startX = quantizedAabbMin[0];
		if (quantizedAabbMax[0]<endX)
			endX = quantizedAabbMax[0];
		if (quantizedAabbMin[2]>startJ)
			startJ = quantizedAabbMin[2];
		if (quantizedAabbMax[2]<endJ)
			endJ = quantizedAabbMax[2];
		break;
	};
	case 2:
	{
		if (quantizedAabbMin[0]>startX)
			startX = quantizedAabbMin[0];
		if (quantizedAabbMax[0]<endX)
			endX = quantizedAabbMax[0];
		if (quantizedAabbMin[1]>startJ)
			startJ = quantizedAabbMin[1];
		if (quantizedAabbMax[1]<endJ)
			endJ = quantizedAabbMax[1];
		break;
	}
	default:
	{
		//need to get valid m_upAxis
		btAssert(0);
	}
	}




	for (int j = startJ; j<endJ; j++)
	{
		for (int x = startX; x<endX; x++)
		{
			btVector3 vertices[3];

			//http://www.ogre3d.org/forums/viewtopic.php?t=58756
			//if (j + 1 & 1 || m_flipQuadEdges || (m_useDiamondSubdivision && !((j + x) & 1)))
		//	if (m_flipQuadEdges || (m_useDiamondSubdivision && !((j)& 1))) // || (m_useZigzagSubdivision && !(j & 1)))
			if (m_flipQuadEdges || (m_useDiamondSubdivision && !((j + x) & 1)) || (m_useZigzagSubdivision && !(j & 1)))
			{
				//first triangle
				//getVertex(x, j, vertices[0]);
				//getVertex(x + 1, j, vertices[1]);
				//getVertex(x + 1, j + 1, vertices[2]);
				//callback->processTriangle(vertices, x, j);
				////second triangle
				//// getVertex(x,j,vertices[0]);//already got this vertex before, thanks to Danny Chapman
				//getVertex(x + 1, j + 1, vertices[1]);
				//getVertex(x, j + 1, vertices[2]);
				//callback->processTriangle(vertices, x, j);

				//meine Lösung die geht!!!
				//first triangle
				getVertex(x, j, vertices[0]);
				getVertex(x, j + 1, vertices[1]);
				getVertex(x + 1, j + 1, vertices[2]);
				callback->processTriangle(vertices, x, j);
				//second triangle
				// getVertex(x,j,vertices[0]);//already got this vertex before, thanks to Danny Chapman
				getVertex(x + 1, j + 1, vertices[1]);
				getVertex(x + 1, j, vertices[2]);
				callback->processTriangle(vertices, x, j);

				
			}
			else
			{
				//first triangle
				getVertex(x, j, vertices[0]);
				getVertex(x, j + 1, vertices[1]);
				getVertex(x + 1, j, vertices[2]);
				callback->processTriangle(vertices, x, j);
				//second triangle
				getVertex(x + 1, j, vertices[0]);
				//getVertex(x,j+1,vertices[1]);
				getVertex(x + 1, j + 1, vertices[2]);
				callback->processTriangle(vertices, x, j);
			}
		}
	}



}

void HeightfieldTerrainShape::getVertex(int x, int y, btVector3& vertex) const
{
	btAssert(x >= 0);
	btAssert(y >= 0);
	btAssert(x<m_heightStickWidth);
	btAssert(y<m_heightStickLength);

	btScalar	height = getRawHeightFieldValue(x, y);

	switch (m_upAxis)
	{
	case 0:
	{
		vertex.setValue(
			height - m_localOrigin.getX(),
			(-m_width / btScalar(2.0)) + x,
			(-m_length / btScalar(2.0)) + y
			);
		break;
	}
	case 1:
	{
		vertex.setValue(
			(-m_width / btScalar(2.0)) + x,
			height - m_localOrigin.getY(),
			(-m_length / btScalar(2.0)) + y
			);

		break;
	};
/*	case 1:
	{
		vertex.setValue(
			(-m_width / btScalar(2.0)) + x,
			height - m_localOrigin.getY(),
			(-m_length / btScalar(2.0)) + y
			);
		
		break;
	};*/
	case 2:
	{
		vertex.setValue(
			(-m_width / btScalar(2.0)) + x,
			(-m_length / btScalar(2.0)) + y,
			height - m_localOrigin.getZ()
			);

		break;
	}
	default:
	{
		//need to get valid m_upAxis
		btAssert(0);
	}
	}

	vertex *= m_localScaling;
}