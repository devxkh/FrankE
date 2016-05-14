#include <XEngine/Components/ScreenComponent.hpp>
#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <sfml/Window.hpp>

namespace XE
{

	ScreenComponent::ScreenComponent(CameraRenderable& camRenderable, sf::Uint32 width, sf::Uint32 height,const XE::Uint16 atlasId)
		: isActive(false)

		, mUIStateManager()
		, wLayer(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable.getGraphicsManager().getGUIRenderer().getLayerRenderer(), 0, 0)
	{
		
		//void createScreen()
		//	{
		//m_Desktop.
		//mUIScreen = new WScreen(mEngine->getUIMgr().getGUIRenderer(), &mCameraController.getOgreCamera(), m_atlasName); //atlas needed to create screen
		//mUIScreen->setSize(m_window->getSize().x, m_window->getSize().y);
		m_Desktop = Desktop::Create(camRenderable.getGraphicsManager().getGUIRenderer(), camRenderable, atlasId);
		//sf::Event event;
		//event.type = sf::Event::Resized;
		//event.size.width = window->getSize().x;
		//event.size.height = window->getSize().y;

		m_Desktop->setSize(width, height);


		//	}

	}


	void  ScreenComponent::setSize(const Uint32 width, const Uint32 height)
	{
		this->width = width;
		wLayer.width = width;

		this->height = height;
		wLayer.height = height;

		m_Desktop->setSize(width, height);
	}

}// ns