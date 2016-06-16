#ifndef _UIFONT_HPP
#define _UIFONT_HPP

#include <XESystem/SystemConfig.hpp>

#include <XEUI/Glyph.hpp>
//#include <XESystem/Logging.hpp>

#include <unordered_map>
#include <memory>

namespace XE {

	class XE_API Font
	{
	public:

		Font():
		//	mRangeBegin(0)
	//		, mRangeEnd(0)
			mSpaceLength(0),
			mLineHeight(0),
			mBaseline(0),
			mLineSpacing(0),
			mLetterSpacing(0),
			mMonoWidth(0)
		{

		}

		//~Font();

		/*! function. getGlyph
		desc.
		Get a glyph (character information) from a specific character.
		note.
		If the character doesn't exist then a null pointer is returned.
		Do not delete the Glyph pointer.
		*/
		inline const FontGlyph* getGlyph(Uint32 character) const
		{
			std::unordered_map<Uint32, FontGlyph>::const_iterator i = mGlyphs.find(character);
			if (i == mGlyphs.end())
			{
			//	LOG(WARNING) << "getGlyph -> glyph not found" << character;
				return 0;
			}

			return &i->second;
		}

		std::unordered_map<Uint32, FontGlyph> mGlyphs;

	/*	Uint32          mRangeBegin
							, mRangeEnd;*/

		float           mSpaceLength,
						mLineHeight,
						mBaseline,
						mLineSpacing,
						mLetterSpacing,
						mMonoWidth;
	};
} // ns XE

#endif