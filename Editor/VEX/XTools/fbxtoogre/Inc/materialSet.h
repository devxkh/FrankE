////////////////////////////////////////////////////////////////////////////////
// materialSet.h
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

#ifndef _MATERIALSET_H
#define _MATERIALSET_H

#include "_singleton.h"
#include "material.h"
#include "FxOgreFBXLog.h"

namespace FxOgreFBX
{
    class MaterialSet : public Singleton<MaterialSet>
    {
    public:
        //constructor
        MaterialSet(){
            //create a default material
            m_pDefaultMat = new Material();
            m_pDefaultMat->m_type = MT_LAMBERT;
            m_pDefaultMat->m_name = "defaultLambert";
            m_pDefaultMat->m_ambient = Point4(0,0,0,1);
            m_pDefaultMat->m_emissive = Point4(0,0,0,1);
            m_pDefaultMat->m_diffuse = Point4(0.5f,0.5f,0.5f,1.0f);
        };
        //destructor
        ~MaterialSet(){
            clear();
            if (m_pDefaultMat)
                delete m_pDefaultMat;
        }
        //clear
        void clear(){
            for (size_t i=0; i<m_materials.size(); i++)
                delete m_materials[i];
            m_materials.clear();
        }


        //add material
        void addMaterial(Material* pMat){
            bool found = false;
            for (size_t i=0; i<m_materials.size() && !found; i++)
            {
                if (!m_materials[i]->name().compare(pMat->name()))
                {
                    found = true;
                    delete pMat;
                }
            }
            if (!found)
                m_materials.push_back(pMat);
        }
        //get material
        Material* getMaterial(const std::string& name)
        {
            for (size_t i=0; i<m_materials.size(); i++)
            {
                if (!m_materials[i]->name().compare(name))
                    return m_materials[i];
            }
            return NULL;
        };
        //get default material
        Material* getDefaultMaterial()
        {
            return m_pDefaultMat;
        };
        //get material set
        static MaterialSet& getSingleton(){
            assert(ms_Singleton);  
            return (*ms_Singleton);
        };
        static MaterialSet* getSingletonPtr(){
            return ms_Singleton;
        };
        //write materials to Ogre XML
        bool writeOgreScript(ParamList &params){
            bool stat;
            for (size_t i=0; i<m_materials.size(); i++)
            {
                stat = m_materials[i]->writeOgreScript(params);
                
                if (true != stat)
                {
                    std::string msg = "Error writing material ";
                    msg += m_materials[i]->name();
                    msg += ", aborting operation\n";
                    FxOgreFBXLog(msg.c_str());
                }
                
            }
            copyTextures(params);
            return true;
        };
        // Copy textures to path specified by params
        void copyTextures(ParamList &params)
        {
            if( params.copyTextures )
            {
                std::vector<std::string> copiedTextures;
                for( size_t matIt=0; matIt<m_materials.size(); matIt++ )
                {
                    
                    for (size_t i=0; i<m_materials[matIt]->m_textures.size(); i++)
                    {
                        std::string texture = m_materials[matIt]->m_textures[i].absFilename;
                        bool bAlreadyCopied = false;
                        for( size_t j=0; j<copiedTextures.size(); ++j)
                        {
                            if( texture == copiedTextures[j] )
                            {
                                bAlreadyCopied = true;
                                break;
                            }
                        }
                        if( !bAlreadyCopied && FileExists(texture) )
                        {
                            copiedTextures.push_back(texture);
                            // Copy file texture to output dir
                            std::string command = "copy \"";
                            command += texture;
                            command += "\" \"";
                            command += params.texOutputDir;
                            
                            if( params.prefixTextures )
                            {
                                command += params.matPrefix;
                            }
                            command += m_materials[matIt]->m_textures[i].filename;
                            command += "\"";
                            FxOgreFBXLog("Copying texture: %s\n", command.c_str());
                            if( 0 != system(command.c_str()) )
                            {
                                FxOgreFBXLog("Failed to copy texture!\n");
                            }
                        }
                    }
                }
            }
        };
    protected:
        std::vector<Material*> m_materials;
        Material* m_pDefaultMat;
    };

};	//end namespace

#endif
