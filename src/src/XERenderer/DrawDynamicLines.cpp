
#include <XERenderer/DrawDynamicLines.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XERenderer/private/DynamicLines.hpp>
#include <XEngine/Scene.hpp>
#include <XERenderer/GraphicsManager.hpp>

//#include <XERenderer/private/ManualObject.hpp>
#include <Ogre/OgreMain/include/OgreManualObject2.h>

#include <XERenderer/OgreSceneManager.hpp>

using namespace Ogre;

namespace XE {

    //------------------------------------------------------------------------------------------------
	DrawDynamicLines::DrawDynamicLines(Scene& scene)
		: _t_ObjectMemoryManager(nullptr),
		__t_DynamicLines(nullptr),
		m_GraphicsManager(scene.getGraphicsManager())
		, _swapBuffer(false)
		, m_rendererisDone(true)
	{
		scene.getGraphicsManager().getIntoRendererQueue().push([this, &scene](){
		
			Ogre::LogManager::getSingleton().logMessage("RQ -> DrawDynamicLines::DrawDynamicLines");

			auto test = scene.getOgreSceneManager();
		
			Ogre::SceneNode* node = test.__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			
			//Ogre::VaoManager*  vao = m_GraphicsManager.getRoot()->getRenderSystem()->getVaoManager();

			//_t_ObjectMemoryManager = new Ogre::ObjectMemoryManager();
			
			__t_DynamicLines = new DynamicLines(0, &test.__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), test.__OgreSceneMgrPtr, Ogre::OperationType::OT_LINE_LIST);
			__t_DynamicLines->setCastShadows(false);
			node->attachObject(__t_DynamicLines);

			//---------------------------------------------------------------------------------------
			//
			//---------------------------------------------------------------------------------------
			//Ogre::ManualObject * manualObject = new Ogre::ManualObject(0, &test.__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), test.__OgreSceneMgrPtr);

			//manualObject->begin("BaseWhite", Ogre::OperationType::OT_LINE_LIST);

			//// Back
			//manualObject->position(0.0f, 0.0f, 0.0f);
			//manualObject->position(0.0f, 1.0f, 0.0f);
			//manualObject->line(0, 1);

			//manualObject->position(0.0f, 1.0f, 0.0f);
			//manualObject->position(1.0f, 1.0f, 0.0f);
			//manualObject->line(2, 3);

			//manualObject->position(1.0f, 1.0f, 0.0f);
			//manualObject->position(1.0f, 0.0f, 0.0f);
			//manualObject->line(4, 5);

			//manualObject->position(1.0f, 0.0f, 0.0f);
			//manualObject->position(0.0f, 0.0f, 0.0f);
			//manualObject->line(6, 7);

			//// Front
			//manualObject->position(0.0f, 0.0f, 1.0f);
			//manualObject->position(0.0f, 10.0f, 1.0f);
			//manualObject->line(8, 9);

			//manualObject->position(0.0f, 1.0f, 1.0f);
			//manualObject->position(1.0f, 1.0f, 1.0f);
			//manualObject->line(10, 11);

			//manualObject->position(1.0f, 1.0f, 1.0f);
			//manualObject->position(1.0f, 0.0f, 1.0f);
			//manualObject->line(12, 13);

			//manualObject->position(1.0f, 0.0f, 1.0f);
			//manualObject->position(0.0f, 0.0f, 1.0f);
			//manualObject->line(14, 15);

			//// Sides
			//manualObject->position(0.0f, 0.0f, 0.0f);
			//manualObject->position(0.0f, 0.0f, 1.0f);
			//manualObject->line(16, 17);

			//manualObject->position(0.0f, 1.0f, 0.0f);
			//manualObject->position(0.0f, 1.0f, 1.0f);
			//manualObject->line(18, 19);

			//manualObject->position(1.0f, 0.0f, 0.0f);
			//manualObject->position(1.0f, 0.0f, 1.0f);
			//manualObject->line(20, 21);

			//manualObject->position(1.0f, 1.0f, 0.0f);
			//manualObject->position(1.0f, 1.0f, 1.0f);
			//manualObject->line(22, 23);

			//manualObject->end();

			//Ogre::SceneNode *sceneNodeLines = test.__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			//sceneNodeLines->attachObject(manualObject);


		//	sceneNodeLines->scale(4.0f, 4.0f, 4.0f);
		//	sceneNodeLines->translate(-4.5f, -1.5f, 0.0f, Ogre::SceneNode::TS_LOCAL);

		});
	}

    //------------------------------------------------------------------------------------------------
	DrawDynamicLines::~DrawDynamicLines()
    {
		/*m_GraphicsManager.getIntoRendererQueue().push([this](){

			Ogre::MaterialManager::getSingleton().remove("BtOgre/DebugLines");
			Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("BtOgre");
			delete __t_DynamicLines;
		});*/
    }

    //------------------------------------------------------------------------------------------------
	void DrawDynamicLines::addPoint(const Ogre::Vector3 &p)
    {
		if (_swapBuffer)
			_PointsBuf1.push_back(p);
		else
			_PointsBuf2.push_back(p);
    }

    //------------------------------------------------------------------------------------------------
	void DrawDynamicLines::addPoint(float x, float y, float z)
    {
		if (_swapBuffer)
			_PointsBuf1.push_back(Ogre::Vector3(x, y, z));
		else
			_PointsBuf2.push_back(Ogre::Vector3(x, y, z));
    }

    //------------------------------------------------------------------------------------------------
	void DrawDynamicLines::setPoint(unsigned short index, const Ogre::Vector3 &value)
    {
		if (_swapBuffer)
			_PointsBuf1[index] = value;
		else
			_PointsBuf2[index] = value;
    }

    //------------------------------------------------------------------------------------------------
	void DrawDynamicLines::clear()
    {
		if (_swapBuffer)
			_PointsBuf1.clear();
		else
			_PointsBuf2.clear();
    }

    //------------------------------------------------------------------------------------------------
	void DrawDynamicLines::update()
    {
		if (m_rendererisDone)
		{
			m_rendererisDone = false;

			bool tmp = _swapBuffer;

			_swapBuffer = _swapBuffer ? false : true;

			m_GraphicsManager.getIntoRendererQueue().push([this, tmp]() {

				//Ogre::LogManager::getSingleton().logMessage("RQ -> DrawDynamicLines::update");
				__t_DynamicLines->_t_Points = tmp ? _PointsBuf1 : _PointsBuf2;
				__t_DynamicLines->update();

				m_GraphicsManager.getFromRendererQueue().push([this]() {
					m_rendererisDone = true;
				});
			});

		}
    }
}
