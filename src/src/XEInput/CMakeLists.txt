# XEInput

# ------------------ Thor -------------------------------
set(INCTHOR ${PROJECT_SOURCE_DIR}/src/ThirdParty/thor/include/thor)
set(SRCTHOR ${PROJECT_SOURCE_DIR}/src/ThirdParty/thor/src)

set(SRC_THOR
    ${SRCTHOR}/Action.cpp
   ${SRCTHOR}/ActionOperations.cpp
   ${SRCTHOR}/Connection.cpp
#   ${SRCTHOR}/InputNames.cpp
   ${SRCTHOR}/ThorJoystick.cpp
   ${SRCTHOR}/ToString.cpp
)

source_group("thor\\src" FILES ${SRC_THOR})

set(INC_THOR
    ${INCTHOR}/Config.hpp
    ${INCTHOR}/Input.hpp
)

source_group("thor\\include" FILES ${INC_THOR})


set(INC_THOR_INPUT
	${INCTHOR}/Input/Action.hpp	
	${INCTHOR}/Input/ActionContext.hpp	
	${INCTHOR}/Input/ActionMap.hpp	
	${INCTHOR}/Input/Connection.hpp	
	${INCTHOR}/Input/EventSystem.hpp	
	#${INCTHOR}/Input/InputNames.hpp	
	${INCTHOR}/Input/Joystick.hpp
)

source_group("thor\\include\\Input" FILES ${INC_THOR_INPUT})


set(INC_THOR_INPUT_DETAIL
	${INCTHOR}/Input/Detail/ActionMap.inl	
	${INCTHOR}/Input/Detail/ActionOperations.hpp	
	${INCTHOR}/Input/Detail/ConnectionImpl.hpp	
	${INCTHOR}/Input/Detail/EventListener.hpp	
	${INCTHOR}/Input/Detail/EventSystem.inl
)

source_group("thor\\include\\Input\\Detail" FILES ${INC_THOR_INPUT_DETAIL})

#set(XEInput_SOURCES ${PROJECT_SOURCE_DIR}/src/src/XEInput/InputConfigFile.cpp)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
#source_group("src" FILES ${XEInput_SOURCES})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ThirdParty/Aurora/include DESTINATION .)

# define the sfml-window target
sfml_add_library(XEInput
                 SOURCES ${INC_THOR} ${SRC_THOR}  ${INC_THOR_INPUT}  ${INC_THOR_INPUT_DETAIL} 
                 DEPENDS OgreMain XESystem SDL2lib
                 EXTERNAL_LIBS ${WINDOW_EXT_LIBS})

#set_target_properties(XEInput PROPERTIES DEFINE_SYMBOL THOR_EXPORTS SFML_WINDOW_EXPORTS)
target_compile_definitions(XEInput PUBLIC THOR_EXPORTS PUBLIC SFML_WINDOW_EXPORTS)


# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEInput PROPERTY FOLDER "libraries")
