//
//  DecalGenerator.h
//  ogre
//
//  Created by Jonathan Lanis on 9/23/12.
//  Copyright (c) 2012 N/A. All rights reserved.
//

#ifndef OgreDecalGenerator_h
#define OgreDecalGenerator_h

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEEffect/Decal/DecalUtility.hpp>
#include <vector>

namespace XE
{
	class OgreSceneManager;

    /// Base class
    class TriangleMesh
    {
    public:
        /// Pure virtual function to be left implemented by the user for maximum flexbility
        /// @param triangles An empty list of triangles to be filled with the ones that are inside the AABB
        virtual void findTrianglesInAABB( const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, std::vector< Triangle >& triangles ) = 0;
    };
    
    /// Only need to create one per mesh
    class OgreMesh : public TriangleMesh
    {
    public:
        OgreMesh() { }
		OgreMesh(const Ogre::v1::MeshPtr& mesh, const Ogre::Vector3& scale);
        
		void initialize(const Ogre::v1::MeshPtr& mesh, const Ogre::Vector3& scale);
        
        void findTrianglesInAABB( const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, std::vector< Triangle >& triangles );
        
    private:
        
        std::vector< Triangle > meshTriangles;
        
    };
    
    // The decal object returned from the DecalGenerator
    //class Decal
    //{
    //public:
    //    
    //    Decal();
    //    
    //    /// Always NULL-check this object before using it.
    //    Ogre::ManualObject* object;
    //};
    
    
    class DecalGenerator
    {
    public:

		DecalGenerator();
		~DecalGenerator();
		
		void initialize(OgreSceneManager& ogreSceneManager);
		Ogre::v1::ManualObject* createDecal(TriangleMesh* mesh, const Ogre::Vector3& pos, float width, float height,
			const Ogre::String& materialName, bool flipTexture = false, Ogre::v1::ManualObject* decalObject = 0);
        
        void turnDebugOn();
        void turnDebugOff();
        void flipDebug();
        
     //   static DecalGenerator& getSingleton() { return mInstance; }
     //   static DecalGenerator* getSingletonPtr() { return &mInstance; }
        
    private:
        
        Ogre::SceneManager* sceneMgr;
        
        Ogre::SceneNode* mDebugNode;
        bool mDebugVisible;
        
        std::vector< UniquePoint > uniquePoints; 
        std::vector< Triangle > triangles;
        std::vector< Ogre::Vector3 > polygon_points;
        std::vector< DecalPolygon > finalPolys;
        
        Ogre::Vector3 clippedPoints[ MAX_CLIPPED_POINTS ];
        bool pointWasClipped[ MAX_CLIPPED_POINTS ];
        
		void AddTriangle(Ogre::v1::ManualObject* mo, std::vector< int >& points, int p1, int p2, int p3, Ogre::v1::ManualObject* lines);

     
        /// left unimplemented to enforce singleton pattern
        DecalGenerator(DecalGenerator const&);
        void operator=(DecalGenerator const&); 
        
      //  static DecalGenerator mInstance;
    };
}

#endif
