// BFG license goes here

#include <assert.h>
#include <cmath>
#include <set>
#include <string>
#include <algorithm>
using std::max;
using std::min;
using std::set;
using std::string;

//#include "cimg/CImg.h"
#include "ft2build.h"
#include FT_FREETYPE_H
//using namespace cimg_library;

#include "BFGColor.h"
#include "BFGDataStream.h"
#include "BFGException.h"
#include "BFGGlyphData.h"
#include "BFGPoint.h"
#include "BFGRect.h"

#include "BFGBitmap.h"

#include "SkylineBinPack.h"

namespace BFG
{
    Bitmap::Bitmap () :
        mAlphabet(),
        mFontSize(0),
        mColor(0,0,0),
        mOutlineColor(0,0,0),
        mOutlineIntensity(0),
        mOutlineWidth(0),
		mPackedBitmapSize(0),
		mBinPack(NULL)
    {
    }
    
    Bitmap::~Bitmap ()
    {
		FreeBinPack();
    }
    
    void Bitmap::setAlphabet (const string& alphabet)
    {
        // Construct non-redundant character set
        uint i;
        set<char> charSet;
        for (i = 0; i < alphabet.length(); ++i)
        {
            char c = alphabet[i];
            // Skip non-printing characters
            if (c ==  ' ') { continue; }
            if (c == '\t') { continue; }
            if (c == '\n') { continue; }
            // Otherwise add to set
            charSet.insert(c);
        }
        //--------------------------------------------------
        // Write character set to alphabet string
        i = 0;
        mAlphabet.resize(charSet.size());
        for (uint j = 0; j < alphabet.length(); ++j)
        {
            char c = alphabet[j];
            if (charSet.count(c)) { mAlphabet[i++] = c; }
        }
    }
    
    void Bitmap::setFileName (const string& fileName)
    {
        mFileName = fileName;
    }

	void Bitmap::setFileSize (const uint fileSize)
    {
        mPackedBitmapSize = fileSize;
    }
    
    void Bitmap::setFontFile (const string& fileName)
    {
        mFontFile = fileName;
    }
    
    void Bitmap::setFontSize (float size)
    {
        mFontSize = size;
    }
    
    void Bitmap::setColor (const Color& color)
    {
        mColor = color;
    }
    
    void Bitmap::setOutlineColor (const Color& color)
    {
        mOutlineColor = color;
    }
    
    void Bitmap::setOutlineIntensity (float intensity)
    {
        mOutlineIntensity = intensity;
    }
    
    void Bitmap::setOutlineWidth (float width)
    {
        mOutlineWidth = width;
    }
    
    void Bitmap::attachDataStream (DataStream* dataStream)
    {
        if (dataStream != NULL) { mDataStreams.insert(dataStream); }
    }
    
	void Bitmap::AllocateBinPack()
	{
		// Size of the packing bin
		mBinPack = new SkylineBinPack(mPackedBitmapSize, mPackedBitmapSize, true);
        // Initialize final packed bitmap image
        mPackedBitmap = Image(mPackedBitmapSize, mPackedBitmapSize, 1, 4, 0);
	}

	void Bitmap::FreeBinPack()
	{
		if (mBinPack)
		{
			delete mBinPack;
			mBinPack = NULL;
		}
	}

	Rect Bitmap::FindBitmapPlaceHolder(const int width, const int height)
	{
		BPRect rDest = mBinPack->Insert(width, height, SkylineBinPack::LevelBottomLeft);
		return Rect(rDest.x, rDest.x+rDest.width, rDest.y, rDest.y+rDest.height);
	}

	void Bitmap::SetPackedBitmapPixel(int x, int y, uint8 r, uint8 g, uint8 b, uint8 a)
	{
		// (r,g,b,a) must be in the 0-255 range
		mPackedBitmap(x, y, 0) = r;
		mPackedBitmap(x, y, 1) = g;
		mPackedBitmap(x, y, 2) = b;
		mPackedBitmap(x, y, 3) = a;
	}

    void Bitmap::generate ()
    {
        // Initialze Freetype
        FT_Error error;
        FT_Library library;
        FT_Face face;
        initFreeType(library, face, mFontFile, mFontSize);
        FT_GlyphSlot slot = face->glyph;
        
        // Find the largest glyph bounding rectangle
        glyphRect    = getGlyphRect(face, mAlphabet);
        glyphWidth   = glyphRect.width()  + 4 * mOutlineWidth;
        glyphHeight  = glyphRect.height() + 4 * mOutlineWidth;
        
        // Let DataStreams know we're starting
        drawingStarted();
        
        // Initialize drawn bitmap
        Image drawBitmap = Image(glyphWidth, glyphHeight, 1, 4);
        
		// draw each bitmap one by one to a small temp bitmap so we can blur and process them
		// without affecting neighbor glyphs and easily crop and get their optimal
		// bounding box size for packing in final bitmap
        for (uint i = 0; i < mAlphabet.length(); ++i)
        {
            char c = mAlphabet[i];
            
			// Load glyph
            error = FT_Load_Char(face, c, FT_LOAD_RENDER);
            if (error) { throw Exception("Error loading char: " + c); }
            
			// Reset temp bitmap back to the glyph color with 0 alpha
	        initBitmap(drawBitmap, TColor(mColor, 0));
            
			// Draw glyph in temp bitmap
            FT_Int drawx = 2 * mOutlineWidth;
			FT_Int drawy = 2 * mOutlineWidth;
            drawGlyph(drawBitmap, slot, drawx, drawy);

			// Draw outline
            if (mOutlineWidth > 0)
            {
                Image outline = getImageChannel(drawBitmap, 3);
                outline.blur(mOutlineWidth/2);
                scalePixels(outline, 1/mOutlineIntensity);
                drawBackground(drawBitmap, outline, mOutlineColor);
            }

			// Now crop to minimal bounding box around glyph. We crop
			// out all the still 0 alpha channel values
			int x, y;
			for (x = 0; x < drawBitmap.width(); ++x)
			{
				for (y = 0; y < drawBitmap.height(); ++y)
				{
					if (drawBitmap(x,y,3) == 0)
					{
						drawBitmap(x,y,0) = 0;
						drawBitmap(x,y,1) = 0;
						drawBitmap(x,y,2) = 0;
					}
				}
			}
			Image croppedImage = drawBitmap.get_autocrop(CImg<uint8>(1,1,1,4,0));

			// Request the packing bin where to pack this glyph
			BPRect rDest = mBinPack->Insert(croppedImage.width(), croppedImage.height(), SkylineBinPack::LevelBottomLeft);

			// Blit the temp cropped bitmap on the final 
			// bitmap at returned packed position
			for (x = 0; x < croppedImage.width(); ++x)
			{
				for (y = 0; y < croppedImage.height(); ++y)
				{
					mPackedBitmap(rDest.x+x, rDest.y+y, 0) = croppedImage(x,y,0);
					mPackedBitmap(rDest.x+x, rDest.y+y, 1) = croppedImage(x,y,1);
					mPackedBitmap(rDest.x+x, rDest.y+y, 2) = croppedImage(x,y,2);
					mPackedBitmap(rDest.x+x, rDest.y+y, 3) = croppedImage(x,y,3);
				}
			}
            
			// Inform DataStreams
			glyphDrawn(c, face, rDest.x, rDest.y, rDest.width, rDest.height);
        }

        // Tell DataStreams we're done
        drawingFinished();
    }
    
    void Bitmap::save ()
    {
		mPackedBitmap.save(mFileName.data());
    }
    
    void Bitmap::drawingStarted ()
    {
        for (std::set<DataStream*>::iterator it = mDataStreams.begin(); it != mDataStreams.end(); ++it)
        {
            (*it)->drawingStarted();
        }
    }
    
    void Bitmap::glyphDrawn (char c, FT_Face& face, FT_Int x, FT_Int y, FT_Int w, FT_Int h)
    {
        // Initialize useful variables
        FT_GlyphSlot slot = face->glyph;
        FT_UInt cIndex = FT_Get_Char_Index(face, c);
        
		// Construct GlyphData
		// Note: Not sure if this still work for QuickGUI data file
        Rect rect = Rect(x, x+w, y, y+h);
		Point origin = Point(slot->bitmap_left, slot->bitmap_top-(2*mOutlineWidth));
        GlyphData gd = GlyphData(c, rect, origin);

		/* ORIGINAL CODE
        Rect rect = Rect(
            x + slot->bitmap_left - mOutlineWidth,
            x + slot->bitmap_left + mOutlineWidth + slot->bitmap.width,
            y - slot->bitmap_top  - mOutlineWidth,
            y - slot->bitmap_top  + mOutlineWidth + slot->bitmap.rows);
        Point origin = Point(x,y);
        GlyphData gd = GlyphData(c, rect, origin);
		*/
        
        // Construct KerningData
        for (uint i = 0; i < mAlphabet.length(); ++i)
        {
            char c1 = mAlphabet[i];
            FT_UInt c1Index = FT_Get_Char_Index(face, c1);
            FT_Vector delta;
            FT_Get_Kerning(face, c1Index, cIndex, FT_KERNING_DEFAULT, &delta);
            KerningData kd = KerningData(c1, c, delta.x >> 6, 0, delta.y >> 6, 0);
            gd.setKerningData(c1, kd);
        }
        
        // Notify DataStreams
        for (std::set<DataStream*>::iterator it = mDataStreams.begin(); it != mDataStreams.end(); ++it)
        {
            (*it)->glyphDrawn(gd);
        }
    }
    
    void Bitmap::drawingFinished ()
    {
        for (std::set<DataStream*>::iterator it = mDataStreams.begin(); it != mDataStreams.end(); ++it)
        {
            (*it)->drawingFinished();
        }
    }
    
    void Bitmap::initFreeType (FT_Library& library, FT_Face& face, const string& fontFile, uint fontSize)
    {
        // Initialize library
        FT_Error error;
        error = FT_Init_FreeType(&library);
        if (error) { throw Exception("Problem loading FreeType Library!");  }
        
        // Load the font
        error = FT_New_Face(library, fontFile.data(), 0, &face);
        if (error == FT_Err_Unknown_File_Format) { throw Exception("Unkown font file format!"); }
        else if (error) { throw Exception("Could not load font file '"+fontFile+"'!"); }
        
        // Set font size
        error = FT_Set_Char_Size(face, 72 * fontSize, 0, 0, 0);
        if (error) { throw Exception("FreeType could not set character size!  God help you!"); }
    }
    
    Rect Bitmap::getGlyphRect (FT_Face& face, const string& alphabet)
    {
        Rect rect = Rect(0,0,0,0);
        FT_GlyphSlot slot = face->glyph;
        FT_Bitmap& bitmap = slot->bitmap;
        for (uint i = 0; i < alphabet.length(); ++i)
        {
            // Load glyph
            char c = alphabet[i];
            FT_Load_Char(face, c, FT_LOAD_RENDER);
            // Expand rectangle if necessary
            rect.left    = min(rect.left,    slot->bitmap_left);
            rect.top     = max(rect.top,     slot->bitmap_top);
            rect.right   = std::max(rect.right, (int)bitmap.width - (int)slot->bitmap_left);
            rect.bottom  = std::min(rect.bottom,  slot->bitmap_top - (int)bitmap.rows);
        }
        return rect;
    }
    
    uint Bitmap::getDimensions (uint count, uint width, uint height)
    {
        uint power = 0;
        while (true)
        {
            uint length = pow((float)2, (float)++power);
            uint x = 0, y = 0;
            for (uint i = 0; i < count; ++i)
            {
                x += width;
                if (x > length) { x = width; y += height; }
                if (y > length) { break; }
            }
            if (y + height <= length) { return length; }
        }
    }
    
    void Bitmap::initBitmap (Image& bitmap, const TColor& color)
    {
        // Initialize image to a transparent constant color
        for (int x = 0; x < bitmap.width(); ++x)
        {
            for (int y = 0; y < bitmap.height(); ++y)
            {
                bitmap(x,y,0) = 255 * color.r;
                bitmap(x,y,1) = 255 * color.g;
                bitmap(x,y,2) = 255 * color.b;
                bitmap(x,y,3) = 255 * color.a;
            }
        }
    }

    void Bitmap::drawGlyph (Image& target, FT_GlyphSlot slot, FT_Int x, FT_Int y)
    {
        // Draw glyph to image with bottom left at <x,y>
        //x += slot->bitmap_left;
        //y -= slot->bitmap_top;
        FT_Bitmap& bitmap = slot->bitmap;
        int width = min((int)bitmap.width, target.width() - x);
        int height = min((int)bitmap.rows, target.height() - y);
        
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                target(x+i, y+j, 3) |= bitmap.buffer[j * bitmap.width + i];
            }
        }
    }
    
    Image Bitmap::getImageChannel (Image& source, uint channel)
    {
        // Construct image from a single channel of source
        Image image = Image(source.width(), source.height());
        for (int x = 0; x < source.width(); ++x)
        {
            for (int y = 0; y < source.height(); ++y)
            {
                image(x,y) = source(x,y,channel);
            }
        }
        return image;
    }

    void Bitmap::scalePixels (Image& image, float power)
    {
        // Raise each pixel to power
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float alpha = image(x,y) / 255.0;
                image(x,y) = 255 * pow(alpha,power);
            }
        }
    }
    
    void Bitmap::drawBackground (Image& image, Image& background, const Color& color)
    {
        // Draw background underneath image in color
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float ta = image(x,y,3) / 255.0;
                float sa = background(x,y) / 255.0;
                image(x,y,0) = image(x,y,0) * ta + 255 * color.r * (1 - ta);
                image(x,y,1) = image(x,y,1) * ta + 255 * color.g * (1 - ta);
                image(x,y,2) = image(x,y,2) * ta + 255 * color.b * (1 - ta);
                image(x,y,3) = 255 * (ta + sa * (1 - ta));
            }
        }
    }
}