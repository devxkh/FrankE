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
#ifndef common_H__
#define common_H__

#include "FxOgreFBXLog.h"

#include "fbxsdk.h"

#include "ogre.h"
#include "OgreDefaultHardwareBufferManager.h"

#include <vector>

namespace FxOgreFBX
{
    class OgreManagers 
    {
    public:
        //constructor
        OgreManagers();
        ~OgreManagers();
        bool Initialize();

        Ogre::LogManager* logMgr; 
        Ogre::ResourceGroupManager* rgm; 
        Ogre::Math* mth; 
        Ogre::LodStrategyManager* lodMgr; 
        Ogre::MaterialManager* matMgr; 
        Ogre::SkeletonManager* skelMgr; 
        Ogre::MeshSerializer* meshSerializer; 
        Ogre::SkeletonSerializer* skeletonSerializer; 
        Ogre::DefaultHardwareBufferManager* bufferManager; 
        Ogre::MeshManager* meshMgr; 
    };

#define MAXIMUM_ANIMATION_DURATION 600.0f

    // Helper function for computing global transforms from the
    // Lcl local transforms in the FBX file.  FbxNode::EvaluateGlobalTransform
    // was not always giving me the correct results (expressions.fbx)
    FbxAMatrix CalculateGlobalTransform(FbxNode *pNode, FbxTime time = FbxTime(-1));

    // Calculates the local transform from  pNode->LclTranslation.Get()  & rotation & scale.
    // This is what is stored in the FBX file, and appears to be more accurate than EvaluateLocalTransform()
    FbxAMatrix computeLocalTransform(FbxNode *pNode);

    FbxAMatrix convertMatrix(const FbxMatrix& mat);
    
    void logMatrix(const FbxAMatrix& mat);

    FbxAMatrix correctMatrix(const FbxAMatrix& mat);
    bool isValidMatrix(const FbxAMatrix& mat);
    bool isVisible(FbxNode *pNode);
    bool GetFullPath(const std::string& inputPath, std::string& outputPath);
    bool FileExists(const std::string& s);
    // Note: only send in directory paths to this, not full file paths.
    bool DirectoryExists(const std::string& s);
    // Note: only send in full file paths to this, not directories.
    bool UserHasWritePermissionsForFile(const std::string& s);


    void AppendKeyedFrames(std::vector<int>& keyedFrames, FbxAnimCurve *pCurve );

    // Taken from FBXSDK samples
    void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition, FbxNode* pNode,FbxMesh* pMesh, FbxTime& pTime, FbxVector4* pVertexArray, FbxPose* pPose);
    FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime,  FbxPose* pPose = NULL,  FbxAMatrix* pParentGlobalPosition = NULL);
    FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
    FbxAMatrix GetGeometry(FbxNode* pNode);
}
#endif // common_H__