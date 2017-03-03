////////////////////////////////////////////////////////////////////////////////
// paramlist.cpp
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
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

#include "paramlist.h"

#include "FxOgreFBXLog.h"

/***** Class ParamList *****/
// method to parse arguments from command line
namespace FxOgreFBX
{
    // Helper function for getting the filename from a full path.
    std::string StripToTopParent(const std::string& filepath)
    {
        int ri = static_cast<int>(filepath.find_last_of('\\'));
        int ri2 = static_cast<int>(filepath.find_last_of('/'));
        if(ri2 > ri)
        {
            ri = ri2;
        }
        return filepath.substr(ri+1);
    }

    std::string StripFilename(const std::string& filepath)
    {
        int ri = static_cast<int>(filepath.find_last_of('\\'));
        int ri2 = static_cast<int>(filepath.find_last_of('/'));
        if(ri2 > ri)
        {
            ri = ri2;
        }
        return filepath.substr(0, ri);
    }
    bool ParamList::setOutputFilePaths(const std::string& meshOutputPath)
    {
        assert(meshFilename.length() > 5 );
        size_t meshIndex = meshFilename.length() - 5;

        size_t folderIndexForward = meshOutputPath.rfind("/", meshOutputPath.length() -1);
        size_t folderIndexBackward = meshOutputPath.rfind("\\", meshOutputPath.length() -1);
        size_t folderIndex;
        if(folderIndexForward == std::string::npos)
        {
            folderIndex = folderIndexBackward;
        }
        else if(folderIndexBackward == std::string::npos)
        {
            folderIndex = folderIndexForward;
        }
        else
        {
            folderIndex = folderIndexBackward > folderIndexForward ? folderIndexBackward : folderIndexForward;
        }
        assert( folderIndex != std::string::npos );

        skeletonFilename = meshFilename.substr(0,meshIndex).append(".SKELETON");
        materialFilename = meshFilename.substr(0,meshIndex).append(".MATERIAL");
        sceneFilename = meshFilename.substr(0,meshIndex).append(".SCENE");

        // Use the base Mesh name to prepend to materials and textures.
        // This will ensure there are no material (or texture) conflicts.
        matPrefix = meshFilename.substr(folderIndex + 1);
        matPrefix = matPrefix.substr(0, matPrefix.length() - 5 ) + "_";

        texOutputDir = meshFilename.substr(0, folderIndex) + "\\";

        return true;
    }

    // method to open output files for writing
    bool ParamList::openFiles()
    {
        std::string msg;
        if (exportMaterial)
        {
            outMaterial.open(materialFilename.c_str());
            if (!outMaterial)
            {
                FxOgreFBXLog( "Error opening file: %s\n", materialFilename.c_str());
                return false;
            }
        }
        if (exportAnimCurves)
        {
            outAnim.open(animFilename.c_str());
            if (!outAnim)
            {
                FxOgreFBXLog( "Error opening file: %s\n", animFilename.c_str());
                return false;
            }
        }
        if (exportCameras)
        {
            outCameras.open(camerasFilename.c_str());
            if (!outCameras)
            {
                FxOgreFBXLog( "Error opening file: %s\n", camerasFilename.c_str());
                return false;
            }
        }
        if (exportParticles)
        {
            outParticles.open(particlesFilename.c_str());
            if (!outParticles)
            {
                FxOgreFBXLog( "Error opening file: %s\n", particlesFilename.c_str());
                return false;
            }
        }
        return true;
    }

    // method to close open output files
    bool ParamList::closeFiles()
    {
        if (exportMaterial)
            outMaterial.close();
    
        if (exportAnimCurves)
            outAnim.close();
            
        if (exportCameras)
            outCameras.close();
        
        return true;
    }

}	//end namespace
