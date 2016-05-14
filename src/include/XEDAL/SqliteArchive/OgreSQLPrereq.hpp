#ifndef __OgreSQLPluginPrerequisites_H__
#define __OgreSQLPluginPrerequisites_H__

//-----------------------------------------------------------------------
// Windows Settings
//-----------------------------------------------------------------------
#if OGRE_PLATFORM == PLATFORM_WIN32
#   if OGRE_DYNAMIC_LINKAGE == 0
#       pragma warn( "No dynamic linkage" )
#       define _OgreSQLExport
#   else
#       ifdef OGRESQL_EXPORTS
#           define _OgreSQLExport __declspec(dllexport)
#       else
#           define _OgreSQLExport __declspec(dllimport)
#       endif
#   endif
#else
#   define _OgreSQLExport
#endif

namespace Ogre {

    // Predeclare classes
    class OgreSQL;
    class OgreSQLArchiveFactory;

}


#endif