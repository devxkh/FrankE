#include <XERenderer/GUI/RenderableShape.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XERenderer/GUI/WLayer.hpp>

#include <memory>

namespace XE
{
	RenderableShape::RenderableShape(WLayer& wLayer)
		: m_guiRenderer(wLayer.m_guiRenderer)
		, m_layer(wLayer)
		, isDirty(false)

		, _layerRenderer(&m_guiRenderer.getLayerRenderer())
	{
			m_layer.addRenderableShape(this);
	}

	RenderableShape::~RenderableShape()
	{
		m_layer.removeRenderableShape(this);
	}

}