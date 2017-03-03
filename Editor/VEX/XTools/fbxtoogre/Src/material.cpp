////////////////////////////////////////////////////////////////////////////////
// material.cpp
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

#include "material.h"

#include "FxOgreFBXLog.h"
#include "common.h"

namespace FxOgreFBX
{
    // Constructor
    Material::Material()
    {
        clear();
    }


    // Destructor
    Material::~Material()
    {
    }


    // Get material name
    std::string& Material::name()
    {
        return m_name;
    }


    // Clear data
    void Material::clear()
    {
        m_name = "";
        m_type = MT_LAMBERT;
        m_lightingOff = false;
        m_isTransparent = false;
        m_isTextured = false;
        m_isMultiTextured = false;
        m_ambient = Point4(1,1,1,1);
        m_diffuse = Point4(1,1,1,1);
        m_specular = Point4(0,0,0,0);
        m_emissive = Point4(0,0,0,0);
        m_textures.clear();
    }

    // Load material data
    bool Material::load(FbxSurfaceMaterial* pGameMaterial,std::vector<int>& uvsets,ParamList& params)
    {
        if( !pGameMaterial )
        {
            return false;
        }
        clear();
        
        //read material name, adding the requested prefix
        std::string tmpStr = params.matPrefix;
        m_name = "";
        if(pGameMaterial)
            tmpStr.append(pGameMaterial->GetName());
        for(size_t i = 0; i < tmpStr.size(); ++i)
        {
            if(tmpStr[i] == ':')
            {
                m_name.append("_");
            }
            else
            {
                m_name.append(tmpStr.substr(i, 1));
            }
        }

        //check if we want to export with lighting off option
        m_lightingOff = params.lightingOff;

        if( pGameMaterial->GetClassId().Is(FbxSurfacePhong::ClassId) || pGameMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) )
        {
            FbxPropertyT<FbxDouble3> lFbxDouble3;
            FbxPropertyT<FbxDouble> lFbxDouble;

            if (pGameMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
            {
                m_type = MT_PHONG;

                // Specular Color (unique to Phong materials)
                lFbxDouble = ((FbxSurfacePhong *) pGameMaterial)->SpecularFactor;
                lFbxDouble3 =((FbxSurfacePhong *) pGameMaterial)->Specular;

                // @todo - this technique doesn't always give correct values. Figure out how to set m_specular correctly.
                //m_specular = Point4(static_cast<float>(lFbxDouble3.Get()[0]* lFbxDouble.Get()), 
                //  static_cast<float>(lFbxDouble3.Get()[1] * lFbxDouble.Get()), 
                //  static_cast<float>(lFbxDouble3.Get()[2] * lFbxDouble.Get()), 1);

                // Display the Shininess
                //lFbxDouble =((FbxSurfacePhong *) pGameMaterial)->Shininess;
                //float shininess = static_cast<float>(lFbxDouble.Get());

                // Display the Reflectivity
                //lFbxDouble =((FbxSurfacePhong *) pGameMaterial)->ReflectionFactor;
                //float reflectivity =  static_cast<float>(lFbxDouble.Get());

            }

            lFbxDouble = ((FbxSurfaceLambert *) pGameMaterial)->AmbientFactor;
            lFbxDouble3 =((FbxSurfaceLambert *) pGameMaterial)->Ambient;
            m_ambient = Point4(static_cast<float>(lFbxDouble3.Get()[0]* lFbxDouble.Get()), 
                static_cast<float>(lFbxDouble3.Get()[1] * lFbxDouble.Get()), 
                static_cast<float>(lFbxDouble3.Get()[2] * lFbxDouble.Get()), 1);

            lFbxDouble = ((FbxSurfaceLambert *) pGameMaterial)->EmissiveFactor;
            lFbxDouble3 =((FbxSurfaceLambert *) pGameMaterial)->Emissive;
            m_emissive = Point4(static_cast<float>(lFbxDouble3.Get()[0]* lFbxDouble.Get()), 
                static_cast<float>(lFbxDouble3.Get()[1] * lFbxDouble.Get()), 
                static_cast<float>(lFbxDouble3.Get()[2] * lFbxDouble.Get()), 1);

            //Opacity is Transparency factor now
            lFbxDouble =((FbxSurfaceLambert *) pGameMaterial)->TransparencyFactor;
            lFbxDouble3 =((FbxSurfaceLambert *) pGameMaterial)->TransparentColor;
            // @todo - This code won't mark textures as transparent incorrectly, but some
            // transparent  materials aren't exported as such.  The TransparencyFactor alone
            // is not reliable, and neither are the Max FBX exporters for that matter.
            if( lFbxDouble3.Get()[0] * lFbxDouble.Get() >= PRECISION )
            {
                m_isTransparent = true;
            }

            lFbxDouble = ((FbxSurfaceLambert *) pGameMaterial)->DiffuseFactor;
            lFbxDouble3 =((FbxSurfaceLambert *) pGameMaterial)->Diffuse;
            float alpha = 1.0f;
            if( m_isTransparent )
            {
                // Evolver files have transparency on the eyes when there is no texture file.
                // Make sure we set the alpha correctly when no texture is present.
                FbxProperty sTextureChannels = pGameMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[0]);
                if( sTextureChannels.IsValid() )
                {
                    int texCount = sTextureChannels.GetSrcObjectCount(FbxTexture::ClassId);
                    if( texCount == 0 )
                    {
                        alpha = static_cast<float>(lFbxDouble.Get());
                    }
                }
            }
            m_diffuse = Point4(static_cast<float>(lFbxDouble3.Get()[0]* lFbxDouble.Get()), static_cast<float>(lFbxDouble3.Get()[1] * lFbxDouble.Get()), static_cast<float>(lFbxDouble3.Get()[2] * lFbxDouble.Get()), alpha);
        }

        // support multiple properties?
        FbxProperty pProperty = pGameMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[0]);
        if( pProperty.IsValid() )
        {
            int texCount = pProperty.GetSrcObjectCount(FbxTexture::ClassId);
            for (int j = 0; j < texCount; ++j)
            {

                FbxLayeredTexture *lLayeredTexture = FbxCast <FbxLayeredTexture>(pProperty.GetSrcObject(FbxLayeredTexture::ClassId, j));
                assert( lLayeredTexture == NULL);

                FbxTexture* pTexture = FbxCast <FbxTexture> (pProperty.GetSrcObject(FbxTexture::ClassId,j));
                if(pTexture)
                {
                    Texture tex;
                    FbxFileTexture *pFileTexture = FbxCast<FbxFileTexture>(pTexture);
                    if (pFileTexture)
                    {

                        // @todo - Rocketbox characters end up with 0 diffuse and black meshes.  For now, always export the diffuse 
                        // channel as 1.0 if there is a texture.
                        m_diffuse = Point4( 1.0f, 1.0f, 1.0f, 1.0f);

                        std::string filepath =  pFileTexture->GetFileName();

                        if( !FileExists(filepath.c_str() ) )
                        {
                            std::string fbx_filepath = StripFilename(params.fbxFilename);
                            std::string filename = StripToTopParent(filepath);
                            std::string relativePath =  fbx_filepath + "\\" + filename;
                            if( FileExists(relativePath.c_str() ) )
                            {
                                filepath = relativePath;
                            }
                            else
                            {
                                // Make sure we have a valid texture file (it has a file extension), then tell the user.
                                if( filename.find('.') != std::string::npos )
                                {
                                    FxOgreFBXLog("ERRORBOXWARNING: Could not locate texture %s.  Try placing it in the FBX file's folder.\n.", filename.c_str());
                                }
                                FxOgreFBXLog("Warning: Could not locate texture %s for material %s.\n.", filepath.c_str(), m_name.c_str());
                            }
                        }


                        for( size_t i = 0; i < filepath.length(); ++i )
                        {

                            if( filepath.at(i) == '/' )
                            {
                                filepath[i] = toascii('\\');
                                
                            }
                            else
                            {
                                filepath[i] = toascii(filepath[i]); 
                            }
                        }
                        
                        tex.absFilename = filepath;
                        tex.filename = FxOgreFBX::StripToTopParent(filepath);
                        tex.bCreateTextureUnit = true;
                    }

                    tex.uvsetIndex = 0;
                    tex.uvsetName = pProperty.GetName();

                    float covU,covV;
                    covU = static_cast<float>(pTexture->GetScaleU());
                    tex.scale_u = covU;
                    if (fabs(tex.scale_u) < PRECISION)
                        tex.scale_u = 0;

                    covV = static_cast<float>(pTexture->GetScaleV());
                    tex.scale_v = covV;
                    if (fabs(tex.scale_v) < PRECISION)
                        tex.scale_v = 0;


                    tex.rot = pTexture->GetRotationW();
                    if (fabs(tex.rot) < PRECISION)
                        tex.rot = 0;

                    if (fabs(pTexture->GetRotationU()) > PRECISION)
                        FxOgreFBXLog( "Warning: U rotation detected. This is unsupported.\n");
                    if (fabs(pTexture->GetRotationV()) > PRECISION)
                        FxOgreFBXLog( "Warning: V rotation detected. This is unsupported.\n");

                    float transU,transV;
                    transU =  static_cast<float>(pTexture->GetTranslationU());
                    tex.scroll_u = -0.5 * (covU-1.0)/covU - transU/covU;
                    if (fabs(tex.scroll_u) < PRECISION)
                        tex.scroll_u = 0;
                    transV =  static_cast<float>(pTexture->GetTranslationV());
                    tex.scroll_v = 0.5 * (covV-1.0)/covV + transV/covV;
                    if (fabs(tex.scroll_v) < PRECISION)
                        tex.scroll_v = 0;

                    // Set texture operation type
                    // Not sure when to set TOT_REPLACE, TOT_ADD, or TOT_ALPHABLEND
                    tex.opType = TOT_MODULATE;

                    m_textures.push_back(tex);
                }
            }
        }
    
        return true;
    }

    
    // Write material data to an Ogre material script file
    bool Material::writeOgreScript(ParamList &params)
    {
        //Start material description
        params.outMaterial << "material \"" << m_name.c_str() << "\"\n";
        params.outMaterial << "{\n";

        //Start technique description
        params.outMaterial << "\ttechnique\n";
        params.outMaterial << "\t{\n";

        //Start render pass description
        params.outMaterial << "\t\tpass\n";
        params.outMaterial << "\t\t{\n";
        //set lighting off option if requested
        if (m_lightingOff)
            params.outMaterial << "\t\t\tlighting off\n\n";
        //set phong shading if requested (default is gouraud)
        // jcr 2012/07/08 disable this phong shading directive because Direct3D9
        //                (what FaceFX Studio uses in D3D mode) does not support
        //                phong, and no card supports phong in fixed function mode.
        //                it's likely that the FBX sdk is incorrectly classifying all
        //                materials as phong in Material::load(). in any case, commenting
        //                out this simply leaves everything as the default shading model
        //                that should work everywhere. we may want to revisit this at some
        //                point.
        //if (m_type == MT_PHONG)
        //    params.outMaterial << "\t\t\tshading phong\n";
        //ambient colour
        // Format: ambient (<red> <green> <blue> [<alpha>]| vertexcolour)
        params.outMaterial << "\t\t\tambient " << m_ambient.w << " " << m_ambient.x << " " << m_ambient.y
            << " " << m_ambient.z << "\n";
        //diffuse colour
        //Format: diffuse (<red> <green> <blue> [<alpha>]| vertexcolour)
        params.outMaterial << "\t\t\tdiffuse " << m_diffuse.w << " " << m_diffuse.x << " " << m_diffuse.y
            << " " << m_diffuse.z << "\n";
        //specular colour
        params.outMaterial << "\t\t\tspecular " << m_specular.w << " " << m_specular.x << " " << m_specular.y
            << " " << m_specular.z << "\n";
        //emissive colour
        params.outMaterial << "\t\t\temissive " << m_emissive.w << " " << m_emissive.x << " " 
            << m_emissive.y << "\n";
        //if material is transparent set blend mode and turn off depth_writing
        if (m_isTransparent)
        {
            params.outMaterial << "\n\t\t\tscene_blend alpha_blend\n";
            params.outMaterial << "\t\t\tdepth_write off\n";
        }
        //write texture units
        for (size_t i=0; i<m_textures.size(); i++)
        {
            if(m_textures[i].bCreateTextureUnit == true)
            {
                //start texture unit description
                params.outMaterial << "\n\t\t\ttexture_unit\n";
                params.outMaterial << "\t\t\t{\n";
                if( params.prefixTextures )
                {
                    params.outMaterial << "\t\t\t\ttexture \"" << params.matPrefix.c_str() << m_textures[i].filename.c_str() << "\"\n";
                }
                else
                {
                    //write texture name
                    params.outMaterial << "\t\t\t\ttexture \"" << m_textures[i].filename.c_str() << "\"\n";
                }
                //write texture coordinate index
                params.outMaterial << "\t\t\t\ttex_coord_set " << m_textures[i].uvsetIndex << "\n";
                //write colour operation
                switch (m_textures[i].opType)
                {
                case TOT_REPLACE:
                    params.outMaterial << "\t\t\t\tcolour_op replace\n";
                    break;
                case TOT_ADD:
                    params.outMaterial << "\t\t\t\tcolour_op add\n";
                    break;
                case TOT_MODULATE:
                    params.outMaterial << "\t\t\t\tcolour_op modulate\n";
                    break;
                case TOT_ALPHABLEND:
                    params.outMaterial << "\t\t\t\tcolour_op alpha_blend\n";
                    break;
                }
                //write texture transforms
                params.outMaterial << "\t\t\t\tscale " << m_textures[i].scale_u << " " << m_textures[i].scale_v << "\n";
                params.outMaterial << "\t\t\t\tscroll " << m_textures[i].scroll_u << " " << m_textures[i].scroll_v << "\n";
                params.outMaterial << "\t\t\t\trotate " << m_textures[i].rot << "\n";
                //end texture unit desription
                params.outMaterial << "\t\t\t}\n";
            }
        }

        //End render pass description
        params.outMaterial << "\t\t}\n";

        //End technique description
        params.outMaterial << "\t}\n";

        //End material description
        params.outMaterial << "}\n";

        return true;
    }

};	//end namespace
