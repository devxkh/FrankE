
#include <XERenderer/private/DebugRenderer.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEngine/Scene.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <Ogre/OgreMain/include/OgreManualObject2.h>
#include <XERenderer/OgreSceneManager.hpp>

namespace XE {


	//------------------------------------------------------------------------------------------------
	DebugRenderer::DebugRenderer(Scene& scene, float fillAlpha)
		: _t_ObjectMemoryManager(nullptr)
		, _t_manualObject(nullptr)
		, m_fillAlpha(fillAlpha)
		, m_GraphicsManager(scene.getGraphicsManager())
		, _swapBuffer(false)
	{
		scene.getGraphicsManager().getIntoRendererQueue().push([this, &scene]() {

			Ogre::LogManager::getSingleton().logMessage("RQ -> DebugRenderer::DebugRenderer");

			auto test = scene.getOgreSceneManager();

			Ogre::SceneNode* node = test.__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);

			_t_manualObject = new Ogre::ManualObject(0, &test.__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), test.__OgreSceneMgrPtr);
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

			Ogre::SceneNode *sceneNodeLines = test.__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			sceneNodeLines->attachObject(_t_manualObject);
		});
	}

	//------------------------------------------------------------------------------------------------
	DebugRenderer::~DebugRenderer()
	{
		//TODO

		/*m_GraphicsManager.getIntoRendererQueue().push([this](){

		Ogre::MaterialManager::getSingleton().remove("BtOgre/DebugLines");
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("BtOgre");
		delete __t_DynamicLines;
		});*/
	}

	std::list<VertexPair>& DebugRenderer::getLineVertices()
	{
		return _swapBuffer ? lineVertices1 : lineVertices2;
	}

	std::list<VertexPair>& DebugRenderer::getTriangleVertices()
	{
		return _swapBuffer ? triangleVertices1 : triangleVertices2;
	}

	std::list<int>& DebugRenderer::getLineIndices()
	{
		return _swapBuffer ? lineIndices1 : lineIndices2;
	}

	std::list<int>& DebugRenderer::getTriangleIndices()
	{
		return _swapBuffer ? triangleIndices1 : triangleIndices2;
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
	void DebugRenderer::clear()
	{
		if (_swapBuffer)
		{
			lineVertices1.clear();
			triangleVertices1.clear();
			lineIndices1.clear();
			triangleIndices1.clear();

		}
		else
		{
			lineVertices2.clear(); 
			triangleVertices2.clear();
			lineIndices2.clear(); 
			triangleIndices2.clear();
		}
	}

	//------------------------------------------------------------------------------------------------
	void DebugRenderer::update()
	{
		if (m_GraphicsManager.GetRenderTask(RenderTaskID::DebugLines).isDone)
		{
			m_GraphicsManager.GetRenderTask(RenderTaskID::DebugLines).isDone = false;

			bool tmp = _swapBuffer;

			_swapBuffer = _swapBuffer ? false : true;

			m_GraphicsManager.getIntoRendererQueue().push([this, tmp]() {

				//Ogre::LogManager::getSingleton().logMessage("RQ -> DebugRenderer::update");
				//__t_DynamicLines->_t_Points = tmp ? _PointsBuf1 : _PointsBuf2;
				//__t_DynamicLines->update();

				std::list<VertexPair>* lineVertices;
				std::list<VertexPair>* triangleVertices;
				std::list<int>* lineIndices;
				std::list<int>* triangleIndices;

				if (_swapBuffer)
				{
					lineVertices = &lineVertices1;
					triangleVertices = &triangleVertices1;
					lineIndices = &lineIndices1;
					triangleIndices = &triangleIndices1;
				}
				else
				{
					lineVertices = &lineVertices2;
					triangleVertices = &triangleVertices2;
					lineIndices = &lineIndices2;
					triangleIndices = &triangleIndices2;
				}

				_t_manualObject->beginUpdate(0);
				if (lineVertices->size() > 0)
				{
					_t_manualObject->estimateVertexCount(lineVertices->size());
					_t_manualObject->estimateIndexCount(lineIndices->size());
					for (std::list<VertexPair>::iterator i = lineVertices->begin(); i != lineVertices->end(); i++)
					{
						_t_manualObject->position(i->first);
						_t_manualObject->colour(i->second);
					}
					for (std::list<int>::iterator i = lineIndices->begin(); i != lineIndices->end(); i++)
						_t_manualObject->index(*i);
				}
				_t_manualObject->end();

				_t_manualObject->beginUpdate(1);
				if (triangleVertices->size() > 0)
				{
					_t_manualObject->estimateVertexCount(triangleVertices->size());
					_t_manualObject->estimateIndexCount(triangleIndices->size());
					for (std::list<VertexPair>::iterator i = triangleVertices->begin(); i != triangleVertices->end(); i++)
					{
						_t_manualObject->position(i->first);
						_t_manualObject->colour(i->second.r, i->second.g, i->second.b, m_fillAlpha);
					}
					for (std::list<int>::iterator i = triangleIndices->begin(); i != triangleIndices->end(); i++)
						_t_manualObject->index(*i);
				}
				_t_manualObject->end();


				m_GraphicsManager.getFromRendererQueue().push([this]() {
					m_GraphicsManager.GetRenderTask(RenderTaskID::DebugLines).isDone = true;
				});
			});

		}
	}
}
