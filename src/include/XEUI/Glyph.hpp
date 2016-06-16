#ifndef _UIGLYPH_HPP
#define _UIGLYPH_HPP

#include <XESystem/SystemConfig.hpp>
#include <sfml/System/Vector2.hpp>

#include <vector>
#include <memory>

namespace XE {

	/*! struct. Kerning
	desc.
	Distances between two characters next to each other.
	*/
	struct GlyphKerning
	{
		GlyphKerning(XE::Uint32 c, float k)
			: character(c)
			, kerning(k)
		{
		
		}

		XE::Uint32 character;
		float kerning;
	};

	/*! struct. Glyph
	desc.
	Texture and size information about a single character loaded from a TextureAtlas.
	*/
	class FontGlyph 
	{

	public:

		FontGlyph() :
			uvTop(0)
			, uvBottom(0)
			, uvWidth(0)
			, uvHeight(0)
			, uvLeft(0)
			, uvRight(0)
			, glyphWidth(0)
			, glyphHeight(0)
			, glyphAdvance(0)
			, verticalOffset(0)
		{
		}

		~FontGlyph()
		{
		}

		float uvTop
			, uvBottom
			, uvWidth
			, uvHeight
			, uvLeft
			, uvRight
			, glyphWidth
			, glyphHeight
			, glyphAdvance
			, verticalOffset;

		sf::Vector2f    texCoords[4];

		std::vector<GlyphKerning> kerning;

		// Get kerning value of a character to the right of another.
		// Ab -- get the kerning value of b, pass on A.
		inline const float getKerning(unsigned char left_of) const
		{
			if (kerning.size() == 0)
				return 0;

			for (size_t i = 0; i < kerning.size(); i++)
			{
				if (kerning[i].character == left_of)
					return kerning[i].kerning;
			}

			return 0;
		}
	};

} // ns XE
#endif