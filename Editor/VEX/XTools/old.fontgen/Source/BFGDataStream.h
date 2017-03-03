// BFG license goes here

#ifndef BFGDATASTREAM_H
#define BFGDATASTREAM_H


#include <fstream>
#include <string>

#include "BFGGlyphData.h"


namespace BFG
{
    // Typedefs
    typedef unsigned int               uint;
    typedef unsigned char              uint8;
    typedef cimg_library::CImg<uint8>  Image;
    
    // Forward declarations
    class Bitmap;
    
    /// Interface for render listeners such as data files
    class DataStream
    {
    public:
        /// Standard constructor
        DataStream () {}
        /// Standard destructor
        virtual ~DataStream () {}
        //--------------------------------------------------
		/// called before drawing beging
		virtual void open(const Bitmap* bitmap) { mBitmap = bitmap; }
        /// Called when drawing begins
        virtual void drawingStarted () { }
        /// Called when drawing a glyph
        virtual void glyphDrawn (const GlyphData& gd) {}
        /// Called when drawing ends
        virtual void drawingFinished () {}
		// Called after drawing ended
		virtual void close () {}
    protected:
        const Bitmap* mBitmap;
    };
    
    /// Placeholder DataStream that doesn't do anything
    class NullDataStream :
        public DataStream
    {
    };
    
    /// QuickGUI data file writer
    class QuickGUIDataFile :
        public DataStream
    {
    public:
        /// Standard constructor
        QuickGUIDataFile () {}
        /// Standard destructor
        virtual ~QuickGUIDataFile () {}
        //--------------------------------------------------
		/// called before drawing beging
		void open(const Bitmap* bitmap);
        /// DataStream: Write bitmap settings to top of file
        void drawingStarted ();
        /// DataStream: Write glyph metrics and kerning data to file
        void glyphDrawn (const GlyphData& gd);
        /// DataStream: Close file
        void drawingFinished ();
		// Called after drawing ended
		void close ();
    private:
        std::ofstream  mFile;
        std::string    mFileName;
    };

    /// Gorilla data file writer
    class GorillaDataFile :
        public DataStream
    {
    public:
        /// Standard constructor
        GorillaDataFile () {}
        /// Standard destructor
        virtual ~GorillaDataFile () {}
        //--------------------------------------------------
		/// called before drawing beging
		void open(const Bitmap* bitmap);
        /// DataStream: Write bitmap settings to top of file
        void drawingStarted ();
        /// DataStream: Write glyph metrics and kerning data to file
        void glyphDrawn (const GlyphData& gd);
        /// DataStream: Close file
        void drawingFinished ();
		// Called after drawing ended
		void close ();
    private:
        std::ofstream  mFile;
        std::string    mFileName;
    };
}


#endif