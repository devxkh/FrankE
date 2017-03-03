////////////////////////////////////////////////////////////////////////////////
// mesh.cpp
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
// Port to 3D Studio Max - Modified original version - Modified original version
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
#include <map>
#include "common.h"
#include "mesh.h"

#include "OgreDefaultHardwareBufferManager.h"

namespace FxOgreFBX
{
    /***** Class Mesh *****/
    // constructor
    Mesh::Mesh(const std::string& name)
    {
        m_name = name;
        m_numTriangles = 0;
        m_pSkeleton = NULL;
        m_sharedGeom.vertices.clear();
        m_sharedGeom.dagMap.clear();
        m_vertexClips.clear();
        m_BSClips.clear();
        m_numBlendShapes = 0;
        m_bindBox.clear();
    }

    // destructor
    Mesh::~Mesh()
    {
        clear();
    }

    // clear data
    void Mesh::clear()
    {
        size_t i;
        m_name = "";
        m_numTriangles = 0;

        std::map<BlendShape*, bool> deletedBlendShapes;
        
        for (i=0; i<m_submeshes.size(); i++)
        {
            deletedBlendShapes[m_submeshes[i]->getBlendShape()] = true;
            delete m_submeshes[i];
        }

        for (i=0; i<m_sharedGeom.dagMap.size(); i++)
        {
            deletedBlendShapes[m_sharedGeom.dagMap[i].pBlendShape] = true;
        }
        
        std::map<BlendShape*, bool>::iterator it  = deletedBlendShapes.begin();
        for(it = deletedBlendShapes.begin(); it!= deletedBlendShapes.end(); ++it)
        {
            if((*it).first)
            {
                delete (*it).first;
            }
        }

        m_sharedGeom.vertices.clear();
        m_sharedGeom.dagMap.clear();
        m_vertexClips.clear();
        m_BSClips.clear();
        m_uvsets.clear();
        m_submeshes.clear();
        if (m_pSkeleton)
            delete m_pSkeleton;
        m_pSkeleton = NULL;
        m_numBlendShapes = 0;
    }

    // get pointer to linked skeleton
    Skeleton* Mesh::getSkeleton()
    {
        return m_pSkeleton;
    }

    bool Mesh::DeleteAnimationFromExisting(OgreManagers& managers, std::string &meshfilepath, std::string &clipName)
    {

        Ogre::MeshPtr pOgreMesh = loadOgreMeshFromFile(managers, meshfilepath);
        if( pOgreMesh.get()->hasAnimation(clipName.c_str()) )
        {
            pOgreMesh.get()->removeAnimation(clipName.c_str());
            FxOgreFBXLog( "Deleted %s animation from mesh.\n", clipName.c_str() );

            Ogre::MeshSerializer meshSerializer;
            try
            {
                meshSerializer.exportMesh(pOgreMesh.get(),meshfilepath.c_str());
            }
            catch( Ogre::Exception& e )
            {
                FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
                return false;
            }
            return true;
        }
        FxOgreFBXLog( "Could not delete %s animation because it did not exist in mesh.\n", clipName.c_str() );
        return false;       
    
    }
    Ogre::MeshPtr Mesh::loadOgreMeshFromFile(OgreManagers& managers, std::string &meshfilepath)
    {
        //http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Loading+Meshes+From+Any+Path
        Ogre::String source = meshfilepath.c_str();
        FILE* pFile = fopen( source.c_str(), "rb" );
        if (!pFile)
            FxOgreFBXLog( "Error! Mesh not found: %s.\n", source.c_str() );
        struct stat tagStat;
        stat( source.c_str(), &tagStat );
        Ogre::MemoryDataStream* memstream = new Ogre::MemoryDataStream(source, tagStat.st_size, true);
        fread( (void*)memstream->getPtr(), tagStat.st_size, 1, pFile );
        fclose( pFile );      


        Ogre::MeshPtr pMesh = managers.meshMgr->createManual("LocalMesh",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::MeshSerializer meshSerializer;
        Ogre::DataStreamPtr stream(memstream);
        
        try
        {
            meshSerializer.importMesh(stream, pMesh.get());     
        }
        catch( Ogre::Exception& e )
        {
            FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
        }
        return pMesh;
    }
    bool Mesh::AddFBXAnimationToExisting(OgreManagers& managers, std::string &meshfilepath, std::string &clipName, ParamList& params, float start, float stop)
    {
        for( int iGeom = 0; iGeom < params.pScene->GetGeometryCount(); ++iGeom )
        {
            FbxGeometry *pGeom = params.pScene->GetGeometry(iGeom);
            FbxNode *pNode = pGeom->GetNode();
            if( !pNode )
            {
                continue;
            }
            if( !pNode->GetMesh() )
            {
                continue;
            }
            FbxMesh *pFBXMesh = pNode->GetMesh();

            if( isVisible(pNode) )
            {
                if( pFBXMesh->GetShapeCount() > 0  )
                {
                    FbxAMatrix bind = getBindPose(pNode, pFBXMesh, params);
                    pBlendShape = new BlendShape(pNode, bind);
                    
                    std::vector<vertex> vertices;

                    // We are pasing in an empty vertex array to loadPoses because we are only interested
                    // in animation data.
                    pBlendShape->loadPoses(params,vertices,0,0,0 );

                    dagInfo di;
                    di.pNode = pNode;
                    di.pBlendShape = pBlendShape;
                    m_sharedGeom.dagMap.push_back(di);
                }                          
            }
        }
        
        loadBlendShapeAnimations(params);
        
        Ogre::MeshPtr pOgreMesh = loadOgreMeshFromFile(managers, meshfilepath);
       
        if( params.fps == 0 )
        {
            FxOgreFBXLog( "Invalid fps rate: 0. Failed to import animation %s.\n", clipName.c_str() );
            return false;
        }
        if( start > stop )
        {
            FxOgreFBXLog( "Invalid start and end time for animation %s: (%f, %f).\n", clipName.c_str(), start, stop );
            return false;
        }
        if( replaceBSAnimation(pOgreMesh, clipName, start, stop, 1/params.fps, params) )
        {
            Ogre::MeshSerializer meshSerializer;
            try
            {
                meshSerializer.exportMesh(pOgreMesh.get(),meshfilepath.c_str());
            }
            catch( Ogre::Exception& e )
            {
                FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
                return false;
            }
            return true;
        }
        return false;
    }

    bool Mesh::preprocessNode(FbxNode *pNode, FbxMesh *pMesh, FbxScene* pScene)
    {
        if(pNode)
        {
            FbxSurfacePhong* lMaterial = NULL;
            lMaterial = pNode->GetSrcObject<FbxSurfacePhong>(0);
            if (lMaterial == NULL)
            {
                FbxString lMaterialName = "defaultPhong";
                FbxString lShadingName  = "Phong";
                FbxDouble3 lBlack(0.0, 0.0, 0.0);
                FbxDouble3 lRed(1.0, 0.0, 0.0);
                FbxDouble3 lDiffuseColor(0.75, 0.75, 0.0);
                lMaterial = FbxSurfacePhong::Create(pScene, lMaterialName.Buffer());

                // Generate primary and secondary colors.
                lMaterial->Emissive           .Set(lBlack);
                lMaterial->Ambient            .Set(lRed);
                lMaterial->AmbientFactor      .Set(1.);
                // Add texture for diffuse channel
                lMaterial->Diffuse           .Set(lDiffuseColor);
                lMaterial->DiffuseFactor     .Set(1.);
                lMaterial->TransparencyFactor.Set(0.4);
                lMaterial->ShadingModel      .Set(lShadingName);
                lMaterial->Shininess         .Set(0.5);
                lMaterial->Specular          .Set(lBlack);
                lMaterial->SpecularFactor    .Set(0.3);

                pNode->AddMaterial(lMaterial);
            }
            FbxGeometryElementMaterial* lMaterialElement = pMesh->CreateElementMaterial();
            lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
            lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

        }
        return true;
    }
    //--------------------------------------------------------------------------------
    //                    Load mesh data from a node                          *
    //--------------------------------------------------------------------------------- 
    bool Mesh::load(FbxNode* pNode,FbxMesh* pMesh, ParamList &params)
    {

        FxOgreFBXLog( "Exporting mesh %s...\n", pNode->GetName());

        if( pMesh->GetPolygonCount() == 0 )
        {
            FxOgreFBXLog( "Mesh %s has no polygons.  Skipping...\n", pNode->GetName());
            return false;
        }

        FbxScene *pScene = params.pScene;
        preprocessNode(pNode,pMesh, pScene);
        bool stat;
        // Set mesh name
        m_name = pNode->GetName();

        // Initialise temporary variables
        newvertices.clear();
        newweights.clear();
        newjointIds.clear();

        newuvsets.clear();
        newpoints.clear();
        newnormals.clear();
        
        shaders.clear();
        pSkinCluster = NULL;
        pBlendShape = NULL;

        polygonSets.clear();

        polygonSets.resize(pNode->GetMaterialCount());

        opposite = false;
        // If the mesh has negative scale, reverse the normals
        FbxVector4 scale = CalculateGlobalTransform(pNode, FbxTime(params.bindframe)).GetS();
        if( scale[0] * scale[1] * scale[2] < 0 )
        {
            FxOgreFBXLog("Scale on mesh %s is reversed.  Setting opposite to true.\n", pNode->GetName());
            opposite = true;
        }

        // Get mesh uvsets
        stat = getUVSets(pNode, pMesh);		
        if (stat != true)
        {
            FxOgreFBXLog("Error retrieving uvsets for current mesh\n");
        }
        
        // Get skin and blendShape modifiers
        stat = getModifiers(pNode, pMesh, params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error retrieving skin cluster linked to current mesh\n");
        }
        // Get vertex data
        stat = getVertices(pNode, pMesh ,params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error retrieving vertex data for current mesh\n");
        }
        
        // Get vertex bone weights
        if (m_pSkeleton)
        {
            getVertexBoneWeights(pNode, pMesh, params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error retrieving veretex bone assignements for current mesh\n");
            }
        }
        
        // Get faces data
        stat = getFaces(pNode, pMesh, params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error retrieving faces data for current mesh\n");
        }
        // Set default values for data (rigidly skinned meshes, bone weights, position indices)
        stat = cleanupData(pNode, params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error cleaning up data for current mesh\n");
        }
        // Build shared geometry
        if (params.useSharedGeom)
        {
            stat = buildSharedGeometry(pNode,params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error building shared geometry for current mesh\n");				
            }
        }
        // Create submeshes (a different submesh for every material linked to the mesh and associated with a polygon)
        stat = createSubmeshes(pNode, pMesh,params);
        if (stat != true)
        {
            FxOgreFBXLog( "Error creating submeshes for current mesh\n");	
        }
    
        // Free up memory
        newvertices.clear();
        newweights.clear();
        newjointIds.clear();
        newpoints.clear();
        newnormals.clear();
        newuvsets.clear();
        shaders.clear();
        pSkinCluster = NULL;
        pBlendShape = NULL;
        polygonSets.clear();
        return true;
    }

    void Mesh::createSkeleton( )
    {
        if (!m_pSkeleton)
            m_pSkeleton = new Skeleton();
    }

    bool Mesh::getModifiers( FbxNode* pNode, FbxMesh *pMesh, ParamList& params )
    {
        if( pMesh->GetShapeCount() > 0  )
        {
            FbxAMatrix bind = getBindPose(pNode, pMesh, params);
            pBlendShape = new BlendShape(pNode, bind);
        }

        return true;
    }
    
    //--------------------------------------------------------------------------------
    //                    Load mesh animations                           *
    //--------------------------------------------------------------------------------
    // Load vertex animations
    bool Mesh::loadAnims(ParamList& params)
    {
        bool stat;
        size_t i;

        FxOgreFBXLog( "Loading vertex animations...\n");
        
        // clear animations data
        m_vertexClips.clear();
        // load the requested clips
        for (i=0; i<params.vertClipList.size(); i++)
        {
            FxOgreFBXLog( "Loading clip %s.\n", params.vertClipList[i].name.c_str() );
            
            stat = loadVertexClip(params.vertClipList[i].name,params.vertClipList[i].start,
                params.vertClipList[i].stop,params.vertClipList[i].rate,params);
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

    // Load blend shape deformers
    bool Mesh::loadBlendShapes(ParamList &params)
    {
        int i;
        FxOgreFBXLog( "Loading blend shape poses...\n");
        
        // Get the blend shape poses
        if (params.useSharedGeom)
        {
            for  (i=0; i<static_cast<int>(m_sharedGeom.dagMap.size()); i++)
            {
                dagInfo di = m_sharedGeom.dagMap[i];
                if (di.pBlendShape)
                    di.pBlendShape->loadPoses(params,m_sharedGeom.vertices,di.numVertices,di.offset);
            }
        }
        else
        {
            for (i=0; i<static_cast<int>(m_submeshes.size()); i++)
            {
                Submesh* pSubmesh = m_submeshes[i];
                if (pSubmesh->m_pBlendShape)
                    pSubmesh->m_pBlendShape->loadPoses(params,pSubmesh->m_vertices,
                        static_cast<long>(pSubmesh->m_vertices.size()),0,i+1);
            }
        }
        return true;
    }
    void Mesh::getKeyedFrames(std::vector<int>& keyedFrames, ParamList& params )
    {
        // Get the blend shape poses
        if (params.useSharedGeom)
        {
            for  (size_t i=0; i<m_sharedGeom.dagMap.size(); i++)
            {
                dagInfo di = m_sharedGeom.dagMap[i];
                if (di.pBlendShape)
                    di.pBlendShape->getKeyedFrames(keyedFrames);
            }
        }
        else if( pBlendShape )
        {
            pBlendShape->getKeyedFrames(keyedFrames);
        }
    }

    bool Mesh::loadBSClipAnim(std::string clipName,float start,float stop,float rate,ParamList& params, Animation& a)
    {
        int startPoseId = 0;
        int j,k = 0;
        a.m_name = clipName;
        a.m_length = stop - start;
        a.m_tracks.clear();
        FxOgreFBXLog( "clip %s\n", clipName.c_str());
        // Read animation tracks from the blend shape deformer
        if (params.useSharedGeom)
        {
            // Create a track for each blend shape
            std::vector<Track> tracks;
            for  (j=0; j<static_cast<int>(m_sharedGeom.dagMap.size()); j++)
            {
                dagInfo di = m_sharedGeom.dagMap[j];
                if (di.pBlendShape)
                {
                    Track t = di.pBlendShape->loadTrack(start,stop,rate,params,0,startPoseId);
                    tracks.push_back(t);
                    startPoseId += static_cast<int>(di.pBlendShape->getPoseGroups().find(0)->second.poses.size());
                }
            }
            // Merge the tracks into a single track (shared geometry must have a single animation track)
            if (tracks.size() > 0)
            {
                Track newTrack;
                // Merge keyframes at the same time position from all tracks
                for (j=0; j<static_cast<int>(tracks[0].m_vertexKeyframes.size()); j++)
                {
                    // Create a new keyframe
                    vertexKeyframe newKeyframe;
                    newKeyframe.time = tracks[0].m_vertexKeyframes[j].time;
                    // Get keyframe at current position from all tracks
                    for (k=0; k<static_cast<int>(tracks.size()); k++)
                    {
                        vertexKeyframe* pSrcKeyframe = &tracks[k].m_vertexKeyframes[j];
                        size_t pri;
                        // Add pose references from this keyframe to the new keyframe for the joined track
                        for (pri=0; pri<pSrcKeyframe->poserefs.size(); pri++)
                        {
                            // Create a new pose reference
                            vertexPoseRef poseref;
                            // Copy pose reference settings from source keyframe
                            poseref.poseIndex = pSrcKeyframe->poserefs[pri].poseIndex;
                            poseref.poseWeight = pSrcKeyframe->poserefs[pri].poseWeight;
                            // Add the new pose reference to the new keyframe
                            newKeyframe.poserefs.push_back(poseref);
                        }
                    }
                    // Add the keyframe to the new joined track
                    newTrack.m_vertexKeyframes.push_back(newKeyframe);
                }
                // Add the joined track to current animation clip
                a.addTrack(newTrack);
                FxOgreFBXLog( "num keyframes: %d.\n", a.m_tracks[0].m_vertexKeyframes.size());
            }
        }
        else
        {
            // Create a track for each submesh
            std::vector<Track> tracks;
            for (j=0; j<static_cast<int>(m_submeshes.size()); j++)
            {
                Submesh* pSubmesh = m_submeshes[j];
                if (pSubmesh->m_pBlendShape)
                {
                    Track t = pSubmesh->m_pBlendShape->loadTrack(start,stop,rate,params,j+1,startPoseId);
                    a.addTrack(t);
                    startPoseId += static_cast<int>(pSubmesh->m_pBlendShape->getPoseGroups().find(j+1)->second.poses.size());
                }
            }
        }
        FxOgreFBXLog( "length: %f.\n", a.m_length);
        return true;
            
    }

    // Load an animation clip
    bool Mesh::loadBSClip(std::string clipName,float start,float stop,float rate,ParamList& params)
    {
        Animation a;
        m_BSClips.push_back(a);
        bool stat = loadBSClipAnim(clipName, start, stop, rate, params, m_BSClips[m_BSClips.size() -1]);
        if( !stat )
        {
            m_BSClips.pop_back();
            return false;
        }
        return true;
    }
    // Load blend shape animations
    bool Mesh::loadBlendShapeAnimations(ParamList& params)
    {
        size_t i;
        FxOgreFBXLog( "Loading blend shape animations...\n");
        
        // Read the list of blend shape clips to export
        for (i=0; i<params.BSClipList.size(); i++)
        {
            FxOgreFBXLog( "Loading clip %s.\n", params.BSClipList[i].name.c_str() );
            bool result = loadBSClip(params.BSClipList[i].name,params.BSClipList[i].start,
                params.BSClipList[i].stop,params.BSClipList[i].rate,params);
            if (result == true)
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

    // Adds a blendshape animation to an Ogre mesh, replacing the existing animation by that name
    // if it exists.
    bool Mesh::replaceBSAnimation(Ogre::MeshPtr pMesh, const std::string& clipName, float start,float stop,float rate,ParamList& params)
    {
        Animation a;
        loadBSClipAnim(clipName, start, stop, rate, params, a);
        if(pMesh.get()->hasAnimation(clipName.c_str()))
        {
           pMesh.get()->removeAnimation(clipName.c_str());
        }
        if( createOgrePoseAnimation(pMesh, a, params) )
        {
            return true;
        }
        return false;
    }

//--------------------------------------------------------------------------------
// ******************* Methods to parse geometry data ***************** /
//--------------------------------------------------------------------------------
    
    // Get uvsets info from the mesh
    bool Mesh::getUVSets(FbxNode *pNode, FbxMesh *pMesh)
    {
        if( pNode && pMesh) 
        {

            for( int i = 0; i < pMesh->GetElementUVCount(); ++i )
            {
                FbxGeometryElementUV* leUV = pMesh->GetElementUV(i);
                switch (leUV->GetMappingMode())
                {
                case FbxGeometryElement::eByPolygonVertex:
                    {
                        newuvsets.push_back(i);
                    }
                    break;
                default:
                    {
                        FxOgreFBXLog( "ERRORBOXWARNING: Unsupported UV format for mesh %s.\n", pNode->GetName());
                        FxOgreFBXLog( "Warning: Unsupported UV format for mesh %s.  Make sure UVs are per-vertex to get textures to display properly.\n", pNode->GetName());
                        assert(false);
                    }
                    break;
                }
            }
            for( int i = static_cast<int>(m_uvsets.size()); i <  pMesh->GetElementUVCount(); ++i)
            {
                uvset uv;
                uv.size = 2;
                m_uvsets.push_back(uv);
            }
            return true;
        }
        return false;
    }



    FbxAMatrix Mesh::getBindPose(FbxNode *pNode, FbxMesh *pMesh, ParamList &params)
    {
        if( !params.useanimframebind )
        {
            int lSkinCount= pMesh->GetDeformerCount(FbxDeformer::eSkin);
            for(int i=0; i!=lSkinCount; ++i)
            {
                int lClusterCount = ((FbxSkin *) pMesh->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
                for (int j = 0; j < lClusterCount; ++j)
                {       
                     
                    FbxCluster *pCluster=((FbxSkin *) pMesh->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);  

                    FbxAMatrix geometryBind;
                    pCluster->GetTransformMatrix(geometryBind);
                    if( isValidMatrix(geometryBind ))
                        return geometryBind;
                }
            }
            // It can be difficult to calculate the correct bind position for the mesh because
            // the FBX Global evaluate functions do not seem to take the inheritance type into account.
            // eInherit_Rrs nodes can mess things up.
            FxOgreFBXLog( "Warning: can not find bind pose for mesh %s.  Attempting to calculate it\n", pNode->GetName());
        }

        FbxAMatrix globalTransform;
        if( getSkeleton() )
        {
            globalTransform = getSkeleton()->CalculateGlobalTransformWithBind(pNode, FbxTime(params.bindframe), params);
        }
        else
        {
            globalTransform = CalculateGlobalTransform(pNode, FbxTime(params.bindframe));
        }
        
        return globalTransform;
    }

    // Get vertex data
    bool Mesh::getVertices(FbxNode *pNode, FbxMesh *pMesh, ParamList &params)
    {
        if( pNode )
        { 
            FbxAMatrix nodeTransform = getBindPose( pNode, pMesh, params); 
            nodeTransform = correctMatrix(nodeTransform);
            FxOgreFBXLog( "Mesh %s has globalTransform:", pNode->GetName());  
            logMatrix(nodeTransform);
            if( pMesh )
            {
                int numVertices = pMesh->GetControlPointsCount();
                newvertices.resize(numVertices);
                newweights.resize(numVertices);
                newjointIds.resize(numVertices);
                FxOgreFBXLog( "Num vertices: %i\n", numVertices);
                for (int i=0; i<numVertices; i++)
                {
                    newvertices[i].pointIdx = -1;
                    newvertices[i].normalIdx = -1;
                    newvertices[i].next = -2;
                }
                //get vertex positions from mesh
                newpoints.resize(numVertices);
                FbxVector4* pControlPoints = pMesh->GetControlPoints();

                if( params.useanimframebind )
                {

		            FbxVector4* lVertexArrayLinear = new FbxVector4[pMesh->GetControlPointsCount()];
		            memcpy(lVertexArrayLinear, pMesh->GetControlPoints(), pMesh->GetControlPointsCount() * sizeof(FbxVector4));
                    FbxTime pTime(params.bindframe);

                    // To set the skeleton to it's position at frame 0, we set the pose to NULL.
                    FbxPose* pPose = NULL;

                    ComputeLinearDeformation(nodeTransform, pNode, pMesh, pTime, lVertexArrayLinear, pPose);
                    for( int i = 0; i < pMesh->GetControlPointsCount(); ++i )
                    {
                        newpoints[i] = nodeTransform.MultT(lVertexArrayLinear[i]);
                    }
                    delete [] lVertexArrayLinear;
                }
                else if( pControlPoints )
                {
                    for( int i = 0; i < numVertices; ++i )
                    {
                        newpoints[i] = nodeTransform.MultT( pControlPoints[i] );
                    }
                }

                int numfaces =pMesh->GetPolygonCount();
                newnormals.resize(numfaces*3);
                int nIdx = 0;

                if( pMesh->CheckIfVertexNormalsCCW() )
                {
                    FxOgreFBXLog( "Counter clockwise normals detected.\n");
                }
                if( pMesh->GetLayer(0)->GetNormals() == NULL)
                {
                    FxOgreFBXLog( "Warning!  Recomputing normals with FbxMesh::ComputeVertexNormals.  This may cause artifacts on some graphics cards.\n");
                    pMesh->InitNormals();
                    pMesh->GenerateNormals();
                }
                FbxVector4 pNormal;
                for( int iFCount = 0; iFCount < numfaces; ++iFCount)
                {
                    for (int i=0; i<3; i++)
                    {
                        pMesh->GetPolygonVertexNormal(iFCount, i, pNormal);
                        // Rotate the normals by the node's rotation.
                        FbxAMatrix mat;
                        mat.SetQ(nodeTransform.GetQ());
                        FbxVector4 norm = mat.MultT(pNormal); 
                        norm.Normalize();
                        newnormals[nIdx] = norm;
                        nIdx++;
                    }
                }
            }
        }
        return true;
    }

    // Get vertex bone assignements
    bool Mesh::getVertexBoneWeights(FbxNode* pNode,  FbxMesh *pMesh, ParamList &params)
    {
        int lSkinCount= pMesh->GetDeformerCount(FbxDeformer::eSkin);
        for(int i=0; i!=lSkinCount; ++i)
        {
            int lClusterCount = ((FbxSkin *) pMesh->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
            for (int j = 0; j < lClusterCount; ++j)
            {
                FbxCluster *pCluster=((FbxSkin *) pMesh->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);
                if( pCluster && m_pSkeleton )
                {
                    int boneIndex = m_pSkeleton->getJointIndex(pCluster->GetLink());
                    int k, lIndexCount = pCluster->GetControlPointIndicesCount();
                    int* lIndices = pCluster->GetControlPointIndices();
                    double* lWeights = pCluster->GetControlPointWeights();

                    for(k = 0; k < lIndexCount; k++)
                    {
                        if(boneIndex >= 0)
                        {
                            newweights[lIndices[k]].push_back(static_cast<float>(lWeights[k]));
                            newjointIds[lIndices[k]].push_back(boneIndex);
                        }
                    }
                }
            }
        }
        return true;
    }

    // Get faces data
    bool Mesh::getFaces(FbxNode *pNode, FbxMesh *pMesh, ParamList &params)
    {
        int i,j,k;

        int numfaces =pMesh->GetPolygonCount();

        // create an iterator to go through mesh polygons
        if (numfaces > 0)
        {
            FxOgreFBXLog( "Iterate over mesh faces\n");
            FxOgreFBXLog( "num polygons = %d\n", numfaces);

            bool different;
            int vtxIdx, nrmIdx;

            nrmIdx = -1;
            for( int iFCount = 0; iFCount < numfaces; ++iFCount)
            {
                int idx;
                face newFace;
                for (i=0; i<3; i++)
                {
                    different = true;
                    vtxIdx = pMesh->GetPolygonVertex(iFCount, i);
                    nrmIdx++;

                    assert(vtxIdx >= 0 && vtxIdx < static_cast<int>(newvertices.size()));
                    assert(nrmIdx >= 0 && nrmIdx < static_cast<int>(newnormals.size()));

                    FbxColor col = GetFBXColor(pMesh, iFCount, i);
                    Point3 color = Point3(col.mRed,col.mGreen,col.mBlue);
                    float alpha = static_cast<float>(col.mAlpha);

                    if (newvertices[vtxIdx].next == -2)	// first time we encounter a vertex in this position
                    {

                        // save vertex position
                        newvertices[vtxIdx].pointIdx = vtxIdx;
                        // save vertex normal
                        newvertices[vtxIdx].normalIdx = nrmIdx;
                        // save vertex colour
                        newvertices[vtxIdx].r = static_cast<float>(color.x);
                        newvertices[vtxIdx].g = static_cast<float>(color.y);
                        newvertices[vtxIdx].b = static_cast<float>(color.z);
                        newvertices[vtxIdx].a = alpha;
                        // save vertex texture coordinates
                        newvertices[vtxIdx].u.resize(newuvsets.size());
                        newvertices[vtxIdx].v.resize(newuvsets.size());
        
                        // save vbas
                        newvertices[vtxIdx].vba.resize(newweights[vtxIdx].size());
                        for (j=0; j<static_cast<int>(newweights[vtxIdx].size()); j++)
                        {
                            newvertices[vtxIdx].vba[j] = (newweights[vtxIdx])[j];
                        }
                        // save joint ids
                        newvertices[vtxIdx].jointIds.resize(newjointIds[vtxIdx].size());
                        for (j=0; j<static_cast<int>(newjointIds[vtxIdx].size()); j++)
                        {
                            newvertices[vtxIdx].jointIds[j] = (newjointIds[vtxIdx])[j];
                        }

                        // save uv sets data
                        for (j=0; j<static_cast<int>(newuvsets.size()); j++)
                        {
                            newvertices[vtxIdx].u[j] = 0;
                            newvertices[vtxIdx].v[j] = 0;

                            int lTextureUVIndex = pMesh->GetTextureUVIndex(iFCount, i);
                            FbxGeometryElementUV* leUV = pMesh->GetElementUV(j);
                            FbxVector2 uvVector = leUV->GetDirectArray().GetAt(lTextureUVIndex);
            
                            Point3 uv(uvVector[0], uvVector[1], 0);
                            uv.y = 1.0f - uv.y;
                            newvertices[vtxIdx].u[j] = static_cast<float>(uv.x);
                            newvertices[vtxIdx].v[j] = static_cast<float>(uv.y);
                        }
                        // save vertex index in face info
                        newFace.v[i] = static_cast<int>(m_sharedGeom.vertices.size()) + vtxIdx;
                        // update value of index to next vertex info (-1 means nothing next)
                        newvertices[vtxIdx].next = -1;
                    }
                    else	// already found at least 1 vertex in this position
                    {
                        // check if a vertex with same attributes has been saved already
                        for (k=vtxIdx; k!=-1 && different; k=newvertices[k].next)
                        {
                            different = false;

                            if (params.exportVertNorm)
                            {
                                FbxVector4 n1 = newnormals[newvertices[k].normalIdx];
                                FbxVector4 n2 = newnormals[nrmIdx];
                                if (n1[0]!=n2[0] || n1[1]!=n2[1] || n1[2]!=n2[2])
                                {
                                    different = true;
                                }
                            }
                            if ((params.exportVertCol) &&
                                (newvertices[k].r!=color.x || newvertices[k].g!=color.y || newvertices[k].b!= color.z || newvertices[k].a!=alpha))
                            {
                                different = true;
                            }

                            if (params.exportTexCoord)
                            {
                                for (j=0; j<static_cast<int>(newuvsets.size()); j++)
                                {
                                    int lTextureUVIndex = pMesh->GetTextureUVIndex(iFCount, i);
                                    FbxGeometryElementUV* leUV = pMesh->GetElementUV(j);
                                    FbxVector2 uvVector = leUV->GetDirectArray().GetAt(lTextureUVIndex);
                    
                                    float u = (float)uvVector[0];
                                    float v = 1.0f - (float)uvVector[1];
  
                                    if (newvertices[k].u[j]!=u || newvertices[k].v[j]!=v)
                                    {
                                        //FxOgreFBXLog( "Different UV.  j: %d (%f,%f) vs. (%f,%f)\n", j, newvertices[k].u[j], newvertices[k].v[j], u, v);
                                        different = true;
                                    }
                                }
                            }
                            idx = k;
                        }
                        // if no identical vertex has been saved, then save the vertex info
                        if (different)
                        {
                            vertexInfo vtx;
                            // save vertex position
                            vtx.pointIdx = vtxIdx;
                            // save vertex normal
                            vtx.normalIdx = nrmIdx;
                            // save vertex colour
                            vtx.r = static_cast<float>(color.x);
                            vtx.g = static_cast<float>(color.y);
                            vtx.b = static_cast<float>(color.z);
                            vtx.a = alpha;
                            // save vertex vba
                            vtx.vba.resize(newweights[vtxIdx].size());
                            for (j=0; j<static_cast<int>(newweights[vtxIdx].size()); j++)
                            {
                                vtx.vba[j] = (newweights[vtxIdx])[j];
                            }
                            // save joint ids
                            vtx.jointIds.resize(newjointIds[vtxIdx].size());
                            for (j=0; j<static_cast<int>(newjointIds[vtxIdx].size()); j++)
                            {
                                vtx.jointIds[j] = (newjointIds[vtxIdx])[j];
                            }
                            // save vertex texture coordinates
                            vtx.u.resize(newuvsets.size());
                            vtx.v.resize(newuvsets.size());
                            for (j=0; j<static_cast<int>(newuvsets.size()); j++)
                            {
                                // Setup default
                                vtx.u[j] = 0;
                                vtx.v[j] = 0;

                                int lTextureUVIndex = pMesh->GetTextureUVIndex(iFCount, i);
                                FbxGeometryElementUV* leUV = pMesh->GetElementUV(j);
                                FbxVector2 uvVector = leUV->GetDirectArray().GetAt(lTextureUVIndex);
                
                                Point3 uv(uvVector[0], uvVector[1], 0);
                                uv.y = 1.0f - uv.y;
                                vtx.u[j] = static_cast<float>(uv.x);
                                vtx.v[j] = static_cast<float>(uv.y);
                            }
                            vtx.next = -1;
                            newvertices.push_back(vtx);
                            // save vertex index in face info
                            newFace.v[i] = static_cast<int>(m_sharedGeom.vertices.size()) + static_cast<int>(newvertices.size())-1;
                            newvertices[idx].next = static_cast<int>(newvertices.size())-1;
                        } 
                        else //	not different
                        {
                            newFace.v[i] = static_cast<int>(m_sharedGeom.vertices.size()) + idx;
                        }
                    }
                }

                int matID = 0;
                FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial();
                if( lMaterialElement )
                {
                    matID = lMaterialElement->GetIndexArray().GetAt(iFCount);
                }
                if ( matID < 0 || matID >= pNode->GetMaterialCount() )
                {
                    matID = 0;
                }

                polygonSets[matID].push_back(newFace);

            } // end iteration of triangles
            
        }
        FxOgreFBXLog( "done reading mesh triangles\n");
        
        return true;
    }

    // Set default values for data (rigidly skinned meshes, bone weights, position indices)
    bool Mesh::cleanupData(FbxNode* pNode, ParamList &params)
    {
        // Make sure there are no invalid vertex or normal indexes.
        assert(newpoints.size() != 0);
        assert(newnormals.size() !=0);
        for(size_t i = 0; i < newvertices.size(); i++)
        {
            if(newvertices[i].pointIdx < 0)
            {
                newvertices[i].pointIdx = 0;
            }
            if(newvertices[i].normalIdx < 0)
            {
                newvertices[i].normalIdx = 0;
            }
        }
        
        // Rigidly skin meshes
        std::string rigidlySkinnedBone = "root bone";
        int defaultJointIndex = -1;
        if(m_pSkeleton)
        {
            std::vector<joint> joints = m_pSkeleton->getJoints();

            defaultJointIndex =m_pSkeleton->getJointIndex(pNode);
            FbxNode* parent = pNode->GetParent();
            while(defaultJointIndex == -1 && parent != NULL)
            {
                defaultJointIndex = m_pSkeleton->getJointIndex(parent);
                parent = parent->GetParent();
            }
            if(defaultJointIndex != -1 )
            {
                rigidlySkinnedBone = joints[defaultJointIndex].name;
            }
        }
        bool bRigidlySkinned = false;
        bool bRigidlySkinToRoot = false;
        if(defaultJointIndex == -1 )
        {
            // All verts must be weighted to bones in Ogre.
            // Weight unskinned vertices to the root bone. 
            defaultJointIndex = 0;
            bRigidlySkinToRoot = true;
        }

        // Perform cleanup to prevent OGRE from crashing, the exporter from crashing
        // and to prevent artists from having to set things up a specific way.
        for(size_t i = 0; i < newvertices.size(); i++)
        {
            // Actually do the rigid skinning.
            if(newvertices[i].jointIds.size() == 0)
            {
                bRigidlySkinned = true;
                newvertices[i].jointIds.push_back(defaultJointIndex);				
            }
            if(newvertices[i].vba.size() == 0)
            {
                newvertices[i].vba.push_back(1.0f);
            }   
        }
        if( bRigidlySkinned )
        {
            if( bRigidlySkinToRoot )
            {
                FxOgreFBXLog("Rigidly skinned unweighted vertices of mesh %s to joint with index 0 because it was unskinned and had no joints as parents.\n", pNode->GetName());
            }
            else 
            {
                FxOgreFBXLog("Rigidly skinned unweighted vertices of mesh %s to joint %s.\n", pNode->GetName(), rigidlySkinnedBone.c_str());
            }
        }
        return true;
    }
    // Build shared geometry
    bool Mesh::buildSharedGeometry(FbxNode* pNode, ParamList &params)
    {
        
        size_t i,j,k;
        FxOgreFBXLog( "Create list of shared vertices\n");
        
        // save a new entry in the shared geometry map: we associate the index of the first 
        // vertex we're loading with the dag path from which it has been read
        dagInfo di;
        di.offset = static_cast<long>(m_sharedGeom.vertices.size());
        di.pNode = pNode;
        di.pBlendShape = pBlendShape;

        // load shared vertices
        for (i=0; i<newvertices.size(); i++)
        {
            vertex v;
            vertexInfo vInfo = newvertices[i];
            assert(vInfo.pointIdx >= 0 &&  vInfo.pointIdx < (int)newpoints.size());
            assert(vInfo.normalIdx >= 0 &&  vInfo.normalIdx < (int)newnormals.size());
            // save vertex coordinates (rescale to desired length unit)

            FbxVector4 point = newpoints[vInfo.pointIdx] * params.lum;
            if (fabs(point[0]) < PRECISION)
                point[0] = 0;
            if (fabs(point[1]) < PRECISION)
                point[1] = 0;
            if (fabs(point[2]) < PRECISION)
                point[2] = 0;
            v.x = point[0];
            v.y = point[1];
            v.z = point[2];
			
            m_bindBox.merge(Point3(v.x, v.y, v.z));

            // save vertex normal
            FbxVector4 normal = newnormals[vInfo.normalIdx];
            if (fabs(normal[0]) < PRECISION)
                normal[0] = 0;
            if (fabs(normal[1]) < PRECISION)
                normal[1] = 0;
            if (fabs(normal[2]) < PRECISION)
                normal[2] = 0;

            v.n.x = normal[0];
            v.n.y = normal[1];
            v.n.z = normal[2];
            if (opposite)
            {
                // Prevents the normals from facing inwards on the mesh, making it 
                // completely dark.
                v.n.x = -normal[0];
                v.n.y = -normal[1];
                v.n.z = -normal[2];
            }

            v.n.Normalize();
            // save vertex color
            v.r = vInfo.r;
            v.g = vInfo.g;
            v.b = vInfo.b;
            v.a = vInfo.a;
            // save vertex bone assignements
            for (k=0; k<vInfo.vba.size(); k++)
            {
                vba newVba;
                assert(k < vInfo.jointIds.size());
                newVba.jointIdx = vInfo.jointIds[k];
                newVba.weight = vInfo.vba[k];
                v.vbas.push_back(newVba);
            }
            // save texture coordinates
            for (k=0; k<vInfo.u.size(); k++)
            {
                texcoord newTexCoords;
                assert(k < vInfo.v.size());
                newTexCoords.u = vInfo.u[k];
                newTexCoords.v = vInfo.v[k];
                newTexCoords.w = 0;
                v.texcoords.push_back(newTexCoords);
            }
            // save vertex index in mesh, to retrieve future positions of the same vertex
            v.index = vInfo.pointIdx;
            // add newly created vertex to vertices list
            m_sharedGeom.vertices.push_back(v);
        }
        // Make sure all vertices have the same number of texture coordinates
        for (i=0; i<m_sharedGeom.vertices.size(); i++)
        {
            vertex* pV = &m_sharedGeom.vertices[i];
            for (j=pV->texcoords.size(); j<m_uvsets.size(); j++)
            {
                texcoord newTexCoords;
                newTexCoords.u = 0;
                newTexCoords.v = 0;
                newTexCoords.w = 0;
                pV->texcoords.push_back(newTexCoords);
            }
        }
        // save number of vertices referring to this mesh dag in the dag path map
        di.numVertices = static_cast<long>(m_sharedGeom.vertices.size()) - di.offset;
        m_sharedGeom.dagMap.push_back(di);
        FxOgreFBXLog( "done creating vertices list\n");
        
        return true;
    }


    // Create submeshes
    bool Mesh::createSubmeshes(FbxNode *pNode, FbxMesh *pMesh,ParamList& params)
    {
        for( int matIndex = 0; matIndex < pNode->GetMaterialCount(); ++matIndex )
        {
            if( polygonSets[matIndex].size() > 0 )
            {
                Submesh* pSubmesh = new Submesh();

                pSubmesh->loadMaterial(pNode->GetMaterial(matIndex),newuvsets,params);

                bool stat = false;
                if (getSkeleton() )
                {
                    //load vertex and face data
                     stat = pSubmesh->load(pNode, pMesh,polygonSets[matIndex],newvertices,newpoints,newnormals,newuvsets,params,m_pSkeleton->CalculateGlobalTransformWithBind(pNode, FbxTime(params.bindframe), params),opposite);
                }
                else
                {
                     stat = pSubmesh->load(pNode, pMesh,polygonSets[matIndex],newvertices,newpoints,newnormals,newuvsets,params,CalculateGlobalTransform(pNode, FbxTime(params.bindframe)),opposite);
                }
                //if we're not using shared geometry, save a pointer to the blend shape deformer
                if (pBlendShape && !params.useSharedGeom)
                    pSubmesh->m_pBlendShape = pBlendShape;
                //add submesh to current mesh
                m_submeshes.push_back(pSubmesh);
                //update number of triangles composing the mesh
                m_numTriangles += pSubmesh->numTriangles();
            }
        }
        return true;
    }




//--------------------------------------------------------------------------------
// ******************** Methods to read vertex animations  *********     /
//--------------------------------------------------------------------------------
    
    //load a vertex animation clip
    bool Mesh::loadVertexClip(std::string& clipName,float start,float stop,float rate,ParamList& params)
    {
        bool stat;
        std::string msg;
        std::vector<float> times;
        // calculate times from clip sample rate
        times.clear();
        for (float t=start; t<stop; t+=rate)
            times.push_back(t);
        times.push_back(stop);
        // get animation length
        float length=0;
        if (times.size() >= 0)
            length = times[times.size()-1] - times[0];
        if (length < 0)
        {
            FxOgreFBXLog( "invalid time range for the clip, we skip it\n");
            return false;
        }
        // create a new animation
        Animation a;
        a.m_name = clipName;
        a.m_length = length;
        a.m_tracks.clear();
        // if we're using shared geometry, create a single animation track for the whole mesh
        if (params.useSharedGeom)
        {
            // load the animation track
            stat = loadMeshTrack(a,times,params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error loading mesh vertex animation\n");
            }
        }
        // else creae a different animation track for each submesh
        else
        {
            // load all tracks (one for each submesh)
            stat = loadSubmeshTracks(a,times,params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error loading submeshes vertex animation\n");
                return false;
            }
        }
        // add newly created animation to animations list
        m_vertexClips.push_back(a);
        // display info
        FxOgreFBXLog( "length: %f.\n",a.m_length );
        FxOgreFBXLog( "num keyframes: %d.\n", a.m_tracks[0].m_vertexKeyframes.size());
        // clip successfully loaded
        return true;
    }


    //load an animation track for the whole mesh (using shared geometry)
    bool Mesh::loadMeshTrack(Animation& a,std::vector<float> &times, FxOgreFBX::ParamList &params)
    {
        size_t i;
        bool stat;
        // create a new track
        Track t;
        t.m_type = TT_MORPH;
        t.m_target = T_MESH;
        t.m_vertexKeyframes.clear();
        // get keyframes at given times
        for (i=0; i<times.size(); i++)
        {
            //load a keyframe for the mesh at current time
            stat = loadKeyframe(t,times[i]-times[0],params);
            if (stat != true)
            {
                FxOgreFBXLog( "Error reading animation keyframe at time: %f.\n", times[i] );
            }
        }
        // add track to given animation
        a.addTrack(t);
        // track sucessfully loaded
        return true;
    }


    //load all submesh animation tracks (one for each submesh)
    bool Mesh::loadSubmeshTracks(Animation& a,std::vector<float> &times, FxOgreFBX::ParamList &params)
    {
        int i,j;
        bool stat;
        // create a new track for each submesh
        std::vector<Track> tracks;
        for (i=0; i<static_cast<int>(m_submeshes.size()); i++)
        {
            Track t;
            t.m_type = TT_MORPH;
            t.m_target = T_SUBMESH;
            t.m_index = i+1;
            t.m_vertexKeyframes.clear();
            tracks.push_back(t);
        }
        // get keyframes at given times
        for (i=0; i<static_cast<int>(times.size()); i++)
        {
            //load a keyframe for each submesh at current time
            for (j=0; j<static_cast<int>(m_submeshes.size()); j++)
            {
                stat = m_submeshes[j]->loadKeyframe(tracks[j],times[i]-times[0],params);
                if (stat != true)
                {
                    FxOgreFBXLog( "Error reading animation keyframe at time: %f for submesh: %d.\n", times[i],  j);
                }
            }
        }
        // add tracks to given animation
        for (i=0; i< static_cast<int>(tracks.size()); i++)
            a.addTrack(tracks[i]);
        // track sucessfully loaded
        return true;
    }


    // Load a keyframe for the whole mesh
    bool Mesh::loadKeyframe(Track& t,float time,ParamList& params)
    {
        size_t i;
        // create a new keyframe
        vertexKeyframe k;
        // set keyframe time
        k.time = time;
        for (i=0; i<m_sharedGeom.dagMap.size(); i++)
        {
/*
            // get the mesh Fn
            dagInfo di = m_sharedGeom.dagMap[i];
            IGameMesh* pGameMesh = (IGameMesh*)di.pNode->GetIGameObject();
            if(!pGameMesh)
                return false;
            if(!pGameMesh->InitializeData() )
                return false;
            std::string name = di.pNode->GetName();
            int meshVertNum = pGameMesh->GetNumberOfVerts();
            bool bIsObjectSpace = true;
            if (params.exportWorldCoords)
                bIsObjectSpace = false;
            // calculate vertex offsets
            for (j=0; j<di.numVertices; j++)
            {
                vertexPosition pos;
                vertex v = m_sharedGeom.vertices[di.offset+j];
                assert(pGameMesh->GetNumberOfVerts() > v.index);
                Point3 point = pGameMesh->GetVertex(v.index, bIsObjectSpace);
                pos.x = point.x;
                pos.y = point.y;
                pos.z = point.z;
                if (fabs(pos.x) < PRECISION)
                    pos.x = 0;
                if (fabs(pos.y) < PRECISION)
                    pos.y = 0;
                if (fabs(pos.z) < PRECISION)
                    pos.z = 0;
                k.positions.push_back(pos);
            }
            di.pNode->ReleaseIGameObject();
            */
        }
        // add keyframe to given track
        t.addVertexKeyframe(k);
        // keyframe successfully loaded
        return true;
    }

    BoundingBox Mesh::calculateBoundingBox(ParamList &params)
    {
        if( !params.useSharedGeom )
        {
            for(size_t i=0; i<m_submeshes.size(); i++)
            {
                m_bindBox.merge(m_submeshes[i]->m_bbox.min);
                m_bindBox.merge(m_submeshes[i]->m_bbox.max);
            }			
        }
        return m_bindBox;
    }

//--------------------------------------------------------------------------------
//  *************************** Export mesh data ********************************* /
//--------------------------------------------------------------------------------
    // Write to a OGRE binary mesh

    bool Mesh::writeOgreBinary(ParamList &params)
    {
        size_t i;

        // Construct mesh
        Ogre::MeshPtr pMesh = Ogre::MeshManager::getSingleton().createManual(m_name.c_str(), 
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        // Write shared geometry data
        if (params.useSharedGeom)
        {
            createOgreSharedGeometry(pMesh,params);
        }
        // Write submeshes data
        for (i=0; i<m_submeshes.size(); i++)
        {
            m_submeshes[i]->createOgreSubmesh(pMesh,params);
        }
        // Set skeleton link (if present)
        if (m_pSkeleton && params.exportSkeleton)
        {
            std::string filename = StripToTopParent(params.skeletonFilename);
            pMesh->setSkeletonName(filename.c_str());
        }
        // Write poses
        if (params.exportBlendShapes)
        {
            createOgrePoses(pMesh,params);
        }
        // Write vertex animations
        if (params.exportVertAnims)
        {
            createOgreVertexAnimations(pMesh,params);
        }
        // Write pose animations
        if (params.exportBSAnims)
        {
            if( !createOgrePoseAnimations(pMesh,params) )
            {
                return false;
            }
        }
        // Create a bounding box for the mesh
        BoundingBox bindBox = calculateBoundingBox(params);

        Ogre::Vector3 min2(static_cast<float>(bindBox.min.x), 
            static_cast<float>(bindBox.min.y), 
            static_cast<float>(bindBox.min.z));
        Ogre::Vector3 max2(static_cast<float>(bindBox.max.x), 
            static_cast<float>(bindBox.max.y), 
            static_cast<float>(bindBox.max.z));
        Ogre::AxisAlignedBox bbox(min2,max2);
        
        FxOgreFBXLog("Setting bounding box for mesh: (%f, %f, %f) (%f, %f, %f)\n", 
	        bbox.getMinimum().x, 
	        bbox.getMinimum().y,
	        bbox.getMinimum().z,
	        bbox.getMaximum().x,
	        bbox.getMaximum().y,
	        bbox.getMaximum().z);
        // Define mesh bounds
        pMesh->_setBounds(bbox,false);
        // Build edges list
        if (params.buildEdges)
        {
            pMesh->buildEdgeList();
        }
        // Build tangents
        if (params.buildTangents)
        {
            Ogre::VertexElementSemantic targetSemantic = params.tangentSemantic == TS_TANGENT ? 
                Ogre::VES_TANGENT : Ogre::VES_TEXTURE_COORDINATES;
            bool canBuild = true;
            unsigned short srcTex, destTex;
            try {
                canBuild = !pMesh->suggestTangentVectorBuildParams(targetSemantic, srcTex, destTex);
            } catch(Ogre::Exception& e) {
                FxOgreFBXLog("Warning: failed to build tangents: %s\n", e.getDescription().c_str());
                canBuild = false;
            }
            if (canBuild)
                pMesh->buildTangentVectors(targetSemantic, srcTex, destTex, 
                params.tangentsSplitMirrored, params.tangentsSplitRotated, params.tangentsUseParity);
        }
        // Export the binary mesh
        Ogre::MeshSerializer serializer;
        try
        {
            serializer.exportMesh(pMesh.getPointer(),params.meshFilename.c_str());
        }
        catch( Ogre::Exception& e )
        {
            FxOgreFBXLog("Error! %s", e.getFullDescription().c_str());
            return false;
        }
        pMesh.setNull();
        return true;
    }

    // Create shared geometry data for an Ogre mesh
    bool Mesh::createOgreSharedGeometry(Ogre::MeshPtr pMesh,ParamList& params)
    {
        int i,j;
        bool stat;
        pMesh->sharedVertexData = new Ogre::VertexData();
        pMesh->sharedVertexData->vertexCount = m_sharedGeom.vertices.size();
        // Define a new vertex declaration
        Ogre::VertexDeclaration* pDecl = new Ogre::VertexDeclaration();
        pMesh->sharedVertexData->vertexDeclaration = pDecl;
        unsigned buf = 0;
        size_t offset = 0;
        // Add vertex position
        pDecl->addElement(buf,offset,Ogre::VET_FLOAT3,Ogre::VES_POSITION);
        offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
        // Add vertex normal
        if (params.exportVertNorm)
        {
            pDecl->addElement(buf, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
            offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
        }
        // Add vertex colour
        if (params.exportVertCol)
        {
            pDecl->addElement(buf, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
            offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
        }
        // Add texture coordinates (maximum of 8!)
        int texCoordsCount = static_cast<int>(m_sharedGeom.vertices[0].texcoords.size());
        if( texCoordsCount > 8 )
        {
			FxOgreFBXLog( "ERRORBOXWARNING: There were too many sets of texture coordinates. Only the first 8 will be exported.\n");
            texCoordsCount = 8;
        }
        for (i=0; i<texCoordsCount; i++)
        {
            Ogre::VertexElementType uvType = Ogre::VertexElement::multiplyTypeCount(Ogre::VET_FLOAT1, 2);
            pDecl->addElement(buf, offset, uvType, Ogre::VES_TEXTURE_COORDINATES, i);
            offset += Ogre::VertexElement::getTypeSize(uvType);
        }
        // Get optimal vertex declaration
        Ogre::VertexDeclaration* pOptimalDecl = pDecl->getAutoOrganisedDeclaration(params.exportVBA, params.exportBlendShapes || params.exportVertAnims, false);
        // Create the vertex buffer using the newly created vertex declaration
        stat = createOgreVertexBuffer(pMesh,pDecl,m_sharedGeom.vertices);
        // Write vertex bone assignements list
        if (params.exportVBA)
        {
            // Create a new vertex bone assignements list
            Ogre::Mesh::VertexBoneAssignmentList vbas;
            // Scan list of shared geometry vertices
            for (i=0; i<static_cast<int>(m_sharedGeom.vertices.size()); i++)
            {
                vertex v = m_sharedGeom.vertices[i];
                // Add all bone assignements for every vertex to the bone assignements list
                for (j=0; j<static_cast<int>(v.vbas.size()); j++)
                {
                    Ogre::VertexBoneAssignment vba;
                    vba.vertexIndex = i;
                    vba.boneIndex = v.vbas[j].jointIdx;
                    vba.weight = v.vbas[j].weight;
                    if (vba.weight > 0.0f)
                        vbas.insert(Ogre::Mesh::VertexBoneAssignmentList::value_type(i, vba));
                }
            }
            // Rationalise the bone assignements list
            pMesh->_rationaliseBoneAssignments(pMesh->sharedVertexData->vertexCount,vbas);
            // Add bone assignements to the mesh
            for (Ogre::Mesh::VertexBoneAssignmentList::iterator bi = vbas.begin(); bi != vbas.end(); bi++)
            {
                pMesh->addBoneAssignment(bi->second);
            }
            pMesh->_compileBoneAssignments();
            pMesh->_updateCompiledBoneAssignments();
        }
        // Reorganize vertex buffers
        pMesh->sharedVertexData->reorganiseBuffers(pOptimalDecl);
        
        return true;
    }

    // Create an Ogre compatible vertex buffer
    bool Mesh::createOgreVertexBuffer(Ogre::MeshPtr pMesh,Ogre::VertexDeclaration* pDecl,const std::vector<vertex>& vertices)
    {
        Ogre::HardwareVertexBufferSharedPtr vbuf = 
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(pDecl->getVertexSize(0),
            pMesh->sharedVertexData->vertexCount, 
            Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
        pMesh->sharedVertexData->vertexBufferBinding->setBinding(0, vbuf);
        size_t vertexSize = pDecl->getVertexSize(0);
        char* pBase = static_cast<char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        Ogre::VertexDeclaration::VertexElementList elems = pDecl->findElementsBySource(0);
        Ogre::VertexDeclaration::VertexElementList::iterator ei, eiend;
        eiend = elems.end();
        float* pFloat;
        Ogre::RGBA* pRGBA;
        // Fill the vertex buffer with shared geometry data
        unsigned long vi;
        Ogre::ColourValue col;
        float ucoord, vcoord;
        for (vi=0; vi<vertices.size(); vi++)
        {
            int iTexCoord = 0;
            vertex v = vertices[vi];
            for (ei = elems.begin(); ei != eiend; ++ei)
            {
                Ogre::VertexElement& elem = *ei;
                switch(elem.getSemantic())
                {
                case Ogre::VES_POSITION:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    *pFloat++ = static_cast<float>(v.x);
                    *pFloat++ = static_cast<float>(v.y);
                    *pFloat++ = static_cast<float>(v.z);
                    break;
                case Ogre::VES_NORMAL:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    *pFloat++ = static_cast<float>(v.n.x);
                    *pFloat++ = static_cast<float>(v.n.y);
                    *pFloat++ = static_cast<float>(v.n.z);
                    break;
                case Ogre::VES_DIFFUSE:
                    {
                        elem.baseVertexPointerToElement(pBase, &pRGBA);
                        Ogre::ColourValue col(v.r, v.g, v.b, v.a);
                        *pRGBA = Ogre::VertexElement::convertColourValue(col, 
                            Ogre::VertexElement::getBestColourVertexElementType());
                    }
                    break;
                case Ogre::VES_TEXTURE_COORDINATES:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    ucoord = v.texcoords[iTexCoord].u;
                    vcoord = v.texcoords[iTexCoord].v;
                    *pFloat++ = ucoord;
                    *pFloat++ = vcoord;
                    iTexCoord++;
                    break;
                }
            }
            pBase += vertexSize;
        }
        vbuf->unlock();
        return true;
    }

    // Create mesh poses for an Ogre mesh
    bool Mesh::createOgrePoses(Ogre::MeshPtr pMesh,ParamList& params)
    {
        int poseCounter = 0;
        if (params.useSharedGeom)
        {
            // Read poses associated from all blendshapes associated to the shared geometry
            for (size_t i=0; i<m_sharedGeom.dagMap.size(); i++)
            {
                BlendShape* pBS = m_sharedGeom.dagMap[i].pBlendShape;
                // Check if we have a blend shape associated to this subset of the shared geometry
                if (pBS)
                {
                    // Get all poses from current blend shape deformer
                    poseGroup& pg = pBS->getPoseGroups().find(0)->second;
                    for (size_t j=0; j<pg.poses.size(); j++)
                    {
                        // Get the pose
                        pose* p = &(pg.poses[j]);
                        if (p->name == "")
                        {
                            p->name = "pose";
                            char buf[32];                               
                            p->name +=  itoa(poseCounter, buf, 10);
                        }
                        
                        Ogre::Mesh::PoseIterator pose_it = pMesh->getPoseIterator();
                        while( pose_it.hasMoreElements() )
                        {
                            Ogre::Pose* current_pose = pose_it.getNext();
                            std::string posename( current_pose->getName().c_str());
                            if( p->name.compare(posename) == 0 )
                            {
                                // If the pose already exists, rename it like Maya's FBX 2013 importer.
                                size_t basename_end = posename.find_last_not_of("0123456789");
                                std::string basename = posename.substr(0, basename_end + 1);
                                std::string numberstring = posename.substr(basename_end + 1, posename.length()- basename_end);
                                int number = 1;
                                if( numberstring.length() > 0 )
                                {
                                    number = atoi(numberstring.c_str());
                                    number++;
                                }
                              
                                p->name = basename;
                                char buf[32];
                                p->name +=  itoa(number, buf, 10);
                            }
                        }
                        
                        // Create a new pose for the ogre mesh
                        Ogre::Pose* pPose = pMesh->createPose(0,p->name.c_str());
                        // Set the pose attributes
                        for (size_t k=0; k<p->offsets.size(); k++)
                        {
                            Ogre::Vector3 offset(p->offsets[k].x,p->offsets[k].y,p->offsets[k].z);
                            pPose->addVertex(p->offsets[k].index,offset);
                        }
                        poseCounter++;
                    }
                }
            }
        }
        else
        {
            // Get poses associated to the submeshes
            for (int i=0; i<static_cast<int>(m_submeshes.size()); i++)
            {
                BlendShape* pBS = m_submeshes[i]->m_pBlendShape;
                // Check if this submesh has a blend shape deformer associated
                if (pBS)
                {
                    // Get the pose group corresponding to the current submesh
                    poseGroup& pg = pBS->getPoseGroups().find(i+1)->second;
                    // Get all poses from current blend shape deformer and current pose group
                    for (int j=0; j<static_cast<int>(pg.poses.size()); j++)
                    {
                        // Get the pose
                        pose* p = &(pg.poses[j]);
                        if (p->name == "")
                        {
                            p->name = "pose";
                            p->name += poseCounter;
                        }
                        // Create a new pose for the ogre mesh
                        Ogre::Pose* pPose = pMesh->createPose(static_cast<Ogre::ushort>(i+1),p->name.c_str());
                        // Set the pose attributes
                        for (int k=0; k<static_cast<int>(p->offsets.size()); k++)
                        {
                            Ogre::Vector3 offset(p->offsets[k].x,p->offsets[k].y,p->offsets[k].z);
                            pPose->addVertex(p->offsets[k].index,offset);
                        }
                        poseCounter++;
                    }
                }
            }
        }
        m_numBlendShapes = poseCounter;
        return true;
    }
    // Create vertex animations for an Ogre mesh
    bool Mesh::createOgreVertexAnimations(Ogre::MeshPtr pMesh,ParamList& params)
    {
        // Read the list of vertex animation clips
        for (size_t i=0; i<m_vertexClips.size(); i++)
        {
            // Create a new animation
            Ogre::Animation* pAnimation = pMesh->createAnimation(m_vertexClips[i].m_name.c_str(),m_vertexClips[i].m_length);
            // Create all tracks for current animation
            for (size_t j=0; j<m_vertexClips[i].m_tracks.size(); j++)
            {
                Track* t = &(m_vertexClips[i].m_tracks[j]);
                // Create a new track
                Ogre::VertexAnimationTrack* pTrack;
                if (t->m_target == T_MESH)
                    pTrack = pAnimation->createVertexTrack(0,pMesh->sharedVertexData,Ogre::VAT_MORPH);
                else
                {
                    pTrack = pAnimation->createVertexTrack(t->m_index,pMesh->getSubMesh(t->m_index-1)->vertexData,
                        Ogre::VAT_MORPH);
                }
                // Create keyframes for current track
                for (size_t k=0; k<t->m_vertexKeyframes.size(); k++)
                {
                    // Create a new keyframe
                    Ogre::VertexMorphKeyFrame* pKeyframe = pTrack->createVertexMorphKeyFrame(t->m_vertexKeyframes[k].time);
                    // Create vertex buffer for current keyframe
                    Ogre::HardwareVertexBufferSharedPtr pBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                        Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3),
                        t->m_vertexKeyframes[k].positions.size(),
                        Ogre::HardwareBuffer::HBU_STATIC, true);
                    float* pFloat = static_cast<float*>(pBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
                    // Fill the vertex buffer with vertex positions
                    size_t vi;
                    std::vector<vertexPosition>& positions = t->m_vertexKeyframes[k].positions;
                    for (vi=0; vi<positions.size(); vi++)
                    {
                        *pFloat++ = static_cast<float>(positions[vi].x);
                        *pFloat++ = static_cast<float>(positions[vi].y);
                        *pFloat++ = static_cast<float>(positions[vi].z);
                    }
                    // Unlock vertex buffer
                    pBuffer->unlock();
                    // Set vertex buffer for current keyframe
                    pKeyframe->setVertexBuffer(pBuffer);
                }
            }
        }
        return true;
    }
    // Create pose animations for an Ogre mesh
    bool Mesh::createOgrePoseAnimation(Ogre::MeshPtr pMesh, Animation &a, ParamList& params)
    {
        // Create a new animation for each clip
        Ogre::Animation* pAnimation = pMesh->createAnimation(a.m_name.c_str(),a.m_length);
        // Create animation tracks for this animation
        for (size_t j=0; j<a.m_tracks.size(); j++)
        {
            Track* t = &a.m_tracks[j];
            // Create a new track
            Ogre::VertexAnimationTrack* pTrack;
            if (t->m_target == T_MESH)
                pTrack = pAnimation->createVertexTrack(0,pMesh->sharedVertexData,Ogre::VAT_POSE);
            else
            {
                pTrack = pAnimation->createVertexTrack(t->m_index,pMesh->getSubMesh(t->m_index-1)->vertexData,
                    Ogre::VAT_POSE);
            }
            // Create keyframes for current track
            for (size_t k=0; k<t->m_vertexKeyframes.size(); k++)
            {
                Ogre::VertexPoseKeyFrame* pKeyframe = pTrack->createVertexPoseKeyFrame(t->m_vertexKeyframes[k].time);
                for (size_t pri=0; pri<t->m_vertexKeyframes[k].poserefs.size(); pri++)
                {
                    vertexPoseRef* pr = &t->m_vertexKeyframes[k].poserefs[pri];
                    if( pr->poseIndex < (int)pMesh->getPoseCount() )
                    {
                        pKeyframe->addPoseReference(pr->poseIndex,pr->poseWeight);
                    }
                    else
                    {
                        FxOgreFBXLog("Error! pose index out of bounds!  Make sure the animation and the base ogre file share the same number of morphs (hint: changing a node's visibility can impact if a morph is exported).\n");
                        return false;
                    }
                }
            }
        }
        return true;
    }
    // Create pose animations for an Ogre mesh
    bool Mesh::createOgrePoseAnimations(Ogre::MeshPtr pMesh,ParamList& params)
    {
        if( m_numBlendShapes > 0 )
        {
            // Get all loaded blend shape clips
            for (size_t i=0; i<m_BSClips.size(); i++)
            {
                if( !createOgrePoseAnimation(pMesh, m_BSClips[i], params) )
                {
                    FxOgreFBXLog("Error!  Failed to create pose animations.\n");
                    return false;
                }
            }
        }
        else
        {
            FxOgreFBXLog("Skipping creation of pose animations because there are no blendshapes.\n");
        }
        return true;
    }

    FbxColor GetFBXColor(FbxMesh *pMesh, int polyIndex, int polyPointIndex)
    {
        int lControlPointIndex = pMesh->GetPolygonVertex(polyIndex, polyPointIndex);
        int vertexId = polyIndex*3 + polyPointIndex;
        FbxColor color;
        for (int l = 0; l < pMesh->GetElementVertexColorCount(); l++)
        {
            FbxGeometryElementVertexColor* leVtxc = pMesh->GetElementVertexColor( l);

            switch (leVtxc->GetMappingMode())
            {
            case FbxGeometryElement::eByControlPoint:
                switch (leVtxc->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    color = leVtxc->GetDirectArray().GetAt(lControlPointIndex);
                    break;
                case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
                        color = leVtxc->GetDirectArray().GetAt(id);
                    }
                    break;
                default:
                    break; // other reference modes not shown here!
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                {
                    switch (leVtxc->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        color = leVtxc->GetDirectArray().GetAt(vertexId);
                        break;
                    case FbxGeometryElement::eIndexToDirect:
                        {
                            int id = leVtxc->GetIndexArray().GetAt(vertexId);
                            color = leVtxc->GetDirectArray().GetAt(id);
                        }
                        break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }
                break;

            case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
            case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
            case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
                break;
            }
        }
        return color;
    }

}; //end of namespace
