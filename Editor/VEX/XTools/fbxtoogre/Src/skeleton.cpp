////////////////////////////////////////////////////////////////////////////////
// skeleton.cpp
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
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

#include "skeleton.h"
#include "submesh.h"
#include "common.h"

namespace FxOgreFBX
{

    // Constructor
    Skeleton::Skeleton()
    {
        m_joints.clear();
        m_animations.clear();
        m_restorePose = "";
    }


    // Destructor
    Skeleton::~Skeleton()
    {
        clear();
    }


    // Clear skeleton data
    void Skeleton::clear()
    {
        m_joints.clear();
        m_animations.clear();
        m_restorePose = "";
        m_jointIndexMap.clear();
        m_bbox.clear();
    }
    int Skeleton::getJointIndex(FbxNode* pNode)
    {
        if(pNode)
        {
            if( m_jointIndexMap.find(pNode->GetName()) != m_jointIndexMap.end() )
            {
                return m_jointIndexMap[pNode->GetName()];
            }
        }
        return -1;
    }
    int Skeleton::getJointIndex(const std::string& name)
    {
        if( m_jointIndexMap.find(name) != m_jointIndexMap.end() )
        {
            return m_jointIndexMap[name];
        }
        return -1;
    }
    void Skeleton::addLowPriorityBones(FbxNode* pRootNode, ParamList &params)
    {
        
        if(pRootNode)
        {
            for( int i = 0; i < pRootNode->GetChildCount(); ++i )
            {
                if( pRootNode->GetChild(i) && pRootNode->GetChild(i)->GetNodeAttribute() )
                {
                    if( FbxNodeAttribute::eSkeleton == pRootNode->GetChild(i)->GetNodeAttribute()->GetAttributeType() )
                    {
                        // No harm if we have already exported it.
                        FbxAMatrix global = CalculateGlobalTransformWithBind(pRootNode->GetChild(i),  FbxTime(params.bindframe), params);
                        
                        bool bLoaded = loadJoint( pRootNode->GetChild(i), params, global );
                        
                        if( bLoaded )
                        {
                            FxOgreFBXLog( "Added low priority bone %s.\n", pRootNode->GetChild(i)->GetName());
                            logMatrix(global);
                        }
                    }
                    // Recursively call function.
                    addLowPriorityBones(pRootNode->GetChild(i),params);
                }
            }
        }
    }

    FbxAMatrix Skeleton::CalculateGlobalTransformWithBind(FbxNode* pNode, FbxTime time, ParamList &params) 
    {
        if( params.useanimframebind )
        {
            return CalculateGlobalTransform(pNode, time);
        }
        else
        {
            FbxAMatrix lTM = pNode->EvaluateLocalTransform(time);
            if( pNode->GetParent() )
            {
                FbxAMatrix parentMatrix;
                if( m_jointIndexMap.find(pNode->GetParent()->GetName()) == m_jointIndexMap.end() )
                {
                    parentMatrix = CalculateGlobalTransform(pNode->GetParent(), time);
                }
                else
                {
                    int index = m_jointIndexMap[pNode->GetParent()->GetName()];
                    parentMatrix = m_joints[index].globalBindPose;
                }
                return parentMatrix * lTM;
            }
            return lTM;
        }
    }

    void Skeleton::addParentsOfExistingJoints(ParamList &params)
    {
        // If the parent for this node doesn't exist, add it here.
        for( size_t i=0; i< m_joints.size(); ++i )
        {
            FbxNode *pNode = m_joints[i].pNode;
            if( pNode->GetParent() )
            {
                if( m_jointIndexMap.find(pNode->GetParent()->GetName()) == m_jointIndexMap.end() )
                {
                    FbxAMatrix global = CalculateGlobalTransformWithBind(pNode->GetParent(),  FbxTime(params.bindframe), params);
                    
                    bool bLoaded = loadJoint(pNode->GetParent(), params, global);

                    FxOgreFBXLog( "Warning joint %s created with no bind pose information.\n", pNode->GetParent()->GetName());
                    logMatrix(global);
                }
            }
        }
    }
    void Skeleton::calculateLocalTransforms(FbxNode* pRootNode, ParamList &params)
    {

        FxOgreFBXLog( "Calculating local transforms for skeleton bones.\n");
        // Calculate global transforms.
        for( size_t i=0; i< m_joints.size(); ++i )
        {
            FbxNode* pNode = m_joints[i].pNode;
            FbxAMatrix localTM, parentTM;

            localTM = m_joints[i].globalBindPose;
            if( params.useanimframebind )
            {
                // We could calculate the local transforms from the global ones, but
                // in some circumstances (blake), this produces incorrect values, possibly as
                // a result of gimble lock.  With useanimframebind, we are relying on the 
                // FBX SDK to calculate everything, so we rely on the EvaluateLocalTransform
                // function as opposed to calculating our own values.
                localTM = m_joints[i].pNode->EvaluateLocalTransform(FbxTime((params.bindframe)));
            }
            else if( m_joints[i].parentIndex != -1 )
            {
                parentTM =  m_joints[m_joints[i].parentIndex].globalBindPose;
                localTM = parentTM.Inverse() * localTM;
            }
            
            m_joints[i].localBindPose = localTM;

            Point3 translation(localTM.GetT()[0], localTM.GetT()[1], localTM.GetT()[2]);
            if (fabs(translation.x) < PRECISION)
                translation.x = 0;
            if (fabs(translation.y) < PRECISION)
                translation.y = 0;
            if (fabs(translation.z) < PRECISION)
                translation.z = 0;

            Point3 scale(localTM.GetS()[0], localTM.GetS()[1], localTM.GetS()[2]);
            if (fabs(scale.x) < PRECISION)
                scale.x = 0;
            if (fabs(scale.y) < PRECISION)
                scale.y = 0;
            if (fabs(scale.z) < PRECISION)
                scale.z = 0;


            m_joints[i].posx = translation.x * params.lum;
            m_joints[i].posy = translation.y * params.lum;
            m_joints[i].posz = translation.z * params.lum;
            
            m_joints[i].quatw = localTM.GetQ()[3]; 
            m_joints[i].quatx = localTM.GetQ()[0];
            m_joints[i].quaty = localTM.GetQ()[1];
            m_joints[i].quatz = localTM.GetQ()[2];

            m_joints[i].scalex = static_cast<float>(scale.x);
            m_joints[i].scaley = static_cast<float>(scale.y);
            m_joints[i].scalez = static_cast<float>(scale.z);

            FxOgreFBXLog( "%s - Local Trans:( %f,%f,%f) Quat( %f,%f,%f,%f), Scale(%f,%f,%f).\n", pNode->GetName(),  translation.x, translation.y, translation.z, localTM.GetQ()[3], localTM.GetQ()[0],localTM.GetQ()[1],localTM.GetQ()[2],scale.x, scale.y, scale.z);            
        }

    }
    bool Skeleton::load(FbxScene *pScene,ParamList& params)
    {
        if( pScene && pScene->GetRootNode() )
        {
            // Search for the bind pose.
            FxOgreFBXLog( "Exporting bind pose.\n");
            loadBindPose(pScene, params);
            FxOgreFBXLog( "Finished exporting bind pose.\n");

            FxOgreFBXLog( "Adding parents of high priority bones.\n");
            addParentsOfExistingJoints(params);

            FxOgreFBXLog( "Adding low priority bones.  They won't impact the mesh, but perhaps useful to in-game systems.\n");
            addLowPriorityBones(pScene->GetRootNode(), params);
            FxOgreFBXLog( "Finished adding low priority bones.\n");

            FxOgreFBXLog( "Adding parents of existing bones.\n");
            addParentsOfExistingJoints(params);
            FxOgreFBXLog( "Finished adding parents of existing bones.\n");


            // Ogre skeletons can only have 256 bones. We sort so parents are added
            // before their children for the most predictable results.
            if( m_joints.size() > OGRE_MAX_NUM_BONES )
            {
                // ERRORBOXWARNING are the most severe warnings prior to a failure state.
                FxOgreFBXLog( "ERRORBOXWARNING: Ogre supports a maximum of 256 bones. Some were not exported.\n");
            }

            FxOgreFBXLog( "Sorting and pruning joints.\n");
            sortAndPruneJoints();
            FxOgreFBXLog( "Finished sorting and pruning joints.\n");


            // Check for duplicates of these high priority bones.
            if( doDuplicateBonesExistRecursive(pScene->GetRootNode()) )
			{
                // ERRORBOXWARNING are the most severe warnings prior to a failure state.
				FxOgreFBXLog( "ERRORBOXWARNING: Multiple bones with the same name found. Bone names must be unique.\n");
			}

            FxOgreFBXLog( "Calculating local transforms.\n");
            calculateLocalTransforms( pScene->GetRootNode(), params);
            FxOgreFBXLog( "Finished calculating local transforms.\n");

            if( m_joints.size() == 0 )
            {
                params.exportSkeleton = false;
                FxOgreFBXLog( "Turning SKELETON export off because there are no bones.\n");
            }

            return true;
        }
        return false;
    }
    
    void Skeleton::loadBindPose(FbxScene *pScene, ParamList& params)
    {
        if( !params.useanimframebind )
        {
            // This contains the most reliable bind pose info, so we export it first.
            for( int i = 0; i < pScene->GetPoseCount(); ++i )
            {
                FbxPose* pPose = pScene->GetPose(i);
                if( pPose->IsBindPose() )
                {
                    for( int j = 0; j < pPose->GetCount(); ++j )
                    {
                        FbxNode *pNode = pPose->GetNode(j);
                        if( !isVisible(pNode) )
                        {
                            continue;
                        }
                        // Only export actual joints here.  Otherwise meshes will create joints unnecessarily.
                        if( pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton )
                        {
                            FbxAMatrix globalBindPose;
                            globalBindPose = convertMatrix(pPose->GetMatrix(j));
                            
                            int jointIndex = getJointIndex(pNode);
                            if( -1 == jointIndex )
                            {
                                if( isValidMatrix(globalBindPose ))
                                {
                                    loadJoint(pNode, params, globalBindPose);
                                }
                            }
                            else if( globalBindPose != m_joints[jointIndex].globalBindPose )
                            {
                                FxOgreFBXLog( "Warning: Multiple bind poses found for joint %s.  Setting bind pose to frame 0 and ignoring all stored bind poses.\n", pNode->GetName());
                                params.useanimframebind = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        // Nodes to export using bind pose information calculated from the animation.
        std::vector<FbxNode*> time0skeletonNodes;

        // Iterate through geometry and look for bones that were not incuded in the bind pose
        // but the mesh is weighted to.
        for( int iGeom = 0; iGeom < pScene->GetGeometryCount(); ++iGeom )
        {
            FbxGeometry *pGeom = pScene->GetGeometry(iGeom);
            if( !isVisible(pGeom->GetNode()) )
            {
                continue;
            }
            bool bIsMeshWeighted = false;
            int lSkinCount= pGeom->GetDeformerCount(FbxDeformer::eSkin);
            for(int i=0; i!=lSkinCount; ++i)
            {
                int lClusterCount = ((FbxSkin *) pGeom->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
                for (int j = 0; j < lClusterCount; ++j)
                {                
                    FbxCluster *pCluster=((FbxSkin *) pGeom->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);
                    if( pCluster )
                    {
                        bIsMeshWeighted = true;
                        FbxNode* pNode = pCluster->GetLink();
                        FbxAMatrix globalMatrix;
                        int jointIndex = getJointIndex(pNode);
                        
                        // Add this joint to the sk
                        time0skeletonNodes.push_back(pNode);

                        if( !params.useanimframebind )
                        {
                            pCluster->GetTransformLinkMatrix(globalMatrix);
                            if( -1 == jointIndex )
                            {
                                //If a bind pose was properly set in the FBX file, this is not needed, but just in case.
                                loadJoint(pNode, params, globalMatrix);
                            }
                            else if( globalMatrix != m_joints[jointIndex].globalBindPose )
                            {
                                FxOgreFBXLog( "Warning: Multiple bind poses found for joint %s on mesh %s.  Setting bind pose to frame 0 and ignoring all stored bind poses.\n",  pNode->GetName(), pGeom->GetName());
                                params.useanimframebind = true;
                                
                            }
                        }
                    }
                }
            }
        }
        if( params.useanimframebind )
        {
            if( m_joints.size() > 0 )
            {
                FxOgreFBXLog( "Recalculating transforms for joints based on bindframe.\n");
            }
            // Delete bind pose information stored thus far.
            clear();
            for( size_t i = 0; i < time0skeletonNodes.size(); ++i )
            {
                FbxAMatrix bindTransform = CalculateGlobalTransform(time0skeletonNodes[i],  FbxTime(params.bindframe));
                loadJoint(time0skeletonNodes[i], params, bindTransform);
            }
        }
        // loop through the geometry again and make sure that parents of unweighted meshes are treated as bones.
        for( int iGeom = 0; iGeom < pScene->GetGeometryCount(); ++iGeom )
        {
            FbxGeometry *pGeom = pScene->GetGeometry(iGeom);
            if( !isVisible(pGeom->GetNode()) )
            {
                continue;
            }
            bool bIsMeshWeighted = false;
            int lSkinCount= pGeom->GetDeformerCount(FbxDeformer::eSkin);
            for(int i=0; i!=lSkinCount; ++i)
            {
                int lClusterCount = ((FbxSkin *) pGeom->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
                for (int j = 0; j < lClusterCount; ++j)
                {                
                    FbxCluster *pCluster=((FbxSkin *) pGeom->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);
                    if( pCluster )
                    {
                        bIsMeshWeighted = true;
                    }
                }
            }
            // If the mesh is unweighted, export it's parent as a bone.
            if( !bIsMeshWeighted )
            {
                FbxNode *pNode = pGeom->GetNode();
                if(  pNode && pNode->GetParent() ) 
                {
                     // If the mesh is unweighted, export its parent as a bone so we can rigidly skin the mesh.
                    FbxAMatrix bindTransform = CalculateGlobalTransformWithBind(pNode,  FbxTime(params.bindframe), params);
                    
                    if( loadJoint(pNode->GetParent(), params, bindTransform) )
                    {
                        FxOgreFBXLog( "Unskinned mesh %s found. Added parent %s to the skeleton.\n", pNode->GetName(), pNode->GetParent()->GetName());
                    }
                }
            }
        }
    }

	bool Skeleton::doDuplicateBonesExistRecursive(FbxNode *pNode)
	{
		assert(pNode);
		bool bDuplicateBonesExist = false;
		int jointIndex = getJointIndex(pNode);
		if( jointIndex >= 0 && jointIndex < OGRE_MAX_NUM_BONES )
		{
			if( m_joints[jointIndex].pNode != pNode )
			{
				FxOgreFBXLog( "Warning!  Duplicate bone found: %s.\n", pNode->GetName());
				// Don't return right away so a warning is printed for all duplicates.
                bDuplicateBonesExist = true;
			}
		}
		for( int i=0; i< pNode->GetChildCount(); ++i )
		{
			if( doDuplicateBonesExistRecursive(pNode->GetChild(i)) )
			{
				// Don't return right away so a warning is printed for all duplicates.
				bDuplicateBonesExist = true;
			}
		}
		return bDuplicateBonesExist;
	}

    void Skeleton::setParentIndexes()
    {
        // Set the parent indexes, so we know what to sort.
        for( size_t i=0; i< m_joints.size(); ++i )
        {
            FbxNode *pNode = m_joints[i].pNode;
            int parentIndex = -1;
            if( pNode->GetParent() )
            {
                if( m_jointIndexMap.find(pNode->GetParent()->GetName()) != m_jointIndexMap.end() )
                {
                    parentIndex = m_jointIndexMap[pNode->GetParent()->GetName()];
                }
            }
            m_joints[i].parentIndex = parentIndex;
        }
    }
    // Ensure that parents are before their children in m_joints
    void Skeleton::sortAndPruneJoints()
    {

        // Set the indexes to sort by
        setParentIndexes();

        std::map<std::string, int> sortedJointIndexMap;
        std::vector<joint> sorted_joints;

        for( size_t i = 0; i < m_joints.size(); ++i )
        {
            sortJoint(m_joints[i], sortedJointIndexMap, sorted_joints);
        }

        // Update the joint list.
        m_joints.clear();
        m_joints = sorted_joints;
        m_jointIndexMap.clear();

        m_jointIndexMap = sortedJointIndexMap;
    }

    void Skeleton::sortJoint(joint j, std::map<std::string, int> &sortedJointIndexMap, std::vector<joint>& sorted_joints )
    {
        // Only export if we haven't already.
        if( sortedJointIndexMap.find(j.name) == sortedJointIndexMap.end() )
        {
            int newParentIndex = j.parentIndex;
            if( j.parentIndex != -1 )
            {
                // Export parents first. 
                sortJoint(m_joints[j.parentIndex], sortedJointIndexMap, sorted_joints );
                newParentIndex = sortedJointIndexMap[j.pNode->GetParent()->GetName()];
            }
            if( sorted_joints.size() >=  OGRE_MAX_NUM_BONES )
            {
                FxOgreFBXLog( "Warning: pruned joint - %s.  Too many bones!\n",j.name.c_str());
            }
            else
            {
                int id = static_cast<int>(sorted_joints.size());

                sorted_joints.push_back(j);
                sortedJointIndexMap[j.name] = id;
                
                sorted_joints[id].id = id;
                sorted_joints[id].parentIndex = newParentIndex;
                FxOgreFBXLog( "%i - %s - parent index: %i.\n", sorted_joints[id].id, sorted_joints[id].name.c_str(), sorted_joints[id].parentIndex);
            }
        }
    }
    // Load a joint
    bool Skeleton::loadJoint(FbxNode* pNode,ParamList& params, FbxAMatrix globalBindPose)
    {	

        if( !pNode )
        {
            FxOgreFBXLog( "Failed to load joint.\n");
            return false;
        }
        if( m_jointIndexMap.find(pNode->GetName()) != m_jointIndexMap.end() )
        {
            // We have already exported this joint.
            return false;
        }

        if( !pNode->GetParent() )
        {
            // Ignore the FBX root node here.
            return false;
        }
        
        // Protect against nodes that have parents with the same name (to avoid infinite recursion)
        std::string nodename(pNode->GetName());
        FbxNode *pParent = pNode->GetParent();
        while(pParent)
        {
            std::string parentname = pParent->GetName();
            if(  parentname.compare(nodename) == 0 )
            {
                FxOgreFBXLog( "Warning! %s joint has a parent by the same name.  Joint names must be unique!  Output file may render incorrectly.",pNode->GetName() );
                pNode = pParent;
                break;
            }
            pParent = pParent->GetParent();
        }

        globalBindPose = correctMatrix(globalBindPose);


        joint newJoint;
        m_joints.push_back(newJoint);
        int index = static_cast<int>(m_joints.size()) - 1;
        m_jointIndexMap[pNode->GetName()] = index;

        m_joints[index].pNode = pNode;
        m_joints[index].name = pNode->GetName();
        m_joints[index].id = index;
        
        FxOgreFBXLog( "%s joint added at index %i with global transform:",pNode->GetName(), index );
        logMatrix(globalBindPose);

        m_joints[index].globalBindPose = globalBindPose;  
        
        return true;
    }
    // Load animations
    bool Skeleton::loadAnims(ParamList& params)
    {
        bool stat;
        size_t i;
        // clear animations list
        m_animations.clear();
        FxOgreFBXLog( "Loading skeleton animations...\n" );
        // load skeleton animation clips for the whole skeleton
        for (i=0; i<params.skelClipList.size(); i++)
        {
            FxOgreFBXLog( "Loading clip %s.\n", params.skelClipList[i].name.c_str() );
            stat = loadClip(params.skelClipList[i].name,params.skelClipList[i].start,
                params.skelClipList[i].stop,params.skelClipList[i].rate,params);
            if (stat == true)
            {
                FxOgreFBXLog( "Clip successfully loaded\n");
            }
            else
            {
                FxOgreFBXLog( "Failed loading clip\n");
            }
        }

        return true;
    }

    bool Skeleton::loadClipAnim(std::string clipName,float start,float stop,float rate,ParamList& params, Animation& a)
    {
        size_t i,j;
        std::vector<float> times;
        times.clear();
        if (rate <= 0)
        {
            FxOgreFBXLog( "invalid sample rate for the clip (must be >0), we skip it\n");
            return false;
        }
        else
        {
            for (float t=start; t<stop; t+=rate)
                times.push_back(t);
            times.push_back(stop);
        }
        // get animation length
        float length=0;
        if (times.size() >= 0)
            length = times[times.size()-1] - times[0];
        if (length < 0)
        {
            FxOgreFBXLog( "invalid time range for the clip, we skip it\n");
            return false;
        }
        a.m_name = clipName.c_str();
        a.m_tracks.clear();
        a.m_length = length;


        // create a track for current clip for all joints
        std::vector<Track> animTracks;
        for (i=0; i<m_joints.size(); i++)
        {
            Track t;
            t.m_type = TT_SKELETON;
            t.m_bone = m_joints[i].name;
            t.m_skeletonKeyframes.clear();
            animTracks.push_back(t);
        }

        // evaluate animation curves at selected times
        for (i=0; i<times.size(); i++)
        {
            //load a keyframe for every joint at current time
            for (j=0; j<m_joints.size(); j++)
            {
                skeletonKeyframe key = loadKeyframe(m_joints[j],times[i],params);
                key.time = key.time - times[0];
                //add keyframe to joint track
                animTracks[j].addSkeletonKeyframe(key);
            }
            if (params.skelBB)
            {                
            }
        }
        // add created tracks to current clip
        for (i=0; i<animTracks.size(); i++)
        {
            a.addTrack(animTracks[i]);
        }
        if( animTracks.size() > 0 )
        {
            // display info
            FxOgreFBXLog( "length: %f\n", a.m_length);
            FxOgreFBXLog( "num keyframes: %d\n", animTracks[0].m_skeletonKeyframes.size());
        }
        
        return true;
    }

    // Load an animation clip
    bool Skeleton::loadClip(std::string clipName,float start,float stop,float rate,ParamList& params)
    {
        Animation a;
        m_animations.push_back(a);
        bool stat = loadClipAnim(clipName, start, stop, rate, params, m_animations[m_animations.size() -1]);
        if( !stat )
        {
            m_animations.pop_back();
            return false;
        }
        return true;
    }

    // Load a keyframe for a given joint at current time
    skeletonKeyframe Skeleton::loadKeyframe(joint& j,float time,ParamList& params)
    {
        FbxTime FbxTime;
        FbxTime.SetSecondDouble(time);
        //create keyframe
        skeletonKeyframe key;
        key.time = time;


        FbxAMatrix localTMOrig = j.localBindPose;
        FbxAMatrix localTMAtTime = localTMOrig;
            
        FbxAMatrix nodeTM, parentTM; 
        if( j.pNode )
        {
            
            nodeTM = CalculateGlobalTransformWithBind(j.pNode, FbxTime, params);
            
            if( params.skelBB )
            {
                // Bounding box info is output to the MESH file, so this will not impact the
                // mesh if called from AddFBXAnimationToExisting.
                m_bbox.merge(Point3(nodeTM.GetT()[0], nodeTM.GetT()[1], nodeTM.GetT()[2]));
            }
            else
            {
                localTMAtTime = j.pNode->EvaluateLocalTransform(FbxTime);
            }
        }

        FbxAMatrix deltaMat =   localTMOrig.Inverse() * localTMAtTime;
        FbxVector4 diff = localTMAtTime.GetT() - localTMOrig.GetT();
        // @todo why does calculating the diff vector like below break UTRef?
       // FbxVector4 diff = deltaMat.GetT();

        Point3 translation(diff[0], diff[1], diff[2]);
        if (fabs(translation.x) < PRECISION)
            translation.x = 0;
        if (fabs(translation.y) < PRECISION)
            translation.y = 0;
        if (fabs(translation.z) < PRECISION)
            translation.z = 0;

        
        Point3 scale(deltaMat.GetS()[0], deltaMat.GetS()[1], deltaMat.GetS()[2]);
        if (fabs(scale.x) < PRECISION)
            scale.x = 0;
        if (fabs(scale.y) < PRECISION)
            scale.y = 0;
        if (fabs(scale.z) < PRECISION)
            scale.z = 0;

        key.tx = translation.x * params.lum;
        key.ty = translation.y * params.lum;
        key.tz = translation.z * params.lum;

        FbxQuaternion quat = deltaMat.GetQ();
        key.quat_w = quat[3];
        key.quat_x = quat[0];
        key.quat_y = quat[1];
        key.quat_z = quat[2];

        key.sx = static_cast<float>(scale.x);
        key.sy = static_cast<float>(scale.y);
        key.sz = static_cast<float>(scale.z);
       
        return key;
    }

    // Restore skeleton pose
    void Skeleton::restorePose()
    {
        // TODO: required in Max?
    }

    // Get joint list
    std::vector<joint>& Skeleton::getJoints()
    {
        return m_joints;
    }

    // Get animations
    std::vector<Animation>& Skeleton::getAnimations()
    {
        return m_animations;
    }

    // Deletes animation from existing skeleton file.
    bool Skeleton::DeleteAnimationFromExisting(OgreManagers& managers, std::string &skeletonFilePath, std::string &clipName)
    {
        Ogre::Skeleton skel = Ogre::Skeleton(managers.skelMgr, "fbxexport_skeleton", 0, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        loadOgreSkeletonFromFile(managers, skeletonFilePath, skel);
        if( skel.hasAnimation(clipName.c_str()) )
        {
            skel.removeAnimation(clipName.c_str());
            FxOgreFBXLog( "Deleted %s animation from skeleton.\n", clipName.c_str() );

            Ogre::SkeletonSerializer skeletonSerializer;
            try
            {
                skeletonSerializer.exportSkeleton(&skel,skeletonFilePath.c_str());
            }
            catch( Ogre::Exception& e )
            {
                FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
                return false;
            }
            return true;
        }
        FxOgreFBXLog( "Could not delete %s animation because it did not exist in skeleton.\n", clipName.c_str() );
        return false;       
    }

    bool Skeleton::loadOgreSkeletonFromFile(OgreManagers& managers, std::string &skeletonFilePath, Ogre::Skeleton& skel)
    {
        Ogre::String source = skeletonFilePath.c_str();
        FILE* pFile = fopen( source.c_str(), "rb" );
        if (!pFile)
            FxOgreFBXLog( "Error! Skeleton not found: %s.\n", source.c_str() );
        struct stat tagStat;
        stat( source.c_str(), &tagStat );
        Ogre::MemoryDataStream* memstream = new Ogre::MemoryDataStream(source, tagStat.st_size, true);
        fread( (void*)memstream->getPtr(), tagStat.st_size, 1, pFile );
        fclose( pFile );      

        Ogre::SkeletonSerializer skeletonSerializer;
        Ogre::DataStreamPtr stream(memstream);

        try
        {
            skeletonSerializer.importSkeleton(stream, &skel);            
        }
        catch( Ogre::Exception& e )
        {
            FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
        }
        return true;
    }

	void Skeleton::DisplayHierarchy(FbxScene* pScene)
	{
		int i;
		FbxNode* lRootNode = pScene->GetRootNode();

		for (i = 0; i < lRootNode->GetChildCount(); i++)
		{
			DisplayHierarchy(lRootNode->GetChild(i), 0);
		}
	}

	void Skeleton::DisplayHierarchy(FbxNode* pNode, int pDepth)
	{
		FbxString lString;
		int i;

		for (i = 0; i < pDepth; i++)
		{
			lString += "     ";
		}

		lString += pNode->GetName();
		lString += "\n";

		FBXSDK_printf(lString.Buffer());

		for (i = 0; i < pNode->GetChildCount(); i++)
		{
			DisplayHierarchy(pNode->GetChild(i), pDepth + 1);
		}
	}

    bool Skeleton::AddFBXAnimationToExisting(OgreManagers &managers, std::string &skeletonFilePath, std::string &clipName, ParamList& params, float start, float stop)
    {
        Ogre::Skeleton skel = Ogre::Skeleton(managers.skelMgr, "fbxexport_skeleton", 0, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        loadOgreSkeletonFromFile(managers, skeletonFilePath, skel);

        m_joints.clear();
        m_jointIndexMap.clear();

        Ogre::Skeleton::BoneIterator iterator = skel.getBoneIterator();
        int id = 0;
        while( iterator.hasMoreElements() )
        {
            Ogre::Bone *pBone = iterator.getNext();
            joint j;
            j.name = pBone->getName().c_str();
            j.id = id;
            id++;
            m_jointIndexMap[j.name] = j.id;
            
            if( params.pScene )
            {
				DisplayHierarchy(params.pScene);

                j.pNode = params.pScene->FindNodeByName(pBone->getName().c_str());
                if( !j.pNode )
                {
                    FxOgreFBXLog( "Warning! Could not find joint %s in scene!\n", pBone->getName().c_str() );
                }
            }
            Ogre::Node *pParent = pBone->getParent();
            if( pParent )
            {
                j.parentName = pParent->getName();
            }

            Ogre::Vector3 pos = pBone->getInitialPosition();
            Ogre::Quaternion quat = pBone->getInitialOrientation();
            Ogre::Vector3 scale = pBone->getInitialScale();
            j.posx = pos.x;
            j.posy = pos.y;
            j.posz = pos.z;
            j.scalex = scale.x;
            j.scaley = scale.y;
            j.scalez = scale.z;
            j.quatw = quat.w;
            j.quatx = quat.x;
            j.quaty = quat.y;
            j.quatz = quat.z;
            
            j.localBindPose.SetT(FbxVector4(pos.x, pos.y, pos.z));
            j.localBindPose.SetQ(FbxQuaternion(quat.x, quat.y, quat.z, quat.w));
            j.localBindPose.SetS(FbxVector4(scale.x, scale.y, scale.z));    


            j.bInheritScale = pBone->getInheritScale();

            m_joints.push_back(j);
        }
        for( size_t i = 0; i < m_joints.size(); ++i )
        {
            int parentIndex = getJointIndex(m_joints[i].parentName);
            m_joints[i].parentIndex = parentIndex;
        }

        if( params.fps == 0 )
        {
            FxOgreFBXLog( "Invalid fps rate: 0. Failed to import animation %s.\n", clipName.c_str() );
        }
        if( start > start )
        {
            FxOgreFBXLog( "Invalid start and end time for animation %s: (%f, %f).\n", clipName.c_str(), start, stop );
            return false;
        }

        replaceAnimation(skel, clipName, start, stop, 1/params.fps, params);

        Ogre::SkeletonSerializer skeletonSerializer;
        try
        {
            skeletonSerializer.exportSkeleton(&skel,skeletonFilePath.c_str());
        }
        catch( Ogre::Exception& e )
        {
            FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
            return false;
        }
        return true;
    }

    // Adds an animation to an Ogre skeleton, replacing the existing animation by that name
    // if it exists.
    bool Skeleton::replaceAnimation(Ogre::Skeleton& skeleton, const std::string& clipName, float start,float stop,float rate,ParamList& params)
    {
        Animation a;
        loadClipAnim(clipName, start, stop, rate, params, a);
        if(skeleton.hasAnimation(clipName.c_str()))
        {
           skeleton.removeAnimation(clipName.c_str());
        }
        addOgreSkeletonAnimation(skeleton, a);
        return true;
    }

    void Skeleton::getKeyedFrames(std::vector<int>& keyedFrames, ParamList& params )
    {
        // Get the animstack for getting blendshape curve info.
        FbxAnimLayer* pAnimLayer = NULL;
        FbxAnimStack* pAnimStack = params.pScene->GetSrcObject<FbxAnimStack>(0);
        if( pAnimStack)
        {
            pAnimLayer = (FbxAnimLayer*) pAnimStack->GetMember(FbxCriteria::ObjectType(FbxAnimLayer::ClassId), 0);
        }

        std::vector<FbxAnimCurve *> curves;
        for( size_t i = 0; i < m_joints.size(); ++i )
        {
            FbxNode *pNode = m_joints[i].pNode;
            if( pNode )
            {
                curves.push_back( pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, false));
                curves.push_back( pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y, false));
                curves.push_back( pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z, false));
                curves.push_back( pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, false));
                curves.push_back( pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y, false));
                curves.push_back( pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z, false));
                curves.push_back( pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, false));
                curves.push_back( pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y, false));
                curves.push_back( pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z, false));
            }
        }
        for( size_t i = 0; i < curves.size(); ++i )
        {
            AppendKeyedFrames(keyedFrames, curves[i]);
        }
    }

    // Write to an OGRE binary skeleton
    bool Skeleton::writeOgreBinary(ParamList &params)
    {
        bool stat;
        
        // Construct skeleton
        std::string name = "fbxExport";
        Ogre::SkeletonPtr pSkeleton = Ogre::SkeletonManager::getSingleton().create(name.c_str(), 
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        // Create skeleton bones
        stat = createOgreBones(*pSkeleton,params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error writing skeleton binary file\n");
        }
        // Create skeleton animation
        if (params.exportSkelAnims)
        {
            stat = createOgreSkeletonAnimations(*pSkeleton,params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error writing ogre skeleton animations\n");
            }
        }
        pSkeleton->setBindingPose();
        // Optimise animations
        pSkeleton->optimiseAllAnimations();

        // Export skeleton binary
        Ogre::SkeletonSerializer serializer;
        serializer.exportSkeleton(pSkeleton.getPointer(),params.skeletonFilename.c_str());
        pSkeleton.setNull();
        // Skeleton successfully exported
        return true;
    }

    // Write joints to an Ogre skeleton
    bool Skeleton::createOgreBones(Ogre::Skeleton& skeleton,ParamList& params)
    {
        size_t i;
        // Create the bones
        for (i=0; i<m_joints.size(); i++)
        {
            joint* j = &m_joints[i];
            // Create a new bone
            Ogre::Bone* pBone = skeleton.createBone(m_joints[i].name.c_str(), m_joints[i].id);
            // Set bone position (relative to it's parent)
            pBone->setPosition(static_cast<Ogre::Real>(j->posx),
                static_cast<Ogre::Real>(j->posy),
                static_cast<Ogre::Real>(j->posz));
            // Set bone orientation (relative to it's parent)
            Ogre::Quaternion orient;
            orient.w = static_cast<Ogre::Real>(j->quatw);
            orient.x = static_cast<Ogre::Real>(j->quatx);
            orient.y = static_cast<Ogre::Real>(j->quaty);
            orient.z = static_cast<Ogre::Real>(j->quatz);
            //orient.FromAngleAxis(Ogre::Radian(j->angle),Ogre::Vector3(j->axisx,j->axisy,j->axisz));
            pBone->setOrientation(orient);
            // Set bone scale (relative to it's parent
            pBone->setScale(j->scalex,j->scaley,j->scalez);

            if( j->bInheritScale == false )
            {
                pBone->setInheritScale(false);
            }
        }
        // Create the hierarchy
        for (i=0; i<m_joints.size(); i++)
        {
            int parentIdx = m_joints[i].parentIndex;
            if (parentIdx >= 0 )
            {
                assert( parentIdx < (int)m_joints.size() );
                // Get the parent joint
                Ogre::Bone* pParent = skeleton.getBone(m_joints[parentIdx].id);
                // Get current joint from skeleton
                Ogre::Bone* pBone = skeleton.getBone(m_joints[i].id);
                // Place current bone in the parent's child list
                pParent->addChild(pBone);
            }
        }
        return true;
    }

    bool Skeleton::addOgreSkeletonAnimation(Ogre::Skeleton& skeleton, FxOgreFBX::Animation& anim)
    {
        // Create a new animation
        Ogre::Animation* pAnimation = skeleton.createAnimation(anim.m_name.c_str(),anim.m_length);
        for (int j=0; j<static_cast<int>(anim.m_tracks.size()); j++)
        {
            Track* t = &anim.m_tracks[j];
            // Create a new track
            Ogre::NodeAnimationTrack* pTrack = pAnimation->createNodeTrack(j,
                skeleton.getBone(t->m_bone.c_str()));
            // Create keyframes for current track
            for (size_t k=0; k<t->m_skeletonKeyframes.size(); k++)
            {
                skeletonKeyframe* keyframe = &t->m_skeletonKeyframes[k];
                // Create a new keyframe
                Ogre::TransformKeyFrame* pKeyframe = pTrack->createNodeKeyFrame(keyframe->time);
                // Set translation
                pKeyframe->setTranslate(Ogre::Vector3(static_cast<Ogre::Real>(keyframe->tx),
                    static_cast<Ogre::Real>(keyframe->ty),
                    static_cast<Ogre::Real>(keyframe->tz)));
                // Set rotation
                Ogre::Quaternion rot = Ogre::Quaternion(static_cast<Ogre::Real>(keyframe->quat_w), 
                    static_cast<Ogre::Real>(keyframe->quat_x), 
                    static_cast<Ogre::Real>(keyframe->quat_y), 
                    static_cast<Ogre::Real>(keyframe->quat_z));

                pKeyframe->setRotation(rot);
                // Set scale
                pKeyframe->setScale(Ogre::Vector3(keyframe->sx,keyframe->sy,keyframe->sz));
            }
        }
        return true;
    }

    // Write skeleton animations to an Ogre skeleton
    bool Skeleton::createOgreSkeletonAnimations(Ogre::Skeleton& skeleton,ParamList& params)
    {
        // Read loaded skeleton animations
        for (size_t i=0; i<m_animations.size(); i++)
        {
            addOgreSkeletonAnimation(skeleton, m_animations[i]);
        }
        return true;
    }

};	//end namespace
