#ifndef _WMarkup_HPP
#define _WMarkup_HPP

#include <map>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <sfml/System/Vector2.hpp>
#include <sfml/System/String.hpp>

namespace XE
{
	//forwarding
	class MarkupText;
	class GUIRenderer;
	class WLayer;

	class WMarkup
	{
	public:
		WMarkup(WLayer& wlayer);
		~WMarkup();

		void setPosition(sf::Vector2f position);
		void setSize(const float width, const float height);

		sf::Vector2f& getPosition();
		sf::Vector2f& getSize();

		void SetText(const sf::String& text);
	private:
		//change/access only in renderthread!
		MarkupText* _t_markuptext;

		GUIRenderer& m_guiRenderer;
		WLayer& m_layer;

		sf::Uint16 m_font;
		sf::String m_text;
		sf::Vector2f m_position;
		sf::Vector2f m_size;

	};

} // namespace XE


#endif // _CAPTION_HPP