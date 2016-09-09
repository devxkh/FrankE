#ifndef _WCAPTION_HPP
#define _WCAPTION_HPP

#include <map>

#include <XESystem/SystemConfig.hpp>
#include <sfml/System/Vector2.hpp>
#include <sfml/System/String.hpp>
#include <Ogre/OgreMain/include/OgreColourValue.h>

#include <XERenderer/GUI/RenderableShape.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>

namespace XE
{
	//forwarding
	class WLayer;
	class FontGlyph;
	class Font;

	class WCaption : public RenderableShape
	{
	public:
		WCaption(WLayer& wlayer, Uint16 fontId);
		~WCaption();

		void setPosition(const sf::Vector2f& position);
		void setSize(const float width, const float height);

		sf::Vector2f& getPosition();
		sf::Vector2f& getSize();

		void setText(const sf::String& text);
		const sf::String& getText();

		sf::Vector2i GetTextStringMetrics(const sf::String& string) const;
		
		void _refresh() override;

		bool intersects(const Ogre::Vector2& coordinates) const;

	//	void  _calculateDrawSize(Ogre::Vector2& size);

		//internal
		std::vector<Vertex>&  _update() override;

	private:


		float _getAdvance(const FontGlyph* glyph, float kerning);
		
		Ogre::ColourValue m_color;
		
		const Font* m_font;

	//	sf::Uint16 m_font;
		sf::String m_text;
		sf::Vector2f m_position;
		sf::Vector2f m_size;
	};

} // namespace XE


#endif // _CAPTION_HPP