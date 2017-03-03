////////////////////////////////////////////////////////////////////////////////
// scene.cpp
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
#include "scene.h"
#include "mesh.h"
#include "FxOgreFBXLog.h"

namespace FxOgreFBX
{
    /***** Class FxOgreScene *****/
    // constructor
    FxOgreScene::FxOgreScene()
    {
        id_counter = 0;
        m_scene_trans = getDefaultTransForm();
    }

    // destructor
    FxOgreScene::~FxOgreScene()
    {
    }
    void FxOgreScene::clear()
    {
        m_lights.clear();
        m_meshes.clear();
        m_cameras.clear();
        id_counter = 0;
        m_scene_trans = getDefaultTransForm();
    }
    FxOgreTransform FxOgreScene::getDefaultTransForm()
    {
        FxOgreTransform trans;
        trans.pos = FxOgrePoint3(0.0f, 0.0f, 0.0f);
        trans.rot = FxOgrePoint4(1.0f, 0.0f, 0.0f, 0.0f);
        trans.scale = FxOgrePoint3(1.0f, 1.0f, 1.0f);
        return trans;
    }
    void FxOgreScene::setSceneTransform(const FxOgreTransform &trans)
    {
        m_scene_trans = trans;
    }
    void FxOgreScene::addLight(FxOgreLight& light)
    {
        id_counter++;
        light.node.id = id_counter;
        m_lights.push_back(light);
    }
    void FxOgreScene::addCamera(FxOgreCamera& camera)
    {
        id_counter++;
        camera.node.id = id_counter;
        m_cameras.push_back(camera);
    }
    void FxOgreScene::addMesh(FxOgreMesh& mesh)
    {
        id_counter++;
        mesh.node.id = id_counter;
        m_meshes.push_back(mesh);
    }

    std::string FxOgreScene::getLightTypeString(FxOgreLightType type)
    {
        switch( type )
        {
        case OGRE_LIGHT_POINT:
            return std::string("point");
        case OGRE_LIGHT_DIRECTIONAL:
            return std::string("directional");
        case OGRE_LIGHT_SPOT:
            return std::string("spot");
        case OGRE_LIGHT_RADPOINT:
            return std::string("radpoint");
        }
        FxOgreFBXLog( "Invalid light type detected. Using point light as default.\n");
        return("point");
    }
    tinyxml2::XMLElement* FxOgreScene::writeNodeData(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* parent, const FxOgreNode &node)
    {
        if(!parent)
        {
            return NULL;
        }
        tinyxml2::XMLElement *pNodeElement = xmlDoc.NewElement("node");
        pNodeElement->SetAttribute( "name", node.name.c_str() );
        pNodeElement->SetAttribute( "id", node.id );
        pNodeElement->SetAttribute( "isTarget", "false");
        parent->LinkEndChild(pNodeElement);

        tinyxml2::XMLElement *pPositionElement = xmlDoc.NewElement("position");
        pPositionElement->SetAttribute( "x", node.trans.pos.x );
        pPositionElement->SetAttribute( "y", node.trans.pos.y );
        pPositionElement->SetAttribute( "z", node.trans.pos.z );
        pNodeElement->LinkEndChild(pPositionElement);

        tinyxml2::XMLElement *pRotationElement = xmlDoc.NewElement("rotation");
        pRotationElement->SetAttribute( "qx", node.trans.rot.x );
        pRotationElement->SetAttribute( "qy", node.trans.rot.y );
        pRotationElement->SetAttribute( "qz", node.trans.rot.z );
        //  flip the w-component of the quaternion?
        pRotationElement->SetAttribute( "qw", node.trans.rot.w );
        pNodeElement->LinkEndChild(pRotationElement);

        tinyxml2::XMLElement *pScaleElement = xmlDoc.NewElement("scale");
        pScaleElement->SetAttribute( "x", node.trans.scale.x );
        pScaleElement->SetAttribute( "y", node.trans.scale.y );
        pScaleElement->SetAttribute( "z", node.trans.scale.z );
        pNodeElement->LinkEndChild(pScaleElement);
        return pNodeElement;
    }

    bool FxOgreScene::writeSceneFile(ParamList &params)
    {
        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLElement *pSceneElement = xmlDoc.NewElement("scene");
        xmlDoc.LinkEndChild(pSceneElement);

        pSceneElement->SetAttribute( "formatVersion", "1.0" );
        pSceneElement->SetAttribute( "minOgreVersion", "1.4" );
        pSceneElement->SetAttribute( "author", "FxOgreFBX");

        tinyxml2::XMLElement *pNodesElement = xmlDoc.NewElement("nodes");
        pSceneElement->LinkEndChild(pNodesElement);

        FxOgreNode node;
        node.trans = m_scene_trans;
        node.name = "SceneTransform";
        tinyxml2::XMLElement *pSceneNodeElement = writeNodeData(xmlDoc, pNodesElement, node);

        for( size_t i = 0; i < m_meshes.size(); ++i )
        {
            tinyxml2::XMLElement *pNodeElement = writeNodeData(xmlDoc, pSceneNodeElement, m_meshes[i].node);
            tinyxml2::XMLElement *pEntityElement = xmlDoc.NewElement("entity");
            pEntityElement->SetAttribute( "name", m_meshes[i].node.name.c_str() );
            pEntityElement->SetAttribute( "id", m_meshes[i].node.id );
            pEntityElement->SetAttribute( "meshFile", m_meshes[i].meshFile.c_str());
            pEntityElement->SetAttribute( "castShadows", "true");
            pEntityElement->SetAttribute( "receiveShadows", "true");
            pNodeElement->LinkEndChild(pEntityElement);
        }

        // A light to compare to to see if we've modified anything from default values.
        FxOgreLight compObj;
        for( size_t i = 0; i < m_lights.size(); ++i )
        {
            tinyxml2::XMLElement *pNodeElement = writeNodeData(xmlDoc, pSceneNodeElement, m_lights[i].node);
            if(pNodeElement)
            {
                tinyxml2::XMLElement *pLightElement = xmlDoc.NewElement("light");
                pLightElement->SetAttribute( "name", m_lights[i].node.name.c_str() );
                pLightElement->SetAttribute( "id", m_lights[i].node.id );
                pLightElement->SetAttribute( "type", getLightTypeString(m_lights[i].type).c_str());
                pLightElement->SetAttribute( "castShadows", "false");
                pNodeElement->LinkEndChild(pLightElement);

                tinyxml2::XMLElement *pNormalElement = xmlDoc.NewElement("normal");
                pNormalElement->SetAttribute( "x", 0.0f );
                pNormalElement->SetAttribute( "y", 0.0f );
                pNormalElement->SetAttribute( "z", -1.0f );
                pLightElement->LinkEndChild(pNormalElement);

                if(	fabs(m_lights[i].diffuseColour.x - compObj.diffuseColour.x) > PRECISION	||
                    fabs(m_lights[i].diffuseColour.y - compObj.diffuseColour.y ) > PRECISION	||
                    fabs(m_lights[i].diffuseColour.z - compObj.diffuseColour.z ) > PRECISION		)
                {
                    tinyxml2::XMLElement *pColourElement = xmlDoc.NewElement("colourDiffuse");
                    pColourElement->SetAttribute( "r", m_lights[i].diffuseColour.x );
                    pColourElement->SetAttribute( "g", m_lights[i].diffuseColour.y );
                    pColourElement->SetAttribute( "b", m_lights[i].diffuseColour.z );
                    pLightElement->LinkEndChild(pColourElement);
                }

                if(	fabs(m_lights[i].specularColour.x - compObj.specularColour.x) > PRECISION	||
                    fabs(m_lights[i].specularColour.y - compObj.specularColour.y ) > PRECISION	||
                    fabs(m_lights[i].specularColour.z - compObj.specularColour.z ) > PRECISION		)
                {
                    tinyxml2::XMLElement *pSpecColourElement = xmlDoc.NewElement("colourSpecular");
                    pSpecColourElement->SetAttribute( "r", m_lights[i].specularColour.x );
                    pSpecColourElement->SetAttribute( "g", m_lights[i].specularColour.y );
                    pSpecColourElement->SetAttribute( "b", m_lights[i].specularColour.z );
                    pLightElement->LinkEndChild(pSpecColourElement);
                }
                if(	m_lights[i].type == OGRE_LIGHT_POINT)
                {
                    tinyxml2::XMLElement *pAttenuationElement = xmlDoc.NewElement("lightAttenuation");
                    pAttenuationElement->SetAttribute( "range", m_lights[i].attenuation_range );
                    pAttenuationElement->SetAttribute( "constant", m_lights[i].attenuation_constant );
                    pAttenuationElement->SetAttribute( "linear", m_lights[i].attenuation_linear );
                    pAttenuationElement->SetAttribute( "quadratic", m_lights[i].attenuation_quadratic );
                    pLightElement->LinkEndChild(pAttenuationElement);
                }
                if(	m_lights[i].type == OGRE_LIGHT_SPOT	)
                {
                    tinyxml2::XMLElement *pAttenuationElement = xmlDoc.NewElement("lightRange");
                    pAttenuationElement->SetAttribute( "inner", m_lights[i].range_inner );
                    pAttenuationElement->SetAttribute( "outer", m_lights[i].range_outer );
                    pAttenuationElement->SetAttribute( "falloff", m_lights[i].range_falloff );
                    pLightElement->LinkEndChild(pAttenuationElement);
                }
            }
        }
        for( size_t i = 0; i < m_cameras.size(); ++i )
        {
            tinyxml2::XMLElement *pNodeElement = writeNodeData(xmlDoc, pSceneNodeElement, m_cameras[i].node);
            if(pNodeElement)
            {
                tinyxml2::XMLElement *pCameraElement = xmlDoc.NewElement("camera");
                pCameraElement->SetAttribute( "name", m_cameras[i].node.name.c_str() );
                pCameraElement->SetAttribute( "id", m_cameras[i].node.id );
                pCameraElement->SetAttribute( "fov", m_cameras[i].fov);
                pNodeElement->LinkEndChild(pCameraElement);

                tinyxml2::XMLElement *pClippingElement = xmlDoc.NewElement("clipping");
                pClippingElement->SetAttribute( "near", m_cameras[i].clipNear );
                pClippingElement->SetAttribute( "far", m_cameras[i].clipFar );
                pCameraElement->LinkEndChild(pClippingElement);
            }
        }
        xmlDoc.SaveFile( params.sceneFilename.c_str() );
        return true;
    }

}; //end of namespace
