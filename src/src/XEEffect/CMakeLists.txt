
# XEEffect

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEEffect)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEEffect)

# ----------------------- XEEffect_SOURCES -------------------------------
set(XEEffect_SOURCES
    #${SRCROOT}/IDAL.cpp
)
source_group("src" FILES ${XEEffect_SOURCES})

# ----------------------- XEEffect_Decal_SOURCES -------------------------------
set(XEEffect_Decal_SOURCES
    ${SRCROOT}/Decal/DecalCursor.cpp
     ${SRCROOT}/Decal/DecalUtility.cpp
     ${SRCROOT}/Decal/OgreDecal.cpp
     ${SRCROOT}/Decal/ProjectiveDecal.cpp
)
source_group("src\\Decal" FILES ${XEEffect_Decal_SOURCES})


# ----------------------- header files -------------------------------
set(XEEffect_HEADER
	 ${INCROOT}/Decal/DecalCursor.hpp
	 ${INCROOT}/Decal/DecalUtility.hpp
	 ${INCROOT}/Decal/OgreDecal.hpp
	 ${INCROOT}/Decal/ProjectiveDecal.hpp
)
source_group("include" FILES ${XEEffect_HEADER}) # Create named folders for the sources within the .vcproj

# ----------------------- Properties->C/C++->General->Additional Include Directories -------------------------------
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/OgreMain/include)
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)

#file(GLOB XEEffect_SOURCES *.cpp)
#file(GLOB XEEffect_HEADER *.hpp)

# Properties->C/C++->General->Additional Include Directories
include_directories (.)

# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables

# Also adds sources to the Solution Explorer ----------------------------------------------------------------------------------
#add_library(XEEffect ${XEEffect_SOURCES} ${XEEffect_HEADER} ${XEEffect_Decal_SOURCES})

# define the sfml-graphics target
sfml_add_library(XEEffect 
	SOURCES ${XEEffect_SOURCES} ${XEEffect_HEADER} ${XEEffect_Decal_SOURCES}
	DEPENDS OgreMain XEPhysics 
	EXTERNAL_LIBS ${XEEffect_EXT_LIBS})

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEEffect PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEEffect
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)