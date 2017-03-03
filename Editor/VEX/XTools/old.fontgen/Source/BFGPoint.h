// BFG license goes here

#ifndef BFGPOINT_H
#define BFGPOINT_H


namespace BFG
{
    /// A pixel location
    class Point
    {
    public:
        int x;
        int y;
        //--------------------------------------------------
        /// Standard constructor
        Point () {}
        /// Value constructor
        Point (int X, int Y) : x(X), y(Y) {}
        /// Standard destructor
        virtual ~Point () {}
    };
}


#endif