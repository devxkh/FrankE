
# XETUI

# --------------------------- Common Files for Testproject ----------------
set(TESTCOMMONROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETCommon)

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETUI)

set(XETCommon_SOURCES
    ${TESTCOMMONROOT}/TestController.cpp
	 ${TESTCOMMONROOT}/TestScene.cpp
    ${TESTCOMMONROOT}/TestControllerSystem.cpp
    ${TESTCOMMONROOT}/Controllers_generated.h
    ${TESTCOMMONROOT}/Netmsg_generated.h
#	${SRCROOT}/GUI.h
)
source_group("src\\common" FILES ${XETCommon_SOURCES})

# all header files
set(XETCommon_HEADER
    ${TESTCOMMONROOT}/TestController.hpp
     ${TESTCOMMONROOT}/TestScene.hpp
	${TESTCOMMONROOT}/TestControllerSystem.hpp
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include\\common" FILES ${XETCommon_HEADER})

# --------------------------- End Common Files for Testproject ----------------


# all source files
set(XETUI_SOURCES
    ${SRCROOT}/main.cpp
	${SRCROOT}/TestMenuState.cpp
	${SRCROOT}/UIState_1.cpp
	${SRCROOT}/UIState_2.cpp
	
#	${SRCROOT}/GUI.h
)
source_group("src" FILES ${XETUI_SOURCES})

# all header files
set(XETUI_HEADER
#	${SRCROOT}/GUI.h
	${SRCROOT}/TestMenuState.hpp
	${SRCROOT}/UIState_1.h
	${SRCROOT}/UIState_2.h
	
	
    ${INCROOT}/XEController.hpp
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XETUI_HEADER})


# define the opengl target
sfml_add_example(XETUI GUI_APP
                 SOURCES ${XETUI_SOURCES} ${XETUI_HEADER} ${XETCommon_HEADER} ${XETCommon_SOURCES}
                 DEPENDS XEngine ${ADDITIONAL_LIBRARIES})

# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
#set_property(TARGET XETUI PROPERTY FOLDER "Tests")


	set (dllSrc	${PROJECT_SOURCE_DIR}/extlibs/bin/x64/fmodL64.dll)
#endif()

message(STATUS  "FMOD source dll: " ${dllSrc})

#http://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
add_custom_command(TARGET XETUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${dllSrc}
        $<TARGET_FILE_DIR:XETUI>)

