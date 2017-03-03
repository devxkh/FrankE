////////////////////////////////////////////////////////////////////////////////
// skeleton.h
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

#ifndef _SKELETON_H
#define _SKELETON_H


#include "Ogre.h"
#include "paramList.h"
#include "animation.h"
#include "vertex.h"

namespace FxOgreFBX
{


    /***** structure to hold joint info *****/
    typedef struct jointTag
    {
        std::string name;
        int id;
        FbxNode *pNode;
        FbxAMatrix globalBindPose, localBindPose;

        int parentIndex;
        double posx,posy,posz;
        //double angle;
        //double axisx,axisy,axisz;
        double quatw, quatx, quaty, quatz;
        float scalex,scaley,scalez;
        bool bInheritScale;

        // Used when loading from an Ogre Skeleton.
        std::string parentName;
    } joint;


    /*********** Class Skeleton **********************/
    class Skeleton
    {
    public:
        //constructor
        Skeleton();
        //destructor
        ~Skeleton();
        //clear skeleton data
        void clear();
        //load skeleton data
        bool load(FbxScene *pScene,ParamList& params);
    
		void DisplayHierarchy(FbxScene* pScene);
		void DisplayHierarchy(FbxNode* pNode, int pDepth);

        // Calculates the global transform for a node given the bind pose information we have already calcualted.
        FbxAMatrix CalculateGlobalTransformWithBind(FbxNode* pNode, FbxTime time, ParamList& params);

        // Fills out the m_joints structure from an external Ogre .Skeleton file. Then adds the animation from the FBX to the skeleton.
        bool AddFBXAnimationToExisting(OgreManagers& managers, std::string &skeletonFilePath, std::string &clipName, ParamList& params, float start, float stop);

        // Deletes animation from existing skeleton file.
        bool DeleteAnimationFromExisting(OgreManagers& managers, std::string &skeletonFilePath, std::string &clipName);

        // returns the index of the bone in the skeleton.  -1 if it doesn't exist.
        int getJointIndex(FbxNode* pNode);
        int getJointIndex(const std::string& name);

        //load skeletal animations
        bool loadAnims(ParamList& params);
        //get joints
        std::vector<joint>& getJoints();
        //get animations
        std::vector<Animation>& getAnimations();
        //restore skeleton pose
        void restorePose();
        //write to an OGRE binary skeleton
        bool writeOgreBinary(ParamList &params);       

        void getKeyedFrames(std::vector<int>& keyedFrames, ParamList& params );

    protected:

        // loads an Ogre skeleton.
        bool loadOgreSkeletonFromFile(OgreManagers& managers, std::string &skeletonFilePath, Ogre::Skeleton& skel);

        //load a joint. 
        bool loadJoint(FbxNode* pNode, ParamList& params, FbxAMatrix globalBindPose);

		// check if there are duplicate nodes.
		bool doDuplicateBonesExistRecursive(FbxNode *pNode);

        // Attempts to find bind pose info and load joints with the reliable transforms associated with it.
        void loadBindPose(FbxScene *pScene, ParamList& params);

        void setParentIndexes();
        void addParentsOfExistingJoints(ParamList &params);

        // Searches the pRootNode and all children for additional FbxNodeAttribute::eSKELETON 
        // nodes,.  This should be called after all meshes have been exported, so higher priority
        // bones are exported first.  Any bones exported here should not have a visible impact
        // on the character, but they might be useful for other in-game systems.
        void addLowPriorityBones(FbxNode* pRootNode, ParamList &params);
        
        void sortAndPruneJoints();
        void sortJoint(joint j, std::map<std::string, int> &sortedJointIndexMap, std::vector<joint>& sorted_joints);
        // Compute local transforms from global ones.
        void calculateLocalTransforms(FbxNode* pRootNode, ParamList &params);


        // Convert a quaternion into angle-axis. The returned FbxVector4 
        // has the last element as the angle;
        FbxVector4 Skeleton::getAngleAxis(FbxQuaternion quat);


        bool isDefinitelyNotJoint(FbxNode *pNode);
        bool loadClipAnim(std::string clipName,float start,float stop,float rate,ParamList& params,  Animation& a);
        
        // Replaces the animation named clipName in the Ogre Skeleton with the animation from the current scene.
        bool replaceAnimation(Ogre::Skeleton& skeleton, const std::string& clipName, float start,float stop,float rate,ParamList& params);

        //load a clip
        bool loadClip(std::string clipName,float start,float stop,float rate,ParamList& params);
        //load a keyframe for a particular joint at current time
        skeletonKeyframe loadKeyframe(joint& j,float time,ParamList& params);
        //write joints to an Ogre skeleton
        bool createOgreBones(Ogre::Skeleton& skeleton,ParamList& params);
        // write skeleton animations to an Ogre skeleton
        bool createOgreSkeletonAnimations(Ogre::Skeleton& skeleton,ParamList& params);

        // adds the anim to the skeleton.
        bool addOgreSkeletonAnimation(Ogre::Skeleton& skeleton, Animation& anim);

        std::map<std::string, int> m_jointIndexMap;
        BoundingBox m_bbox;

        std::vector<joint> m_joints;

        std::vector<Animation> m_animations;
        std::string m_restorePose;
    };

}	//end namespace

#endif
