////////////////////////////////////////////////////////////////////////////////
// scene.h
// Author     : Doug Perkowski
// Start Date : March 27th, 2008
// Copyright  : Copyright (c) 2002-2014 OC3 Entertainment, Inc.
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                                                                *
*   This program is free software; you can redistribute it and/or modify         *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or            *
*   (at your option) any later version.                                          *
*                                                                                *
**********************************************************************************/
#ifndef _SCENE_H
#define _SCENE_H


#include "paramList.h"
#include "tinyxml2.h"

namespace FxOgreFBX
{
    /***** structures to store scene info *****/
    enum FxOgreLightType
    {
        OGRE_LIGHT_POINT,
        OGRE_LIGHT_DIRECTIONAL,
        OGRE_LIGHT_SPOT,
        OGRE_LIGHT_RADPOINT
    };
    
    typedef struct FxOgrePoint3Tag
    {
        float x, y, z;
        FxOgrePoint3Tag()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        FxOgrePoint3Tag(float X, float Y, float Z)
        {
            x = X;
            y = Y;
            z = Z;
        }
    } FxOgrePoint3;

    typedef struct FxOgrePoint4Tag
    {
        float w, x, y, z;
        FxOgrePoint4Tag()
        {
            w = 0.0f;
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        FxOgrePoint4Tag(float W, float X, float Y, float Z)
        {
            w = W;
            x = X;
            y = Y;
            z = Z;
        }
    } FxOgrePoint4;

    typedef struct FxOgreTransformTag
    {
        FxOgrePoint3 pos;
        FxOgrePoint4 rot;
        FxOgrePoint3 scale;
    } FxOgreTransform;

    typedef struct FxOgreNodeTag
    {
        FxOgreTransform trans;
        bool isTarget;
        std::string name;
        int id;
    } FxOgreNode;

    typedef struct FxOgreLightTag
    {
        FxOgreNode node;
        FxOgreLightType type;
        FxOgrePoint3 diffuseColour;
        FxOgrePoint3 specularColour;
        // Point light parameters
        float attenuation_range, attenuation_constant, attenuation_linear, attenuation_quadratic;
        // Spotlight parameters
        float range_inner, range_outer, range_falloff;
        FxOgreLightTag()
        {
            type = OGRE_LIGHT_POINT;
            attenuation_range = 0.0f;
            attenuation_constant = 0.0f;
            attenuation_linear = 0.0f;
            attenuation_quadratic = 0.0f;
            range_inner = 0.0f;
            range_outer = 0.0f;
            range_falloff = 0.0f;
        }
    } FxOgreLight;

    typedef struct FxOgreCameraTag
    {
        FxOgreNode node;
        float fov, clipNear, clipFar;
        
    } FxOgreCamera;

    typedef struct FxOgreMeshTag
    {
        FxOgreNode node;
        std::string meshFile;
    } FxOgreMesh;

    /***** Class FxOgreScene *****/
    class FxOgreScene
    {
    public:
        //constructor
        FxOgreScene();
        //destructor
        ~FxOgreScene();
        // Clears structures in between exports
        void clear();
        bool writeSceneFile(ParamList &params);
        void addLight(FxOgreLight& light);
        void addMesh(FxOgreMesh& node);
        void setSceneTransform(const FxOgreTransform& trans);
        FxOgreTransform getDefaultTransForm( );
        void addCamera(FxOgreCamera& camera);
        int getNumMeshes() {return static_cast<int>(m_meshes.size());}
        void clearMeshes() {m_meshes.clear();}
    protected:
       
        FxOgreTransform m_scene_trans;
        std::vector<FxOgreLight> m_lights;
        std::vector<FxOgreCamera> m_cameras;
        std::vector<FxOgreMesh> m_meshes;
        int id_counter;
        tinyxml2::XMLElement* writeNodeData(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* parent, const FxOgreNode &node);
        std::string getLightTypeString(FxOgreLightType type);

    };

}; // end of namespace

#endif
