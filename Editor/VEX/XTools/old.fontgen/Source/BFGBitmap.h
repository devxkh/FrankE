// BFG license goes here

#ifndef BFGBITMAP_H
#define BFGBITMAP_H


#include <set>
#include <string>

//#include "cimg/CImg.h"
#include "ft2build.h"
#include FT_FREETYPE_H

#include "BFGColor.h"
#include "BFGRect.h"

// Forward declarations
class SkylineBinPack;

namespace BFG
{
    // Typedefs
    typedef unsigned int               uint;
    typedef unsigned char              uint8;
    typedef cimg_library::CImg<uint8>  Image;
    
    // Forward declarations
    class DataStream;
    
    /// The main bitmap generator class
    class Bitmap
    {
    public:
        /// Standard constructor
        Bitmap ();
        /// Standard destructor
        virtual ~Bitmap ();
        //--------------------------------------------------
        /// Set the output file
        void setFileName (const std::string& fileName);
        /// Set the output file size
        void setFileSize (const uint fileSize);
        /// Set the alphabet to be rendered
        /// @note Whitespace and duplicate characters are ignored.
        void setAlphabet (const std::string& alphabet);
        /// Set the font that will be used to create the bitmap
        void setFontFile (const std::string& fileName);
        /// Set the font size to use (roughly pixel height)
        void setFontSize (float size);
        /// Set the foreground color of the font
        void setColor (const Color& color);
        /// Set the background (shadow) color
        void setOutlineColor (const Color& color);
        /// Set the intensity (darkness) of the outline
        void setOutlineIntensity (float intensity);
        /// Set the width (size) of the outline
        void setOutlineWidth (float width);
		/// bin pack
		void AllocateBinPack();
		void FreeBinPack();
        //--------------------------------------------------
        /// Set a DataStream to be notified of render events
        void attachDataStream (DataStream* dataStream);
        /// Generate the bitmap using the current settings
        void generate ();
        /// Save the generated bitmap to a file
        void save ();
        //--------------------------------------------------
        /// Return the name of the output file
        std::string getFileName () const { return mFileName; }
        /// Return the alphabet
        const std::string& getAlphabet () const { return mAlphabet; }
        /// Return the font file
        std::string getFontFile () const { return mFontFile; }
        /// Return the font size
        float getFontSize () const { return mFontSize; }
        /// Return the color
        Color getColor () const { return mColor; }
        /// Return the outline color
        Color getOutlineColor () const { return mOutlineColor; }
        /// Return the outline intensity
        float getOutlineIntensity () const { return mOutlineIntensity; }
        /// Return the outline width
        float getOutlineWidth () const { return mOutlineWidth; }

		uint getGlyphHeight() const { return glyphHeight; }
		uint getGlyphWidth() const { return glyphWidth; }
		Rect getGlyphRect() const { return glyphRect; }

		Rect FindBitmapPlaceHolder(const int width, const int height);
		void SetPackedBitmapPixel(int x, int y, uint8 r, uint8 g, uint8 b, uint8 a);
    private:
        std::string            mFileName;
        std::string            mAlphabet;
        std::string            mFontFile;
        float                  mFontSize;
        Color                  mColor;
        Color                  mOutlineColor;
        float                  mOutlineIntensity;
        float                  mOutlineWidth;

		SkylineBinPack*        mBinPack;	

		Rect glyphRect;
        uint glyphWidth;
        uint glyphHeight;

        //--------------------------------------------------
		//Image                  mDrawBitmap;		// Bitmap where we draw glyphs evenly and blur
        
		int                    mPackedBitmapSize; // Texture will be mPackedBitmapSize x mPackedBitmapSize
		Image                  mPackedBitmap;	// Packed bitmap of the already drawn glyphs

		std::set<DataStream*>  mDataStreams;
        //--------------------------------------------------
        /// Notify DataStreams that drawing began
        void drawingStarted ();
        /// Notify DataStreams that a glyph is being rendered
        void glyphDrawn (char c, FT_Face& face, FT_Int x, FT_Int y, FT_Int w, FT_Int h);
        /// Notify DataStreams that drawing ended
        void drawingFinished ();
        //--------------------------------------------------
        /// Initialize FreeType library
        void initFreeType (FT_Library& library, FT_Face& face, const string& fontFile, uint fontSize);
        /// Return a bounding rectangle for all glyphs in the font
        Rect getGlyphRect (FT_Face& face, const std::string& alphabet);
        /// Return the minimum bitmap side length
        uint getDimensions (uint count, uint width, uint height);
        /// Initialize an RGBA bitmap with a constant pixel value
        void initBitmap (Image& bitmap, const TColor& color);
        /// Draw a glyph to the target image
        /// @arg (x,y)   bottom left corner
        void drawGlyph (Image& target, FT_GlyphSlot slot, FT_Int x, FT_Int y);
        /// Return a single channel of the source image as a new image
        Image getImageChannel (Image& source, uint channel);
        /// Modify image by raising each pixel value to a power
        void scalePixels (Image& image, float power);
        /// Draw colored background mask underneath the destination image
        void drawBackground (Image& image, Image& background, const Color& color);
    };
}


#endif