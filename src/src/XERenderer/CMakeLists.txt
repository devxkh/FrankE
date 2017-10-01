
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

set(XERenderer_Resources_SOURCES
   
	${SRCROOT}/Resource/gltfAsset.cpp
   	${SRCROOT}/Resource/XEMesh.cpp
    ${SRCROOT}/Resource/XEMaterial.cpp
)
source_group("src\\resource" FILES ${XERenderer_Resources_SOURCES})

set(XERenderer_Resources_HEADER
 
	${INCROOT}/Resource/gltfAsset.h
	${INCROOT}/Resource/XEMesh.hpp
	${INCROOT}/Resource/XEMaterial.hpp
)
source_group("include\\resource" FILES ${XERenderer_Resources_HEADER})


# ------------ Editor ---------------
set(XERenderer_Editor_SOURCES   
     ${SRCROOT}/Editor/LightVisualHelper.cpp
	 ${SRCROOT}/Editor/ImGuiRenderable.cpp	 
	 ${SRCROOT}/Editor/ImGuizmo.h
	 ${SRCROOT}/Editor/ImGuizmo.cpp
	 ${SRCROOT}/../../Thirdparty/imgui/imgui.cpp		
	 ${SRCROOT}/../../Thirdparty/imgui/imgui_draw.cpp 		
	 ${SRCROOT}/../../Thirdparty/imgui/imgui_demo.cpp
)
source_group("src\\Editor" FILES ${XERenderer_Editor_SOURCES})

set(XERenderer_Editor_HEADER
	 ${INCROOT}/Editor/LightVisualHelper.hpp
	
	 ${INCROOT}/Editor/ImguiManager.cpp	 
	 ${INCROOT}/Editor/ImguiManager.h	
	 ${INCROOT}/Editor/ImguiRenderable.cpp	 
	 
	 ${INCROOT}/Editor/ImGuiRenderable.h
)

source_group("include\\Editor" FILES ${XERenderer_Editor_HEADER})

# ------------ Hlms ---------------
set(XERenderer_Hlms_SOURCES   
     ${SRCROOT}/Hlms/XEHlmsProjection.cpp
     ${SRCROOT}/Hlms/XEHlmsUnlit.cpp
	 ${SRCROOT}/Hlms/XEHlmsUnlitDatablock.cpp
	 ${SRCROOT}/Hlms/XEHlmsJsonUnlit.cpp
)
source_group("src\\Hlms" FILES ${XERenderer_Hlms_SOURCES})

set(XERenderer_Hlms_HEADER
	 ${INCROOT}/Hlms/XEHlmsProjection.hpp
	 ${INCROOT}/Hlms/XEHlmsUnlit.hpp
	 ${INCROOT}/Hlms/XEHlmsUnlitDatablock.hpp
	 ${INCROOT}/Hlms/XEHlmsJsonUnlit.hpp
)

source_group("include\\Hlms" FILES ${XERenderer_Hlms_HEADER})


# ------------ Animation ---------------
set(XERenderer_Animation_SOURCES   
     ${SRCROOT}/Animation/TextureAnimationController.cpp
)
source_group("src\\Animation" FILES ${XERenderer_Animation_SOURCES})

set(XERenderer_Animation_HEADER
	 ${INCROOT}/Animation/TextureAnimationController.hpp
)

source_group("include\\Animation" FILES ${XERenderer_Animation_HEADER})


set(XERenderer_private_SOURCES
		${SRCROOT}/private/DebugRenderer.cpp
		${SRCROOT}/private/DebugRenderer.hpp
		${SRCROOT}/private/DynamicLines.cpp
		${SRCROOT}/private/DynamicRenderable.cpp
		${SRCROOT}/private/DynamicLines.hpp
		${SRCROOT}/private/DynamicRenderable.hpp
		${SRCROOT}/private/ScreenRenderable.hpp
	#	${SRCROOT}/private/gltf_loader.h
	#	${SRCROOT}/private/OgreHelper.cpp
	#	${SRCROOT}/private/OgreHelper.hpp
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
	${INCROOT}/GUI/Font.hpp
)
source_group("include\\GUI" FILES ${XEGraphics_HEADER})


include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Common/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/Components/Hlms/Pbs/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/RenderSystems/GL3Plus/include/GLSL)

enable_unity_build(XERenderer  ${XERenderer_SOURCES} ${XERenderer_private_SOURCES} ${XEGraphics_SOURCES}  ${XERenderer_Editor_SOURCES})


sfml_add_library(XERenderer 
	SOURCES ${XERenderer_SOURCES} ${XERenderer_HEADER} ${XERenderer_private_SOURCES} ${XEGraphics_HEADER} ${XEGraphics_SOURCES} ${XERenderer_Editor_HEADER} ${XERenderer_Editor_SOURCES}
	 ${XERenderer_Hlms_HEADER} ${XERenderer_Hlms_SOURCES} ${XERenderer_Animation_HEADER} ${XERenderer_Animation_SOURCES} ${XERenderer_Resources_SOURCES} ${XERenderer_Resources_HEADER}
	DEPENDS OgreMain XEDAL 
	RenderSystem_GL3Plus 
#	RenderSystem_Direct3D11
	OgreHlmsPbs OgreHlmsUnlit
	EXTERNAL_LIBS ${XERenderer_EXT_LIBS})



set_property(TARGET XERenderer PROPERTY FOLDER "libraries")

#cotire(XERenderer)