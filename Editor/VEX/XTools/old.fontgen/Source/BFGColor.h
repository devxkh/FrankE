// BFG license goes here

#ifndef BFGCOLOR_H
#define BFGCOLOR_H


#include <string>


namespace BFG
{
    /// RGB color without transparency
    class Color
    {
    public:
        float r;
        float g;
        float b;
        //------------------------------------------------------
        /// Standard constructor
        Color ();
        /// Value constructor
        Color (float R, float G, float B);
        /// String constructor
        Color (const std::string& value);
        //------------------------------------------------------
        /// Bounded load
        void load (float R, float G, float B);
        /// Return "r g b"
        std::string toString ();
    };
    
    /// RGBA color with transparency
    class TColor
    {
    public:
        float r;
        float g;
        float b;
        float a;
        //------------------------------------------------------
        /// Standard constructor
        TColor ();
        /// Value constructor
        TColor (float R, float G, float B, float A);
        /// RGB + Alpha constructor
        TColor (const Color& color, float alpha);
        //------------------------------------------------------
        /// Bounded load
        void load (float R, float G, float B, float A);
        /// Return "r g b a"
        std::string toString ();
    };
}


#endif