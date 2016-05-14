#ifndef _WRECTANGLE_HPP
#define _WRECTANGLE_HPP

#include <map>

//#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <sfml/System/Vector2.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>

#include <vector>

namespace XFB_UI
{
	class Colour;
}

namespace Colours
{
	class Colour;
}

namespace XE
{
	//forwarding
	class WLayer;
	struct SpriteData;

	class WRectangle : public RenderableShape
	{
	public:

		WRectangle::WRectangle(WLayer& wlayer, float left, float top, float width, float height);
		WRectangle::~WRectangle();

		void setPosition(const sf::Vector2f& position);
		void setSize(const sf::Vector2f& size);

		void setBackground(const XFB_UI::Colour* colour);
		void setBackground(const Colours::Colour& colour);
		void setBackground(const Ogre::ColourValue& colour);

		sf::Vector2f& getPosition();
		sf::Vector2f& getSize();

		const SpriteData* setBackgroundImage(const std::string& imageName);

		inline WLayer& getLayer() { return m_layer; }

		bool intersects(const Ogre::Vector2& coordinates) const;

		void  background_image(const SpriteData* sprite);
		
		void _refresh() override;

		//internal
		std::vector<Vertex>&  _update() override;
	
	private:

		const SpriteData* _spriteImagePtr;
		Ogre::ColourValue  _backgroundColor;
		sf::Vector2f      _UV[4];

		sf::Vector2f m_position;
		sf::Vector2f m_size;
	};

} // namespace XE


#endif // _WRECTANGLE_HPP