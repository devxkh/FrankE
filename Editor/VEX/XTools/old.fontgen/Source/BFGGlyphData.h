// BFG license goes here

#ifndef BFGGLYPHDATA_H
#define BFGGLYPHDATA_H


#include <map>
#include <string>

#include "BFGPoint.h"
#include "BFGRect.h"


namespace BFG
{
    /// Stores kerning data for char2 following char1
    /// @note Since KerningData objects can be returned for character pairs that
    /// don't contain kerning information, "kerned=false" means no kerning and
    /// the values should be ignored because they probably weren't initialized.
    class KerningData
    {
    public:
        bool  kerned;
        char  char1;
        char  char2;
        int   left;
        int   right;
        int   top;
        int   bottom;
        //--------------------------------------------------
        /// Standard constructor
        KerningData () : kerned(false) {}
        /// Value constructor
        KerningData (char c1, char c2, int l, int r, int t, int b) :
            kerned(true),
            char1(c1),
            char2(c2),
            left(l),
            right(r),
            top(t),
            bottom(b)
        { if (!l && !r && !t && !b) { kerned = false; } }
        /// Standard destructor
        virtual ~KerningData () {}
    };
    
    /// Stores glyph's metrics
    class GlyphData
    {
    public:
        typedef std::map<char, KerningData> KerningMap;
        //--------------------------------------------------
        /// Standard constructor
        GlyphData () {}
        /// Value constructor
        GlyphData (char character, const Rect& textureRect, const Point& textureOrigin) :
            mCharacter(character),
            mTextureRect(textureRect),
            mTextureOrigin(textureOrigin)
        {}
        /// Standard destructor
        virtual ~GlyphData () {}
        //--------------------------------------------------
        /// Return the character represented by the glyph
        char getCharacter () const { return mCharacter; }
        /// Return the texture rectangle the glyph occupies
        Rect getTextureRect () const { return mTextureRect; }
        /// Return the texture coordinates of the glyph's bottom-left corner
        Point getTextureOrigin () const { return mTextureOrigin; }
        /// Return KerningData for the glyph following glyph <c>
        KerningData getKerningData (char c) const { return const_cast<KerningMap&>(mKerningData)[c]; }
        /// Set the KerningData for the glyph following glyph <c>
        void setKerningData (char c, const KerningData& kd) { mKerningData[c] = kd; }
    private:
        char        mCharacter;
        Rect        mTextureRect;
        Point       mTextureOrigin;
        KerningMap  mKerningData;
    };
}


#endif