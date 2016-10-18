#include <XERenderer/GUI/RenderableLayer.hpp>

#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>

#include <Ogre/OgreMain/include/OgreSceneManager.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include "OgreHlmsManager.h"
#include "OgreHlms.h"


namespace XE {


	RenderableLayer::RenderableLayer(Uint32 id, GUIRenderer& guiRenderer,
		Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr, const Uint16 atlasId)

		: //ManualObject(id, objManager, sceneMgr) //renderqueueID
		MovableObject(id, objManager, sceneMgr, 0)
		, Renderable()
		, m_guiRenderer(guiRenderer)

		, m_sceneMgr(sceneMgr)
		, m_sceneNodeLines(0)
		, mOperationType(Ogre::v1::RenderOperation::OT_TRIANGLE_LIST)

		, m_currentVertexBufferSize(0)
		, m_currentIndexBufferSize(0)
		,_initalizied(false)
	{
		//set renderqueue -> opengl error bind buffer after adding item??
	//	sceneMgr->getRenderQueue()->setRenderQueueMode(254, Ogre::RenderQueue::Modes::FAST);
	//	this->setRenderQueueGroup(254);

		m_sceneNodeLines = sceneMgr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		m_sceneNodeLines->attachObject(this);

		Ogre::RenderSystem *renderSystem = m_guiRenderer.getGraphicsManager().getRoot()->getRenderSystem();
		m_VaoManager = renderSystem->getVaoManager();
	
		Ogre::Aabb aabb(Ogre::Aabb::BOX_INFINITE);
		mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex);
		mObjectData.mWorldAabb->setFromAabb(aabb, mObjectData.mIndex);
		mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
		mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();

		// default overlays to preserve their own detail level
		mPolygonModeOverrideable = false;

		//>>>>>-------------- 2D --------------------
		// use identity projection and view matrices
		mUseIdentityProjection = true;
		mUseIdentityView = true;
		//<<<<<-------------- 2D --------------------

	}
	
	void RenderableLayer::getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) {
		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
			"RenderableLayer does not implement getRenderOperation. "
			"Use MovableObject::setRenderQueueGroup to change the group.",
			"RenderableLayer::getRenderOperation");
	}

	void RenderableLayer::updateVertices(std::queue<Vertex>& vertices)
	{
		if (vertices.size() == 0)
		{
			clear();
			return;
		}

		if (vertices.size() > m_currentVertexBufferSize) // resize
		{
			m_currentVertexBufferSize = vertices.size();
			m_currentIndexBufferSize = m_currentVertexBufferSize; //FIXME lesser indexes are needed!!

			clear();

			Ogre::VertexElement2Vec vertexElements;
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_POSITION));
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE));
			vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES));

			m_vertexBuffer = m_VaoManager->createVertexBuffer(vertexElements, vertices.size(), Ogre::BT_DYNAMIC_PERSISTENT_COHERENT, 0, false);

			//Now the Vao
			Ogre::VertexBufferPackedVec vertexBuffers;
			vertexBuffers.push_back(m_vertexBuffer);

			//-------------- index -----------------
			m_indexBuffer = m_VaoManager->createIndexBuffer(Ogre::IndexBufferPacked::IT_16BIT,
				m_currentIndexBufferSize, //index buffer size -> todo currently one index per vertex!!!??
				Ogre::BT_DYNAMIC_DEFAULT,
				NULL, false);

			m_Vao = m_VaoManager->createVertexArrayObject(vertexBuffers, m_indexBuffer, Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);

			mVaoPerLod[0].push_back(m_Vao);
			//mVaoPerLod[1].push_back(m_Vao); //needed for shadow caster Node!

			if (!_initalizied)
			{
				setDatablock("HlmsUnlit1"); // set this after  createVertexArrayObject  and mVaoPerLod[0].push_back(vao) ?? or else crash in renderable
				setCastShadows(false);

				mRenderables.push_back(this);
				_initalizied = true;
			}
			else
			{
			
			}


		}
		else if (vertices.size() < m_currentVertexBufferSize) //shrink 
				m_Vao->setPrimitiveRange(0, vertices.size());
		

		Uint32 idx = 0;
		int vertexCnt = 0;
			

		float* mVertexBufferCursor = (float*)(m_vertexBuffer->map(0, m_vertexBuffer->getNumElements()));

		Ogre::Aabb aabb;

		while (!vertices.empty())
		{
			auto vertex = vertices.front();

			//position
			*mVertexBufferCursor++ = vertex.position.x;
			*mVertexBufferCursor++ = vertex.position.y;
			*mVertexBufferCursor++ = vertex.position.z;

			aabb.merge(vertex.position);
		
			//color
			*mVertexBufferCursor++ = vertex.colour.r;
			*mVertexBufferCursor++ = vertex.colour.g;
			*mVertexBufferCursor++ = vertex.colour.b;
			*mVertexBufferCursor++ = vertex.colour.a;

			//texture
			*mVertexBufferCursor++ = vertex.uv.x;
			*mVertexBufferCursor++ = vertex.uv.y;
			
			//if (vertexCnt == 0)
			//	idx = 0; //set Index 0
			//else if (vertexCnt == 1)
			//	idx = 1; //set Index 0
			//else if (vertexCnt == 2)
			//	idx = 2; //set Index 0
			//else if (vertexCnt == 3)
			//	idx = 3; //set Index 0
			//else if (vertexCnt == 4)
			//	idx = 0;
			//else if (vertexCnt == 5) //quad finished
			//	idx = 2;

			//-----------> index(idx);
			idx++;
			vertices.pop();

			//if (vertexCnt == 5) //quad finished
			//{
			//	idx = 0;
			//	vertexCnt = 0;
			//}else
			//	vertexCnt++;

		}
	
		m_vertexBuffer->unmap(Ogre::UO_UNMAP_ALL);


		//-------------- index -----------------

		char* mIndexBufferCursor = (char*)m_indexBuffer->map(0, idx);

		for (int i = 0; i < idx; i++)
		{
			*((Uint16 *)mIndexBufferCursor) = i;
			mIndexBufferCursor += sizeof(Uint16);
		}
		m_indexBuffer->unmap(Ogre::UO_UNMAP_ALL);
		//-------------- end index -----------------

	
		Ogre::Aabb aabb2(Ogre::Aabb::BOX_INFINITE);//2D
		mObjectData.mLocalAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
		mObjectData.mWorldAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
		//mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex); //3D
		//mObjectData.mLocalRadius[mObjectData.mIndex] = aabb.getRadius();//3D
		mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
		mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
	}

	void RenderableLayer::clear()
	{
		if (!_initalizied)
			return;

		//clear aabb
		mObjectData.mLocalAabb->setFromAabb(Ogre::Aabb::BOX_NULL, mObjectData.mIndex);
		mObjectData.mLocalRadius[mObjectData.mIndex] = 0.0f;

		m_currentVertexBufferSize = 0;

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

	RenderableLayer::~RenderableLayer()
	{
		//m_sceneMgr->destroyManualObject(this);
		m_sceneMgr->destroySceneNode(m_sceneNodeLines);

	}

	const Ogre::String& RenderableLayer::getMovableType(void) const
	{
		return "UI";
	}

}