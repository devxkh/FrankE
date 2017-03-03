// BFG license goes here


#include <fstream>
#include <string>
using std::ofstream;
using std::string;
using std::endl;

#include "BFGBitmap.h"
#include "BFGGlyphData.h"
#include "BFGPoint.h"
#include "BFGRect.h"

#include "BFGDataStream.h"


namespace BFG
{
	// QuickGUI data file
	void QuickGUIDataFile::open(const Bitmap* bitmap)
	{
        mBitmap = bitmap;

		// Derive data filename from bitmap file
		mFileName = mBitmap->getFileName();
		mFileName = mFileName.substr(0, mFileName.find_last_of("."));
		mFileName += ".font";
		
		mFile.open(mFileName.data());
	}

	void QuickGUIDataFile::drawingStarted()
    {
        mFile << "Bitmap: " << mBitmap->getFileName() << endl;
        mFile << "Font: " << mBitmap->getFontFile() << endl;
        mFile << "Size: " << mBitmap->getFontSize() << endl;
        mFile << "Color: " << mBitmap->getColor().toString() << endl;
        mFile << "OutlineColor: " << mBitmap->getOutlineColor().toString() << endl;
        mFile << "OutlineWidth: " << mBitmap->getOutlineWidth() << endl;
        mFile << "OutlineIntensity: " << mBitmap->getOutlineIntensity() << endl;
        mFile << "Alphabet: " << mBitmap->getAlphabet() << endl;
        mFile << endl;
        mFile << "GlyphData:" << endl;
    }
    
    void QuickGUIDataFile::glyphDrawn (const GlyphData& gd)
    {
        // Glyph data
        char c = gd.getCharacter();
        Rect rect = gd.getTextureRect();
        Point origin = gd.getTextureOrigin();
        mFile << "  " << c << ": "
            << rect.left    << " "
            << rect.right   << " "
            << rect.top     << " "
            << rect.bottom  << " "
            << origin.x     << " "
            << origin.y     << "\n";
        //--------------------------------------------------
        // Kerning data
        const string& alphabet = mBitmap->getAlphabet();
        for (uint i = 0; i < alphabet.length(); ++i)
        {
            char c1 = alphabet[i];
            KerningData kd = gd.getKerningData(c1);
            if (!kd.kerned) { continue; }
            mFile << "    " << c1 << ": "
                << kd.left    << " "
                << kd.right   << " "
                << kd.top     << " "
                << kd.bottom  << "\n";
        }
    }
    
    void QuickGUIDataFile::drawingFinished ()
    {
    }

	void QuickGUIDataFile::close()
	{
        mFile.close();
	}

	// Gorilla data file

	void GorillaDataFile::open(const Bitmap* bitmap)
	{
        mBitmap = bitmap;
        
		// Derive data filename from bitmap file
		mFileName = mBitmap->getFileName();
		mFileName = mFileName.substr(0, mFileName.find_last_of("."));
		mFileName += ".gorilla";
		mFile.open(mFileName.data());
	}

    void GorillaDataFile::drawingStarted()
    {
		mFile << "[Font." << mBitmap->getFontSize() << "]" << endl;
        mFile << "lineheight " << mBitmap->getGlyphHeight() << endl;
        mFile << "spacelength " << (int)(mBitmap->getGlyphWidth()*0.6f) << endl;
		//mFile << "baseline " << mBitmap->getGlyphRect().height() << endl;
		mFile << "baseline " << 0 << endl;
		mFile << "kerning -0.5" << endl;
		mFile << "letterspacing 0" << endl;
		mFile << "monowidth " << mBitmap->getFontSize()+1 << endl;
		mFile << "range " << (int)mBitmap->getAlphabet()[0] << " " << (int)mBitmap->getAlphabet()[mBitmap->getAlphabet().length()-1] << endl;
    }
    
    void GorillaDataFile::glyphDrawn (const GlyphData& gd)
    {
        // Glyph data
        char c = gd.getCharacter();
        Rect rect = gd.getTextureRect();
        Point origin = gd.getTextureOrigin();
        mFile << "glyph_" << (int)c << " "
            << rect.left    << " "
            << rect.top     << " "
			<< rect.right-rect.left << " "
            << rect.bottom-rect.top << endl;

		mFile << "verticaloffset_" << (int)c << " " << -gd.getTextureOrigin().y << endl;

        //--------------------------------------------------
        // Kerning data
        const string& alphabet = mBitmap->getAlphabet();
        for (uint i = 0; i < alphabet.length(); ++i)
        {
            char c1 = alphabet[i];
            KerningData kd = gd.getKerningData(c1);
            if (!kd.kerned) { continue; }
			mFile << "kerning_" << (int)kd.char2 << " " << (int)kd.char1 << " " << kd.right-kd.left << endl;
        }
    }
    
    void GorillaDataFile::drawingFinished ()
    {
		// Blank line
		mFile << endl;
    }

	void GorillaDataFile::close()
	{
		// All font data filled. Last thing to do
		// is find a placeholder for the whitepixel
		// which will be a 3x3 pixel with the center
		// one as being the used whitepixel.
		Bitmap* bmp = const_cast<Bitmap*>(mBitmap);
		Rect loc = bmp->FindBitmapPlaceHolder(3, 3);
		for(int y=0; y<3; ++y)
		{
			for(int x=0; x<3; ++x)
			{
				bmp->SetPackedBitmapPixel(loc.left+x, loc.top+y, 255, 255, 255, 255);
			}
		}

		// Write the [texture] section
		mFile<< "[Texture]" << endl;
        mFile << "file " << mBitmap->getFileName() << endl;
		mFile << "whitepixel " << loc.left+1 << " " << loc.top+1 << endl;
		mFile << endl;

        mFile.close();
	}
}