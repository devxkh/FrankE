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
#include "Ogre.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "ogreExporter.h"
#include "FBXSDKCommon.h"
#include <algorithm>
#include <limits>

#include "OgreLodStrategyManager.h"

namespace FxOgreFBX
{
    OgreExporter::OgreExporter()
    {
        m_pMesh = NULL;
        m_pMaterialSet = NULL;
    }

    OgreExporter::~OgreExporter()
    {
        DestroySdkObjects(m_params.pSdkManager, m_params.pScene);
    }

	bool OgreExporter::InitializeLogging(const char *logfilename)
	{
        // Setup the log.
        if( logfilename )
        {
            // Make sure the log directory exists.
            std::string logFilePath;

            if( !GetFullPath(logfilename, logFilePath) )
            {
                FxOgreFBXLog( "Could not convert path: %s.\n", logfilename );
                return false;
            }

            std::string logDirectory = StripFilename(logFilePath);
            if( !DirectoryExists(logDirectory) )
            {
                FxOgreFBXLog("Error! The log directory %s does not exist\n", logDirectory.c_str());
                return false;
            }

            // Make sure the user has write permissions for the log file.
            if( !UserHasWritePermissionsForFile(logfilename) )
            {
                FxOgreFBXLog("Warning! The current user does not have write permissions for the file %s\n", logfilename);
            }
            else
            {
                FxOgreFBXLogFile::SetPath(logfilename);
            }
            FxOgreFBXLog("logfilename: %s\n", logfilename);
			return true;
        }
		return false;
	}
    bool OgreExporter::Initialize(const char* fbxfilename, const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname)
    {
		// Initialize the logging (does not clear the log).
		if( !InitializeLogging(logfilename) )
		{
			return false;
		}

        // Setup Skeleton and Mesh files.
        m_meshfilepath = "";
        m_skeletonfilepath = "";
        m_animationname = "";

        if( meshfilename )
        {
            FxOgreFBXLog("mesh file: %s\n", meshfilename);
            m_meshfilepath = meshfilename;
            // Make sure the mesh file exists.
            if( !FileExists(m_meshfilepath) )
            {
                FxOgreFBXLog("Error! The file does not exist: %s\n", m_meshfilepath.c_str());
                return false;
            }
            // Make sure the user has write permissions for the skeleton file.
            else if( !UserHasWritePermissionsForFile(m_meshfilepath) )
            {
                FxOgreFBXLog("Error! The current user does not have write permissions for the file %s\n", m_meshfilepath.c_str());
                return false;
            }  
        }
        if( skeletonfilename )
        {
            FxOgreFBXLog("skeleton file: %s\n", skeletonfilename);
            m_skeletonfilepath = skeletonfilename;
            // Make sure the skeleton file exists.
            if( !FileExists(m_skeletonfilepath) )
            {
                if(m_meshfilepath.length() > 0 )
                {
                    // We don't fail here because morph-only content doesn't have a skeleton, but 
                    // it is convenient to always asume a skeleton file exists when calling into
                    // the application.
                    FxOgreFBXLog("Warning! The skeleton file does not exist: %s\n", m_skeletonfilepath.c_str());
                    FxOgreFBXLog("Proceeding with export to support morph-only content without a .SKELETON file.");
                    m_skeletonfilepath = "";
                }
                else
                {
                    FxOgreFBXLog("Error! No mesh file was specified, and the skeleton file does not exist: %s\n", m_skeletonfilepath.c_str());
                    return false;
                }

            }
            // Make sure the user has write permissions for the skeleton file.
            else if( !UserHasWritePermissionsForFile(m_skeletonfilepath) )
            {
                FxOgreFBXLog("Error! The current user does not have write permissions for the file %s\n", m_skeletonfilepath.c_str());
                return false;
            }   
        }
        if( animname )
        {
            FxOgreFBXLog("animation name: %s\n", animname);
            m_animationname = animname;
        }

        // Setup FBX
        m_fbxfilename = "";
        if( fbxfilename )
        {
            FxOgreFBXLog("fbx file: %s\n", fbxfilename);
            m_fbxfilename = fbxfilename;
            // Check if the input FBX file exists.
            if( !FileExists(m_fbxfilename) )
            {
                FxOgreFBXLog("Error! FBX file does not exist! %s\n", m_fbxfilename.c_str());
                return false;
            }

            FbxManager* pSdkManager = NULL;
            FbxScene* pScene = NULL;

            // Prepare the FBX SDK.
            InitializeSdkObjects(pSdkManager, pScene);

            bool lResult = false;
            lResult = LoadScene(pSdkManager, pScene, fbxfilename);

            if(!lResult)
            {
                return lResult;
            }

            m_params.pScene = pScene;
            m_params.pSdkManager = pSdkManager;
            m_params.fbxFilename = fbxfilename;

            FbxGlobalSettings& lGlobalSettings = m_params.pScene->GetGlobalSettings();
            FbxTime::EMode lTimeMode = lGlobalSettings.GetTimeMode(); 
            m_params.fps = (float) FbxTime::GetFrameRate(lTimeMode);

            std::string filenamePath(FxOgreFBX::StripFilename(fbxfilename));
        }
       
        /*
        // FBX files can display differently depending on the unit conversions (see expressions.fbx)
        // Do the same conversions in our importer, so files look like they do in Max/Maya with 
        // Autodesk Media & Entertainment import settings.
        FbxSystemUnit SceneSystemUnit = pScene->GetGlobalSettings().GetSystemUnit();
        if( SceneSystemUnit.GetScaleFactor() != 1.0 )
        {
            FbxSystemUnit::cm.ConvertScene( pScene);
        }
        FbxAxisSystem SceneAxisSystem = pScene->GetGlobalSettings().GetAxisSystem();
        FbxAxisSystem OurAxisSystem(FbxAxisSystem::YAxis, FbxAxisSystem::ParityOdd, FbxAxisSystem::RightHanded);
        if( SceneAxisSystem != OurAxisSystem )
        {
            OurAxisSystem.ConvertScene(pScene);
        }
        */

        return true;
    }   


    bool OgreExporter::DeleteOgreAnimation( const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname)
    {
        
        if( !Initialize(NULL, skeletonfilename, meshfilename, logfilename, animname))
        {
            return false;
        }

        OgreManagers managers; 
        // Setup Ogre Managers  
        if( !managers.Initialize() )
        {
            FxOgreFBXLog("Error! Could not initialize Ogre.\n");
            return false;
        }
        Skeleton* pSkeleton = NULL;
        Mesh* pMesh = NULL;
        if( m_skeletonfilepath.length() > 0 )
        {
            pSkeleton = new Skeleton();
            pSkeleton->DeleteAnimationFromExisting(managers, m_skeletonfilepath, m_animationname);
            delete pSkeleton;
        }
        if( m_meshfilepath.length() > 0 )
        {
            pMesh = new Mesh();
            pMesh->DeleteAnimationFromExisting(managers, m_meshfilepath, m_animationname);
            delete pMesh;
        }
        return true;

    }

    bool OgreExporter::GetAnimationBounds(FbxScene *pScene, float& start, float& stop )
    {
        float fbx_start, fbx_stop;
        GetFBXAnimationBounds(pScene, fbx_start, fbx_stop);
        // Assume there is a key at zero for the fbx file, even if there isn't.
        fbx_start = min(0.0f, fbx_start);
        fbx_stop = max(0.0f, fbx_stop);

        // We bound the passed in values by the file values, so the caller doesn't have
        // to know the exact start & end time...they just pass in a wide range and the
        // bounds are set appropriately.
        start = max(start, fbx_start);

        // Negative time keys don't make sense to Ogre.  We don't support them here, but warn if we find them.
        if( start < 0.0f )
        {
            FxOgreFBXLog( "Warning! Negative time keys are not supported.  Negative keys being ignored.\n", start, stop );
            start = 0.0f;
        }
        stop = min(stop, fbx_stop);

        if( stop < start )
        {
            FxOgreFBXLog( "Error! Stop time %f is less than start time %f!\n", start, stop );
            return false;
        }
        // Warn if t
        if( stop - start > MAXIMUM_ANIMATION_DURATION )
        {
            FxOgreFBXLog( "Warning! Truncating animation bounds from (%f, %f) to (0, 10).\n", start, stop );
            start = 0.0f;
            stop = 10.0f;
        }
        return true;
    }

    bool OgreExporter::GetFBXAnimationBounds(FbxScene *pScene, float& start, float& stop )
    {
        if( !pScene )
        {
            return false;
        }
        start = FLT_MAX;
        stop = -FLT_MAX;

        FbxTime kStop = FBXSDK_TIME_MINUS_INFINITE;
        FbxTime kStart = FBXSDK_TIME_INFINITE;

        // Iterate through all curves to find the start and end time of the animation. Works
        // for bones and morph targets.
        for(int i = 0; i < pScene->GetSrcObjectCount(FbxAnimCurve::ClassId); ++i) 
        {
            FbxAnimCurve* pCurve = (FbxAnimCurve*)pScene->GetSrcObject(FbxAnimCurve::ClassId, i);
            if( pCurve )
            {
                int numKeys = pCurve->KeyGetCount();
                if( numKeys > 0 )
                {
                    float first = (float)pCurve->KeyGet(0).GetTime().GetSecondDouble();
                    float last = first;

                    if( numKeys > 1 )
                    {
                        last = (float)pCurve->KeyGet(numKeys-1).GetTime().GetSecondDouble();
                    }
                    if( first < start )
                    {
                        start = first;
                    }
                    if( last > stop )
                    {
                        stop = last;
                    }
                }
            }
        }
        return true;
    }

    bool OgreExporter::AddFBXAnimationToExisting(const char* fbxfilename, const char* skeletonfilename, const char* meshfilename, const char* logfilename, const char* animname,  int start, int stop, float rate)
    {
        if(!Initialize(fbxfilename, skeletonfilename, meshfilename, logfilename, animname))
        {
            return false;
        }
        
        OgreManagers managers; 
        // Setup Ogre Managers  
        if( !managers.Initialize() )
        {
            FxOgreFBXLog("Error! Could not initialize Ogre.\n");
            return false;
        }
        
        if( rate != 0 )
        {
            FxOgreFBXLog("Forcing frame rate to: %f\n", rate);
            m_params.fps = rate;
        }
        float start_sec = (float)start/m_params.fps;
        float stop_sec = (float)stop/m_params.fps;

        if(!GetAnimationBounds(m_params.pScene, start_sec, stop_sec))
        {
            FxOgreFBXLog("Error! Invalid animation bounds.\n");
            return false;
        }

        FxOgreFBXLog("Adding animation from file: %s\n", m_fbxfilename.c_str());
        FxOgreFBXLog("start %d   stop %d   rate %f\n.", start, stop, rate);
       
        Skeleton* pSkeleton = NULL;
        Mesh* pMesh = NULL;
        pSkeleton = new Skeleton();

        // initialize skeletonAddResult to true so that if the skeleton file doesn't exist, we do not fail.
        bool skeletonAddResult = true;
        bool morphAddResult = true;
        if( m_skeletonfilepath.length() > 0 )
        {
            skeletonAddResult = pSkeleton->AddFBXAnimationToExisting(managers, m_skeletonfilepath, m_animationname, m_params, start_sec, stop_sec);
        }        
        pMesh = new Mesh();
        if( m_meshfilepath.length() > 0 )
        {
            morphAddResult = pMesh->AddFBXAnimationToExisting(managers, m_meshfilepath, m_animationname, m_params, start_sec, stop_sec);
        } 

        printAnimInfo(m_animationname, m_params.fps, start_sec, pMesh, pSkeleton );

        delete pSkeleton;
        delete pMesh;
        
        return (morphAddResult && skeletonAddResult);
    }

    bool OgreExporter::exportScene(const char* fbxfilename, const char* outputmeshfilename, const char* logfilename, const char* animname,const char* frame0name,  bool copyUniqueTextures, int bindframe)
    {
		// Clear the log before a full scene export.  We need to initialize the logging
		// before deleting the log.  We'll call InitializeLogging inside of Initialize 
		// so the information logged there will be preserved. .
		InitializeLogging(logfilename);
		FxOgreFBXLogFile::ClearLog();

        if(!Initialize(fbxfilename, NULL, NULL, logfilename, animname))
        {
            return false;
        }

        std::string copyTex = "false";
        if( copyUniqueTextures )
        {
            copyTex = "true";
        }
        FxOgreFBXLog("copyUniqueTextures: %s\n", copyTex.c_str());

        // Make sure the input file exists.
        if( !FileExists(fbxfilename) )
        {
            FxOgreFBXLog("Error! The input FBX file %s does not exist\n", fbxfilename);
            return false;
        }
        if( copyUniqueTextures )
        {
            m_params.copyTextures = true;
            m_params.prefixTextures = true;
        }
        if( bindframe != INT_MAX )
        {
            FxOgreFBXLog("Bind frame specified: %i. FBX bind pose information will be ignored.\n", bindframe);
            m_params.useanimframebind = true;
            m_params.bindframe = bindframe;
        }

        std::string uppercaseMeshName = outputmeshfilename;
        if( outputmeshfilename )
        {
            m_params.meshFilename = outputmeshfilename;
            for (size_t i=0; i<m_params.meshFilename.length(); ++i)
            {
                uppercaseMeshName[i]=toupper(m_params.meshFilename[i]);
            } 
        }
        else
        {
            std::string temp = fbxfilename;
            for (size_t i=0; i<temp.length(); ++i)
            {
                temp[i]=toupper(temp[i]);
            } 
            size_t fbxIndex = temp.rfind(".FBX", temp.length() -1);

            m_params.meshFilename = temp.substr(0,fbxIndex).append(".MESH");
        }

        size_t meshIndex = uppercaseMeshName.rfind(".MESH", uppercaseMeshName.length() -1);
        if( meshIndex == std::string::npos)
        {	
            FxOgreFBXLog( "Invalid meshfile path: %s\n",  m_params.meshFilename.c_str());
            return false;
        }

        // Make sure we have the full path to the output mesh file.
        if( !GetFullPath(m_params.meshFilename, m_params.meshFilename) )
        {
            FxOgreFBXLog( "Could not convert path: %s.\n", m_params.meshFilename );
            return false;
        }
        // Make sure the output directory exists.
        std::string outputDirectory = StripFilename(m_params.meshFilename);
        if( !DirectoryExists(outputDirectory) )
        {
            FxOgreFBXLog("Error! The output directory %s does not exist\n", outputDirectory.c_str());
            return false;
        }

        // Make sure the user has write permissions for the file.
        if( !UserHasWritePermissionsForFile(m_params.meshFilename) )
        {
            FxOgreFBXLog("Error! The current user does not have write permissions for the file %s\n", m_params.meshFilename.c_str());
            return false;
        }

        FxOgreFBXLog( "Mesh file: %s\n" , m_params.meshFilename.c_str());

        m_params.setOutputFilePaths(m_params.meshFilename);

        // Create a new empty mesh
        m_pMesh = new Mesh();

        // Create a new empty material set
        m_pMaterialSet = new MaterialSet();

        if (m_params.exportVBA || m_params.exportSkeleton)
        {
            m_pMesh->createSkeleton();
            if( !m_pMesh->getSkeleton()->load(m_params.pScene, m_params) )
			{
				FxOgreFBXLog("Error! Skeleton could not be written!\n");
				return false;
			}
        }
        FbxNode* lRootNode = m_params.pScene->GetRootNode();
        if( lRootNode )
        {
            for(int i = 0; i < lRootNode->GetChildCount(); i++)
            {
                // Call recursive translateNode once for each child of the root node
                translateNode(lRootNode->GetChild(i));
            }
        }
        // Load blend shapes
        if (m_params.exportBlendShapes)
            m_pMesh->loadBlendShapes(m_params);

        if( animname )
        {
            stat = prepareAnimationClip(animname);
        }
        if( frame0name )
        {
            stat = prepareFrame0Anim(frame0name);
        }

        // Read blend shape animations
        if (m_params.exportBSAnims)
        {
            m_pMesh->loadBlendShapeAnimations(m_params);
        }
        if (m_params.exportSkelAnims)
        {
            m_pMesh->getSkeleton()->loadAnims(m_params);
        }

        if(m_params.exportScene && m_params.exportMesh)
        {

            FxOgreTransform sceneTrans = m_FxOgreScene.getDefaultTransForm();
            if( m_params.pScene )
            {
                if( m_params.pScene->GetGlobalSettings().GetAxisSystem() == FbxAxisSystem::eMax )
                {
                    // If this is a Z-up FBX file from Max, add a -90 degree rotation to the X-axis
                    // so that the content will appear upright in the Ogre viewport.  
                    sceneTrans.rot = FxOgrePoint4( 0.707f, -0.707f, 0.0f, 0.0f); 
                    m_FxOgreScene.setSceneTransform(sceneTrans);
                }
            }

            FxOgreMesh meshNode;

            meshNode.node.trans.scale = FxOgrePoint3(1.0f, 1.0f, 1.0f);

            if(m_params.useSharedGeom )
            {
                // See if we need to scale this mesh up because it is unusually small.
                BoundingBox bbox = m_pMesh->calculateBoundingBox(m_params);
                float bboxScale = static_cast<float>(bbox.getBiggestAxis());
                if( bboxScale > 0.0f && bboxScale < 20.0f )
                {
                    sceneTrans.scale =  FxOgrePoint3(20.0f / bboxScale, 20.0f / bboxScale, 20.0f / bboxScale);
                }
                else if( bboxScale > 1000.0f )
                {
                    sceneTrans.scale =  FxOgrePoint3(1000.0f / bboxScale, 1000.0f / bboxScale, 1000.0f / bboxScale );
                }
                FxOgreFBXLog( "Setting Scene scale: %f \n", (float)sceneTrans.scale.x);
                m_FxOgreScene.setSceneTransform(sceneTrans);
            }

            meshNode.node.trans.rot = FxOgrePoint4(1.0f, 0.0f, 0.0f, 0.0f);
            std::string filename = StripToTopParent(m_params.meshFilename);
            meshNode.meshFile = filename.c_str();
            //int ri = filename.find_last_of(".");
            meshNode.node.name = filename.substr(0,filename.length()-5);
            m_FxOgreScene.addMesh(meshNode);
        }
        stat = writeOgreData();

        FxOgreFBXLog("Deleting mesh...\n");

        if (m_pMesh)
            delete m_pMesh;
        FxOgreFBXLog("Deleting materials...\n");
        if (m_pMaterialSet)
            delete m_pMaterialSet;
        FxOgreFBXLog("Closing files...\n");
        m_params.closeFiles();
        FxOgreFBXLog("Completed OgreExporter::exportScene...\n");
        
        return stat;
    }

    bool OgreExporter::prepareFrame0Anim(const char* clipName)
    {
        clipInfo clip;
        clip.name = clipName;
        clip.start = 0;
        clip.stop = 0;
        clip.rate = 1;
        m_params.skelClipList.push_back(clip);
        return true;
    }

    bool OgreExporter::printAnimInfo(std::string animname, float fps, float start, Mesh* pMesh, Skeleton *pSkeleton )
    {
        if( m_params.pScene && fps != 0 )
        {
            // Make sure the Global time mode and frame rate is set to the file's time mode & frame rate
            FbxTime::SetGlobalTimeMode(m_params.pScene->GetGlobalSettings().GetTimeMode());

            std::vector<int> keyedFrames;
            if( pMesh )
            {
                pMesh->getKeyedFrames(keyedFrames, m_params);
            }
            if( pSkeleton )
            {
                pSkeleton->getKeyedFrames(keyedFrames, m_params);
            }

            // shift the frames by the start frame of the animation (we want frames WRT the ogre skeleton animation).
            int startframe = (int) (start / fps);

            // Sort and remove duplicates.
            vector<int>::iterator it;
            std::sort(keyedFrames.begin(), keyedFrames.end());
            it =  std::unique(keyedFrames.begin(), keyedFrames.end() );
            keyedFrames.resize( it - keyedFrames.begin() );
            
           
            // Output some animation info to the log.  
            FxOgreFBXLog( "ANIMATION={\"name\": \"%s\", \"fps\": %f, \"keys\": [", animname.c_str(), m_params.fps );
            if( keyedFrames.size() > 0 )
            {
                char buf[64];
                
                std::string keystring;
                for( size_t i =0 ; i < keyedFrames.size() - 1; ++i )
                {
                    
                    keystring = itoa(keyedFrames[i] - startframe, buf, 10 );
                    keystring += ", ";
                    // print frames with separate calls to FxOgreFBXLog so we don't try to log a string that is too long.
                    FxOgreFBXLog( "%s", keystring.c_str());
                    
                }
                keystring = itoa(keyedFrames[keyedFrames.size() - 1] - startframe, buf, 10 );
                FxOgreFBXLog( "%s", keystring.c_str());
               
            }
            FxOgreFBXLog( "]}\n");
            
            return true;
        }
        return false;
    }


    bool OgreExporter::prepareAnimationClip(const char* clipName)
    {
        if( m_params.pScene && m_pMesh && m_params.fps != 0)
        {
            float stop =  FLT_MAX;
            float start = -FLT_MAX;
            if( GetAnimationBounds(m_params.pScene, start, stop))
            {
                clipInfo bsclip;
                bsclip.name = clipName;
                bsclip.start = start;
                bsclip.stop = stop;
                bsclip.rate = 1 / m_params.fps;
                m_params.BSClipList.push_back(bsclip);
            
                if( m_pMesh->getSkeleton() )
                {

                    clipInfo skelclip;
                    skelclip.name = clipName;
                    skelclip.start = start;
                    skelclip.stop = stop;
                    skelclip.rate = 1 / m_params.fps;
                    m_params.skelClipList.push_back(skelclip);
                }
                printAnimInfo(clipName, m_params.fps, start, m_pMesh, m_pMesh->getSkeleton() );
                return true;
            }
        }
        return false;
    }

    bool OgreExporter::translateNode(FbxNode* pNode)
    {
        bool stat = false;
        if( pNode )
        {
            FbxNodeAttribute::EType lAttributeType;
            if(pNode->GetNodeAttribute() == NULL)
            {
                std::string name;
                if( pNode->GetName() )
                {
                    name =  pNode->GetName();
                }
                FxOgreFBXLog( "NULL Node Attribute: %s\n", name.c_str());
            }
            else
            {
                lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

                switch (lAttributeType)
                {
                case FbxNodeAttribute::eMarker:  
                   // DisplayMarker(pNode);
                    break;

                case FbxNodeAttribute::eSkeleton: 
                    break;

                case FbxNodeAttribute::eMesh:    
                    {
                        // Don't display hidden meshes.  
                        if( isVisible(pNode) )
                        {
							  
                            FbxGeometryConverter lGeometryConverter(m_params.pSdkManager);

							//  Doug Perkowski 6/25/2014
							// Instead of looping through the node attributes, we only use the default one.
							// The samples work this way, and certain content was resulting in duplicate meshes
							// where there were two eMesh node attributes.
							if( pNode->GetNodeAttribute() )
                            {
                                if( pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh )
                                {
                                    FbxMesh *pNonTriangulatedMesh = (FbxMesh*) pNode->GetNodeAttribute();
                                    FbxMesh* pMesh = (FbxMesh*) lGeometryConverter.Triangulate(pNonTriangulatedMesh, false);
                                    if(!pMesh)
                                    {
                                        FxOgreFBXLog("GeometryConverter.Triangulate() for mesh failed!\n");
                                    }
                                    assert(pMesh != NULL);
                                    stat = m_pMesh->load(pNode, pMesh, m_params);                           
                                }
                            }
                        }
                    }
                    break;

                case FbxNodeAttribute::eNurbs:      
                   // DisplayNurb(pNode);
                    break;

                case FbxNodeAttribute::ePatch:     
                   // DisplayPatch(pNode);
                    break;

                case FbxNodeAttribute::eCamera:    
                    addCameraToScene(pNode);
                    break;

                case FbxNodeAttribute::eLight:     
                    addLightToScene(pNode);
                    break;

                case FbxNodeAttribute::eLODGroup:
                   // DisplayLodGroup(pNode);
                    break;
                }   

            }      
            for(int i = 0; i < pNode->GetChildCount(); i++)
            {
                translateNode(pNode->GetChild(i));
            }
        }
        return true;
    }
    void OgreExporter::addLightToScene( FbxNode* pNode )
    {
        if( pNode )
        {
            FbxLight* pLight = (FbxLight*) pNode->GetNodeAttribute();
            if( pLight )
            {
                FxOgreLight light;
                light.node = getFxOgreNode(pNode);
                switch(  pLight->LightType.Get()  )
                {
                case 0:
                    light.type = OGRE_LIGHT_POINT;
                    break;
                case 1:
                    light.type = OGRE_LIGHT_DIRECTIONAL;
                    break;
                case 2:
                    light.type = OGRE_LIGHT_SPOT;
                    break;
                default:
                    FxOgreFBXLog("Unsupported light type.  Failed to export.\n");
                    return;
                }             
                
                float intensity = 1.0f;
                if (pLight->Intensity.IsValid())
                {
                    intensity = static_cast<float>(pLight->Intensity.Get()) * .01f;
                }
                light.diffuseColour.x = static_cast<float>(pLight->Color.Get()[0]) * intensity;
                light.diffuseColour.y = static_cast<float>(pLight->Color.Get()[1]) * intensity;
                light.diffuseColour.z = static_cast<float>(pLight->Color.Get()[2]) * intensity;

                light.attenuation_range = 0.0f;
                if(light.type == OGRE_LIGHT_POINT)
                {
                    // Max lets attenuation start at a specific point.  Ogre seems to 
                    // require that attenuation begins immediately.  We use the
                    // Attenuation end as the range.
                    light.attenuation_range = static_cast<float>(pLight->FarAttenuationEnd.Get());

                    // FBX default is for the range to be 0, but this has the effect of turning off the light in Ogre.
                    if( light.attenuation_range < PRECISION )
                    {
                         light.attenuation_range = 100.0f;
                    }

                    light.attenuation_constant = 1.0f;

                    // Inverse decay
                    if(  pLight->DecayType.Get() == FbxLight::eLinear )
                    {
                        light.attenuation_linear = 1.0f;
                    }
                    // Inverse Square decay
                    else if( pLight->DecayType.Get() == FbxLight::eQuadratic )
                    {
                        light.attenuation_quadratic = 1.0f;
                    }
                    else if( pLight->DecayType.Get() == FbxLight::eNone )
                    {
                        light.attenuation_range = std::numeric_limits<float>::max();
                    }
                }
                if(light.type == OGRE_LIGHT_SPOT)
                {
                    light.range_inner = 0.0f;
                    light.range_falloff  = 0.0f;
                    light.range_outer = 1.0f;
                    
                    light.range_outer = static_cast<float>(pLight->OuterAngle.Get()) * 3.1415926535f / 180.0f;
                    light.range_inner = static_cast<float>(pLight->InnerAngle.Get()) * 3.1415926535f / 180.0f;

                }
                m_FxOgreScene.addLight(light);
            }
        }
    }
    void OgreExporter::addCameraToScene( FbxNode* pNode )
    {
        if( pNode )
        {
            FbxCamera* pCamera = (FbxCamera*) pNode->GetNodeAttribute();
            if( pCamera )
            {
                FxOgreCamera camera;
                FxOgreFBXLog("Exporting camera %s...\n", pNode->GetName());

                camera.node = getFxOgreNode(pNode);
                camera.fov = static_cast<float>(pCamera->FieldOfView.Get());
                camera.clipNear = static_cast<float>(pCamera->NearPlane.Get());
                camera.clipFar = static_cast<float>(pCamera->FarPlane.Get());
                m_FxOgreScene.addCamera(camera);
            }
        }
    }
    FxOgreNode OgreExporter::getFxOgreNode( FbxNode* pNode )
    {
        assert(pNode != NULL);
        FxOgreNode node;
        node.name = pNode->GetName();
        FbxAMatrix mat = CalculateGlobalTransform(pNode, FbxTime(m_params.bindframe));
        node.trans.pos.x = static_cast<float>(mat.GetT()[0]);
        node.trans.pos.y = static_cast<float>(mat.GetT()[1]);
        node.trans.pos.z = static_cast<float>(mat.GetT()[2]);
        node.trans.rot.w = static_cast<float>(mat.GetQ()[3]);
        node.trans.rot.x = static_cast<float>(mat.GetQ()[0]);
        node.trans.rot.y = static_cast<float>(mat.GetQ()[1]);
        node.trans.rot.z = static_cast<float>(mat.GetQ()[2]);
        node.trans.scale.x = static_cast<float>(mat.GetS()[0]);
        node.trans.scale.y = static_cast<float>(mat.GetS()[1]);
        node.trans.scale.z = static_cast<float>(mat.GetS()[2]);
        return node;
    }
    
    bool OgreExporter::writeOgreData()
    {
        // Create Ogre Root
    //		Ogre::Root ogreRoot;
        // Create singletons
        Ogre::LogManager logMgr;

        // Doug Perkowski - 02/04/09
        // Creating default log to avoid crashes in skeleton serialization.
        Ogre::LogManager::getSingleton().createLog("Ogre.log", true, true, true);
        Ogre::ResourceGroupManager rgm;
        Ogre::MeshManager meshMgr;
        Ogre::SkeletonManager skelMgr;
        Ogre::MaterialManager matMgr;
        Ogre::DefaultHardwareBufferManager hardwareBufMgr;

        // Doug Perkowski  - 03/09/10
        // Creating LodStrategyManager
        // http://www.ogre3d.org/forums/viewtopic.php?f=8&t=55844
        Ogre::LodStrategyManager lodstrategymanager;   
        
        // Write mesh binary
        if (m_params.exportMesh)
        {
            std::cout << "Writing mesh binary...\n";

            if( m_pMesh->getNumSubmeshes() == 0 )
            {
                FxOgreFBXLog( "ERRORBOXWARNING: No meshes could be exported from the FBX file.\n");
                FxOgreFBXLog( "Error: No meshes exported.  Check the FBX file.\n");
                return false;
            }
            std::cout.flush();
            stat = m_pMesh->writeOgreBinary(m_params);
            if (stat != true)
            {
                std::cout << "Error writing mesh binary file\n";
                std::cout.flush();
            }
        }
        // Write skeleton binary
        if (m_params.exportSkeleton)
        {
            if (m_pMesh->getSkeleton())
            {
                FxOgreFBXLog("Writing skeleton binary...\n");
                stat = m_pMesh->getSkeleton()->writeOgreBinary(m_params);
                if (stat != true)
                {
                    FxOgreFBXLog("Error writing skeleton binary file\n");
                }
            }
            else
            {
                FxOgreFBXLog("Failure: No joints found. Make sure vertices are weighted to bones. Skeleton file will not be exported.\n");
            }
        }
        // Write materials data
        if (m_params.exportMaterial)
        {
            m_params.openFiles();

            FxOgreFBXLog("Writing materials data...\n");
            
            stat  = m_pMaterialSet->writeOgreScript(m_params);
            if (stat != true)
            {
                FxOgreFBXLog("Error writing materials file\n");
            }
        }
        // Write Scene
        if (m_params.exportScene)
        {
            FxOgreFBXLog("Writing scene data...\n");
            
            stat  = m_FxOgreScene.writeSceneFile(m_params);
            if (stat != true)
            {
                FxOgreFBXLog("Error writing scene file\n");
            }
        }
        m_FxOgreScene.clear();
        return true;
    }
}
