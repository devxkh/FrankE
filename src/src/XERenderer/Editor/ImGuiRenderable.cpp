#include <XERenderer/Editor/ImgGuiRenderable.hpp>

#include <XERenderer/GUI/GUIRenderer.hpp>
//#include <XERenderer/CameraRenderable.hpp>
//#include <XERenderer/GUI/RenderableShape.hpp>
#include <XERenderer/GraphicsManager.hpp>
//#include <XERenderer/GUI/GorillaRenderer.hpp>

#include <Ogre/OgreMain/include/OgreSceneManager.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include "OgreHlmsManager.h"
#include "OgreHlms.h"

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

#include <Ogre/OgreMain/include/OgreMaterial.h>
#include <Ogre/OgreMain/include/OgreTechnique.h>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreViewport.h>

#include <ThirdParty/imgui/imgui.h>

//fowarding
struct ImDrawList;

namespace XE {

	const Ogre::uint8 RENDER_QUEUE_OVERLAY = 254;
	Ogre::IdString ImGUICompositorPassProvider::mPassId = Ogre::IdString("IMGUIPASS");

	ImGUIPass::ImGUIPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
		Ogre::CompositorNode *parentNode, Ogre::SceneManager* sceneMgr)
		: Ogre::CompositorPass(definition, target, parentNode)
		, m_sceneMgr(sceneMgr)
	{

	}

	void ImGUIPass::execute(const Ogre::Camera *lodCameraconst)
	{
		//lodCameraconst->getLastViewport()->setScissors();

		m_sceneMgr->getRenderQueue()->render(m_sceneMgr->getDestinationRenderSystem(), RENDER_QUEUE_OVERLAY, RENDER_QUEUE_OVERLAY + 1, false, false);

		//static_cast<Ogre2RenderManager*>(RenderManager::getInstancePtr())->render();
	}

	ImgGuiMovableObject::ImgGuiMovableObject(Uint32 id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
		: MovableObject(id, objManager, sceneMgr, RENDER_QUEUE_OVERLAY)
		, m_sceneMgr(sceneMgr)
		, mOperationType(Ogre::OperationType::OT_TRIANGLE_LIST)
		, m_sceneNode(0)
	{

		//set renderqueue -> opengl error bind buffer after adding item??
		sceneMgr->getRenderQueue()->setRenderQueueMode(RENDER_QUEUE_OVERLAY, Ogre::RenderQueue::Modes::FAST);
		this->setRenderQueueGroup(RENDER_QUEUE_OVERLAY);

		sceneMgr->getRenderQueue()->setSortRenderQueue(RENDER_QUEUE_OVERLAY, Ogre::RenderQueue::DisableSort);


		m_sceneNode = sceneMgr->getRootSceneNode(Ogre::SCENE_STATIC)->createChildSceneNode(Ogre::SCENE_STATIC);
		m_sceneNode->attachObject(this);

		setCastShadows(false);

		Ogre::Aabb aabb(Ogre::Aabb::BOX_INFINITE);
		mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex);
		mObjectData.mWorldAabb->setFromAabb(aabb, mObjectData.mIndex);
		mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
		mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();

	}

	const Ogre::String& ImgGuiMovableObject::getMovableType(void) const
	{
		return "ImgGUI";
	}

	ImgGuiMovableObject::~ImgGuiMovableObject() {

		//m_sceneMgr->destroyManualObject(this);
		m_sceneMgr->destroySceneNode(m_sceneNode);
	}


	ImgGuiRenderable::ImgGuiRenderable(GUIRenderer& guiRenderer, ImgGuiMovableObject* imgGuiMovableObject)
		: //MovableObject(id, objManager, sceneMgr, 0),
		ScreenRenderable()
		, m_ImgGuiMovableObject(imgGuiMovableObject)
		, m_guiRenderer(guiRenderer)
		, m_currentVtxCount(0)
		, m_currentIdxCount(0)
		, _initialized(false)
	{

		Ogre::RenderSystem *renderSystem = m_guiRenderer.getGraphicsManager().getRoot()->getRenderSystem();
		m_VaoManager = renderSystem->getVaoManager();


	
		// default overlays to preserve their own detail level
		mPolygonModeOverrideable = false;


		//m_camera->getParentSceneNode()->attachObject(this);
		//m_sceneNodeLines->setPosition(Ogre::Vector3(0,-400,0));

	//	auto test =  _getParentNodeFullTransform();

		//>>>>>-------------- 2D --------------------
		//Ogre::Matrix4 projMatrix(2.0f / m_guiRenderer.m_ViewportSize.x, 0.0f, 0.0f, -1.0f,
		//	0.0f, -2.0f / m_guiRenderer.m_ViewportSize.y, 0.0f, 1.0f,
		//	0.0f, 0.0f, -1.0f, 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f);

		Ogre::Matrix4 projMatrix((1.0f / m_guiRenderer.m_ViewportSize.x) * 2.0f, 0.0f, 0.0f, -1.0f,
			0.0f, (1.0f / m_guiRenderer.m_ViewportSize.y) * -2.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);


		setCustomProjectionMatrix(true, projMatrix);

		//// use identity projection and view matrices
		//mUseIdentityProjection = true;
	//	mUseIdentityView = true;
		//<<<<<-------------- 2D --------------------




	}

	void ImgGuiRenderable::getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) {

		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
			"ImgGuiRenderable does not implement getRenderOperation. "
			"Use MovableObject::setRenderQueueGroup to change the group.",
			"ImgGuiRenderable::getRenderOperation");
	}

	void ImgGuiRenderable::getWorldTransforms(Ogre::Matrix4* xform) const
	{
		mTransform = Ogre::Matrix4::IDENTITY;
		xform = &mTransform;
	}

	void ImgGuiRenderable::updateVertexData(const ImDrawVert* vtxBuf, const ImDrawIdx* idxBuf, unsigned int vtxCount, unsigned int idxCount)
	{
		//return;
		//m_sceneNodeLines->setPosition(m_camera->getPosition());
		//m_sceneNodeLines->setOrientation(m_camera->getOrientation());	

		if (idxCount != m_currentIdxCount || vtxCount != m_currentVtxCount)
		{
			m_currentVtxCount = vtxCount;
			m_currentIdxCount = idxCount;
			
			if (_initialized)
				clear();

			Ogre::VertexElement2Vec vertexElements;
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT2, Ogre::VES_POSITION));
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES));
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_COLOUR, Ogre::VES_DIFFUSE));


			m_vertexBuffer = m_VaoManager->createVertexBuffer(vertexElements, vtxCount, Ogre::BT_DYNAMIC_PERSISTENT_COHERENT, 0, false);
			m_indexBuffer = m_VaoManager->createIndexBuffer(Ogre::IndexBufferPacked::IT_16BIT, idxCount, Ogre::BT_DYNAMIC_DEFAULT, NULL, false);

			//Now the Vao
			Ogre::VertexBufferPackedVec vertexBuffers;
			vertexBuffers.push_back(m_vertexBuffer);
			m_Vao = m_VaoManager->createVertexArrayObject(vertexBuffers, m_indexBuffer, Ogre::OperationType::OT_TRIANGLE_LIST);
			mVaoPerLod[0].push_back(m_Vao);

			if (!_initialized)
			{
				m_ImgGuiMovableObject->mRenderables.push_back(this); //getRenderOperation needs -> mVaoPerLod !!
				
				
				Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(m_guiRenderer.getGraphicsManager().getRoot()->getHlmsManager()->getDatablock("HlmsUnlitImgui"));
				datablock->setTexture(0, 0, mFontTex);

				setDatablock("HlmsUnlitImgui"); // set this after  createVertexArrayObject  and mVaoPerLod[0].push_back(vao) ?? or else crash in renderable
											//		setDatablock("HlmsUnlit1"); // set this after  createVertexArrayObject  and mVaoPerLod[0].push_back(vao) ?? or else crash in renderable

				_initialized = true;
			}

		}

		ImDrawVert* vtx_dst = (ImDrawVert*)(m_vertexBuffer->map(0, vtxCount));
		ImDrawIdx* idx_dst = (ImDrawIdx*)m_indexBuffer->map(0, idxCount);

		memcpy(vtx_dst, vtxBuf, vtxCount * sizeof(ImDrawVert));
		memcpy(idx_dst, idxBuf, idxCount * sizeof(ImDrawIdx));

		m_vertexBuffer->unmap(Ogre::UO_UNMAP_ALL);
		m_indexBuffer->unmap(Ogre::UO_UNMAP_ALL);

		vtx_dst += vtxCount;
		idx_dst += idxCount;

		//Ogre::Aabb aabb2(Ogre::Aabb::BOX_INFINITE);//2D
		//mObjectData.mLocalAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
		//mObjectData.mWorldAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
		//																//mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex); //3D
		//																//mObjectData.mLocalRadius[mObjectData.mIndex] = aabb.getRadius();//3D
		//mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
		//mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
	}

	void ImgGuiRenderable::clear()
	{
		//if (!_initialized)
		//	return;

		//clear aabb
		//mObjectData.mLocalAabb->setFromAabb(Ogre::Aabb::BOX_NULL, mObjectData.mIndex);
		//mObjectData.mLocalRadius[mObjectData.mIndex] = 0.0f;

		Ogre::VertexArrayObject *vao = m_Vao;

		if (vao)
		{
			Ogre::VaoManager *vaoManager = m_VaoManager;

			const Ogre::VertexBufferPackedVec &vertexBuffers = vao->getVertexBuffers();

			Ogre::VertexBufferPackedVec::const_iterator itBuffers = vertexBuffers.begin();
			Ogre::VertexBufferPackedVec::const_iterator endBuffers = vertexBuffers.end();

			while (itBuffers != endBuffers)
			{
				Ogre::VertexBufferPacked * vertexBuffer = *itBuffers;

				if (vertexBuffer->getMappingState() != Ogre::MS_UNMAPPED)
				{
					vertexBuffer->unmap(Ogre::UO_UNMAP_ALL);
				}

				vaoManager->destroyVertexBuffer(vertexBuffer);

				++itBuffers;
			}

			Ogre::IndexBufferPacked * indexBuffer = vao->getIndexBuffer();

			if (indexBuffer)
			{
				if (indexBuffer->getMappingState() != Ogre::MS_UNMAPPED)
				{
					indexBuffer->unmap(Ogre::UO_UNMAP_ALL);
				}

				vaoManager->destroyIndexBuffer(indexBuffer);
			}

			vaoManager->destroyVertexArrayObject(vao);
		}

		m_Vao = 0;
		mVaoPerLod[0].clear();
		mVaoPerLod[1].clear();
	}

	ImgGuiRenderable::~ImgGuiRenderable()
	{

	}

}