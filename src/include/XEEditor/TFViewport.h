#include <Ogre.h>
#include <Ogre/AnimationSystem.h>
#include <Helper/Clamp.h>
#include <OgreTagPoint.h>


//#include <Ogre/RenderSystems/GL/include/OgreGLPlugin.h>
#include <Ogre/RenderSystems/Direct3D9/include/OgreD3D9Plugin.h>

#define DLLEXPORT __declspec( dllexport )

void UpdateBoneColours();

class SelectionRectangle
	: public Ogre::ManualObject
{
public:
	SelectionRectangle(const Ogre::String& name)
		: Ogre::ManualObject(name)
	{
		setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
		setUseIdentityProjection(true);
		setUseIdentityView(true);
		setQueryFlags(0);
		SetCorners(0, 0, 0, 0);
		setVisible(false);
	}

	void SetCorners(float left, float top, float right, float bottom)
	{
		left = left * 2 - 1;
		right = right * 2 - 1;
		top = 1 - top * 2;
		bottom = 1 - bottom * 2;

		clear();
		begin("", Ogre::RenderOperation::OT_LINE_STRIP);
		position(left, top, -1);
		position(right, top, -1);
		position(right, bottom, -1);
		position(left, bottom, -1);
		position(left, top, -1);
		end();

		setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
	}

	void SetCorners(const Ogre::Vector2& topLeft, const Ogre::Vector2& bottomRight)
	{
		SetCorners(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}
};



struct CameraNodes
{
	Ogre::SceneNode* prePos;
	Ogre::SceneNode* yaw;
	Ogre::SceneNode* pitch;
	Ogre::SceneNode* postPos;

	float nextYawDegrees;
	float nextPitchDegrees;

	CameraNodes(Ogre::SceneNode* pParent, Ogre::Camera* pCamera)
		: nextYawDegrees(0)
		, nextPitchDegrees(0)
	{
		prePos = pParent->createChildSceneNode();
		yaw = prePos->createChildSceneNode();
		pitch = yaw->createChildSceneNode();
		postPos = pitch->createChildSceneNode();
		postPos->attachObject(pCamera);
	}

	void Update()
	{
		yaw->yaw(Ogre::Degree(nextYawDegrees));
		nextYawDegrees = 0;

		pitch->pitch(Ogre::Degree(nextPitchDegrees));
		nextPitchDegrees = 0;
	}
};

struct BoneInfo
{
	Ogre::Bone* pBone;
	float displayWeight;
	bool selected;
};

struct BoneDisplayInfo
{
	int boneInfoIndex;
	Ogre::TagPoint* pTagPoint;
	Ogre::Entity* pEntity;
};

struct ImplData
{
	Ogre::Root* pRoot;
	Ogre::SceneManager* pSceneManager;
	Ogre::Camera* pCamera;
	Ogre::Viewport* pViewport;
	Ogre::RenderWindow* pRenderWindow;
	Ogre::RenderSystem* pRenderSystem;

	Ogre::SceneNode* pSceneNode;
	Ogre::Entity* pEntity;

	CameraNodes* pCameraNodes;

	tecnofreak::ogre::AnimationSystem* pAnimationSystem;


	SelectionRectangle* pSelectionRect;
	Ogre::PlaneBoundedVolumeListSceneQuery* pVolumeQuery;
	bool mouseBoneSelectionModeEnabled;

	std::vector< BoneInfo > boneInfoList;
	std::vector< BoneDisplayInfo > boneDisplayInfoList;

	bool boneSelectionChangedSinceLastCall;

	ImplData()
		: pRoot(NULL)
		, pSceneManager(NULL)
		, pCamera(NULL)
		, pViewport(NULL)
		, pRenderWindow(NULL)
		, pRenderSystem(NULL)
		, pSceneNode(NULL)
		, pEntity(NULL)
		, pCameraNodes(NULL)
		, pAnimationSystem(NULL)
		, pSelectionRect(NULL)
		, pVolumeQuery(NULL)
		, mouseBoneSelectionModeEnabled(false)
		, boneSelectionChangedSinceLastCall(true)
	{
	}
};



ImplData g_data;
float g_zoomStepDistance = 0;
Ogre::Vector2 g_mousePosition(0, 0);
Ogre::Vector2 g_oldMousePosition(0, 0);
Ogre::Vector2 g_originalMousePosition(0, 0);
bool g_orbitButtonDown = false;
bool g_zoomButtonDown = false;
bool g_selectButtonDown = false;
const int ORBIT_BUTTON = 0;
const int ZOOM_BUTTON = 1;
const int SELECT_BUTTON = 0;
const float DEGREES_PER_SCREEN_UNIT = 1;
const float ZOOM_STEPS_PER_SCREEN_UNIT = 4;


void LogMessage(const char* message)
{
	assert(message != NULL);

	assert(g_data.pRoot != NULL);
	Ogre::LogManager::getSingleton().logMessage(Ogre::String(message));
}

void CreateResourceGroups()
{
	//no zip!
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("TecnoFreak", "FileSystem", "TecnoFreak");
}

void SetRenderSystem()
{
	g_data.pRoot->installPlugin(new Ogre::D3D9Plugin());

#if OGRE_VERSION_MINOR > 6 && OGRE_VERSION_MAJOR >= 1
	Ogre::RenderSystemList renderSystems = g_data.pRoot->getAvailableRenderers();
#else
	Ogre::RenderSystemList& renderSystems = *g_data.pRoot->getAvailableRenderers();
#endif
	if (renderSystems.empty())
	{
		return;
	}

	std::cout << "SetRenderSystem" << std::endl;

	g_data.pRenderSystem = renderSystems[0];
	g_data.pRoot->setRenderSystem(g_data.pRenderSystem);
	std::cout << "SetRenderSystem  done" << std::endl;

}

void InitialiseRenderSystem()
{
	SetRenderSystem();

	g_data.pRenderSystem->setConfigOption("Full Screen", "No");
	g_data.pRenderSystem->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
}

void GetDefaultInitParams(Ogre::NameValuePairList* pParams)
{
}

void CreateRenderWindow(const char* windowHandle)
{
	std::cout << "CreateRenderWindow " << std::endl;
	Ogre::NameValuePairList params;
	GetDefaultInitParams(&params);
	params["externalWindowHandle"] = Ogre::String(windowHandle);
	g_data.pRenderWindow = g_data.pRoot->createRenderWindow("", 0, 0, false, &params);
	std::cout << "CreateRenderWindow  done" << std::endl;
}


void CreateMaterialResourcesFromPath(const char* path)
{
	const char* const CHARACTER_MATERIAL_RESOURCE_GROUP_NAME = "TecnoFreakCharacterMaterial";
	try
	{
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(CHARACTER_MATERIAL_RESOURCE_GROUP_NAME);
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(CHARACTER_MATERIAL_RESOURCE_GROUP_NAME);
	}
	catch (...)
	{
	}

	std::vector< Ogre::String > additionalMaterialPaths;
	additionalMaterialPaths.push_back("../materials");
	additionalMaterialPaths.push_back("../materials/programs");
	additionalMaterialPaths.push_back("../materials/scripts");
	additionalMaterialPaths.push_back("../materials/textures");

	for (size_t i = 0; i < additionalMaterialPaths.size(); i++)
	{
		const Ogre::String& partialPath = additionalMaterialPaths[i];
		Ogre::String completePath = path;
		completePath.append(partialPath.begin(), partialPath.end());

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(completePath, "FileSystem", CHARACTER_MATERIAL_RESOURCE_GROUP_NAME);
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(CHARACTER_MATERIAL_RESOURCE_GROUP_NAME);
}

void CreateResourcesFromPath(const char* path)
{
	std::cout << "CreateResourcesFromPath,path:" << path << std::endl;


	const char* const CHARACTER_RESOURCE_GROUP_NAME = "TecnoFreakCharacter";

	try
	{
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(CHARACTER_RESOURCE_GROUP_NAME);
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(CHARACTER_RESOURCE_GROUP_NAME);
	}
	catch (...)
	{
	}

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, "FileSystem", CHARACTER_RESOURCE_GROUP_NAME);

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(CHARACTER_RESOURCE_GROUP_NAME);

	static Ogre::String s_lastLoadedCharacterPath = "";
	bool differentPath = (strcmpi(s_lastLoadedCharacterPath.c_str(), path) != 0);
	if (differentPath)
	{
		CreateMaterialResourcesFromPath(path);
		s_lastLoadedCharacterPath = Ogre::String(path);
	}
}

void SetCameraDistance(float distance)
{
	if (g_data.pCameraNodes == NULL)
	{
		return;
	}

	g_data.pCameraNodes->postPos->setPosition(Ogre::Vector3(0, 0, std::max< float >(0, distance)));
}

float GetCameraDistance()
{
	if (g_data.pCameraNodes == NULL)
	{
		return 0;
	}

	return g_data.pCameraNodes->postPos->getPosition().z;
}

void ResetCamera()
{
	if (g_data.pEntity == NULL)
	{
		return;
	}

	float radius = g_data.pEntity->getBoundingRadius();

	g_zoomStepDistance = 0.0025f * radius;

	float distance = 3 * radius;
	SetCameraDistance(distance);

	Ogre::Vector3 center = g_data.pSceneNode->getPosition() + g_data.pEntity->getBoundingBox().getCenter();
	g_data.pCameraNodes->prePos->setPosition(Ogre::Vector3(0, center.y, 0));
}

void PerformSelection(const Ogre::Vector2& firstPoint, const Ogre::Vector2& secondPoint)
{
	if (g_data.pEntity == NULL)
	{
		return;
	}

	Ogre::SkeletonInstance* pSkeletonInstance = g_data.pEntity->getSkeleton();
	if (pSkeletonInstance == NULL)
	{
		return;
	}

	const float renderWindowWidth = g_data.pRenderWindow->getWidth();
	if (renderWindowWidth == 0)
	{
		return;
	}

	const float renderWindowHeight = g_data.pRenderWindow->getHeight();
	if (renderWindowHeight == 0)
	{
		return;
	}

	float left = firstPoint.x / renderWindowWidth;
	float right = secondPoint.x / renderWindowWidth;
	float top = firstPoint.y / renderWindowHeight;
	float bottom = secondPoint.y / renderWindowHeight;

	if (right < left)
	{
		std::swap(right, left);
	}

	if (bottom < top)
	{
		std::swap(bottom, top);
	}

	for (size_t i = 0; i < g_data.boneInfoList.size(); ++i)
	{
		BoneInfo& boneInfo = g_data.boneInfoList[i];
		boneInfo.selected = false;
	}

	const float MIN_SELECTION_AREA = 0.0001;
	const float selectionWidth = right - left;
	const float selectionHeight = bottom - top;
	const float selectionArea = selectionWidth * selectionHeight;
	if (selectionArea < MIN_SELECTION_AREA)
	{
		return;
	}

	Ogre::PlaneBoundedVolume vol;
	g_data.pCamera->getCameraToViewportBoxVolume(left, top, right, bottom, &vol);

	Ogre::PlaneBoundedVolumeList volList;
	volList.push_back(vol);

	g_data.pVolumeQuery->setVolumes(volList);

	Ogre::SceneQueryResult result = g_data.pVolumeQuery->execute();


	for (Ogre::SceneQueryResultMovableList::iterator it = result.movables.begin(); it != result.movables.end(); ++it)
	{
		const Ogre::MovableObject* pSelectedObject = *it;

		for (size_t i = 0; i < g_data.boneDisplayInfoList.size(); ++i)
		{
			const BoneDisplayInfo& boneDisplayInfo = g_data.boneDisplayInfoList[i];
			const Ogre::Entity* pBoneEntity = boneDisplayInfo.pEntity;

			bool selectedObjectMatches = (pBoneEntity == pSelectedObject);
			if (selectedObjectMatches)
			{
				int boneInfoIndex = boneDisplayInfo.boneInfoIndex;
				BoneInfo& boneInfo = g_data.boneInfoList[boneInfoIndex];
				boneInfo.selected = true;

				g_data.boneSelectionChangedSinceLastCall = true;
			}
		}
	}
}


void AddBoneVisuals()
{
	// TODO: Make boneScaleFactor configurable
	const Ogre::String boneMeshName = "bone.mesh";
	const Ogre::String boneMaterialName = "TecnoFreak/Bone_Material";
	const float boneScaleFactor = 0.02f;

	if (g_data.pEntity == NULL)
	{
		return;
	}

	Ogre::SkeletonInstance* pSkeletonInstance = g_data.pEntity->getSkeleton();
	if (pSkeletonInstance == NULL)
	{
		return;
	}

	Ogre::MaterialPtr pMaterial = Ogre::MaterialManager::getSingleton().getByName(boneMaterialName);
	if (pMaterial.isNull())
	{
		LogMessage("TecnoFreak: Bone Material not found!");
		return;
	}

	Ogre::Skeleton::BoneIterator boneIt = pSkeletonInstance->getBoneIterator();
	while (boneIt.hasMoreElements())
	{
		Ogre::Bone* pBone = boneIt.getNext();

		BoneInfo boneInfo;
		boneInfo.pBone = pBone;
		boneInfo.selected = false;
		boneInfo.displayWeight = 1.f;

		int boneInfoIndex = static_cast< int >(g_data.boneInfoList.size());
		g_data.boneInfoList.push_back(boneInfo);

		std::vector< Ogre::Node* > childNodes;
		Ogre::Node::ChildNodeIterator childNodeIt = pBone->getChildIterator();
		while (childNodeIt.hasMoreElements())
		{
			Ogre::Node* pChildNode = childNodeIt.getNext();
			childNodes.push_back(pChildNode);
		}

		const Ogre::String& boneName = pBone->getName();

		for (size_t i = 0; i < childNodes.size(); i++)
		{
			const Ogre::Node* pCurrentNode = childNodes[i];
			const Ogre::String& childNodeName = pCurrentNode->getName();

			const Ogre::String boneEntityName = boneName + " -> " + childNodeName;
			Ogre::Entity* pBoneEntity = g_data.pSceneManager->createEntity(boneEntityName, boneMeshName);

			const Ogre::String clonedMaterialName = boneEntityName + " : Material";
			LogMessage(clonedMaterialName.c_str());
			Ogre::MaterialPtr pClonedBoneMaterial = pMaterial->clone(clonedMaterialName);
			pBoneEntity->getSubEntity(0)->setMaterial(pClonedBoneMaterial);
			pBoneEntity->setVisible(false);
			pBoneEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_LATE);

			Ogre::TagPoint* pBoneTagPoint = g_data.pEntity->attachObjectToBone(boneName, pBoneEntity);
			const Ogre::Vector3& currentNodePosition = pCurrentNode->getPosition();
			pBoneTagPoint->setOrientation(((Ogre::Vector3) (pBoneTagPoint->getOrientation() * Ogre::Vector3::UNIT_Y)).getRotationTo(currentNodePosition));
			pBoneTagPoint->setScale(boneScaleFactor, pCurrentNode->getPosition().length(), boneScaleFactor);

			BoneDisplayInfo boneDisplayInfo;
			boneDisplayInfo.boneInfoIndex = boneInfoIndex;
			boneDisplayInfo.pEntity = pBoneEntity;
			boneDisplayInfo.pTagPoint = pBoneTagPoint;

			g_data.boneDisplayInfoList.push_back(boneDisplayInfo);
		}

		if (childNodes.size() == 0)
		{
			const Ogre::String boneEntityName = pBone->getName();
			Ogre::Entity* pBoneEntity = g_data.pSceneManager->createEntity(boneEntityName, boneMeshName);

			const Ogre::String clonedMaterialName = boneEntityName + " : Material";
			Ogre::MaterialPtr pClonedBoneMaterial = pMaterial->clone(clonedMaterialName);
			pBoneEntity->getSubEntity(0)->setMaterial(pClonedBoneMaterial);
			pBoneEntity->setVisible(false);
			pBoneEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_LATE);

			Ogre::TagPoint* pBoneTagPoint = g_data.pEntity->attachObjectToBone(boneName, pBoneEntity);
			pBoneTagPoint->setScale(Ogre::Vector3(boneScaleFactor * 2));
			pBoneTagPoint->yaw(Ogre::Degree(180));
			pBoneTagPoint->roll(Ogre::Degree(90));

			BoneDisplayInfo boneDisplayInfo;
			boneDisplayInfo.boneInfoIndex = boneInfoIndex;
			boneDisplayInfo.pEntity = pBoneEntity;
			boneDisplayInfo.pTagPoint = pBoneTagPoint;

			g_data.boneDisplayInfoList.push_back(boneDisplayInfo);
		}
	}
}

void UpdateBoneColours()
{
	for (size_t i = 0; i < g_data.boneDisplayInfoList.size(); ++i)
	{
		BoneDisplayInfo& boneDisplayInfo = g_data.boneDisplayInfoList[i];
		int boneInfoIndex = boneDisplayInfo.boneInfoIndex;

		const BoneInfo& boneInfo = g_data.boneInfoList[boneInfoIndex];

		Ogre::ColourValue boneOuterColour = Ogre::ColourValue(0.3f, 0.9, 0.7f, 1);
		Ogre::ColourValue boneInnerColour = Ogre::ColourValue(0.1f, 0.25f, 0.2f, 1);

		if (g_data.mouseBoneSelectionModeEnabled)
		{
			if (!boneInfo.selected)
			{
				boneOuterColour /= 2;
			}

			Ogre::ColourValue weightColours[] =
			{
				Ogre::ColourValue::Black,
				Ogre::ColourValue(204.f / 255, 102.f / 255, 51.f / 255, 1),
				Ogre::ColourValue(255.f / 255, 204.f / 255, 102.f / 255, 1),
				Ogre::ColourValue::White
			};

			const int colourCount = sizeof(weightColours) / sizeof(Ogre::ColourValue);
			const int intervalCount = colourCount - 1;
			assert(2 <= intervalCount);

			float weight = boneInfo.displayWeight;
			int interval = static_cast< int >(floor(weight * (intervalCount)));
			float intervalRange = 1.f / (intervalCount);
			float weightInterval = (weight - (interval * intervalRange)) / intervalRange;

			Ogre::ColourValue zeroWeight = weightColours[interval];
			Ogre::ColourValue fullWeight = weightColours[interval + 1];

			boneInnerColour = (fullWeight * weightInterval) + (zeroWeight * (1.f - weightInterval));
		}

		boneDisplayInfo.pEntity->getSubEntity(0)->getTechnique()->getPass(0)->setAmbient(boneInnerColour);
		boneDisplayInfo.pEntity->getSubEntity(0)->getTechnique()->getPass(1)->setAmbient(boneOuterColour);
	}


}

bool IsAltKeyDown()
{
	return ((GetAsyncKeyState(VK_MENU) & 0x8000) == 0x8000);
}

extern "C"
{

	DLLEXPORT void InitImpl(const char* windowHandle)
	{
		std::cout << "shit" << std::endl;

		g_data.pRoot = new Ogre::Root();
		LogMessage("TecnoFreak: Initialising Ogre Viewport");

		std::cout << "shitx1" << std::endl;
		LogMessage("TecnoFreak: Setting up resources");
		CreateResourceGroups();
		std::cout << "shitx2" << std::endl;

		LogMessage("TecnoFreak: Initialising Render System");
		InitialiseRenderSystem();

		std::cout << "shitx3" << std::endl;
		
		g_data.pRoot->initialise(false);

		LogMessage("TecnoFreak: Creating Render Window");
		CreateRenderWindow(windowHandle);

		std::cout << "shit1" << std::endl;
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		LogMessage("TecnoFreak: Initialising scene manger");
		g_data.pSceneManager = g_data.pRoot->createSceneManager(Ogre::ST_GENERIC);
		g_data.pCamera = g_data.pSceneManager->createCamera("Default");
		g_data.pCamera->setNearClipDistance(0.1f);
		g_data.pCamera->setAutoAspectRatio(true);
		g_data.pViewport = g_data.pRenderWindow->addViewport(g_data.pCamera);

		g_data.pViewport->setBackgroundColour(Ogre::ColourValue::Red);

		Ogre::SceneNode* pRootSceneNode = g_data.pSceneManager->getRootSceneNode();

		g_data.pCameraNodes = new CameraNodes(pRootSceneNode, g_data.pCamera);
	
		g_data.pSceneManager->setAmbientLight(XE::ColourValue(0.5f, 0.5f, 0.5f));
		XE::Light *light = g_data.pSceneManager->createLight("MainLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		std::cout << "shit2" << std::endl;

		g_data.pSelectionRect = new SelectionRectangle("Selection SelectionRectangle");
		pRootSceneNode->attachObject(g_data.pSelectionRect);

		g_data.pVolumeQuery = g_data.pSceneManager->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());

		LogMessage("TecnoFreak: Finished initialising Ogre viewport");
	}

	DLLEXPORT void ShutdownImpl()
	{
		ImplData tmp = g_data;
		g_data = ImplData();

		delete tmp.pAnimationSystem;
		delete tmp.pCameraNodes;
		delete tmp.pSelectionRect;
		delete tmp.pRoot;
	}


	DLLEXPORT void RedrawImpl()
	{
		if (g_data.pRoot == NULL)
		{
			return;
		}

		if (g_data.pRenderWindow == NULL)
		{
			return;
		}

		if (g_data.pCameraNodes == NULL)
		{
			return;
		}

		static Ogre::Timer s_frameTimer;
		const unsigned long elapsedMilliseconds = s_frameTimer.getMilliseconds();
		const float elapsedSeconds = static_cast< float >(elapsedMilliseconds) / 1000.f;
		s_frameTimer.reset();

		g_data.pRenderWindow->windowMovedOrResized();
		g_data.pRoot->renderOneFrame();
		g_data.pCameraNodes->Update();
		UpdateBoneColours();

		if (g_data.pAnimationSystem != NULL)
		{
			g_data.pAnimationSystem->update(elapsedSeconds);
		}
	}


	DLLEXPORT const char* GetFileOpenTitleImpl()
	{
		return "Load Ogre Model";
	}


	DLLEXPORT const char* GetFileOpenFilterImpl()
	{
		return "Ogre Mesh File (*.mesh)|*.mesh|All Files (*.*)|*.*";
	}


	DLLEXPORT bool LoadAnimableImpl(const char* path, const char* filename, const char* name)
	{
		std::cout << "LoadAnimableImpl,path:" << path << ",file:" << filename << ",name:" << name << std::endl;


		LogMessage("TecnoFreak: Loading Entity");
		if (g_data.pEntity != NULL)
		{
			return false;
		}

		CreateResourcesFromPath(path);

		g_data.pEntity = g_data.pSceneManager->createEntity(name, filename);
		if (g_data.pEntity == NULL)
		{
			return false;
		}

		g_data.pSceneNode = g_data.pSceneManager->getRootSceneNode()->createChildSceneNode();
		g_data.pSceneNode->attachObject(g_data.pEntity);

		assert(g_data.pAnimationSystem == NULL);
		g_data.pAnimationSystem = new tecnofreak::ogre::AnimationSystem(g_data.pEntity);

		AddBoneVisuals();

		ResetCamera();

		return true;
	}


	DLLEXPORT bool ClearAnimableImpl()
	{
		Ogre::LogManager::getSingleton().logMessage("TecnoFreak: Clearing entity");
		if (g_data.pEntity == NULL)
		{
			return false;
		}

		delete g_data.pAnimationSystem;
		g_data.pAnimationSystem = NULL;

		g_data.pSceneNode->detachObject(g_data.pEntity);
		g_data.pSceneManager->destroyEntity(g_data.pEntity);
		g_data.pSceneManager->destroySceneNode(g_data.pSceneNode);

		g_data.pEntity = NULL;
		g_data.pSceneNode = NULL;

		for (size_t i = 0; i < g_data.boneDisplayInfoList.size(); ++i)
		{
			Ogre::Entity* pBoneEntity = g_data.boneDisplayInfoList[i].pEntity;
			g_data.pSceneManager->destroyEntity(pBoneEntity);
		}

		g_data.boneDisplayInfoList.clear();
		g_data.boneInfoList.clear();

		return true;
	}


	DLLEXPORT int GetAnimationCountImpl()
	{
		if (g_data.pEntity == NULL)
		{
			return 0;
		}

		Ogre::SkeletonInstance* pSkeleton = g_data.pEntity->getSkeleton();
		if (pSkeleton == NULL)
		{
			return 0;
		}

		int animationCount = static_cast< int >(pSkeleton->getNumAnimations());
		return animationCount;
	}


	DLLEXPORT const char* GetAnimationNameImpl(int animationIndex)
	{
		std::cout << "GetAnimationNameImpl,idx:" << animationIndex << std::endl;


		if (g_data.pEntity == NULL)
		{
			return "";
		}

		Ogre::SkeletonInstance* pSkeleton = g_data.pEntity->getSkeleton();
		if (pSkeleton == NULL)
		{
			return "";
		}

		int animationCount = static_cast< int >(pSkeleton->getNumAnimations());
		if (animationIndex < 0 || animationCount <= animationIndex)
		{
			return "";
		}

		Ogre::Animation* pAnimation = pSkeleton->getAnimation(static_cast< unsigned short >(animationIndex));
		if (pAnimation == NULL)
		{
			return "";
		}

		const char* name = pAnimation->getName().c_str();
		return name;
	}


	DLLEXPORT void OnMouseClickImpl(int mouseButton, int x, int y)
	{
	}


	DLLEXPORT void OnMouseMoveImpl(int x, int y)
	{
		g_mousePosition = Ogre::Vector2(x, y);
		Ogre::Vector2 mouseIncrement = g_mousePosition - g_oldMousePosition;

		if (g_orbitButtonDown)
		{
			if (g_data.pCameraNodes != NULL)
			{
				g_data.pCameraNodes->nextYawDegrees += -mouseIncrement.x * DEGREES_PER_SCREEN_UNIT;
				g_data.pCameraNodes->nextPitchDegrees += -mouseIncrement.y * DEGREES_PER_SCREEN_UNIT;
			}
		}

		if (g_zoomButtonDown)
		{
			float distance = GetCameraDistance();
			distance += mouseIncrement.y * g_zoomStepDistance * ZOOM_STEPS_PER_SCREEN_UNIT;
			SetCameraDistance(distance);
		}

		if (g_selectButtonDown)
		{
			const float renderWindowWidth = g_data.pRenderWindow->getWidth();
			const float renderWindowHeight = g_data.pRenderWindow->getHeight();
			const float x1 = g_originalMousePosition.x / renderWindowWidth;
			const float y1 = g_originalMousePosition.y / renderWindowHeight;
			const float x2 = g_mousePosition.x / renderWindowWidth;
			const float y2 = g_mousePosition.y / renderWindowHeight;
			g_data.pSelectionRect->SetCorners(x1, y1, x2, y2);
			g_data.pSelectionRect->setVisible(true);

			PerformSelection(g_originalMousePosition, g_mousePosition);
		}

		g_oldMousePosition = g_mousePosition;
	}


	DLLEXPORT void OnMouseWheelImpl(int delta)
	{
		float distance = GetCameraDistance();
		distance += -delta * g_zoomStepDistance;
		SetCameraDistance(distance);
	}


	DLLEXPORT void OnMouseDownImpl(int mouseButton, int x, int y)
	{
		bool allowOrbitModifierKeyDown = IsAltKeyDown();
		bool selectionMode = !allowOrbitModifierKeyDown && g_data.mouseBoneSelectionModeEnabled;

		if (mouseButton == ORBIT_BUTTON && !selectionMode)
		{
			g_orbitButtonDown = true;
		}

		if (mouseButton == ZOOM_BUTTON)
		{
			g_zoomButtonDown = true;
		}

		if (mouseButton == SELECT_BUTTON && selectionMode)
		{
			g_selectButtonDown = true;
			g_originalMousePosition = Ogre::Vector2(x, y);
		}
	}


	DLLEXPORT void OnMouseUpImpl(int mouseButton, int x, int y)
	{
		if (mouseButton == ORBIT_BUTTON)
		{
			g_orbitButtonDown = false;
		}

		if (mouseButton == ZOOM_BUTTON)
		{
			g_zoomButtonDown = false;
		}

		if (mouseButton == SELECT_BUTTON && g_selectButtonDown)
		{
			g_selectButtonDown = false;
			g_data.pSelectionRect->setVisible(false);
			PerformSelection(g_originalMousePosition, g_mousePosition);
		}
	}


	DLLEXPORT void LoadAnimationTreeImpl(const char* filename)
	{
		std::cout << "LoadAnimationTreeImpl,file:" << filename << std::endl;


		LogMessage("TecnoFreak: Loading new animation tree");
		assert(filename != NULL);
		if (filename == NULL)
		{
			return;
		}

		if (g_data.pAnimationSystem == NULL)
		{
			return;
		}

		g_data.pAnimationSystem->loadAnimationTree(filename);
	}


	DLLEXPORT void SetParameterValueImpl(const char* parameterName, float parameterValue)
	{
		std::cout << "SetParam:" << parameterName << ",val:" << parameterValue << std::endl;
		assert(parameterName != NULL);
		if (parameterName == NULL)
		{
			return;
		}

		if (g_data.pAnimationSystem == NULL)
		{
			return;
		}


		tecnofreak::IParameter* pParameter = g_data.pAnimationSystem->getParameter(parameterName);
		if (pParameter == NULL)
		{
			return;
		}

		pParameter->setValue(parameterValue);
	}


	DLLEXPORT void ShowSkeletonImpl(bool showSkeleton)
	{
		if (g_data.pEntity == NULL)
		{
			return;
		}

		for (size_t i = 0; i < g_data.boneDisplayInfoList.size(); ++i)
		{
			Ogre::Entity* pBoneEntity = g_data.boneDisplayInfoList[i].pEntity;
			pBoneEntity->setVisible(showSkeleton);
		}
	}

	DLLEXPORT void SetBackgroundColorImpl(float r, float g, float b)
	{
		if (g_data.pViewport == NULL)
		{
			return;
		}
		g_data.pViewport->setBackgroundColour(Ogre::ColourValue(r, g, b));
	}

	DLLEXPORT void SetMouseBoneSelectionModeImpl(bool enableBoneSelectionMode)
	{
		g_data.mouseBoneSelectionModeEnabled = enableBoneSelectionMode;
	}

	DLLEXPORT void ResetBoneDisplayWeightsImpl()
	{
		for (size_t i = 0; i < g_data.boneInfoList.size(); ++i)
		{
			BoneInfo& boneInfo = g_data.boneInfoList[i];
			boneInfo.displayWeight = 1.f;
		}
	}

	DLLEXPORT int GetBoneCountImpl()
	{
		int boneCount = static_cast< int >(g_data.boneInfoList.size());
		return boneCount;
	}

	DLLEXPORT void SetBoneSelectedByIndexImpl(int boneId, bool select)
	{
		if (boneId < 0 || static_cast< int >(g_data.boneInfoList.size()) <= boneId)
		{
			return;
		}

		if (g_data.boneInfoList[boneId].selected != select)
		{
			g_data.boneInfoList[boneId].selected = select;

			g_data.boneSelectionChangedSinceLastCall = true;
		}
	}

	DLLEXPORT void ClearSelectedBonesImpl()
	{
		for (size_t i = 0; i < g_data.boneInfoList.size(); ++i)
		{
			if (g_data.boneInfoList[i].selected != false)
			{
				g_data.boneSelectionChangedSinceLastCall = true;
			}
			g_data.boneInfoList[i].selected = false;
		}
	}

	DLLEXPORT bool IsBoneSelectedByIndexImpl(int boneId)
	{
		if (boneId < 0 || static_cast< int >(g_data.boneInfoList.size()) <= boneId)
		{
			return false;
		}

		return g_data.boneInfoList[boneId].selected;
	}

	DLLEXPORT float GetBoneDisplayWeightByIndexImpl(int boneId)
	{
		if (boneId < 0 || static_cast< int >(g_data.boneInfoList.size()) <= boneId)
		{
			return 0;
		}

		return g_data.boneInfoList[boneId].displayWeight;
	}

	DLLEXPORT void SetBoneDisplayWeightByIndexImpl(int boneId, float weight)
	{
		if (boneId < 0 || static_cast< int >(g_data.boneInfoList.size()) <= boneId)
		{
			return;
		}

		g_data.boneInfoList[boneId].displayWeight = tecnofreak::helper::clamp(weight, 0.f, 1.f);
	}


	DLLEXPORT const char* GetBoneNameByIndexImpl(int boneId)
	{
		if (boneId < 0 || static_cast< int >(g_data.boneInfoList.size()) <= boneId)
		{
			return "";
		}

		const Ogre::String& boneName = g_data.boneInfoList[boneId].pBone->getName();
		return boneName.c_str();
	}


	DLLEXPORT bool CheckBoneSelectionChangedSinceLastCallImpl()
	{
		bool changed = g_data.boneSelectionChangedSinceLastCall;
		g_data.boneSelectionChangedSinceLastCall = false;
		return changed;
	}

}
