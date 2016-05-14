#include <XERenderer/GUI/WMarkup.hpp>
#include <XERenderer/GUI/WLayer.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>

namespace XE
{

	WMarkup::WMarkup(WLayer& wLayer) :
		m_guiRenderer(wLayer.m_guiRenderer)
		, m_layer(wLayer)
		, m_font(9)
	{
		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this](){

			//default glyph index (index = fontsize) -> todo make set glyphindex function in gorilla
		//	_t_markuptext = m_layer._t_Layer->createMarkupText(m_font, 0, 0, "");

		});
	}

	WMarkup::~WMarkup()
	{
		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this](){
		//	m_layer._t_Layer->destroyMarkupText(_t_markuptext);
		});
	}

	void WMarkup::setPosition(sf::Vector2f position)
	{
		m_position = position;

		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this](){
		/*	_t_markuptext->left(m_position.x);
			_t_markuptext->top(m_position.y);*/
		});
	}
	void WMarkup::setSize(const float width, const float height)	{

		m_size.x = width;
		m_size.y = height;

		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this](){
		//	_t_markuptext->size(m_size.x, m_size.y);
		});
	}

	sf::Vector2f& WMarkup::getPosition()	{
		return m_position;
	}
	sf::Vector2f& WMarkup::getSize()	{
		return m_size;
	}

	void WMarkup::SetText(const sf::String& text)
	{
	//	m_text = text;
		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this, text](){
			sf::String tmp = text; //reference to m_text is lost - need to make a copy
		//	_t_markuptext->text(tmp);
		});

	}

} // namespace XE