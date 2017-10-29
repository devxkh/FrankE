
#XEngine lib

# Collect sources into the variable XEngine_SOURCES without
# having to explicitly list each header and source file.
#

add_subdirectory(XEngine/Animation)

# ---------------- XEAudio -----------------------

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEAudio)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEAudio)

# all source files
set(XEAudio_SOURCES
 #   ${SRCROOT}/ResourceStream.cpp
	 
#	 ${SRCROOT}/ResourceStream.hpp
   #  ${SRCROOT}/XESoundFactory.cpp
	 ${SRCROOT}/SoundHandle.cpp
	 ${SRCROOT}/SoundListener.cpp
	 ${SRCROOT}/SoundManager.cpp
)

source_group("src\\audio" FILES ${XEAudio_SOURCES})

# all header files
set(XEAudio_HEADER
#	 ${INCROOT}/XESoundFactory.hpp
     ${INCROOT}/SoundHandle.hpp
     ${INCROOT}/SoundListener.hpp
	 ${INCROOT}/SoundManager.hpp
)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include\\audio" FILES ${XEAudio_HEADER})

#----------------------------------------------


set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src)

set(XEngineModules_SOURCES
    ${INCROOT}/XEInput.hpp
    ${INCROOT}/XESystem.hpp
   # ${INCROOT}/XEEntity.hpp 
    ${INCROOT}/XENetwork.hpp 
	${INCROOT}/XEUI.hpp
	${INCROOT}/XEAudio.hpp
	${INCROOT}/XERenderer.hpp
)
source_group("include\\modules" FILES ${XEngineModules_SOURCES})



set(SCRIPTINCROOT ${PROJECT_SOURCE_DIR}/src/include/XEScripts)
set(SCRIPTSRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEScripts)

# ----------------------- XEScripts_SOURCES -------------------------------
set(XEScripts_SOURCES
    ${SCRIPTSRCROOT}/LuaEngine.cpp
)
source_group("src\\Scripts" FILES ${XEScripts_SOURCES})


# ----------------------- header files -------------------------------
set(XEScripts_HEADER
	 ${SCRIPTINCROOT}/LUAEngine.h 
	 ${SCRIPTINCROOT}/luna.h
)
source_group("include\\Scripts" FILES ${XEScripts_HEADER}) # Create named folders for the sources within the .vcproj

# ----------------------- XEScripts_Sol files -------------------------------
set(SolROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sol)

set(XEScripts_LUAHEADER
	 ${SCRIPTINCROOT}/LUA/LuaQuaternion.hpp
	 ${SCRIPTINCROOT}/LUA/LuaVector3.hpp
	 ${SolROOT}/sol.hpp
)
source_group("include\\Scripts\\LUA" FILES ${XEScripts_LUAHEADER}) 

set(SolROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sol)

set(XEScripts_LUASRC
	 ${SCRIPTSRCROOT}/LUA/LuaQuaternion.cpp
	 ${SCRIPTSRCROOT}/LUA/LuaVector3.cpp
	 
	# ${SCRIPTSRCROOT}/LUA/LuaMathAPI.c
)
source_group("src\\Scripts\\LUA" FILES ${XEScripts_LUASRC}) 


# ----------------------- Properties->C/C++->General->Additional Include Directories -------------------------------
#include_directories (${PROJECT_SOURCE_DIR}/src/include)


#file(GLOB XEScripts_SOURCES *.cpp)
#file(GLOB XEScripts_HEADER *.hpp)

# Properties->C/C++->General->Additional Include Directories
#include_directories (.)


#target_compile_definitions(XEScripts PUBLIC XESCRIPTS_EXPORTS)


####################### Controller ################################
# all source files
set(XEController_SOURCES
#	 ${SRCROOT}/XEngine/Controller/ControllerManager.cpp
	${SRCROOT}/XEngine/Controller/SDLInputHandler.cpp
	${SRCROOT}/XEngine/Controller/WindowManager.cpp
)

source_group("src\\controller" FILES ${XEController_SOURCES})

# all header files
set(XEController_HEADER
#	  ${INCROOT}/XEngine/Controller/InputCmd.hpp
#	 ${INCROOT}/XEngine/Controller/ControllerManager.hpp
	${INCROOT}/XEngine/Controller/SDLInputHandler.hpp
	${INCROOT}/XEngine/Controller/WindowManager.hpp

)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include\\controller" FILES ${XEController_HEADER})



# all source files
set(XEController_UI_SOURCES
	 ${SRCROOT}/XEngine/Controller/UI/UI_Console.cpp
	 ${SRCROOT}/XEngine/Controller/UI/UIFrameStatState.cpp
)
source_group("src\\controller\\UI" FILES ${XEController_UI_SOURCES})

# all header files
set(XEController_UI_HEADER
	 ${INCROOT}/XEngine/Controller/UI/UIFrameStatState.hpp
	 ${INCROOT}/XEngine/Controller/UI/UI_Console.hpp
)
source_group("include\\controller\\UI" FILES ${XEController_UI_HEADER})


####################### main ################################

# all header files
set(XESystems_HEADER
	 ${INCROOT}/XEngine/Systems/SpawnSystem.hpp
     ${INCROOT}/XEngine/Systems/RenderBodySystem.hpp
	 ${INCROOT}/XEngine/Systems/EntityRenderSystem.hpp
	 ${INCROOT}/XEngine/Systems/FreeLookCameraSystem.hpp
	 ${INCROOT}/XEngine/Systems/PhysicsSystem.hpp
	 ${INCROOT}/XEngine/Systems/AnimationSystem.hpp
)
source_group("include\\systems" FILES ${XESystems_HEADER})

set(XESystems_SOURCES
	  ${SRCROOT}/XEngine/Systems/AnimationSystem.cpp
	  ${SRCROOT}/XEngine/Systems/FreeLookCameraSystem.cpp
	  ${SRCROOT}/XEngine/Systems/PhysicsSystem.cpp
	  ${SRCROOT}/XEngine/Systems/RenderBodySystem.cpp
	  ${SRCROOT}/XEngine/Systems/SpawnSystem.cpp
)
source_group("src\\systems" FILES ${XESystems_SOURCES})


# all header files
set(XEComponents_HEADER
	${INCROOT}/XEngine/Components/NetId.hpp
	${INCROOT}/XEngine/Components/SpawnPointComponent.hpp
    ${INCROOT}/XEngine/Components/SpawnComponent.hpp
	${INCROOT}/XEngine/Components/Controller.hpp
    ${INCROOT}/XEngine/Components/CameraFree.hpp
	${INCROOT}/XEngine/Components/CameraFix.hpp
	${INCROOT}/XEngine/Components/Body.hpp
	${INCROOT}/XEngine/Components/AnimationComponent.hpp
	${INCROOT}/XEngine/Components/ScreenComponent.hpp
	${INCROOT}/XEngine/Components/PhysicsComponents.hpp
)
source_group("include\\components" FILES ${XEComponents_HEADER})

set(XEComponents_SOURCES
	${SRCROOT}/XEngine/Components/Controller.cpp
	${SRCROOT}/XEngine/Components/Body.cpp
	${SRCROOT}/XEngine/Components/CameraFree.cpp
	${SRCROOT}/XEngine/Components/CameraFix.cpp
	${SRCROOT}/XEngine/Components/AnimationComponent.cpp
	${SRCROOT}/XEngine/Components/ScreenComponent.cpp 
	${SRCROOT}/XEngine/Components/PhysicsComponent.cpp
	${SRCROOT}/XEngine/Components/SpawnPointComponent.cpp
	${SRCROOT}/XEngine/Components/SpawnComponent.cpp
)
source_group("src\\components" FILES ${XEComponents_SOURCES})




#---------------- Extern ----------------------
# all source files
set(XEEngineExtern_SOURCES
   
     ${SRCROOT}/XEngine/Extern/Extern.cpp
 
)
source_group("src\\extern" FILES ${XEEngineExtern_SOURCES})

# all header files
set(XEEngineExtern_HEADER
	 ${INCROOT}/XEngine/Extern/Extern.h
)

source_group("include\\extern" FILES ${XEEngineExtern_HEADER})


#--------------------------------------
set(XEngine_main_INCLUDES
    ${INCROOT}/XEngine/XENetObserver.hpp
     ${INCROOT}/XEngine/OgreLogListener.hpp
   ${INCROOT}/XEngine/Scene.hpp
    ${INCROOT}/XEngine/Settings.hpp
    ${INCROOT}/XEngine/Node.hpp
	
    ${INCROOT}/XEngine/EntityHolder.hpp
)
source_group("include\\main" FILES ${XEngine_main_INCLUDES})


set(XEngine_main_SOURCES
    ${SRCROOT}/XEngine/Scene.cpp
    ${SRCROOT}/XEngine/Settings.cpp
    ${SRCROOT}/XEngine/OgreLogListener.cpp
    ${SRCROOT}/XEngine/Node.cpp
    ${SRCROOT}/XEngine/XENetObserver.cpp
)
source_group("src\\main" FILES ${XEngine_main_SOURCES})

# all source files
set(XEngine_SOURCES
    ${SRCROOT}/XEngine.cpp
)
source_group("src" FILES ${XEngine_SOURCES})

set(XEngine_math_INCLUDES
   # ${INCROOT}/XEngine/Math/Quaternion.hpp
)
source_group("include\\math" FILES ${XEngine_math_INCLUDES})


# all header files
set(XEngine_HEADER
    ${INCROOT}/XEngine.hpp 
	
    #  ${INCROOT}/OgreBuildSettings.h
    ${INCROOT}/XEState.h
)


#set(XEngine_UI_INCLUDE
#    ${INCROOT}/XEngine/UI/UIFrameStatState.hpp
#)
#source_group("include\\UI" FILES ${XEngine_UI_INCLUDE})

#set(XEngine_UI_SOURCES
#    ${SRCROOT}/XEngine/UI/UIFrameStatState.cpp
#)
#source_group("src\\UI" FILES ${XEngine_UI_SOURCES})

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XEngine_HEADER})



#--------------------------- MAIN - SFML ----------------------------
set(INCROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include/SFML/Main)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src/SFML/Main)

# sources
if(SFML_OS_WINDOWS)
    set(SRC ${SRC} ${SRCROOT}/MainWin32.cpp)
elseif(SFML_OS_IOS)
    set(SRC ${SRC} ${SRCROOT}/MainiOS.mm)
elseif(SFML_OS_ANDROID)
    set(SRC ${SRC} ${SRCROOT}/MainAndroid.cpp)
else()
    return()
endif()
source_group("src\\main" FILES ${SRC})

# define the sfml-main target
#add_library(sfml-main STATIC ${SRC})

# set the debug suffix
#set_target_properties(sfml-main PROPERTIES DEBUG_POSTFIX -d)

# insert the major version number in the output filename
#set_target_properties(sfml-main PROPERTIES OUTPUT_NAME "sfml-main")

# set the target's folder (for IDEs that support it, e.g. Visual Studio)
#set_target_properties(sfml-main PROPERTIES FOLDER "SFML")

# setup the install rule
#install(TARGETS sfml-main ARCHIVE DESTINATION lib${LIB_SUFFIX} COMPONENT devel)

# because of a current limitation on Android (which prevents one library
# from depending on shared libraries), we need a boostrap activity which
# will load our shared libraries manually
#if(SFML_OS_ANDROID)
#todo !!!! -----	sfml_add_library(sfml-activity SOURCES ${PROJECT_SOURCE_DIR}/src/SFML/Main/SFMLActivity.cpp)
#endif()


#must be set in projects cmake file
source_group("src\\Animation" FILES ${XEAnimation_SOURCES})
source_group(src\\Animation\\Helper FILES ${XEAnimationHelper_SOURCES})
source_group("include\\Animation\\XML" FILES ${XEScripts_TINYXML_HEADER}) # Create named folders for the sources within the .vcproj
source_group("src\\Animation\\Animation" FILES ${XEEngineAnimation_SOURCES})
source_group("include\\Animation" FILES ${XEAnimation_HEADER})
source_group("src\\Animation\\Nodes" FILES ${XEAnimationNodes_SOURCES})
source_group("src\\Animation\\Property" FILES ${XEAnimationProp_SOURCES})
source_group("include\\Animation\\Animation" FILES ${XEEngineAnimation_HEADER})



list(APPEND XEDAL_EXT_LIBS ${PHYSFSFILE_LIBRARIES})

message("PHYSFSFILE_LIBRARIES:" ${PHYSFSFILE_LIBRARIES})

list(APPEND XEDAL_EXT_LIBS ${FMODFILE_LIBRARY})

message("XEngine_EXT_LIBS:" ${XEngine_EXT_LIBS})

enable_unity_build(XEngine  ${XEngine_SOURCES}  ${XEngineModules_SOURCES}  ${SRC} ${XEngine_UI_SOURCES}  ${XEEngineRTOS_SOURCES} ${XEEngineRTC_SOURCES}
		  ${XEComponents_SOURCES}  ${XESystems_SOURCES}
		 ${XEngine_main_SOURCES} 
			 ${XEEngineAnimation_SOURCES}
				 ${XEAudio_SOURCES} 
			${XEScripts_SOURCES}${XEScripts_LUASRC}
	 ${XEController_SOURCES}  ${XEController_UI_SOURCES} 
	  ${XEAnimation_SOURCES} ${XEAnimationNodes_SOURCES} ${XEAnimationProp_SOURCES}
	 ${XEAnimationHelper_SOURCES})


#----------------------------------------------------------------
# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XEngine ${XEngine_SOURCES}) 
                     #   ${SIMPLE_FUNCTION_SOURCES} 
                    #    ${ADVANCED_FUNCTION_SOURCES})
# define the sfml-graphics target
sfml_add_library(XEngine
	SOURCES ${XEngine_SOURCES} ${XEngine_HEADER} ${XEngineModules_SOURCES}  ${SRC} ${XEngine_UI_SOURCES} ${XEngine_UI_INCLUDE} ${XEEngineRTOS_SOURCES} ${XEEngineRTC_SOURCES}
		 ${XEComponents_HEADER} ${XEComponents_SOURCES} ${XESystems_HEADER} ${XESystems_SOURCES}
		${XEngine_main_INCLUDES} ${XEngine_main_SOURCES} ${XEngine_math_INCLUDES}
			${XEEngineAnimation_HEADER} ${XEEngineAnimation_SOURCES}
			${XEEngineExtern_HEADER} ${XEEngineExtern_SOURCES}
				 ${XEAudio_SOURCES} ${XEAudio_HEADER} 
			${XEScripts_SOURCES} ${XEScripts_HEADER} ${XEScripts_LUASRC} ${XEScripts_LUAHEADER}
	 ${XEController_SOURCES} ${XEController_HEADER} ${XEController_UI_SOURCES} ${XEController_UI_HEADER}

	  ${XEAnimation_SOURCES} ${XEAnimation_HEADER} ${XEAnimationNodes_SOURCES} ${XEAnimationProp_SOURCES}
	 #${XEAnimation_Ogre_SOURCES} 	${XEAnimation_Ogre_INCLUDES}
	 ${XEAnimationHelper_SOURCES} ${XEScripts_TINYXML_HEADER} 

	DEPENDS OgreMain XEDAL XEUI XERenderer XEEffect XEInput liblua SDL2lib # XEMath
	 XEPhysics XESystem XEUI XENetwork Enet 
	#OgreTerrain OgrePaging XEAnimation 
	EXTERNAL_LIBS ${XEngine_EXT_LIBS})


# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEngine PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

#for xeanimation
target_compile_definitions(XEngine PUBLIC XEANIMATION_EXPORTS)
target_compile_definitions(XEngine PUBLIC OGRE_STATIC_LIB)

target_compile_definitions(XEngine PUBLIC NOMINMAX) #FIX https://github.com/google/flatbuffers/issues/105

# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEngine
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)


# Sub-directories where more CMakeLists.txt exist
#add_subdirectory(XEController)
#add_subdirectory(XEEntity)
add_subdirectory(XERenderer)
add_subdirectory(XEInput)
add_subdirectory(XESystem)
add_subdirectory(XENetwork)

#add_subdirectory(XEAudio)
add_subdirectory(XEDAL)
#add_subdirectory(XEDebugger)
add_subdirectory(XEEffect)
#add_subdirectory(XEMath)
add_subdirectory(XEPhysics)



add_subdirectory(XEUI)

#add_subdirectory(XEEditor)
