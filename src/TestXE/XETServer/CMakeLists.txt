
# XETServer

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETServer)

# all source files
set(XETServer_SOURCES
    ${SRCROOT}/main.cpp
	${SRCROOT}/ServerState.cpp
)
source_group("src" FILES ${XETServer_SOURCES})

# all header files
set(XETServer_HEADER
	${SRCROOT}/ServerState.hpp
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XETServer_HEADER})


# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/TestXE/XETServer)
include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/../XEngine/src/include/XEDAL/Objects) #flatbuffer file
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/src)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/thor/include)
include_directories (${PROJECT_SOURCE_DIR}/src/include/XEAnimation)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/OgreMain/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Terrain/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/bullet)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/Recast/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DebugUtils/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/Detour/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DetourCrowd/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DetourTileCache/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/OgreCrowd/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav)


include_directories (${PROJECT_SOURCE_DIR}/../XEngine/src/ThirdParty/Lua/src)
include_directories (${PROJECT_SOURCE_DIR}/../XEngine/src/ThirdParty/LuaJIT/src)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/google/flatbuffers/include)

include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/enet/include)

# ogre buildsettings
include_directories (${PROJECT_BINARY_DIR}/src/Ogre/include)

# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
#add_executable (XETServer ${XETServer_SOURCES} ${XETServer_HEADER})


# Properties->Linker->Server->Additional Dependencies
#target_link_libraries (XETServer XEngine)

##
# find libraries
 #       find_sfml_dependency(PHYSFS_LIBRARY "physfs" "physfs")
      



# Adds logic to INSTALL.vcproj to copy math.dll to destination directory
#install (TARGETS XETServer
#         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

# find OpenGL and GLU
#find_package(physfs REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIR})

  
#find_sfml_dependency(SNDFILE_LIBRARY "libsndfile" physfs)

######set(ADDITIONAL_LIBRARIES XEGraphics ${PHYSFSFILE_LIBRARY}) #${SNDFILE_LIBRARY}) #${OPENGL_LIBRARIES})

# define the opengl target
sfml_add_example(XETServer GUI_APP
                 SOURCES ${XETServer_SOURCES} ${XETServer_HEADER}
                 DEPENDS XEngine ${ADDITIONAL_LIBRARIES})

# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
#set_property(TARGET XETServer PROPERTY FOLDER "Tests")




	set (dllSrc	${PROJECT_SOURCE_DIR}/extlibs/bin/x64/fmodL64.dll)
#endif()

message(STATUS  "FMOD source dll: " ${dllSrc})

#http://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
add_custom_command(TARGET XETServer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${dllSrc}
        $<TARGET_FILE_DIR:XETServer>)