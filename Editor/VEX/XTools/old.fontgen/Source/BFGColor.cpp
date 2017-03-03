// BFG license goes here


#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
using std::max;
using std::min;
using std::set;
using std::stringstream;
using std::string;

//#include "cimg/CImg.h"
#include "ft2build.h"
#include FT_FREETYPE_H
//using namespace cimg_library;

#include "BFGBitmap.h"


namespace BFG
{
    Color::Color ()
    {
    }
    
    Color::Color (float R, float G, float B)
    {
        load(R,G,B);
    }
    
    Color::Color (const std::string& value)
    {
        sscanf(value.data(), "%f %f %f", &r, &g, &b);
        load(r,g,b);
    }
    
    void Color::load (float R, float G, float B)
    {
        r = min(1.0f, max(0.0f, R));
        g = min(1.0f, max(0.0f, G));
        b = min(1.0f, max(0.0f, B));
    }
    
    string Color::toString ()
    {
        stringstream value;
        value << r << " " << g << " " << b;
        return value.str();
    }
    
    TColor::TColor ()
    {
    }
    
    TColor::TColor (float R, float G, float B, float A)
    {
        load(R,G,B,A);
    }
    
    TColor::TColor (const Color& color, float alpha)
    {
        load(color.r, color.g, color.b, alpha);
    }
    
    void TColor::load (float R, float G, float B, float A)
    {
        r = min(1.0f, max(0.0f, R));
        g = min(1.0f, max(0.0f, G));
        b = min(1.0f, max(0.0f, B));
        a = min(1.0f, max(0.0f, A));
    }
    
    string TColor::toString ()
    {
        stringstream value;
        value << r << " " << g << " " << b << " " << a;
        return value.str();
    }
}