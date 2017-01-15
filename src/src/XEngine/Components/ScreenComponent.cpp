#include <XEngine/Components/ScreenComponent.hpp>
#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XERenderer/GUI/WLayer.hpp>
#include <SDL.h>

namespace XE
{

	ScreenComponent::ScreenComponent(CameraRenderable& camRenderable, SDL_Window* window, const Uint16 atlasId)
		: isActive(false)
		, mUIStateManager(0)
		, wLayer(0)
	{
		mUIStateManager = std::make_shared<UIStateManager>();
		wLayer = std::make_shared<WLayer>(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable.getGraphicsManager().getGUIRenderer().getLayerRenderer(), 0, 0);
		m_Desktop = Desktop::Create(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable, atlasId);
		SDL_GetWindowSize(window, &width, &height);
	}

	ScreenComponent::ScreenComponent(CameraRenderable& camRenderable, Uint32 width, Uint32 height,const Uint16 atlasId)
		: isActive(false)
		, mUIStateManager(0)
		, wLayer(0)
	{		
		mUIStateManager = std::make_shared<UIStateManager>();
		wLayer = std::make_shared<WLayer>(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable.getGraphicsManager().getGUIRenderer().getLayerRenderer(), 0, 0);
		m_Desktop = Desktop::Create(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable, atlasId);
		m_Desktop->setSize(width, height);
	}

	ScreenComponent::~ScreenComponent()
	{

	}

	void  ScreenComponent::setSize(const Uint32 width, const Uint32 height)
	{
		this->width = width;
		wLayer->width = width;

		this->height = height;
		wLayer->height = height;

		m_Desktop->setSize(width, height);
	}

}// ns