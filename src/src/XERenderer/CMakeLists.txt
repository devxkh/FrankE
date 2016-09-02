
# XERenderer

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XERenderer)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XERenderer)

set(XERenderer_SOURCES
   
    ${SRCROOT}/Renderable.cpp
    ${SRCROOT}/DebugDrawer.cpp
    ${SRCROOT}/LightRenderable.cpp
    ${SRCROOT}/CameraRenderable.cpp
	${SRCROOT}/OgreSceneManager.cpp
    ${SRCROOT}/GraphicsManager.cpp
	${SRCROOT}/OgreWorkspace.cpp
	${SRCROOT}/DrawDynamicLines.cpp
    ${SRCROOT}/Animation.cpp
)
source_group("src" FILES ${XERenderer_SOURCES})

set(XERenderer_HEADER
	 ${INCROOT}/GraphicsManager.hpp
	 ${INCROOT}/Animation.h
	 ${INCROOT}/Renderable.hpp
	 ${INCROOT}/DebugDrawer.hpp
	 ${INCROOT}/LightRenderable.hpp
	 ${INCROOT}/CameraRenderable.hpp
	 ${INCROOT}/OgreSceneManager.hpp
	 ${INCROOT}/OgreWorkspace.hpp
	 ${INCROOT}/DrawDynamicLines.hpp
	 ${INCROOT}/AnimationRenderable.hpp
)
source_group("include" FILES ${XERenderer_HEADER})


# ------------ Editor ---------------
set(XERenderer_Editor_SOURCES   
     ${SRCROOT}/Editor/LightVisualHelper.cpp
)
source_group("src\\Editor" FILES ${XERenderer_Editor_SOURCES})

set(XERenderer_Editor_HEADER
	 ${INCROOT}/Editor/LightVisualHelper.hpp
)

source_group("include\\Editor" FILES ${XERenderer_Editor_HEADER})



set(XERenderer_private_SOURCES
		${SRCROOT}/private/DebugRenderer.cpp
		${SRCROOT}/private/DebugRenderer.hpp
		${SRCROOT}/private/DynamicLines.cpp
		${SRCROOT}/private/DynamicRenderable.cpp
		${SRCROOT}/private/DynamicLines.hpp
		${SRCROOT}/private/DynamicRenderable.hpp
)
source_group("src\\private" FILES ${XERenderer_private_SOURCES})



# ----------------------- XEGraphics_SOURCES -------------------------------
set(XEGraphics_SOURCES
	${SRCROOT}/GUI/GorillaRenderer.cpp
	${SRCROOT}/GUI/WLayer.cpp
	${SRCROOT}/GUI/WRectangle.cpp
	${SRCROOT}/GUI/WCaption.cpp
	${SRCROOT}/GUI/WMarkup.cpp
	${SRCROOT}/GUI/GUIRenderer.cpp
	${SRCROOT}/GUI/LayerRenderer.cpp
	${SRCROOT}/GUI/RenderableShape.cpp
	${SRCROOT}/GUI/RenderableLayer.cpp	
)
source_group("src\\GUI" FILES ${XEGraphics_SOURCES})

# ----------------------- header files -------------------------------
set(XEGraphics_HEADER
	${INCROOT}/GUI/GorillaRenderer.hpp
	${INCROOT}/GUI/WLayer.hpp
	${INCROOT}/GUI/WRectangle.hpp
	${INCROOT}/GUI/WCaption.hpp
	${INCROOT}/GUI/WMarkup.hpp
	${INCROOT}/GUI/GUIRenderer.hpp
	${INCROOT}/GUI/RenderableShape.hpp
	${INCROOT}/GUI/LayerRenderer.hpp
	${INCROOT}/GUI/RenderableLayer.hpp
)
source_group("include\\GUI" FILES ${XEGraphics_HEADER})


include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Common/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Pbs/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include/GLSL)

sfml_add_library(XERenderer 
	SOURCES ${XERenderer_SOURCES} ${XERenderer_HEADER} ${XERenderer_private_SOURCES} ${XEGraphics_HEADER} ${XEGraphics_SOURCES} ${XERenderer_Editor_HEADER} ${XERenderer_Editor_SOURCES}

	DEPENDS OgreMain XEDAL 
	RenderSystem_GL3Plus 
#	RenderSystem_Direct3D11
	OgreHlmsPbs OgreHlmsUnlit
	EXTERNAL_LIBS ${XERenderer_EXT_LIBS})


set_property(TARGET XERenderer PROPERTY FOLDER "libraries")