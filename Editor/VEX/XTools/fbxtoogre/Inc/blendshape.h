////////////////////////////////////////////////////////////////////////////////
// blendshape.h
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
// Port to 3D Studio Max - Modified original version
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : December 10th, 2007
////////////////////////////////////////////////////////////////////////////////
// Port to FBX - Modified original version
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

#ifndef _BLENDSHAPE_H
#define _BLENDSHAPE_H

#include "paramList.h"
#include "animation.h"
#include "vertex.h"

#include <unordered_map>

namespace FxOgreFBX
{
    typedef struct
    {
        int targetIndex;
        std::vector<pose> poses;
    } poseGroup;
    // Blend Shape Class
    class BlendShape
    {
    public:
        // Constructor

        BlendShape(FbxNode* pNode, const FbxAMatrix& mat);
        // Destructor
        ~BlendShape();
        // Clear blend shape data
        void clear();
        // Load blend shape poses
        bool loadPoses(ParamList &params,std::vector<vertex> &vertices,
            long numVertices,long offset=0,long targetIndex=0);
        //load a blend shape animation track
        Track loadTrack(float start,float stop,float rate,ParamList& params,int targetIndex, int startPoseId);

        void getKeyedFrames(std::vector<int>& keyedFrames );

        vertexKeyframe loadKeyframe(float time, poseGroup& pg,int startPoseId);
        // Get blend shape poses
        std::unordered_map<int, poseGroup>& getPoseGroups();
        

    protected:
        // Internal methods

        // Protected members
        FbxNode* m_pNode;
        FbxAMatrix m_bindPose;

        //original values to restore after export
        float m_origEnvelope;
        std::vector<float> m_origWeights;
        //blend shape poses
        std::unordered_map<int, poseGroup> m_poseGroups;
        //blend shape target (shared geometry or submesh)
        target m_target;
    };


}	// end namespace

#endif
