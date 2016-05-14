#include <XERenderer/GUI/WLayer.hpp>

#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/RenderableLayer.hpp>

#include <XERenderer/GUI/Screen.hpp>

#include <Ogre/OgreMain/include/OgreRoot.h>


namespace XE
{
	WLayer::WLayer(GUIRenderer& guiRenderer, LayerRenderer& layerRenderer, XE::Uint16 index, const XE::Uint16 atlasId)
		: m_guiRenderer(guiRenderer)
		, m_layerRenderer(layerRenderer)
		, m_index(index)
		, atlasData(guiRenderer.getAtlasData(atlasId))
		, isDirty(false)
		, _t_renderableLayer(0)
	{
		m_layerRenderer.addWlayer(this);

		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this, index, atlasId]() {

			_t_renderableLayer = m_layerRenderer._t_createRenderableLayer(index, atlasId);
		});
	}

	WLayer::~WLayer()
	{
		m_layerRenderer.removeWlayer(this);

		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this]() {
			m_layerRenderer._t_destroyRenderableLayer(_t_renderableLayer);
		});
	}

	std::vector<RenderableShape*>& WLayer::getRenderableShapes() {
		return m_renderableShapes;
	}

	void WLayer::addRenderableShape(RenderableShape* renderableShape) {

		m_renderableShapes.emplace_back(renderableShape);
	}

	void WLayer::removeRenderableShape(RenderableShape* renderableShape)
	{
		m_renderableShapes.erase(std::find(m_renderableShapes.begin(), m_renderableShapes.end(), renderableShape));
	}

	void WLayer::setPosition(const Ogre::Vector3& pos)
	{
		m_position = pos;

		isDirty = true;
	}
	//void _transform(std::vector<Vertex>& vertices, size_t begin, size_t end)
	//{
	//	Ogre::Vector2 mMaxSize = Ogre::Vector2(600,400);
	//	Ogre::Vector2 halfSize = mMaxSize * 0.5;
	//	for (size_t i = begin; i < end; i++)
	//	{
	//		vertices[i].position.x = (vertices[i].position.x * 0.01f) - halfSize.x;
	//		vertices[i].position.y = (vertices[i].position.y * -0.01f) + halfSize.y;
	//	}
	//}

	void WLayer::update()
	{
		if (m_guiRenderer.getGraphicsManager().GetRenderTask(RenderTaskID::RenderGUI).isDone)
		{
			//Ogre::Vector2 mSize = Ogre::Vector2(800, 600);

		//	Ogre::Vector2 halfSize(width * 0.5 , height * 0.5); //from ScreenRenderable

			Ogre::Vector3 mScale(1, 1, 1);

			float mInvWidth = 1.0f / width; // mSize.x;
			float mInvHeight = 1.0f / height; // mSize.y;
			Ogre::Matrix4         mVertexTransform;

			mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(1, 0, 0, 0));	//top	
	//		mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z)); //left side
	//		mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z)); //bottom
	//		mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(270), Ogre::Vector3::UNIT_Z)); //right side

			int debugoiint = 0;

			for each (auto renderableShape in m_renderableShapes)
			{
				std::vector<Vertex>& tmp = renderableShape->_update();

				for (std::vector<Vertex>::iterator it = tmp.begin(); it != tmp.end(); ++it)
				{
					m_RenderBuffer.push(*it);

					XE::Vertex& tmp = m_RenderBuffer.back();


					tmp.position.x = ((tmp.position.x) * mInvWidth) *2- 0.99999;
					tmp.position.y = ((tmp.position.y) * mInvHeight)  *-2 + 0.99999;

					debugoiint++;
					//>>>>>-------------- 2D --------------------	
				/*	tmp.position.x = ((tmp.position.x) * mInvWidth)  - 1;
					tmp.position.y = ((tmp.position.y) * mInvHeight)  *-1 + 1;
					tmp.position = mVertexTransform * tmp.position;*/
					//<<<<<-------------- 2D --------------------

					//>>>>>-------------- 3D --------------------	
					//	tmp.position.x = (tmp.position.x  -halfSize.x) * 0.01f;
				//	tmp.position.y = (tmp.position.y  -halfSize.y ) *0.01f;
				}
			}

			m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this]() {			
			
				_t_renderableLayer->updateVertices(m_RenderBuffer);

				//TODO move to location after last rendered layer !
				m_guiRenderer.getGraphicsManager().getFromRendererQueue().push([this]() {
					m_guiRenderer.getGraphicsManager().GetRenderTask(RenderTaskID::RenderGUI).isDone = true;
				});
			});

			m_guiRenderer.getGraphicsManager().GetRenderTask(RenderTaskID::RenderGUI).isDone = false;
		}
	}

	void WLayer::setVisible(bool isVisible) { m_isVisible = isVisible; }
	bool WLayer::isVisible() { return m_isVisible; }

} // namespace XE