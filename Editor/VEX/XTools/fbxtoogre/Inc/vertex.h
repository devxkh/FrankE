////////////////////////////////////////////////////////////////////////////////
// vertex.h
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
// Port to 3D Studio Max - Modified original version
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : December 10th, 2007
////////////////////////////////////////////////////////////////////////////////
// Port to FBX - Modified original version
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : January 8th, 2012
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                                                                *
*   This program is free software; you can redistribute it and/or modify         *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or            *
*   (at your option) any later version.                                          *
*                                                                                *
**********************************************************************************/

#ifndef _VERTEX_H
#define _VERTEX_H

/***** structure for uvsets info *****/
    typedef struct uvsettag
    {
        short size;					//number of coordinates (between 1 and 3)
    } uvset;
    /***** structure for texture coordinates *****/
    typedef struct texcoordstag
    {
        float u, v, w;				//texture coordinates	
    } texcoord;

    /***** structure for vertex bone assignements *****/
    typedef struct vbatag
    {
        float weight;	//weight
        int jointIdx;	//index of associated joint
    } vba;
/*
    typedef struct Point3tag
    {
        double x, y, z;
    } Point3;
*/
    class Point3 
    {
    public:
        //constructor
        Point3(){x=0;y=0;z=0;}
        Point3(double xi, double yi, double zi){x=xi;y=yi;z=zi;}
        ~Point3(){}
        double x, y, z;
        void Normalize(){
            double l = sqrt(x*x + y*y + z*z);
            x= x/l;
            y= y/l;
            z= z/l;
        }
    };
    class BoundingBox
    {
    public:
        BoundingBox(){min = Point3(); max = Point3(); bIsFirst = true;}
        void merge(const Point3& p)
        {
            if( bIsFirst )
            {
                min = p;
                max = p;
                bIsFirst = false;
            }
            else
            {
                min.x = std::min(p.x, min.x);
                min.y = std::min(p.y, min.y);
                min.z = std::min(p.z, min.z);
                max.x = std::max(p.x, max.x);
                max.y = std::max(p.y, max.y);
                max.z = std::max(p.z, max.z);
            }
        }
        void clear()
        {
            bIsFirst = true;
        }
        bool isEmpty()
        {
            return getBiggestAxis() < PRECISION;
        }
        double getBiggestAxis()
        {
            double maxAxis = std::max(max.x - min.x, max.y - min.y);
            return std::max(maxAxis, max.z - min.z);
        }
        Point3 min,max;
    private:
        bool bIsFirst;
    };


    /***** structure for vertex data *****/
    typedef struct vertextag
    {
        double x, y, z;						//vertex coordinates
        Point3 n;							//vertex normal (Doug Perkowski - 11/16/2007 - modified to replace Maya-specific MVector)
        float r,g,b,a;						//vertex colour
        std::vector<texcoord> texcoords;	//vertex texture coordinates
        std::vector<vba> vbas;				//vertex bone assignements
        long index;							//vertex index in the maya mesh to which this vertex refers
    } vertex;

    /***** structure for vertex info *****/
    // used to hold indices to access MFnMesh data
    typedef struct vertexInfotag
    {
        int pointIdx;				//index to points list (position)
        int normalIdx;				//index to normals list
        float r,g,b,a;				//colour
        std::vector<float> u;		//u texture coordinates
        std::vector<float> v;		//v texture coordinates
        std::vector<float> vba;		//vertex bone assignements
        std::vector<int> jointIds;	//ids of joints affecting this vertex
        int next;					//index of next vertex with same position
    } vertexInfo;

    /***** structure for face info *****/
    typedef struct facetag
    {
        long v[3];		//vertex indices
    } face;

    /***** array of face infos *****/
    typedef std::vector<face> faceArray;

#endif
