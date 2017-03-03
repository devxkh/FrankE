
set(INCROOT ${PROJECT_SOURCE_DIR}/fbxtoogre/Inc)
set(SRCROOT ${PROJECT_SOURCE_DIR}/fbxtoogre/Src)

set(FBXTOOGRE_INCLUDES
    ${INCROOT}/_singleton.h
    ${INCROOT}/animation.h
    ${INCROOT}/blendshape.h
    ${INCROOT}/common.h
    ${INCROOT}/FBXSDKCommon.h
    ${INCROOT}/FxOgreFBXDLL.h
    ${INCROOT}/material.h
    ${INCROOT}/materialSet.h
    ${INCROOT}/mesh.h
    ${INCROOT}/ogreExporter.h
    ${INCROOT}/paramlist.h
    ${INCROOT}/scene.h
    ${INCROOT}/skeleton.h
    ${INCROOT}/submesh.h
    ${INCROOT}/vertex.h
    ${INCROOT}/xmlsupport.h
)
source_group("include" FILES ${FBXTOOGRE_INCLUDES})

set(FBXTOOGRE_SOURCES
  
	 ${SRCROOT}/blendshape.cpp
	 ${SRCROOT}/common.cpp
	 ${SRCROOT}/FxOgreFBXDLL.cpp
	 ${SRCROOT}/FxOgreFBXLog.cpp
	 ${SRCROOT}/material.cpp
	 ${SRCROOT}/materialSet.cpp
	 ${SRCROOT}/mesh.cpp
	 ${SRCROOT}/ogreExporter.cpp
	 ${SRCROOT}/paramlist.cpp
	 ${SRCROOT}/scene.cpp
	 ${SRCROOT}/skeleton.cpp
	 ${SRCROOT}/submesh.cpp
	 ${SRCROOT}/xmlsupport.cpp
)
source_group("src" FILES ${FBXTOOGRE_SOURCES})

set(ROOTP ${PROJECT_SOURCE_DIR}/fbxtoogre)

# ----------------------- header files -------------------------------
set(XEScripts_TINYXML_HEADER
     ${ROOTP}/tinyxml/tinyxml2.h
     ${ROOTP}/tinyxml/tinyxml2.cpp
     #${ROOTP}/tinyxml/tinystr.cpp
     #${ROOTP}/tinyxml/tinyxml.cpp
     #${ROOTP}/tinyxml/tinyxmlerror.cpp
     #${ROOTP}/tinyxml/tinyxmlparser.cpp
)
source_group("include\\XML" FILES ${XEScripts_TINYXML_HEADER}) # Create named folders for the sources within the .vcproj


set(FBXTOOGRE_INCLUDE_DIRECTORIES
  
F:/Projekte/coop/VEX/XTools/fbxtoogre/Inc
F:/Projekte/coop/ogre_main_build/include #todo use ogre cmake settings!!
F:/Projekte/coop/ogre_main/OgreMain/include
E:/Programme/Autodesk/FBX/FBX\ SDK/2016.1/include
F:/Projekte/coop/VEX/XTools/fbxtoogre/tinyxml
)


# Properties->C/C++->General->Additional Include Directories
# add sfml system headers
include_directories(${FBXTOOGRE_INCLUDE_DIRECTORIES})

# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer

# define the sfml-system target
add_library(FBXTOOGRE SHARED ${FBXTOOGRE_SOURCES} ${FBXTOOGRE_INCLUDES} ${XEScripts_TINYXML_HEADER})

# searching for include directory
#find_path(SIFTGPU_INCLUDE_DIR siftgpu.h)

## searching for library file
#find_library(FBXTOOGRE_LIBRARY siftgpu)
#
#if (SIFTGPU_INCLUDE_DIR AND SIFTGPU_LIBRARY)
#    # you may need that if further action in your CMakeLists.txt depends
#    # on detecting your library
#    set(SIFTGPU_FOUND TRUE)
#
#    # you may need that if you want to conditionally compile some parts
#    # of your code depending on library availability
#    add_definitions(-DHAVE_LIBSIFTGPU=1)
#
#    # those two, you really need
#    include_directories(${SIFTGPU_INCLUDE_DIR})
 set(YOUR_LIBRARIES 
	E:/Programme/Autodesk/FBX/FBX\ SDK/2016.1/lib/vs2015/x64/debug/libfbxsdk-mt.lib  # relase or debug!!

Advapi32.lib
Wininet.lib
F:/Projekte/coop/ogre_main_build/lib/Debug/OgreMainStatic_d.lib)

    set(YOUR_LIBRARIES ${YOUR_LIBRARIES})
#endif ()

target_link_libraries(FBXTOOGRE ${YOUR_LIBRARIES})


#add_definitions(-SFML_SYSTEM_EXPORTS)
set_target_properties(FBXTOOGRE PROPERTIES DEFINE_SYMBOL FBXTOOGRE_EXPORTS)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET FBXTOOGRE PROPERTY FOLDER "Tools")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XESystem
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
#		COMPONENT library)


add_subdirectory(Exec)

