#include "common.h"

#ifdef IOS_REF
    #undef  IOS_REF
    #define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif


using namespace std;


namespace FxOgreFBX
{

    void InitializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene)
    {
        // The first thing to do is to create the FBX SDK manager which is the 
        // object allocator for almost all the classes in the SDK.
        pSdkManager = FbxManager::Create();

        if (!pSdkManager)
        {
            //printf("Unable to create the FBX SDK manager\n");
            exit(0);
        }

        // create an IOSettings object
        FbxIOSettings * ios = FbxIOSettings::Create(pSdkManager, IOSROOT );
        pSdkManager->SetIOSettings(ios);

        // Load plugins from the executable directory
        FbxString lPath = FbxGetApplicationDirectory();
        pSdkManager->LoadPluginsDirectory(lPath.Buffer());

        // Create the entity that will hold the scene.
        pScene = FbxScene::Create(pSdkManager,"");
    }

    void DestroySdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene)
    {
        // The fbx sdk docs say destroying the sdk manager will destroy all
        // objects that the sdk manager previously created so according to the
        // docs it is sufficient to simply destroy the sdk manager to clean up.
        if( pSdkManager )
        {
            pSdkManager->Destroy();
        }

        pSdkManager = NULL;
        pScene = NULL;
    }

    bool LoadScene(FbxManager* pSdkManager, FbxDocument* pScene, const char* pFilename)
    {
        int lFileMajor, lFileMinor, lFileRevision;
        int lSDKMajor,  lSDKMinor,  lSDKRevision;
        //int lFileFormat = -1;
        int i, lAnimStackCount;
        bool lStatus;
        //char lPassword[1024];

        // Get the file version number generate by the FBX SDK.
        FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

		FxOgreFBXLog("FBX SDK version number: %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

        // Create an importer.
        FbxImporter* lImporter = FbxImporter::Create(pSdkManager,"");

        // Initialize the importer by providing a filename.
        const bool lImportStatus = lImporter->Initialize(pFilename, -1, pSdkManager->GetIOSettings());
        lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

        if( !lImportStatus )
        {
            FxOgreFBXLog("Call to FbxImporter::Initialize() failed.\n");
			FbxString error = lImporter->GetStatus().GetErrorString();
            FxOgreFBXLog("Error returned: %s\n", error.Buffer());
            //printf("Call to FbxImporter::Initialize() failed.\n");
            //printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

			if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
			{
				FxOgreFBXLog("ERRORBOXWARNING: The FBX file format is not supported by this tool.  Check for updates, or save in an older FBX format."); 
                FxOgreFBXLog("FBX version number for file %s is unsupported: %d.%d.%d\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
			}
            return false;
        }
		
        if (lImporter->IsFBX())
        {
			FxOgreFBXLog("FBX file version number: %d.%d.%d\n", lFileMajor, lFileMinor, lFileRevision);

			bool fileIsNewer = false;
			if( lFileMajor > lSDKMajor )
			{
				fileIsNewer = true;
			}
			else if( lFileMinor > lSDKMinor )
			{
				fileIsNewer = true;
			}
			if( fileIsNewer )
			{
				FxOgreFBXLog("ERRORBOXWARNING: The file version is greater than the FBX SDK version.  Try exporting a %d.%d file for improved results.\n", lSDKMajor, lSDKMinor);
			}

            // From this point, it is possible to access animation stack information without
            // the expense of loading the entire file.

           // printf("Animation Stack Information\n");

            lAnimStackCount = lImporter->GetAnimStackCount();

            //printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
            //printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
            //printf("\n");

            for(i = 0; i < lAnimStackCount; i++)
            {
                FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

                //printf("    Animation Stack %d\n", i);
                //printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
                //printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

                // Change the value of the import name if the animation stack should be imported 
                // under a different name.
                //printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

                // Set the value of the import state to false if the animation stack should be not
                // be imported. 
                //printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
                //printf("\n");
            }

            // Set the import states. By default, the import states are always set to 
            // true. The code below shows how to change these states.
            IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
            IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
            IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
            IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
            IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
            IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
            IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
        }

        // Import the scene.
        lStatus = lImporter->Import(pScene);

        // Destroy the importer.
        lImporter->Destroy();

        return lStatus;
    }
}