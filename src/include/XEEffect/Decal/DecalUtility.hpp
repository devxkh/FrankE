#ifndef OgreDecalUtility_h
#define OgreDecalUtility_h

#include <Ogre/OgreMain/include/Ogre.h>
#include <vector>

namespace XE
{
    const int MAX_CLIPPED_POINTS = 100;
    const float VEC_EPSILON = 0.001; /// Used when comparing vectors for equality
       
    class Triangle
    {
    public:
        Triangle() { }
        Triangle( const Ogre::Vector3& v1, const Ogre::Vector3& v2, const Ogre::Vector3& v3 )
        {
            v[0] = v1;
            v[1] = v2;
            v[2] = v3;
            
            normal = ( v[1] - v[0] ).crossProduct( v[2] - v[0] );
            normal.normalise();
        }
        
        Ogre::Vector3 v[3];
        Ogre::Vector3 normal;
    };
    
    struct UniquePoint
    {
    public:
        
        UniquePoint( const Ogre::Vector3& vertex, bool edge )
        {
            p = vertex;
            uvCoord.x = uvCoord.y = -1;
            
            isEdge = edge;
        }
        
        Ogre::Vector3 p;
        Ogre::Vector3 normal;
        Ogre::Vector2 uvCoord;
        bool isEdge;
    };
    
    class DecalPolygon
    {
    public:
        
        DecalPolygon( const Ogre::Vector3& normal )
        {
            norm = normal;
        }
        
        /// A list of indicies that index into the uniquePoints vector
        std::vector< int > points;
        
        Ogre::Vector3 norm;
    };

    
    /// Return true if the triangle's bounding box intersects the given AABB
    bool collide_triangle_bounding_box( const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, const Triangle& triangle );
    
    /// Return true if the triangle intsersects the given AABB
    bool collide_triangle_exact( const Ogre::Vector3& m_min, const Ogre::Vector3& m_max, const Triangle& triangle);
    
    /// Clips a polygon against an edge plane
    int plane_clip_polygon( const Ogre::Vector4 & plane, const Ogre::Vector3 * polygon_points, int polygon_point_count, Ogre::Vector3 * clipped);
    
    // Extract verticies and indicies from an Ogre3D Mesh into arrays
	void extractTrianglesFromMesh(std::vector<Triangle>& triangleList, const Ogre::v1::MeshPtr& mesh, const Ogre::Vector3 &position,
                             const Ogre::Quaternion &orient, Ogre::Vector3 scale);
    
    /// Returns the area of a polygon
    double area3D_Polygon( int n, const Ogre::Vector3* V, const Ogre::Vector3& N );
    
    /// Check for duplicates
    bool isDuplicate( const std::vector<UniquePoint>& uniquePoints, const Ogre::Vector3& p, int& duplicateIndex );
    bool isDuplicate( const std::vector< Ogre::Vector3 >& points, const Ogre::Vector3& p );
  

    double max( double a, double b );
    double min( double a, double b );
    double average( double a, double b );
    
    /// Create a cube object, used for debug drawing
	//Ogre::v1::ManualObject* createCubeMesh(Ogre::SceneManager* sceneMgr, const Ogre::Vector3&pos, float size, Ogre::ColourValue color,
	//	Ogre::v1::ManualObject* moDebug = 0, int offset = 0);


}


#endif
