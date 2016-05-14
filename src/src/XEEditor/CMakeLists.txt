
# XEEditor

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEEditor)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEEditor)

# ----------------------- XEEditor_Event_SOURCES -------------------------------
set(XEEditor_Event_SOURCES
     ${SRCROOT}/Event/ConvertEvent.hpp
)
source_group("src\\Event" FILES ${XEEditor_Event_SOURCES})

# ----------------------- XEEditor_SOURCES -------------------------------
set(XEEditor_SOURCES
     ${SRCROOT}/Editor.cpp
     ${SRCROOT}/EditorCommands.cpp
     ${SRCROOT}/IEditor.cpp
)
source_group("src" FILES ${XEEditor_SOURCES})

# ----------------------- XEEditor_Event_HEADERS ------------------------------
set(XEEditor_Event_HEADERS
     ${INCROOT}/Event/Config.h
     ${INCROOT}/Event/Event.h
     ${INCROOT}/Event/Keyboard.h
     ${INCROOT}/Event/Mouse.h
)
source_group("include\\Event" FILES ${XEEditor_Event_HEADERS})

# ----------------------- header files -------------------------------
set(XEEditor_HEADER
	 #${INCROOT}/TFViewport.h
	 #${INCROOT}/SelectionRectangle.h
	 ${INCROOT}/Editor.hpp
	 ${INCROOT}/EditorCommands.hpp
	 ${INCROOT}/IEditor.hpp
)
source_group("include" FILES ${XEEditor_HEADER}) # Create named folders for the sources within the .vcproj

# ----------------------- Properties->C/C++->General->Additional Include Directories -------------------------------
include_directories (${PROJECT_SOURCE_DIR}/src/TestXE/XETEditor)
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


#include_directories (${PROJECT_SOURCE_DIR}/extlibs/headers/luajit)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/google/flatbuffers/include)

# ogre buildsettings
include_directories (${PROJECT_BINARY_DIR}/src/Ogre/include)

#file(GLOB XEEditor_SOURCES *.cpp)
#file(GLOB XEEditor_HEADER *.hpp)

# Properties->C/C++->General->Additional Include Directories
include_directories (.)

# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables

# Also adds sources to the Solution Explorer ----------------------------------------------------------------------------------
#add_library(XEEditor ${XEEditor_SOURCES} ${XEEditor_HEADER} ${XEEditor_Decal_SOURCES})

# define the sfml-graphics target
add_library(XEEditor  SHARED 
	 ${XEEditor_SOURCES} ${XEEditor_Event_SOURCES} ${XEEditor_HEADER} ${XEEditor_Event_HEADERS}
	 )
	#EXTERNAL_LIBS ${XEEditor_EXT_LIBS} ${ADDITIONAL_LIBRARIES})

 # link the target to its SFML dependencies
 target_link_libraries(XEEditor XEngine)
 # link the target to its external dependencies
 target_link_libraries(XEEditor ${XEEditor_EXT_LIBS} ${ADDITIONAL_LIBRARIES})

target_compile_definitions(XEEditor PUBLIC XE_EDITOR_EXPORTS)
target_compile_definitions(XEEditor PUBLIC OGRE_STATIC_LIB)
	

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEEditor PROPERTY FOLDER "libraries")

set_property(TARGET XEEditor PROPERTY LINK_FLAGS "-shared-libgcc -shared-libstdc++")

# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEEditor
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)