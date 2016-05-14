#include <float.h>
#include <XEEffect/Decal/DecalUtility.hpp>
#include <cassert>

namespace XE
{
    /*
     THE FOLLOWING WAS MODIFIED FROM BULLET SOURCE CODE, UNDER THE ZLIB LICENSE
     */
    
    #define BOX_PLANE_EPSILON 0.000001f
    
    enum eBT_PLANE_INTERSECTION_TYPE
    {
        BT_CONST_BACK_PLANE = 0,
        BT_CONST_COLLIDE_PLANE,
        BT_CONST_FRONT_PLANE
    };

    /*! Vector blending
     Takes two vectors a, b, blends them together*/
    void vec_blend(Ogre::Vector3 &vr, const Ogre::Vector3 &va,const Ogre::Vector3 &vb, double blend_factor)
    {
        vr = (1-blend_factor)*va + blend_factor*vb;
    }


    //! This function calcs the distance from a 3D plane
    void plane_clip_polygon_collect(
                                                         const Ogre::Vector3 & point0,
                                                         const Ogre::Vector3 & point1,
                                                         double dist0,
                                                         double dist1,
                                                         Ogre::Vector3 * clipped,
                                                         int & clipped_count)
    {
        bool _prevclassif = (dist0>DBL_EPSILON);
        bool _classif = (dist1>DBL_EPSILON);
        if(_classif!=_prevclassif)
        {
            double blendfactor = -dist0/(dist1-dist0);
            
            assert(clipped_count < MAX_CLIPPED_POINTS);
            vec_blend(clipped[clipped_count],point0,point1,blendfactor);
            clipped_count++;
        }
        if(!_classif)
        {
            assert(clipped_count < MAX_CLIPPED_POINTS);
            clipped[clipped_count] = point1;
            clipped_count++;
        }
    }

    double distance_point_plane(const Ogre::Vector4 & plane,const Ogre::Vector3 &point)
    {
        return point.dotProduct( Ogre::Vector3(plane.x, plane.y, plane.z) ) - plane[3];
    }

    int plane_clip_polygon(
                              const Ogre::Vector4 & plane,
                              const Ogre::Vector3 * polygon_points,
                              int polygon_point_count,
                              Ogre::Vector3 * clipped)
    {
        int clipped_count = 0;
        
        
        //clip first point
        double firstdist = distance_point_plane(plane,polygon_points[0]);
        if(!(firstdist>DBL_EPSILON))
        {
            assert(clipped_count < MAX_CLIPPED_POINTS);
            
            clipped[clipped_count] = polygon_points[0];
            clipped_count++;
        }
        
        double olddist = firstdist;
        for(int i=1;i<polygon_point_count;i++)
        {
            double dist = distance_point_plane(plane,polygon_points[i]);
            
            plane_clip_polygon_collect(
                                          polygon_points[i-1],polygon_points[i],
                                          olddist,
                                          dist,
                                          clipped,
                                          clipped_count);
            
            
            olddist = dist;
        }
        
        //RETURN TO FIRST  point
        
        plane_clip_polygon_collect(
                                      polygon_points[polygon_point_count-1],polygon_points[0],
                                      olddist,
                                      firstdist,
                                      clipped,
                                      clipped_count);
        
        return clipped_count;
    }
    
    

    
    
    ///Swap numbers
void BT_SWAP_NUMBERS(double& a, double& b)
{
    a = a+b; 
    b = a-b; 
    a = a-b; 
}

bool TEST_CROSS_EDGE_BOX_MCR(Ogre::Vector3& edge, Ogre::Vector3& absolute_edge, const Ogre::Vector3& pointa, const Ogre::Vector3& pointb, Ogre::Vector3& _extend,
                             int i_dir_0, int i_dir_1, int i_comp_0, int i_comp_1)
{
    const double dir0 = -edge[i_dir_0];
    const double dir1 = edge[i_dir_1];
    double pmin = pointa[i_comp_0]*dir0 + pointa[i_comp_1]*dir1;
    double pmax = pointb[i_comp_0]*dir0 + pointb[i_comp_1]*dir1;
    
    if(pmin>pmax)
    {
        BT_SWAP_NUMBERS(pmin,pmax); 
    }
    
    const double abs_dir0 = absolute_edge[i_dir_0];
    const double abs_dir1 = absolute_edge[i_dir_1];
    const double rad = _extend[i_comp_0] * abs_dir0 + _extend[i_comp_1] * abs_dir1;
    
    if(pmin>rad || -rad>pmax) 
        return false;
        
    return true;
}

    
bool TEST_CROSS_EDGE_BOX_X_AXIS_MCR(Ogre::Vector3& edge, Ogre::Vector3& absolute_edge, const Ogre::Vector3& pointa, 
                                    const Ogre::Vector3& pointb, Ogre::Vector3& _extend)
{
    return TEST_CROSS_EDGE_BOX_MCR(edge,absolute_edge,pointa,pointb,_extend,2,1,1,2);
}

bool TEST_CROSS_EDGE_BOX_Y_AXIS_MCR(Ogre::Vector3& edge, Ogre::Vector3& absolute_edge, const Ogre::Vector3& pointa, 
                                    const Ogre::Vector3& pointb, Ogre::Vector3& _extend)
{
    return TEST_CROSS_EDGE_BOX_MCR(edge,absolute_edge,pointa,pointb,_extend,0,2,2,0);
}

bool TEST_CROSS_EDGE_BOX_Z_AXIS_MCR(Ogre::Vector3& edge, Ogre::Vector3& absolute_edge, const Ogre::Vector3& pointa, 
                                    const Ogre::Vector3& pointb, Ogre::Vector3& _extend)
{
    return TEST_CROSS_EDGE_BOX_MCR(edge,absolute_edge,pointa,pointb,_extend,1,0,0,1);
}

    
    void get_center_extend(const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, Ogre::Vector3 & center,Ogre::Vector3 & extend)
	{
		center = (m_max+m_min)*0.5f;
		extend = m_max - center;
	}
    
    void projection_interval(const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, const Ogre::Vector3 & direction, double &vmin, double &vmax)
	{
		Ogre::Vector3 center = (m_max+m_min)*0.5f;
		Ogre::Vector3 extend = m_max-center;
        
		double _fOrigin =  direction.dotProduct(center);
		double _fMaximumExtent = extend.dotProduct(Ogre::Vector3( fabs( direction.x ), fabs( direction.y ), fabs( direction.z ) ));
		vmin = _fOrigin - _fMaximumExtent;
		vmax = _fOrigin + _fMaximumExtent;
	}
    
    eBT_PLANE_INTERSECTION_TYPE plane_classify(const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, const Ogre::Vector4 &plane)
	{
		double _fmin,_fmax;
		projection_interval(m_min, m_max, Ogre::Vector3(plane.x, plane.y, plane.z), _fmin, _fmax);
        
		if(plane[3] > _fmax + BOX_PLANE_EPSILON)
		{
			return BT_CONST_BACK_PLANE; // 0
		}
        
		if(plane[3]+BOX_PLANE_EPSILON >=_fmin)
		{
			return BT_CONST_COLLIDE_PLANE; //1
		}
		return BT_CONST_FRONT_PLANE;//2
	}
    
    //! Simple test for planes.
	bool collide_plane(const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, const Ogre::Vector4 & plane)
	{
		eBT_PLANE_INTERSECTION_TYPE classify = plane_classify(m_min, m_max, plane);
		return (classify == BT_CONST_COLLIDE_PLANE);
	}
    
    //! test for a triangle, with edges
	bool collide_triangle_exact( const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, const Triangle& triangle)
	{
        
        //Ogre::Vector3 n = (triangle.v[1] - triangle.v[0]).crossProduct( triangle.v[2] - triangle.v[0] );
        //n.normalise();
        
        const Ogre::Vector3& n = triangle.normal;
        
        Ogre::Vector4 triangle_plane( n.x, n.y, n.z, triangle.v[0].dotProduct( n ) );
        
        
		if(!collide_plane(m_min, m_max, triangle_plane)) 
            return false;
        
		Ogre::Vector3 center,extends;
		get_center_extend(m_min, m_max, center,extends);
        
        
		const Ogre::Vector3 v1(triangle.v[0] - center);
		const Ogre::Vector3 v2(triangle.v[1] - center);
		const Ogre::Vector3 v3(triangle.v[2] - center);
        
		//First axis
		Ogre::Vector3 diff(v2 - v1);
		Ogre::Vector3 abs_diff = Ogre::Vector3( fabs(diff.x), fabs(diff.y), fabs(diff.z) ); //diff.absolute();
		//Test With X axis
		if (!TEST_CROSS_EDGE_BOX_X_AXIS_MCR(diff,abs_diff,v1,v3,extends))
            return false;
		//Test With Y axis
		if (!TEST_CROSS_EDGE_BOX_Y_AXIS_MCR(diff,abs_diff,v1,v3,extends))
            return false;
        
		//Test With Z axis
		if (!TEST_CROSS_EDGE_BOX_Z_AXIS_MCR(diff,abs_diff,v1,v3,extends))
            return false;
        
        
		diff = v3 - v2;
		abs_diff = Ogre::Vector3( fabs(diff.x), fabs(diff.y), fabs(diff.z) ); //diff.absolute();
		//Test With X axis
		if (!TEST_CROSS_EDGE_BOX_X_AXIS_MCR(diff,abs_diff,v2,v1,extends))
            return false;
        
		//Test With Y axis
		if (!TEST_CROSS_EDGE_BOX_Y_AXIS_MCR(diff,abs_diff,v2,v1,extends))
            return false;
		//Test With Z axis
		if (!TEST_CROSS_EDGE_BOX_Z_AXIS_MCR(diff,abs_diff,v2,v1,extends))
            return false;
        
		diff = v1 - v3;
		abs_diff = Ogre::Vector3( fabs(diff.x), fabs(diff.y), fabs(diff.z) ); //diff.absolute();
		//Test With X axis
		if (!TEST_CROSS_EDGE_BOX_X_AXIS_MCR(diff,abs_diff,v3,v2,extends))
            return false;
		//Test With Y axis
		if (!TEST_CROSS_EDGE_BOX_Y_AXIS_MCR(diff,abs_diff,v3,v2,extends))
            return false;
		//Test With Z axis
		if (!TEST_CROSS_EDGE_BOX_Z_AXIS_MCR(diff,abs_diff,v3,v2,extends))
            return false;
        
		return true;
	}
    
    
    double area3D_Polygon( int n, const Ogre::Vector3* V, const Ogre::Vector3& N )
    {
        double area = 0;
        double an, ax, ay, az;  // abs value of normal and its coords
        int   coord;           // coord to ignore: 1=x, 2=y, 3=z
        int   i, j, k;         // loop indices
        
        // select largest abs coordinate to ignore for projection
        ax = (N.x>0 ? N.x : -N.x);     // abs x-coord
        ay = (N.y>0 ? N.y : -N.y);     // abs y-coord
        az = (N.z>0 ? N.z : -N.z);     // abs z-coord
        
        coord = 3;                     // ignore z-coord
        if (ax > ay) {
            if (ax > az) coord = 1;    // ignore x-coord
        }
        else if (ay > az) coord = 2;   // ignore y-coord
        
        // compute area of the 2D projection
        for (i=1, j=2, k=0; i<=n; i++, j++, k++)
            switch (coord) {
                case 1:
                    area += (V[i].y * (V[j].z - V[k].z));
                    continue;
                case 2:
                    area += (V[i].x * (V[j].z - V[k].z));
                    continue;
                case 3:
                    area += (V[i].x * (V[j].y - V[k].y));
                    continue;
            }
        
        // scale to get area before projection
        an = sqrt( ax*ax + ay*ay + az*az);  // length of normal vector
        switch (coord) {
            case 1:
                area *= (an / (2*ax));
                break;
            case 2:
                area *= (an / (2*ay));
                break;
            case 3:
                area *= (an / (2*az));
        }
        return fabs(area);
    }
    
    /// create a list of unique points, and a list of triangles with indicies into that list
    
    bool isDuplicate( const std::vector<UniquePoint>& uniquePoints, const Ogre::Vector3& p, int& duplicateIndex )
    {
        std::vector<UniquePoint>::const_iterator iter;
        
        int index = 0;
        
        for (iter = uniquePoints.begin(); iter != uniquePoints.end(); ++iter)
        {
            if ( fabs( iter->p.x - p.x ) < VEC_EPSILON && fabs( iter->p.y - p.y ) < VEC_EPSILON && fabs( iter->p.z - p.z ) < VEC_EPSILON )
            {
                duplicateIndex = index;
                return true;
            }
            
            ++index;
        }
        
        return false;
    }
    
    bool isDuplicate( const std::vector< Ogre::Vector3 >& points, const Ogre::Vector3& p )
    {
        std::vector< Ogre::Vector3 >::const_iterator iter;
        
        for (iter = points.begin(); iter != points.end(); ++iter)
        {
            if ( fabs( iter->x - p.x ) < VEC_EPSILON && fabs( iter->y - p.y ) < VEC_EPSILON && fabs( iter->z - p.z ) < VEC_EPSILON )
            {
                return true;
            }
            
        }
        
        return false;
    }

        
    double max( double a, double b )
    {
        if (a > b)
            return a;
        
        return b;
    }

    double min( double a, double b )
    {
        if (a < b)
            return a;
        
        return b;
    }
    
    double average( double a, double b )
    {
        return (a + b) * 0.5;
    }
    
    bool collide_triangle_bounding_box( const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, const Triangle& triangle )
    {
        static float minX, maxX, minY, maxY, minZ, maxZ, x, y, z;
        
        minX = maxX = triangle.v[0].x;
        minY = maxY = triangle.v[0].y;
        minZ = maxZ = triangle.v[0].z;
        
        for (int i = 1; i < 3; ++i)
        {
            x = triangle.v[i].x;
            y = triangle.v[i].y;
            z = triangle.v[i].z;
            
            if (x < minX)
                minX = x;
            
            if (x > maxX)
                maxX = x;
            
            if (y < minY)
                minY = y;
            
            if (y > maxY)
                maxY = y;
            
            if (z < minZ)
                minZ = z;
            
            if (z > maxZ)
                maxZ = z;
        }
        
        if ( minX > aabbMax.x || maxX < aabbMin.x || minY > aabbMax.y ||
            maxY < aabbMin.y || minZ > aabbMax.z || maxZ < aabbMin.z )
		{
			return false;
		}
        
		return true;
    }

    
    // Extract verticies and indicies from an Ogre3D Mesh into arrays
    /// This is a modified version taken from the Ogre wiki
	void extractTrianglesFromMesh(std::vector<Triangle>& triangleList, const Ogre::v1::MeshPtr& mesh,
                            const Ogre::Vector3 &position,
                            const Ogre::Quaternion &orient,
                            Ogre::Vector3 scale )
    {
        
   //     bool added_shared = false;
   //     size_t current_offset = 0;
   //     size_t shared_offset = 0;
   //     size_t next_offset = 0;
   //     size_t index_offset = 0;
   //     
   //     size_t index_count = 0;
   //     size_t vertex_count = 0;
   //     
   //     // Calculate how many vertices and indices we're going to need
   //     for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
   //     {
			//Ogre::v1::SubMesh* submesh = mesh->getSubMesh(i);
   //         
   //         // We only need to add the shared vertices once
   //         if(submesh->useSharedVertices)
   //         {
   //             if( !added_shared )
   //             {
   //                 vertex_count += mesh->sharedVertexData->vertexCount;
   //                 added_shared = true;
   //             }
   //         }
   //         else
   //         {
   //             vertex_count += submesh->vertexData->vertexCount;
   //         }
   //         
   //         // Add the indices
   //         index_count += submesh->indexData->indexCount;
   //     }
   //     
   //     
   //     // Allocate space for the vertices and indices
   //     Ogre::Vector3* vertices = new Ogre::Vector3[vertex_count];
   //     unsigned long* indices = new unsigned long[index_count];
   //     
   //     added_shared = false;
   //     
   //     // Run through the submeshes again, adding the data into the arrays
   //     for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
   //     {
			//Ogre::v1::SubMesh* submesh = mesh->getSubMesh(i);
   //         
			//Ogre::v1::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
   //         
   //         if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
   //         {
   //             if(submesh->useSharedVertices)
   //             {
   //                 added_shared = true;
   //                 shared_offset = current_offset;
   //             }
   //             
			//	const Ogre::v1::VertexElement* posElem =
   //             vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
   //             
			//	Ogre::v1::HardwareVertexBufferSharedPtr vbuf =
   //             vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
   //             
   //             unsigned char* vertex =
			//		static_cast<unsigned char*>(vbuf->lock(Ogre::v1::HardwareBuffer::HBL_READ_ONLY));
   //             
   //             // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
   //             //  as second argument. So make it float, to avoid trouble when Ogre::Real will
   //             //  be comiled/typedefed as double:
   //             //      Ogre::Real* pReal;
   //             float* pReal;
   //             
   //             for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
   //             {
   //                 posElem->baseVertexPointerToElement(vertex, &pReal);
   //                 
   //                 Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
   //                 
   //                 vertices[current_offset + j] = (orient * (pt * scale)) + position;
   //             }
   //             
   //             vbuf->unlock();
   //             next_offset += vertex_data->vertexCount;
   //         }
   //         
   //         
   //         Ogre::v1::IndexData* index_data = submesh->indexData;
   //         size_t numTris = index_data->indexCount / 3;
			//Ogre::v1::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
   //         
			//bool use32bitindexes = (ibuf->getType() == Ogre::v1::HardwareIndexBuffer::IT_32BIT);
   //         
			//unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::v1::HardwareBuffer::HBL_READ_ONLY));
   //         unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
   //         
   //         
   //         size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
   //         
   //         if ( use32bitindexes )
   //         {
   //             for ( size_t k = 0; k < numTris*3; ++k)
   //             {
   //                 indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
   //             }
   //         }
   //         else
   //         {
   //             for ( size_t k = 0; k < numTris*3; ++k)
   //             {
   //                 indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
   //                 static_cast<unsigned long>(offset);
   //             }
   //         }
   //         
   //         ibuf->unlock();
   //         current_offset = next_offset;
   //     }
   //     
   //     
   //     Ogre::Vector3 vertexPos[3];
   //     Ogre::Vector3 v;
   //     
   //     for (unsigned i = 0; i < index_count; i += 3)
   //     {
   //         for (int k = 0; k < 3; ++k)
   //         {
   //             v = vertices[ indices[i + k] ];
   //             vertexPos[k] = v;
   //         }
   //         
   //         triangleList.push_back( Triangle( vertexPos[0], vertexPos[1], vertexPos[2] ) );
   //     }
   //     
   //     delete [] vertices;
   //     delete [] indices;
         
    }
    
    
  //  Ogre::v1::ManualObject* createCubeMesh(Ogre::SceneManager* sceneMgr, const Ogre::Vector3&pos, float size, Ogre::ColourValue color, 
		//Ogre::v1::ManualObject* moDebug, int offset)
  //  {
  //      bool seperateSequence = false;
  //      
  //      if (!moDebug)
  //      {
  //          seperateSequence = true;
  //          moDebug = sceneMgr->createManualObject();
  //      }
  //      
  //      if (seperateSequence)
  //          moDebug->begin("debug_draw", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  //      
  //      float z1 = pos.z - size;
  //      float z2 = pos.z + size;
  //      
  //      float x1 = pos.x - size;
  //      float x2 = pos.x + size;
  //      
  //      float y1 = pos.y - size;
  //      float y2 = pos.y + size;
  //      
  //      
  //      moDebug->position(x1, y1, z1); // 0
  //      moDebug->colour( color );
  //      moDebug->position(x2, y1, z1); // 1
  //      moDebug->colour( color );
  //      moDebug->position(x2, y2, z1); // 2
  //      moDebug->colour( color );
  //      moDebug->position(x1, y2, z1); // 3
  //      moDebug->colour( color );
  //      
  //      moDebug->position(x1, y1, z2); // 4
  //      moDebug->colour( color );
  //      moDebug->position(x2, y1, z2); // 5
  //      moDebug->colour( color );
  //      moDebug->position(x2, y2, z2); // 6
  //      moDebug->colour( color );
  //      moDebug->position(x1, y2, z2); // 7
  //      moDebug->colour( color );
  //      
  //      moDebug->triangle( 0 + offset, 2 + offset, 1 + offset );  
  //      moDebug->triangle( 0 + offset, 3 + offset, 2 + offset );  
  //      
  //      moDebug->triangle( 0 + offset, 4 + offset, 7 + offset );  
  //      moDebug->triangle( 0 + offset, 7 + offset, 3 + offset );  
  //      
  //      moDebug->triangle( 3 + offset, 7 + offset, 6 + offset );  
  //      
  //      moDebug->triangle( 3 + offset, 6 + offset, 2 + offset );  
  //      
  //      moDebug->triangle( 0 + offset, 1 + offset, 4 + offset );  
  //      moDebug->triangle( 1 + offset, 5 + offset, 4 + offset );  
  //      
  //      moDebug->triangle( 1 + offset, 6 + offset, 5 + offset ); 
  //      moDebug->triangle( 1 + offset, 2 + offset, 6 + offset );  
  //      
  //      moDebug->triangle( 7 + offset, 4 + offset, 5 + offset );  
  //      moDebug->triangle( 5 + offset, 6 + offset, 7 + offset );  
  //      
  //      if (seperateSequence)
  //          moDebug->end();
  //      
  //      return moDebug;
  //      
  //  }

}

