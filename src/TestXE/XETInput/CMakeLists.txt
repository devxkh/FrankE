
# XETInput

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETInput)

# all source files
set(XETInput_SOURCES
    ${SRCROOT}/main.cpp
	${SRCROOT}/WindowState.cpp
)
source_group("src" FILES ${XETInput_SOURCES})

# all header files
set(XETInput_HEADER
	${SRCROOT}/WindowState.hpp
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XETInput_HEADER})


# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/TestXE/XETInput)
include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_SOURCE_DIR}/src/include)
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


include_directories (${PROJECT_SOURCE_DIR}/extlibs/headers/luajit)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/google/flatbuffers/include)
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/enet)

# ogre buildsettings
include_directories (${PROJECT_BINARY_DIR}/src/Ogre/include)

# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
#add_executable (XETInput ${XETInput_SOURCES} ${XETInput_HEADER})


# Properties->Linker->Input->Additional Dependencies
#target_link_libraries (XETInput XEngine)

##
# find libraries
 #       find_sfml_dependency(PHYSFS_LIBRARY "physfs" "physfs")
      



# Adds logic to INSTALL.vcproj to copy math.dll to destination directory
#install (TARGETS XETInput
#         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

# find OpenGL and GLU
#find_package(physfs REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIR})

  
#find_sfml_dependency(SNDFILE_LIBRARY "libsndfile" physfs)

######set(ADDITIONAL_LIBRARIES XEGraphics ${PHYSFSFILE_LIBRARY}) #${SNDFILE_LIBRARY}) #${OPENGL_LIBRARIES})

# define the opengl target
sfml_add_example(XETInput GUI_APP
                 SOURCES ${XETInput_SOURCES} ${XETInput_HEADER}
                 DEPENDS XEngine ${ADDITIONAL_LIBRARIES})

# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
#set_property(TARGET XETInput PROPERTY FOLDER "Tests")

