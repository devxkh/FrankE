// BFG license goes here

#ifndef BFGRECT_H
#define BFGRECT_H


namespace BFG
{
    /// A pixel rectangle
    class Rect
    {
    public:
        int left;
        int right;
        int top;
        int bottom;
        //--------------------------------------------------
        /// Standard constructor
        Rect () {}
        /// Value constructor
        Rect (int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
        //--------------------------------------------------
        /// Return the rectangle's height
        int height () { return top - bottom; }
        /// Return the rectangle's width
        int width () { return right - left; }
    };
}


#endif