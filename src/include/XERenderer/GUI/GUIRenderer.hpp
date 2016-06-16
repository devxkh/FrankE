#ifndef _GUIRENDERER_HPP
#define _GUIRENDERER_HPP

#include <map>
#include <string>
#include <vector>
#include <memory>
//#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
//#include <Ogre/OgreMain/include/Math/Array/OgreObjectMemoryManager.h>

#include <XESystem/SystemConfig.hpp>
#include <ThirdParty/sfml/include/sfml/System/String.hpp>
#include <ThirdParty/sfml/include/sfml/System/Vector2.hpp>
#include <XEUI/Font.hpp>
#include <XERenderer/GUI/LayerRenderer.hpp>

namespace Ogre {
	class ObjectMemoryManager;
	class SceneManager;
}

namespace sol { class state;  }

namespace XE
{
	//forwarding
	class WScreenRenderable;
	class WScreen;
	class GraphicsManager;
	class TextureAtlas;

	struct AtlasData
	{
		TextureAtlas*  _t_textureAtlasPtr;
		sf::Vector2f    texelOffset;
		sf::Vector2f    textureSize;
	};

	struct SpriteData
	{
		float uvTop, uvLeft, uvRight, uvBottom, spriteWidth, spriteHeight;

		sf::Vector2f    texCoords[4];
	};

	class GUIRenderer
	{
	public:
		GUIRenderer(GraphicsManager& graphicsManager);

		~GUIRenderer();

		void addScreen(WScreen* screen);	

		GraphicsManager& getGraphicsManager() { return m_graphicsManager; }
		
		void registerObject(sol::state& lua);
		
		bool loadAtlas(const std::string& fileName);

		XE::Uint16 GetFontLineHeight(XE::Uint16 font_size) const;

		sf::Vector2i GetTextStringMetrics(const std::basic_string<XE::Uint32>& string, unsigned int font_size) const;

		sf::Vector2i GetTextStringMetrics(const sf::String& string, unsigned int font_size) const;

		const SpriteData* getSprite(const std::string& spriteName);

		const Font* getFont(const XE::Uint32 fontId) const;

		AtlasData& getAtlasData(const XE::Uint16& id);

		LayerRenderer& getLayerRenderer();

		void update();

		//returned pointer only usable in renderthread
		TextureAtlas* _t_getAtlas(const XE::Uint16 atlasId);
		void _t_update();
		void _t_init(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);


		//internal
		sf::Vector2f _whitePixelPos;

	private:
		
		LayerRenderer m_layerRenderer;

		std::map<XE::Uint16, std::unique_ptr<TextureAtlas>> _t_atlas;
		
		void  _calculateCoordinates(sf::Vector2f texelOffset, sf::Vector2f inverseTextureSize);

		void addAtlas(const std::string& atlasName, const std::string& texName, const std::string& ressGroup, XE::Uint16 atlasId = 0);

		sf::Vector2f m_TexelOffset;
	
		std::vector<WScreen*> m_screens;
		GraphicsManager& m_graphicsManager;


		std::map<XE::Uint16, std::unique_ptr<AtlasData>> _atlasData;

		//data for mainthread
		std::map<std::string, std::unique_ptr<SpriteData>> _sprites;
		std::map<XE::Uint32, Font> _fonts;

	};

} // namespace XE


#endif // _GUIRENDERER_HPP