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
namespace FxOgreFBX
{
#define XE_EDITOR_EXPORTS

	//works not with c++ projects
#define EDITOR_API_EXPORT extern "C" __declspec(dllexport)//extern c important for c# and c++ compatibility
#define EDITOR_API_IMPORT  extern "C" __declspec(dllimport) //extern c important for c# and c++ compatibility
	//__declspec(dllimport)

	////////////////////////////////////////////////////////////
	// Define portable import / export macros
	////////////////////////////////////////////////////////////
#if defined(XE_EDITOR_EXPORTS)

#define XE_EDITOR_API EDITOR_API_EXPORT

#else

#define XE_EDITOR_API EDITOR_API_IMPORT

#endif


    //class FxOgreFBXDLL
    //{
    //public:

        // Exports the FBX file at path fbxfilename.  outmeshfilename specifies the output .MESH file name,
        // while the .SKELETON, .MATERIAL, and .SCENE filenames are computed based on the .MESH file name.
        // If no outmeshfilename is specified, it is derived from the FBX filename.
        //  - animname: if non-null the animation from the entire FBX file is output to the FBX file with this name.
        //  - frame0name: if non-null, this exports a one-frame animation with the given name to the .SKELETON using frame 0 values.
        //  - copyUniqueTextures:  prepends the mesh filename (no extension) to the texture name and material names and
        //      copies the textures to the .MESH output path folder.
        //  - bindframe: if not equal to MAXINT, the specified frame will be use to bind the meshes to the skeleton.
        //      by default, the fbx bindpose information is used, unless there are multiple bind poses in which case 0 is the default.
        //static 
			XE_EDITOR_API bool ExportOgreFromFBX(const char* fbxfilename, const char* outmeshfilename, const char *logfilename, const char *animname, const char *frame0name, bool copyUniqueTextures, int bindframe);

        // Loads the existing .SKELETON file and/or .MESH file and adds the animation data contained in the fbxfilename to 
        // the files, then saves the .SKELETON file and/or .MESH file, overwriting the originals. 
        //   - start: the start time (in frames) when the animation starts in the fbx file.  Pass extremely negative number to default to FBX file start.
        //   - stop:  the stop time (in frames) when the animation stops in the fbx file. Pass extremely positive number to default to FBX file stop.
        //   - rate:  The animation frame rate at which to sample the animation. Pass 0 to default to FBX file rate.
        //   - fbxfilename: The FBX file.  
			XE_EDITOR_API bool AddFBXAnimationToExisting(const char* fbxfilename, const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname, int start, int stop, float rate);

        // Deletes an Ogre Animation from the existing .SKELETON and .MESH files if the files and animation exist.
			XE_EDITOR_API bool DeleteOgreAnimation( const char* skeletonfilename,  const char* meshfilename, const char *logfilename, const char *animname);

  //  };

}