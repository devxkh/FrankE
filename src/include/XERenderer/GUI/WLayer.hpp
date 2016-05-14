#ifndef _WLAYER_HPP
#define _WLAYER_HPP

#include <XESystem/SystemConfig.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>

#include <vector>
#include <memory>


namespace XE
{
	//forwarding
	class GUIRenderer;
	class LayerRenderer;
	struct AtlasData;
	class RenderableLayer;

	class XE_API WLayer
	{
	public:

		WLayer::WLayer(GUIRenderer& guiRenderer, LayerRenderer& layerRenderer,XE::Uint16 index = 0, const XE::Uint16 atlasId = 0);

		WLayer::~WLayer();

		void setVisible(bool isVisible);
		bool isVisible();

		//change/access only in renderthread!
		//Layer* _t_Layer;

		void update();

		AtlasData& atlasData;


		void addRenderableShape(RenderableShape* renderableShape);
		void removeRenderableShape(RenderableShape* renderableShape);

		LayerRenderer& m_layerRenderer;
		GUIRenderer& m_guiRenderer;

		void setPosition(const Ogre::Vector3& pos);

		std::vector<RenderableShape*>& getRenderableShapes();

		bool isDirty;

		Uint32 width;
		Uint32 height;

	private:

		Ogre::Vector3 m_position;


		RenderableLayer* _t_renderableLayer;

		std::queue<Vertex> m_RenderBuffer;
		
		bool m_isVisible;

		std::vector<RenderableShape*> m_renderableShapes;



		XE::Uint16 m_index;


	};

} // namespace XE


#endif // _WLAYER_HPP