#ifndef _ATLASDATA_HPP
#define _ATLASDATA_HPP


#include <XESystem/SystemConfig.hpp>
#include <sfml/System/Vector2.hpp>
#include <map>
#include <memory>

namespace XE
{
	struct SpriteData
	{
		Uint32 uvTop, uvLeft, uvRight, uvBottom, spriteWidth, spriteHeight;

		sf::Vector2i    texCoords[4];
	};

	struct AtlasData
	{
		const SpriteData* getSprite(const std::string& spriteName);
		const Font* getFont(const XE::Uint32 fontId) const;

		std::map<std::string, std::unique_ptr<SpriteData>> _sprites;
		std::map<XE::Uint32, std::unique_ptr<Font>> _fonts;
	};
}

#endif
