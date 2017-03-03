////////////////////////////////////////////////////////////////////////////////
// An Ogre Exporter for FBX
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : January 8th, 2012
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                                                                *
*   This program is free software; you can redistribute it and/or modify         *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or            *
*   (at your option) any later version.                                          *
*                                                                                *
**********************************************************************************/
#include "paramlist.h"
#include "mesh.h"
#include "scene.h"
#include "MaterialSet.h"
namespace FxOgreFBX
{
    class OgreExporter 
    {
    public:
        // public methods
        OgreExporter();
        ~OgreExporter();		

        bool exportScene(const char* fbxfilename, const char* outputmeshfilename, const char* logfilename, const char* clipName, const char* frame0name, bool copyUniqueTextures, int bindframe);

        bool AddFBXAnimationToExisting(const char* fbxfilename, const char* skeletonfilename, const char* meshfilename, const char* logfilename, const char* clipName,  int start, int stop, float rate);

        bool DeleteOgreAnimation( const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname);

        bool printAnimInfo(std::string animname, float fps, float start, Mesh* pMesh, Skeleton *pSkeleton );

        bool GetAnimationBounds(FbxScene *pScene, float& start, float& stop);

        

        ParamList m_params;
    private:

        bool GetFBXAnimationBounds(FbxScene *pScene, float& start, float& stop);

        bool Initialize(const char* fbxfilename, const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname);

		bool InitializeLogging( const char *logfilename);

        bool translateNode(FbxNode* pNode);

        // Adds the default FBX animation to m_params.skelClipList
        bool prepareAnimationClip(const char* clipName);
        bool prepareFrame0Anim(const char* clipName);
        bool writeOgreData();
        
        void addLightToScene( FbxNode* pNode );
        void addCameraToScene( FbxNode* pNode );
        FxOgreNode OgreExporter::getFxOgreNode( FbxNode* pNode );

        bool stat;
        Mesh* m_pMesh;
        MaterialSet* m_pMaterialSet;

        std::string m_fbxfilename, m_meshfilepath, m_skeletonfilepath, m_animationname;


        FxOgreScene m_FxOgreScene;
    };
}