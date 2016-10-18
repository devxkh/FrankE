
#include <XERenderer/private/DebugRenderer.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEngine/Scene.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <Ogre/OgreMain/include/OgreManualObject2.h>
#include <XERenderer/OgreSceneManager.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>

#include <Ogre/OgreMain/include/OgreRoot.h>
#include "OgreHlmsManager.h"
#include "OgreHlms.h"


namespace XE {

	//------------------------------------------------------------------------------------------------
	DebugRenderer::DebugRenderer(Uint32 id, Scene& scene, Ogre::ObjectMemoryManager* objManager, float fillAlpha)
		: MovableObject(id, objManager, scene.getOgreSceneManager().__OgreSceneMgrPtr, 0)
		, _t_ObjectMemoryManager(objManager)
	//	, _t_manualObject(nullptr)
		, _t_sceneMrg(scene.getOgreSceneManager().__OgreSceneMgrPtr)
		, m_fillAlpha(fillAlpha)
		, m_GraphicsManager(scene.getGraphicsManager())

		, m_rendererIsDone(true)

		, m_sceneNodeLines(0)
		, m_initalized(false)

	{
	//	scene.getGraphicsManager().getIntoRendererQueue().push([this]() {

			Ogre::LogManager::getSingleton().logMessage("RQ -> DebugRenderer::DebugRenderer");

			m_sceneNodeLines = _t_sceneMrg->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			m_sceneNodeLines->attachObject(this);

			std::unique_ptr<DebugRenderable> p1(new DebugRenderable(m_GraphicsManager));
			_t_renderables.push_back(std::move(p1));


			Ogre::Aabb aabb(Ogre::Aabb::BOX_INFINITE);
			mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex);
			mObjectData.mWorldAabb->setFromAabb(aabb, mObjectData.mIndex);
			mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
			mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();

			/*Ogre::SceneNode* node = _t_sceneMrg->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);

			_t_manualObject = new Ogre::ManualObject(0, &_t_sceneMrg->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), _t_sceneMrg);
			_t_manualObject->begin("debug_draw", Ogre::v1::RenderOperation::OT_LINE_LIST);

			_t_manualObject->position(Ogre::Vector3::ZERO);
			_t_manualObject->colour(Ogre::ColourValue::ZERO);
			_t_manualObject->index(0);
			_t_manualObject->end();
			_t_manualObject->begin("debug_draw", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);
			_t_manualObject->position(Ogre::Vector3::ZERO);
			_t_manualObject->colour(Ogre::ColourValue::ZERO);
			_t_manualObject->index(0);
			_t_manualObject->end();

			node->attachObject(_t_manualObject);*/
	//	});
	}

	//------------------------------------------------------------------------------------------------

	void DebugRenderer::updateVertices(std::queue<Vertex>& vertices)
	{
		if (vertices.size() == 0)
		{
			clear();
			return;
		}

		_t_renderables[0]->updateVertices(vertices);
		//todo _t_renderables[1]->updateVertices(vertices);

		if (!m_initalized)
		{
			setCastShadows(false);

			mRenderables.push_back(_t_renderables[0].get());
			//todo mRenderables.push_back(_t_renderables[1].get());

			m_initalized = true;
		}

		Ogre::Aabb aabb2(Ogre::Aabb::BOX_INFINITE);//2D
		mObjectData.mLocalAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
		mObjectData.mWorldAabb->setFromAabb(aabb2, mObjectData.mIndex); //2D
																		//mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex); //3D
																		//mObjectData.mLocalRadius[mObjectData.mIndex] = aabb.getRadius();//3D
		mObjectData.mLocalRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
		mObjectData.mWorldRadius[mObjectData.mIndex] = std::numeric_limits<Ogre::Real>::max();
	}

	void DebugRenderer::clear()
	{
		if (!m_initalized)
			return;

		//clear aabb
		mObjectData.mLocalAabb->setFromAabb(Ogre::Aabb::BOX_NULL, mObjectData.mIndex);
		mObjectData.mLocalRadius[mObjectData.mIndex] = 0.0f;

		//if (_swapBuffer)
		//{
		////	lineVertices1.clear();
		////	triangleVertices1.clear();
		//	lineIndices1.clear();
		//	triangleIndices1.clear();
		//}
		//else
		//{
		////	lineVertices2.clear();
		////	triangleVertices2.clear();
		//	lineIndices2.clear();
		//	triangleIndices2.clear();
		//}

	}

	DebugRenderer::~DebugRenderer()
	{
		//m_sceneMgr->destroyManualObject(this);
		_t_sceneMrg->destroySceneNode(m_sceneNodeLines);

	}

	const Ogre::String& DebugRenderer::getMovableType(void) const
	{
		return "DebugRenderer";
	}



	//------------------------------------------------------------------------------------------------
	//void DebugRenderer::addPoint(const Ogre::Vector3 &p)
	//{
	//	if (_swapBuffer)
	//		_PointsBuf1.push_back(p);
	//	else
	//		_PointsBuf2.push_back(p);
	//}

	////------------------------------------------------------------------------------------------------
	//void DebugRenderer::addPoint(float x, float y, float z)
	//{
	//	if (_swapBuffer)
	//		_PointsBuf1.push_back(Ogre::Vector3(x, y, z));
	//	else
	//		_PointsBuf2.push_back(Ogre::Vector3(x, y, z));
	//}

	////------------------------------------------------------------------------------------------------
	//void DebugRenderer::setPoint(unsigned short index, const Ogre::Vector3 &value)
	//{
	//	if (_swapBuffer)
	//		_PointsBuf1[index] = value;
	//	else
	//		_PointsBuf2[index] = value;
	//}

	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	//void DebugRenderer::update()
	//{
	//	if (m_rendererIsDone)
	//	{
	//		m_rendererIsDone = false;


	//		m_GraphicsManager.getIntoRendererQueue().push([this, tmp]() {

	//			//Ogre::LogManager::getSingleton().logMessage("RQ -> DebugRenderer::update");
	//			//__t_DynamicLines->_t_Points = tmp ? _PointsBuf1 : _PointsBuf2;
	//			//__t_DynamicLines->update();

	//		

	//			//lineVertices);
	//			//_t_manualObject->beginUpdate(0);
	//			//if (lineVertices->size() > 0)
	//			//{
	//			//	_t_manualObject->estimateVertexCount(lineVertices->size());
	//			//	_t_manualObject->estimateIndexCount(lineIndices->size());
	//			//	for (std::list<VertexPair>::iterator i = lineVertices->begin(); i != lineVertices->end(); i++)
	//			//	{
	//			//		_t_manualObject->position(i->first);
	//			//		_t_manualObject->colour(i->second);
	//			//	}
	//			//	for (std::list<int>::iterator i = lineIndices->begin(); i != lineIndices->end(); i++)
	//			//		_t_manualObject->index(*i);
	//			//}
	//			//_t_manualObject->end();

	//			//_t_manualObject->beginUpdate(1);
	//			//if (triangleVertices->size() > 0)
	//			//{
	//			//	_t_manualObject->estimateVertexCount(triangleVertices->size());
	//			//	_t_manualObject->estimateIndexCount(triangleIndices->size());
	//			//	for (std::list<VertexPair>::iterator i = triangleVertices->begin(); i != triangleVertices->end(); i++)
	//			//	{
	//			//		_t_manualObject->position(i->first);
	//			//		_t_manualObject->colour(i->second.r, i->second.g, i->second.b, m_fillAlpha);
	//			//	}
	//			//	for (std::list<int>::iterator i = triangleIndices->begin(); i != triangleIndices->end(); i++)
	//			//		_t_manualObject->index(*i);
	//			//}
	//			//_t_manualObject->end();


	//			m_GraphicsManager.getFromRendererQueue().push([this]() {
	//				m_rendererIsDone = true;
	//			});
	//		});

	//	}
	//}


	DebugRenderable::DebugRenderable(GraphicsManager& gMgr)
		: Renderable()
		, mOperationType(Ogre::v1::RenderOperation::OT_TRIANGLE_LIST)

		, m_currentVertexBufferSize(0)
		, m_currentIndexBufferSize(0)
	{
		Ogre::RenderSystem *renderSystem = gMgr.getRoot()->getRenderSystem();
		m_VaoManager = renderSystem->getVaoManager();

	}



	void DebugRenderable::updateVertices(std::queue<Vertex>& vertices) {

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

			setDatablock("HlmsUnlit1"); // set this after  createVertexArrayObject  and mVaoPerLod[0].push_back(vao) ?? or else crash in renderable			
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
	}

	void DebugRenderable::clear()
	{
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

	void DebugRenderable::getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) {
		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
			"DebugRenderable does not implement getRenderOperation. "
			"Use MovableObject::setRenderQueueGroup to change the group.",
			"DebugRenderable::getRenderOperation");
	}

	DebugRenderable::~DebugRenderable()
	{

	}

}
