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

Overview
----------------------------------------------------------------------------------
FxOgreFBX converts FBX files into binary .MESH, .SKELETON files and text-based 
.MATERIAL and .Scene files.  It is based off of and for the most part mirrors 
the functionality of Francesco Giordana's Maya exporter. It is released under LGPL.


Usage
----------------------------------------------------------------------------------
A command-line utility ExecFxOgreFBX.exe (requires OgreMain.dll & FxOgreFBX.dll)
can convert FBX files by dragging the FBX files onto the EXE.  The base mesh and
skeleton files are generated using this FBX file.  For additional animations, the 
FBX file directory is searched for FBX files matching the pattern: 

'original_fbxfilename' @ 'animation_name' .fbx

animation_name will then be added to the Ogre skeleton and mesh files.  So for 
example, dragging a file character.fbx onto ExecFxOgreFBX.exe will export it.  If 
character@walk.fbx is in the same folder as character.fbx, the resulting ogre 
skeleton and mesh files will contain the walk animation as well, including blendshape
and bone animations.

For more advanced options, like adding an animation to an existing .skeleton or
.mesh file, run the command with no arguments to see the documentation


Building from Source
-------------------------------------------------------------------------------
External code and libraries are not included for Ogre, FBX, or tinyxml2 (v2.1.0)
(https://github.com/leethomason/tinyxml2), but you will need to include these in 
the project before building.  The External folder is currently empty, but 
placing the FBX, Ogre, and tinyxml2 source files in their respective folders
will let you build without modifying project settings.


Things to watch out for
----------------------------------------------------------------------------------
- Weight all vertices to bones.  The exporter will try to deal with unskinned 
meshes the best that it can, but to remove uncertainty, do the binding yourself.

- The default behaviour is to use frame 0 as the bind pose.  You can force a 
different frame to use, or specify that the FBX bindpose should be used.  If
the FBX bindpose is used, there must only be one bindpose specified in the 
FBX file.

- Use the FBX Converter to view FBX files.  Not all scenes from 3D packages export 
to the FBX format well, so use Autodesk's tool to see if it is a problem with the
FBX or this tool. 

- In some cases, if an FBX file does not look correct, you can fix the issue by
importing it into the source animation package, and re-exporting it as an FBX file.
The FBX importers apparently can fix some common problems exported with FBX files.

- Avoid joints with eINHERIT_Rrs.  In Maya this is known as "Segment Scale 
Compensate"

- Transparency info is not always correctly written to the FBX file.  Add the 
following lines to the material file after the emissive color to add it:
    scene_blend alpha_blend
    depth_write off
    

