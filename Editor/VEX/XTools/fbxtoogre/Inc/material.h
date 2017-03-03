////////////////////////////////////////////////////////////////////////////////
// material.h
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

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "paramList.h"

namespace FxOgreFBX
{

    typedef enum {MT_SURFACE_SHADER,MT_LAMBERT,MT_PHONG,MT_BLINN,MT_CGFX} MaterialType;

    typedef enum {TOT_REPLACE,TOT_MODULATE,TOT_ADD,TOT_ALPHABLEND} TexOpType;

    typedef enum {TAM_CLAMP,TAM_BORDER,TAM_WRAP,TAM_MIRROR} TexAddressMode;


    class Point4
    {
        public:
            Point4(){};
            ~Point4(){};
            Point4(float iw, float ix, float iy, float iz)
            {
                w = iw;
                x = ix;
                y = iy;
                z = iz;
            }
            float w, x, y, z;
    };
    class Texture
    {
    public:
        //constructor
        Texture() {
            scale_u = scale_v = 1;
            scroll_u = scroll_v = 0;
            rot = 0;
            am_u = am_v = TAM_CLAMP;
            // Most textures like normal, specular, bump, etc. can't just
            // be summed into the diffuse channel and need
            bCreateTextureUnit = false;
        }
        //destructor
        ~Texture(){};
    
        //public members
        std::string filename;
        std::string absFilename;
        TexOpType opType;
        std::string uvsetName;
        int uvsetIndex;
        bool bCreateTextureUnit;
        TexAddressMode am_u,am_v;
        double scale_u,scale_v;
        double scroll_u,scroll_v;
        double rot;
    };


    /***** Class Material *****/
    class Material
    {
    public:
        //constructor
        Material();
        //destructor
        ~Material();
        //get material name
        std::string& name();
        //clear material data
        void clear();

        //load material data
        bool load( FbxSurfaceMaterial* pGameMaterial,std::vector<int>& uvsets,ParamList& params);
        //write material data to Ogre material script
        bool writeOgreScript(ParamList &params);

    public:

        std::string m_name;
        MaterialType m_type;
        Point4 m_ambient, m_diffuse, m_specular, m_emissive;
        bool m_lightingOff;
        bool m_isTransparent;
        bool m_isTextured;
        bool m_isMultiTextured;
        std::vector<Texture> m_textures;

    };

};	//end of namespace

#endif
