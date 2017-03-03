////////////////////////////////////////////////////////////////////////////////
// An Ogre Exporter for FBX
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
#include "FxOgreFBXDLL.h"
#include "ogreExporter.h"


namespace FxOgreFBX
{
    bool AddFBXAnimationToExisting(const char* fbxfilename, const char* skeletonfilename, const char* meshfilename, const char* logfilename, const char *animname, int start, int stop, float rate)
    {
        OgreExporter exporter;
        return exporter.AddFBXAnimationToExisting(fbxfilename, skeletonfilename, meshfilename, logfilename, animname, start, stop, rate );
    }

    bool ExportOgreFromFBX(const char* fbxfilename, const char* outmeshfilename, const char* logfilename, const char* animname, const char* frame0name, bool copyUniqueTextures, int bindframe)
    {
        OgreExporter exporter;
        return exporter.exportScene(fbxfilename, outmeshfilename, logfilename, animname, frame0name, copyUniqueTextures, bindframe );
    }

    bool DeleteOgreAnimation( const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname)
    {
        OgreExporter exporter;
        return exporter.DeleteOgreAnimation( skeletonfilename, meshfilename, logfilename, animname );
    }

}

