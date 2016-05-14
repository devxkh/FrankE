set(INCROOTENET ${PROJECT_SOURCE_DIR}/src/ThirdParty/enet/include/enet)
set(SRCROOTENET ${PROJECT_SOURCE_DIR}/src/ThirdParty/enet)

# all source files
set(SRC_ENET
        ${SRCROOTENET}/callbacks.c
        ${SRCROOTENET}/compress.c
        ${SRCROOTENET}/host.c
        ${SRCROOTENET}/list.c
        ${SRCROOTENET}/packet.c
        ${SRCROOTENET}/peer.c
        ${SRCROOTENET}/protocol.c
        ${SRCROOTENET}/unix.c
        ${SRCROOTENET}/win32.c
   
    ${INCROOTENET}/callbacks.h
 ${INCROOTENET}/enet.h
 ${INCROOTENET}/list.h
 ${INCROOTENET}/protocol.h
 ${INCROOTENET}/time.h
 ${INCROOTENET}/types.h
 ${INCROOTENET}/unix.h
 ${INCROOTENET}/utility.h
 ${INCROOTENET}/win32.h
)
source_group("enet" FILES ${SRC_ENET})

# Properties->C/C++->General->Additional Include Directories
# add sfml Network headers
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/enet/include)

# define the sfml-Network target
sfml_add_library(Enet  SOURCES  ${SRC_ENET})


macro(add_Shared target)

    # parse the arguments
    cmake_parse_arguments(THIS "GUI_APP" "" "SOURCES;DEPENDS" ${ARGN})

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})
	
  #create as executable
   #     add_executable(${target} ${THIS_SOURCES})

	#create as dll
     add_library(${target} SHARED ${THIS_SOURCES})

    # set the debug suffix
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "thirdparty")

    # for gcc >= 4.0 on Windows, apply the SFML_USE_STATIC_STD_LIBS option if it is enabled
    if(SFML_OS_WINDOWS AND SFML_COMPILER_GCC AND NOT SFML_GCC_VERSION VERSION_LESS "4")
        if(SFML_USE_STATIC_STD_LIBS AND NOT SFML_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
        elseif(NOT SFML_USE_STATIC_STD_LIBS AND SFML_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
        endif()
    endif()

	target_compile_definitions(${target} PUBLIC ENET_DLL)
	

	SET_TARGET_PROPERTIES(${target} PROPERTIES LINKER_LANGUAGE C)

    # link the target to its SFML dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})
    endif()

    # add the install rule
    install(TARGETS ${target}
            ARCHIVE DESTINATION ${INSTALL_MISC_DIR}/executables/${target} COMPONENT executables
			RUNTIME DESTINATION ${INSTALL_MISC_DIR}/executables/${target} COMPONENT executables
            BUNDLE DESTINATION ${INSTALL_MISC_DIR}/executables/${target} COMPONENT executables)

    # install the example's source code
    install(FILES ${THIS_SOURCES}
            DESTINATION ${INSTALL_MISC_DIR}/executables/${target}
            COMPONENT examples)

    # install the example's resources as well
    set(EXAMPLE_RESOURCES "${CMAKE_SOURCE_DIR}/executables/${target}/resources")
    if(EXISTS ${EXAMPLE_RESOURCES})
        install(DIRECTORY ${EXAMPLE_RESOURCES}
                DESTINATION ${INSTALL_MISC_DIR}/executables/${target}
                COMPONENT examples)
    endif()

endmacro()


 add_Shared(Enet_dll SOURCES ${SRC_ENET} DEPENDS wsock32 WinMM ws2_32)

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET Enet PROPERTY FOLDER "thirdparty")

