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

//http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/index.html?url=cpp_ref/_view_scene_2_scene_context_8cxx-example.html,topicNumber=cpp_ref__view_scene_2_scene_context_8cxx_example_htmld944e67f-1965-426e-9ca8-ffadf3a3b493

#include <iostream>
#include <fstream>
#include "float.h"
#include <map>
#include <vector>
#include <string>
#include "FxOgreFBXDLL.h"

#include <windows.h>
using namespace std;


static std::string instructions = "\
Usage: Drag an FBX file onto the EXE.  Animation files in the form of\n\
fbxfile_name@anim_name.fbx will be exported to the SKELETON and MESH files.\n\n\n\
\
Alternatively, call with the following options: \n\
 -f the path of the FBX file to export\n\
 -l the log file to overide ExecFxOgreFBX-log.txt\n\n\n\
\
 CHARACTER OUTPUT - Full character options:\n ----\n\
 -o the path of the output .MESH file.  SKELETON, MATERIAL, & SCENE files are auto-generated.\n\
 -t flag to copy textures to mesh output directory.  Texture names are prepended with mesh name.\n\
 -z the name to use for the one-frame animation at frame zero.\n\
 -g Specifies the frame to use as the bind pose (default is frame 0). \n\
 -b if specified, the -g flag is ignored and the FBX bind pose is used. If there is not a consistent bind pose for all meshes, frame 0 is used as a fallback.  Note, bounding boxes are computed from the bind pose so this may create bounding boxes inconsistent with the animation. \n\
 -e the name to use for the animation from the entire FBX file.\n\n\n\
\
 ANIMATION MODIFICATION - Modify existing .SKELETON and .MESH options:\n ----\n\
 -s the path of the existing skeleton file to add (bones) animations to. \n\
 -m the path of the existing mesh file to add (blendshape) animations to. If this file exists, a non-existing .SKELETON file will not fail the MORPH export.\n\
 -r the frame rate to use.  0 defaults to FBX file value.\n\
 -a the anim name, start frame, & end frame. Use a large end frame and zero for the start frame (negative time keys not supported) to default to FBX file bounds.\n\
 -d puts the EXE in delete mode.  The input FBX is ignored and the specified animation is deleted from the .SKELETON and .MESH files. (if it exists)\n\n\n\
 EXAMPLES\n ----\n\
 FxOgreFBX.exe \"C:\\Users\\me\\myfbx.fbx\"\n\
 FxOgreFBX.exe -f \"C:\\Users\\me\\myfbx.fbx\" -o \"C:\\Users\\me\\myfbx.MESH\"\n\
 FxOgreFBX.exe -f \"C:\\Users\\me\\myfbx@walkanim.fbx\" -m \"C:\\Users\\me\\myfbx.MESH\" -s \"C:\\Users\\me\\myfbx.SKELETON\" -a walkanim -1000 1000\n\
 FxOgreFBX.exe -d walkanim -m \"C:\\Users\\me\\myfbx.MESH\" -s \"C:\\Users\\me\\myfbx.SKELETON\"\n\
 FxOgreFBX.exe -f \"C:\\Users\\me\\anims.fbx\" -s \"C:\\Users\\me\\myfbx.SKELETON\" -a walkanim 0 50 -a runanim 51 100\n";

struct animClipInfo
{
    string name;
    string fbxfile;
    int start;
    int stop;
};

struct commandLineOptions
{
    string fbxfile;
    string inputskeletonfile;
    string outputmeshfile;
    string inputmeshfile;
    string deltetanimname;
     
    // The name for the animation in the FBX file.  
    // The anims array requires a fresh loading of the FBX file.  
    //This is done quickly while exporting the mesh.
    string quickexportAnimName; 
    // The name of the animation at frame 0.
    string frame0Name; 

    string logfile;

    int bindframe;
    float rate;
    bool copyUniqueTextures;
    bool error;
    vector<animClipInfo> anims;
};


typedef map<string, string> commandLineOptionList;

std::string s2upper(const std::string& s)
{
    std::string up = s;
    for( size_t i=0; i < s.length(); ++i )
    {
        up[i] = toupper(s[i]);
    }
    return up;
}
void printUsage()
{
    cout << instructions.c_str();
}

commandLineOptions parseArgs(int numArgs, char *argv[])
{
    commandLineOptions opts;
    opts.rate = 0;
    opts.copyUniqueTextures = false;
    opts.error = false;
    opts.bindframe = 0;
    if( numArgs == 1 )
    {
        printUsage();
    }

    if( numArgs > 0 )
    {
        std::string exename = argv[0];
        if( exename.length() > 4 )
        {
            opts.logfile = exename.substr(0, exename.length() - 4) + "-log.txt";
        }
    }
    // Support a single argument for when you drag an FBX file onto the 
    // EXE file.

	std::string testFile = "F:/Projekte/coop/XGame/_devFolder/Work/Character/character.fbx";
//   std::string testFile = "F:/Projekte/coop/XGame/_devFolder/Work/Character/Test/TestUVMaps.fbx";
  
	if( true) //numArgs == 2 )
    {
		opts.fbxfile = testFile;// argv[1];
        opts.outputmeshfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".MESH";
        opts.inputskeletonfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".SKELETON";
        opts.inputmeshfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".MESH";

        opts.frame0Name = "BaseFBXFrame0Anim";
        opts.quickexportAnimName = "BaseFBXFileAnim";  

        // Search for other FBX files matching file pattern
        std::string animFilePattern  = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + "@*";
        WIN32_FIND_DATAA data;
        HANDLE h = FindFirstFileA(animFilePattern.c_str(), &data);
        if( h!=INVALID_HANDLE_VALUE ) 
        {
	        do
	        {
		        char*   pFileName = new char [strlen(data.cFileName) + 1];
		        for( size_t i = 0; i < strlen( data.cFileName ); i++ )
			        pFileName[i] = char( data.cFileName[i] );

		        pFileName[strlen( data.cFileName )] = '\0';
		        
                std::string animfile( pFileName );
                if( animfile.length() > 4 )
                {
                    std::string ext = animfile.substr(animfile.length() - 4, 4);

                    if( s2upper(ext) == ".FBX" )
                    {
                        int animdeliminator = static_cast<int>(animfile.find_first_of('@'));
                        animClipInfo anim;
                        size_t animNameLength = animfile.length() - animdeliminator - 5;
                        anim.name = animfile.substr(animdeliminator+1, animNameLength);

                        anim.fbxfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + "@" + anim.name +".FBX";

                        // Start and end will be bounded by the FBX file's bounds.
                        anim.start = -INT_MAX;
                        anim.stop = INT_MAX ;
                        opts.anims.push_back(anim);
                    }
                }

	        } while(FindNextFileA(h, &data));
        } 
    } 
    else
    {
        for (int i = 1; i < numArgs; ++i)
        {
            std::string tmp(argv[i]);
            if( tmp == "-f" )
            {
                if( (i+1) < numArgs )
                {
                    opts.fbxfile = argv[i+1];
                }
            }
            else if( tmp == "-o" )
            {
                if( (i+1) < numArgs )
                {
                    opts.outputmeshfile = argv[i+1];
                }
            }
            else if( tmp == "-a" )
            {
                if( (i+3) < numArgs )
                {
                    std::string startFrame(argv[i+2]);
                    std::string endFrame(argv[i+3]);
                    if( std::string::npos != startFrame.find_first_not_of("-0123456789.") || 
                        std::string::npos != endFrame.find_first_not_of("-0123456789.") )
                    {
                        cout << "-a must be followed by start and end frame.\n";
                        opts.error = true;
                    }
                    else
                    {
                        animClipInfo anim;
                        anim.name = argv[i+1];
                        anim.fbxfile = opts.fbxfile;
                        anim.start = (int)atoi(argv[i+2]);
                        anim.stop = (int)atoi(argv[i+3]);
                        opts.anims.push_back(anim);
                    }
                }
                else
                {
                    cout << "-a must be followed by start and end frame.\n";
                    opts.error = true;
                }
            }
            else if( tmp == "-d" )
            {
                if( (i+1) < numArgs )
                {
                    opts.deltetanimname = argv[i+1];
                }
            }
            else if( tmp == "-r" )
            {
                if( (i+1) < numArgs )
                {
                    opts.rate = (float)atof(argv[i+1]);
                }
            }
            else if( tmp == "-t" )
            {
                opts.copyUniqueTextures = true;
            }
            else if( tmp == "-g" )
            {
                if( (i+1) < numArgs )
                {
                    opts.bindframe = (int)atoi(argv[i+1]);
                }
            }
            else if( tmp == "-s" )
            {
                if( (i+1) < numArgs )
                {
                    opts.inputskeletonfile = argv[i+1];
                }
            }
            else if( tmp == "-m" )
            {
                if( (i+1) < numArgs )
                {
                    opts.inputmeshfile = argv[i+1];
                }
            }
            else if( tmp == "-z" )
            {
                if( (i+1) < numArgs )
                {
                    opts.frame0Name = argv[i+1];
                }
            }
            else if( tmp == "-e" )
            {
                if( (i+1) < numArgs )
                {
                    opts.quickexportAnimName = argv[i+1];
                }
            }
            else if( tmp == "-l" )
            {
                if( (i+1) < numArgs )
                {
                    opts.logfile = argv[i+1];
                }
            }
            else if( tmp == "-b" )
            {
                // INT_MAX is used to specify to take the bind pose from the FBX.
                opts.bindframe = INT_MAX;
            }
        }
    }
    return opts;
}

int main(int argc, char *argv[])
{
    const char *pAnimName = NULL;
    const char *pFrame0AnimName = NULL;
    const char *pMeshInputPath = NULL;
    const char *pSkeletonInputPath = NULL;
    const char *pLogPath = NULL;
    const char *pDeltetAnimName = NULL;


    commandLineOptions ops = parseArgs(argc, argv);
    if( ops.error )
    {
        cout << "Error parsing arguments.\n";
        return -1;
    }

    if( ops.quickexportAnimName.length() > 0 )
    {
        pAnimName = ops.quickexportAnimName.c_str();
    }
    if( ops.frame0Name.length() > 0 )
    {
        pFrame0AnimName = ops.frame0Name.c_str();
    }
    if( ops.inputskeletonfile.length() > 0 )
    {
        pSkeletonInputPath = ops.inputskeletonfile.c_str();
    }
    if( ops.inputmeshfile.length() > 0 )
    {
        pMeshInputPath = ops.inputmeshfile.c_str();
    }
    if( ops.logfile.length() > 0 )
    {
        pLogPath = ops.logfile.c_str();
    }
    // Check for delete mode
    if( ops.deltetanimname.length() > 0 )
    {
        cout << "Delete mode specified with -d\n";
        pDeltetAnimName =  ops.deltetanimname.c_str();
    
        if( ops.inputskeletonfile.length() > 0 || ops.inputmeshfile.length() > 0)
        {
			FxOgreFBX::DeleteOgreAnimation(pSkeletonInputPath, pMeshInputPath, pLogPath, pDeltetAnimName);
        }
        else
        {
            cout << "An animation was specified to delete with -d, but an existing skeleton or mesh file was not specified with -s or -m.\n";
            return -1;
        }
        return 0;
    }

    if( ops.fbxfile.length() == 0 )
    {
        cout << "Please specify an FBX file with -f.\n";
        return -1;
    }
    
    if( ops.outputmeshfile.length() > 0 )
    {

        bool success = FxOgreFBX::ExportOgreFromFBX(ops.fbxfile.c_str(), ops.outputmeshfile.c_str(), pLogPath, pAnimName, pFrame0AnimName, ops.copyUniqueTextures, ops.bindframe);
        if( !success )
        {
            cout << "ExportOgreFromFBX failed!\n";
            return -1;
        }
    }
    if(  ops.anims.size() > 0 )
    {
        if( ops.inputskeletonfile.length() > 0 || ops.inputmeshfile.length() > 0)
        { 
            for( size_t i = 0; i < ops.anims.size(); ++i )
            {
                if( !FxOgreFBX::AddFBXAnimationToExisting(ops.anims[i].fbxfile.c_str(), pSkeletonInputPath, pMeshInputPath, pLogPath, ops.anims[i].name.c_str(), ops.anims[i].start, ops.anims[i].stop, ops.rate))
                {
                    cout << "Failed to add FBX animation!\n";
                    return -1;
                }
            }
        }
        else
        {
            cout << "Animations were specified with -a, but an existing skeleton or mesh file was not specified with -s or -m.\n";
        }
    }
    if( ops.anims.size() ==0 && ops.outputmeshfile.length() == 0 ) 
    {
        cout << "No animations were specified with -a, no output mesh files were specified with -o.  Nothing to do!\n";
        return -1;
    }

    return 0;
}
