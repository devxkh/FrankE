
# XERenderer

# Collect sources into the variable XEngine_SOURCES without
# having to explicitly list each header and source file.
#
set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XERenderer)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XERenderer)

# all source files
set(XERenderer_SOURCES
   
     ${SRCROOT}/Renderable.cpp
      ${SRCROOT}/LightRenderable.cpp
#     ${SRCROOT}/StaticRenderable.cpp
 #    ${SRCROOT}/AnimationRenderable.cpp
  #   ${SRCROOT}/OgreCharEntity.cpp
    # ${SRCROOT}/OgreStaticEntity.cpp
     ${SRCROOT}/CameraRenderable.cpp
   ${SRCROOT}/OgreSceneManager.cpp
     ${SRCROOT}/GraphicsManager.cpp
	 ${SRCROOT}/OgreWorkspace.cpp
		${SRCROOT}/DrawDynamicLines.cpp
			${SRCROOT}/DrawDynamicLines.cpp
	
     ${SRCROOT}/Animation.cpp
)
source_group("src" FILES ${XERenderer_SOURCES})

# all header files
set(XERenderer_HEADER
	 ${INCROOT}/GraphicsManager.hpp
	  ${INCROOT}/Animation.h
	 ${INCROOT}/Renderable.hpp
	 ${INCROOT}/LightRenderable.hpp
#	 ${INCROOT}/StaticRenderable.hpp
#	 ${INCROOT}/AnimationRenderable.hpp
#	 ${INCROOT}/OgreStaticEntity.hpp
	# ${INCROOT}/OgreCharEntity.hpp
	  ${INCROOT}/CameraRenderable.hpp
	  ${INCROOT}/OgreSceneManager.hpp
	${INCROOT}/OgreWorkspace.hpp
	${INCROOT}/DrawDynamicLines.hpp
	
	 ${INCROOT}/AnimationRenderable.hpp
	# ${INCROOT}/RenderableComponents.hpp
)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XERenderer_HEADER})





set(XERenderer_private_SOURCES
		${SRCROOT}/private/DynamicLines.cpp
		${SRCROOT}/private/DynamicRenderable.cpp
		${SRCROOT}/private/DynamicLines.hpp
		${SRCROOT}/private/DynamicRenderable.hpp
		${SRCROOT}/private/ManualObject.hpp
		${SRCROOT}/private/ManualObject.cpp
)
source_group("src\\private" FILES ${XERenderer_private_SOURCES})



# ----------------------- XEGraphics_SOURCES -------------------------------
set(XEGraphics_SOURCES
    ${SRCROOT}/GUI/GorillaRenderer.cpp
	 ${SRCROOT}/GUI/WLayer.cpp
#	 ${SRCROOT}/GUI/WScreen.cpp
	 ${SRCROOT}/GUI/WRectangle.cpp
	 ${SRCROOT}/GUI/WCaption.cpp
	 ${SRCROOT}/GUI/WMarkup.cpp
	# ${SRCROOT}/GUI/WScreenRenderable.cpp
	 ${SRCROOT}/GUI/GUIRenderer.cpp
	 ${SRCROOT}/GUI/LayerRenderer.cpp
	 ${SRCROOT}/GUI/RenderableShape.cpp
	 ${SRCROOT}/GUI/RenderableLayer.cpp
	
	# ${SRCROOT}/GUI/Screen.cpp
	# ${SRCROOT}/GUI/ScreenRenderable.cpp
	
)
source_group("src\\GUI" FILES ${XEGraphics_SOURCES})

# ----------------------- header files -------------------------------
set(XEGraphics_HEADER
	 ${INCROOT}/GUI/GorillaRenderer.hpp
	 ${INCROOT}/GUI/WLayer.hpp
#	 ${INCROOT}/GUI/WScreen.hpp
	 ${INCROOT}/GUI/WRectangle.hpp
	 ${INCROOT}/GUI/WCaption.hpp
	 ${INCROOT}/GUI/WMarkup.hpp
	# ${INCROOT}/GUI/WScreenRenderable.hpp
	 ${INCROOT}/GUI/GUIRenderer.hpp
	 ${INCROOT}/GUI/RenderableShape.hpp
	 ${INCROOT}/GUI/LayerRenderer.hpp
	${INCROOT}/GUI/RenderableLayer.hpp
	
	# ${INCROOT}/GUI/Screen.hpp
	# ${INCROOT}/GUI/ScreenRenderable.hpp

)
source_group("include\\GUI" FILES ${XEGraphics_HEADER}) # Create named folders for the sources within the .vcproj




# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src)

include_directories (${PROJECT_SOURCE_DIR}/src/include/XERenderer/Physics)
include_directories (${PROJECT_SOURCE_DIR}/src/src/XERenderer/Physics)

#include_directories (${PROJECT_SOURCE_DIR}/extlibs/headers/luajit)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/lua_5_2_3/src)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Terrain/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/OgreMain/include)


include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Common/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Pbs/include)

include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include/GLSL)

include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)

##################################################################

# Properties->C/C++->General->Additional Include Directories
#include_directories (.)


# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XERenderer ${XERenderer_SOURCES} ${XERenderer_HEADER} ${Physics_SOURCES})

# define the sfml-graphics target
sfml_add_library(XERenderer 
	SOURCES ${XERenderer_SOURCES} ${XERenderer_HEADER} ${XERenderer_private_SOURCES} ${XEGraphics_HEADER} ${XEGraphics_SOURCES}

	DEPENDS OgreMain XEDAL 
	RenderSystem_GL3Plus 
#	RenderSystem_Direct3D11
	OgreHlmsPbs OgreHlmsUnlit
	#OgreTerrain OgrePaging
	EXTERNAL_LIBS ${XERenderer_EXT_LIBS})

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XERenderer PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XERenderer
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)