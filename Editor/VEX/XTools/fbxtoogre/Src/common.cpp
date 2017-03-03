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
#include "common.h"

#ifdef WIN32
#include <windows.h>
#endif

#include "OgreLodStrategyManager.h"

namespace FxOgreFBX
{

	OgreManagers::OgreManagers()
	{
		logMgr = 0;
		rgm = 0;
		mth = 0;
		lodMgr = 0;
		matMgr = 0;
		skelMgr = 0;
		meshSerializer = 0;
		skeletonSerializer = 0;
		bufferManager = 0; // This is needed because we don't have a rendersystem.
		meshMgr = 0;
	}

	bool OgreManagers::Initialize()
	{
		try
		{
			logMgr = new Ogre::LogManager();
			rgm = new Ogre::ResourceGroupManager();
			mth = new Ogre::Math();
			lodMgr = new Ogre::LodStrategyManager();
			matMgr = new Ogre::MaterialManager();
			matMgr->initialise();
			skelMgr = new Ogre::SkeletonManager();
			meshSerializer = new Ogre::MeshSerializer();
			skeletonSerializer = new Ogre::SkeletonSerializer();
			bufferManager = new Ogre::DefaultHardwareBufferManager();
			meshMgr = new Ogre::MeshManager();
			Ogre::LogManager::getSingleton().createLog("Ogre.log", true, true, true);
		}
		catch (Ogre::Exception& e)
		{
			FxOgreFBXLog("An error occurred while initializing Ogre: %s", e.getDescription().c_str());

			delete meshMgr;
			delete bufferManager;
			delete skeletonSerializer;
			delete meshSerializer;
			delete skelMgr;
			delete matMgr;
			delete lodMgr;
			delete mth;
			delete rgm;
			delete logMgr;
			return false;
		}
		return true;
	}
	OgreManagers::~OgreManagers()
	{
		delete meshMgr;
		delete bufferManager;
		delete skeletonSerializer;
		delete meshSerializer;
		delete skelMgr;
		delete matMgr;
		delete lodMgr;
		delete mth;
		delete rgm;
		delete logMgr;
	}

	bool isVisible(FbxNode *pNode)
	{
		// First check if this node is part of a display layer that is invisible.
		if (pNode && pNode->GetDocument())
		{
			int numLayers = pNode->GetDocument()->GetMemberCount<FbxDisplayLayer>();
			for (int i = 0; i < numLayers; ++i)
			{
				FbxDisplayLayer* pDisplayLayer = pNode->GetDocument()->GetMember<FbxDisplayLayer>(i);
				FbxObject *pMemberNode = pDisplayLayer->FindMember<FbxNode>(pNode->GetName());
				if (pMemberNode)
				{
					if (!pDisplayLayer->Show)
					{
						return false;
					}
				}
			}
		}

		// Initialize to the Show property.  In Maya, this is set by the Shape object's Visibility checkbox
		// in the "Object Display" tab. Unlike the main Visibility checkbox in the main Object's "Display"
		// tab, this property is not inherited by children.
		bool bIsVisible = false;
		if (pNode)
		{
			bIsVisible = pNode->Show.Get();
		}
		FbxNode* pParentNode = pNode;
		while (pParentNode != NULL && bIsVisible)
		{
			bIsVisible = pParentNode->GetVisibility();
			if (!pParentNode->VisibilityInheritance.Get())
			{
				break;
			}
			pParentNode = pParentNode->GetParent();
		}
		return bIsVisible;
	}
	FbxAMatrix computeLocalTransform(FbxNode *pNode)
	{
		FbxAMatrix localTM;
		FbxVector4 lT, lR, lS;
		lT = pNode->LclTranslation.Get();
		lR = pNode->LclRotation.Get();
		lS = pNode->LclScaling.Get();
		localTM.SetT(lT);
		localTM.SetR(lR);
		localTM.SetS(lS);
		return localTM;
	}
	void AppendKeyedFrames(std::vector<int>& keyedFrames, FbxAnimCurve *pCurve)
	{
		if (pCurve)
		{
			for (int k = 0; k < pCurve->KeyGetCount(); ++k)
			{
				int frame = (int)pCurve->KeyGet(k).GetTime().GetFrameCount();
				keyedFrames.push_back(frame);
			}
		}
	}
	// taken from FBX SDK's examples\Transformations\main.cxx
	FbxAMatrix CalculateGlobalTransform(FbxNode* pNode, FbxTime time)
	{
		// There seems to be some variance between calculating the global transform and
		// using the FBX calculate it with EvaluateGlobalTransform.  
		/*
		FbxAMatrix lTM = pNode->EvaluateLocalTransform(time);

		if( pNode->GetParent() )
		{
		FbxAMatrix parentMatrix = CalculateGlobalTransform(pNode->GetParent(), time);
		return parentMatrix * lTM;
		}
		// root node
		// params.exportWorldCoords?
		return lTM;
		*/
		return pNode->EvaluateGlobalTransform(time);
	}

	FbxAMatrix convertMatrix(const FbxMatrix& mat)
	{
		FbxVector4 trans, shear, scale;
		FbxQuaternion rot;
		double sign;
		mat.GetElements(trans, rot, shear, scale, sign);
		FbxAMatrix ret;
		ret.SetT(trans);
		ret.SetQ(rot);
		ret.SetS(scale);
		return ret;
	}
	void logMatrix(const FbxAMatrix& mat)
	{
		FxOgreFBXLog("Pos( %f, %f, %f ), Quat( %f, %f, %f, %f), Scale(%f, %f, %f)\n", mat.GetT()[0], mat.GetT()[1], mat.GetT()[2], mat.GetQ()[3], mat.GetQ()[0], mat.GetQ()[1], mat.GetQ()[2], mat.GetS()[0], mat.GetS()[1], mat.GetS()[2]);
	}
	bool isValidMatrix(const FbxAMatrix& mat)
	{
		// Check that scales aren't zero and quaternions don't have //1.#QNAN0 values
		if (mat.GetQ()[0] != mat.GetQ()[0] ||
			mat.GetS()[0] == 0)
		{
			return false;
		}
		return true;
	}

	FbxAMatrix correctMatrix(const FbxAMatrix& mat)
	{
		if (!isValidMatrix(mat))
		{
			FxOgreFBXLog("Detected invalid matrix:\n");
			logMatrix(mat);
			FxOgreFBXLog("Returning identity matrix:\n");
			return FbxAMatrix();
		}
		return mat;
	}

#ifdef WIN32
	bool GetFullPath(const std::string& inputPath, std::string& outputPath)
	{
		char fullPath[_MAX_PATH] = { 0 };

		if (!_fullpath(fullPath, inputPath.c_str(), _MAX_PATH))
		{
			return false;
		}

		outputPath = fullPath;

		return true;
	}
	bool FileExists(const std::string& s)
	{
		DWORD attribs = GetFileAttributesA(s.c_str());

		if (INVALID_FILE_ATTRIBUTES == attribs)
		{
			if (ERROR_FILE_NOT_FOUND == GetLastError())
			{
				// File not found.  Could also be invalid path.
			}
			return false;
		}
		// Return false if this is a directory, not a file.
		if (attribs & FILE_ATTRIBUTE_DIRECTORY)
		{
			return false;
		}
		return true;
	}
	// Note: only send in directory paths to this, not full file paths.
	bool DirectoryExists(const std::string& s)
	{
		DWORD attribs = GetFileAttributesA(s.c_str());
		if (INVALID_FILE_ATTRIBUTES == attribs &&
			ERROR_FILE_NOT_FOUND == GetLastError())
		{
			return false;
		}

		if (attribs & FILE_ATTRIBUTE_DIRECTORY)
		{
			return true;
		}

		return false;
	}
	// Note: only send in full file paths to this, not directories.
	bool UserHasWritePermissionsForFile(const std::string& s)
	{
		bool hasWritePermissions = false;

		DWORD length = 0;

		if (!GetFileSecurityA(s.c_str(),
			OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
			NULL,
			NULL,
			&length) && ERROR_INSUFFICIENT_BUFFER == GetLastError())
		{
			PSECURITY_DESCRIPTOR security = static_cast<PSECURITY_DESCRIPTOR>(malloc(length));

			if (security && GetFileSecurityA(s.c_str(),
				OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
				security,
				length,
				&length))
			{
				HANDLE hToken = NULL;

				if (OpenProcessToken(GetCurrentProcess(),
					TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE | STANDARD_RIGHTS_READ,
					&hToken))
				{
					HANDLE hImpersonatedToken = NULL;

					if (DuplicateToken(hToken,
						SecurityImpersonation,
						&hImpersonatedToken))
					{
						GENERIC_MAPPING mapping = { 0xFFFFFFFF };
						PRIVILEGE_SET   privileges = { 0 };
						DWORD           grantedAccess = 0;
						DWORD           privilegesLength = sizeof(privileges);
						BOOL            result = FALSE;

						mapping.GenericRead = FILE_GENERIC_READ;
						mapping.GenericWrite = FILE_GENERIC_WRITE;
						mapping.GenericExecute = FILE_GENERIC_EXECUTE;
						mapping.GenericAll = FILE_ALL_ACCESS;

						// We only care about write access.
						DWORD accessRights = GENERIC_WRITE;

						MapGenericMask(&accessRights,
							&mapping);

						if (AccessCheck(security,
							hImpersonatedToken,
							accessRights,
							&mapping,
							&privileges,
							&privilegesLength,
							&grantedAccess,
							&result))
						{
							hasWritePermissions = result ? true : false;
						}

						CloseHandle(hImpersonatedToken);
					}

					CloseHandle(hToken);
				}

				free(security);
			}
		}

		// If the file did not exist, try to create it to see if the user has
		// write permissions. Technically the file not existing should make
		// this whole function return false, but since we only call this
		// function in the context of "can I create and write to this file?"
		// we use CreateFile as a failsafe. If CreateFile fails, the user
		// really can't create or write to the file. If the file already
		// existed, the access checks above will let us know if the user can
		// write to the file.
		if (ERROR_FILE_NOT_FOUND == GetLastError())
		{
			HANDLE hFile = CreateFileA(s.c_str(),
				GENERIC_WRITE,
				FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			CloseHandle(hFile);
			if (INVALID_HANDLE_VALUE != hFile)
			{
				hasWritePermissions = true;
				DeleteFileA(s.c_str());
			}
		}

		return hasWritePermissions;
	}
#else
#   error "Implement GetFullPath, FileExists, DirectoryExists, and UserHasWritePermissionsForFile for non-Windows platform!"
#endif


	// -------------------------------------------------------------------------------------
	// Below are taken from DrawScene.cxx in the FBX SDK samples.  They are used to compute
	// The vertex positions after skin deformations for multiple bindposes.
	// -------------------------------------------------------------------------------------
	// Get the matrix of the given pose
	FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex)
	{
		FbxAMatrix lPoseMatrix;
		FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

		memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

		return lPoseMatrix;
	}

	// Get the global position of the node for the current pose.
	// If the specified node is not part of the pose or no pose is specified, get its
	// global position at the current time.
	FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose, FbxAMatrix* pParentGlobalPosition)
	{
		FbxAMatrix lGlobalPosition;
		bool        lPositionFound = false;

		if (pPose)
		{
			int lNodeIndex = pPose->Find(pNode);

			if (lNodeIndex > -1)
			{
				// The bind pose is always a global matrix.
				// If we have a rest pose, we need to check if it is
				// stored in global or local space.
				if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
				{
					lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
				}
				else
				{
					// We have a local matrix, we need to convert it to
					// a global space matrix.
					FbxAMatrix lParentGlobalPosition;

					if (pParentGlobalPosition)
					{
						lParentGlobalPosition = *pParentGlobalPosition;
					}
					else
					{
						if (pNode->GetParent())
						{
							lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
						}
					}

					FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
					lGlobalPosition = lParentGlobalPosition * lLocalPosition;
				}

				lPositionFound = true;
			}
		}

		if (!lPositionFound)
		{
			// There is no pose entry for that node, get the current global position instead.

			// Ideally this would use parent global position and local position to compute the global position.
			// Unfortunately the equation 
			//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
			// does not hold when inheritance type is other than "Parent" (RSrs).
			// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
			lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
		}

		return lGlobalPosition;
	}

	// Get the geometry offset to a node. It is never inherited by the children.
	FbxAMatrix GetGeometry(FbxNode* pNode)
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}


	// Scale all the elements of a matrix.
	void MatrixScale(FbxAMatrix& pMatrix, double pValue)
	{
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pMatrix[i][j] *= pValue;
			}
		}
	}
	void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue)
	{
		pMatrix[0][0] += pValue;
		pMatrix[1][1] += pValue;
		pMatrix[2][2] += pValue;
		pMatrix[3][3] += pValue;
	}


	// Sum two matrices element by element.
	void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix)
	{
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pDstMatrix[i][j] += pSrcMatrix[i][j];
			}
		}
	}

	//Compute the transform matrix that the cluster will transform the vertex.
	void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition,
		FbxNode* pMeshNode,
		FbxMesh* pMesh,
		FbxCluster* pCluster,
		FbxAMatrix& pVertexTransformMatrix,
		FbxTime pTime,
		FbxPose* pPose)
	{
		FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

		FbxAMatrix lReferenceGlobalInitPosition;
		FbxAMatrix lReferenceGlobalCurrentPosition;
		FbxAMatrix lAssociateGlobalInitPosition;
		FbxAMatrix lAssociateGlobalCurrentPosition;
		FbxAMatrix lClusterGlobalInitPosition;
		FbxAMatrix lClusterGlobalCurrentPosition;

		FbxAMatrix lReferenceGeometry;
		FbxAMatrix lAssociateGeometry;
		FbxAMatrix lClusterGeometry;

		FbxAMatrix lClusterRelativeInitPosition;
		FbxAMatrix lClusterRelativeCurrentPositionInverse;

		if (lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel())
		{
			pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
			// Geometric transform of the model
			lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
			lAssociateGlobalInitPosition *= lAssociateGeometry;
			lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose);

			pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);

			// Multiply lReferenceGlobalInitPosition by Geometric Transformation
			lReferenceGeometry = GetGeometry(pMeshNode);
			lReferenceGlobalInitPosition *= lReferenceGeometry;

			lReferenceGlobalCurrentPosition = pGlobalPosition;

			// Get the link initial global position and the link current global position.
			pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
			// Multiply lClusterGlobalInitPosition by Geometric Transformation
			lClusterGeometry = GetGeometry(pCluster->GetLink());
			lClusterGlobalInitPosition *= lClusterGeometry;
			lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

			// Compute the shift of the link relative to the reference.
			//ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
			pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
				lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
		}
		else
		{
			pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
			lReferenceGlobalCurrentPosition = pGlobalPosition;

			// Multiply lReferenceGlobalInitPosition by Geometric Transformation
			lReferenceGeometry = GetGeometry(pMeshNode);
			lReferenceGlobalInitPosition *= lReferenceGeometry;

			// Get the link initial global position and the link current global position.
			pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
			lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

			// Compute the initial position of the link relative to the reference.
			lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;

			// Compute the current position of the link relative to the reference.
			lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;

			// Compute the shift of the link relative to the reference.
			pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
		}
	}



	// Taken from FBXSDK samples
	// Deform the vertex array in classic linear way.
	void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition,
		FbxNode* pMeshNode,
		FbxMesh* pMesh,
		FbxTime& pTime,
		FbxVector4* pVertexArray,
		FbxPose* pPose)
	{
		FbxSkin *pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
		if (!pSkin)
		{
			return;
		}
		// All the links must have the same link mode.
		FbxCluster::ELinkMode lClusterMode = pSkin->GetCluster(0)->GetLinkMode();

		int lVertexCount = pMesh->GetControlPointsCount();
		FbxAMatrix* lClusterDeformation = new FbxAMatrix[lVertexCount];
		memset(lClusterDeformation, 0, lVertexCount * sizeof(FbxAMatrix));

		double* lClusterWeight = new double[lVertexCount];
		memset(lClusterWeight, 0, lVertexCount * sizeof(double));

		if (lClusterMode == FbxCluster::eAdditive)
		{
			for (int i = 0; i < lVertexCount; ++i)
			{
				lClusterDeformation[i].SetIdentity();
			}
		}

		// For all skins and all clusters, accumulate their deformation and weight
		// on each vertices and store them in lClusterDeformation and lClusterWeight.
		int lSkinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
		for (int lSkinIndex = 0; lSkinIndex<lSkinCount; ++lSkinIndex)
		{
			FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

			int lClusterCount = lSkinDeformer->GetClusterCount();
			for (int lClusterIndex = 0; lClusterIndex<lClusterCount; ++lClusterIndex)
			{
				FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
				if (!lCluster->GetLink())
					continue;

				FbxAMatrix lVertexTransformMatrix;
				ComputeClusterDeformation(pGlobalPosition, pMeshNode, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

				int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
				for (int k = 0; k < lVertexIndexCount; ++k)
				{
					int lIndex = lCluster->GetControlPointIndices()[k];

					// Sometimes, the mesh can have less points than at the time of the skinning
					// because a smooth operator was active when skinning but has been deactivated during export.
					if (lIndex >= lVertexCount)
						continue;

					double lWeight = lCluster->GetControlPointWeights()[k];

					if (lWeight == 0.0)
					{
						continue;
					}

					// Compute the influence of the link on the vertex.
					FbxAMatrix lInfluence = lVertexTransformMatrix;
					MatrixScale(lInfluence, lWeight);

					if (lClusterMode == FbxCluster::eAdditive)
					{
						// Multiply with the product of the deformations on the vertex.
						MatrixAddToDiagonal(lInfluence, 1.0 - lWeight);
						lClusterDeformation[lIndex] = lInfluence * lClusterDeformation[lIndex];

						// Set the link to 1.0 just to know this vertex is influenced by a link.
						lClusterWeight[lIndex] = 1.0;
					}
					else // lLinkMode == FbxCluster::eNormalize || lLinkMode == FbxCluster::eTotalOne
					{
						// Add to the sum of the deformations on the vertex.
						MatrixAdd(lClusterDeformation[lIndex], lInfluence);

						// Add to the sum of weights to either normalize or complete the vertex.
						lClusterWeight[lIndex] += lWeight;
					}
				}//For each vertex			
			}//lClusterCount
		}

		//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
		for (int i = 0; i < lVertexCount; i++)
		{
			FbxVector4 lSrcVertex = pVertexArray[i];
			FbxVector4& lDstVertex = pVertexArray[i];
			double lWeight = lClusterWeight[i];

			// Deform the vertex if there was at least a link with an influence on the vertex,
			if (lWeight != 0.0)
			{
				lDstVertex = lClusterDeformation[i].MultT(lSrcVertex);
				if (lClusterMode == FbxCluster::eNormalize)
				{
					// In the normalized link mode, a vertex is always totally influenced by the links. 
					lDstVertex /= lWeight;
				}
				else if (lClusterMode == FbxCluster::eTotalOne)
				{
					// In the total 1 link mode, a vertex can be partially influenced by the links. 
					lSrcVertex *= (1.0 - lWeight);
					lDstVertex += lSrcVertex;
				}
			}
		}

		delete[] lClusterDeformation;
		delete[] lClusterWeight;
	}



}