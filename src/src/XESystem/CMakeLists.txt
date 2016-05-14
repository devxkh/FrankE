
set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src)

set(XESystemEntityINCLUDES
    ${INCROOT}/XESystem/Entityx/System.h
    ${INCROOT}/XESystem/Entityx/quick.h
    ${INCROOT}/XESystem/Entityx/Event.h
    ${INCROOT}/XESystem/Entityx/Entity.h
    ${INCROOT}/XESystem/Entityx/entityx.h
    ${INCROOT}/XESystem/Entityx/config.h.in
    ${INCROOT}/XESystem/Entityx/config.h
)
source_group("include\\entity" FILES ${XESystemEntityINCLUDES})

set(XESystemEntitySOURCES
  
	 ${INCROOT}/XESystem/Entityx/Entity.cc
	 ${INCROOT}/XESystem/Entityx/Event.cc
	 ${INCROOT}/XESystem/Entityx/System.cc
)
source_group("src\\entity" FILES ${XESystemEntitySOURCES})

set(XESystemEntitytags_INCLUDES
    ${INCROOT}/XESystem/Entityx/tags/TagsComponent.h
)
source_group("include\\entity\\tags" FILES ${XESystemEntitytags_INCLUDES})

set(XESystemEntitydeps_INCLUDES
    ${INCROOT}/XESystem/Entityx/deps/Dependencies.h
)
source_group("include\\entity\\deps" FILES ${XESystemEntitydeps_INCLUDES})

set(XESystemEntity3rdpartyINCLUDES
    ${INCROOT}/XESystem/Entityx/3rdparty/catch.hpp
	${INCROOT}/XESystem/Entityx/3rdparty/simplesignal.h
)
source_group("include\\entity\\deps" FILES ${XESystemEntity3rdpartyINCLUDES})

set(XESystemEntityhelp_INCLUDES
    ${INCROOT}/XESystem/Entityx/help/NonCopyable.h
    ${INCROOT}/XESystem/Entityx/help/Pool.h
    ${INCROOT}/XESystem/Entityx/help/Timer.h
)
source_group("include\\entity\\help" FILES ${XESystemEntityhelp_INCLUDES})


set(XESystemEntityhelp_SOURCES
  
	 ${INCROOT}/XESystem/Entityx/help/Pool.cc
	${INCROOT}/XESystem/Entityx/help/Timer.cc	
)
source_group("src\\entity\\help" FILES ${XESystemEntityhelp_SOURCES})


set(XESystemMath_INCLUDES
#  #${INCROOT}/XESystem/Math/AreaAllocator.h
#  ${INCROOT}/XESystem/Math/AxisAlignedBox.h
#  ${INCROOT}/XESystem/Math/Color.h
#  ${INCROOT}/XESystem/Math/Math.h
#  ${INCROOT}/XESystem/Math/Matrix3.h
#  ${INCROOT}/XESystem/Math/Matrix3x4.h
#  ${INCROOT}/XESystem/Math/Matrix4.h
#  ${INCROOT}/XESystem/Math/Plane.h
#    ${INCROOT}/XESystem/Math/PlaneBoundedVolume.h
#  ${INCROOT}/XESystem/Math/Ray.h
#  ${INCROOT}/XESystem/Math/Frustum.h
#  ${INCROOT}/XESystem/Math/Polyhedron.h
#  ${INCROOT}/XESystem/Math/Quaternion.h
#  ${INCROOT}/XESystem/Math/Random.h
#  ${INCROOT}/XESystem/Math/Rect.h
#  ${INCROOT}/XESystem/Math/Sphere.h
#  ${INCROOT}/XESystem/Math/StringHash.h
#  ${INCROOT}/XESystem/Math/Vector2.h
#  ${INCROOT}/XESystem/Math/Vector3.h
#  ${INCROOT}/XESystem/Math/Vector4.h
)
source_group("include\\math" FILES ${XESystemMath_INCLUDES})

set(XESystemMath_SOURCES
  
#  #${SRCROOT}/XESystem/Math/AreaAllocator.cpp
#  ${SRCROOT}/XESystem/Math/AxisAlignedBox.cpp
#  ${SRCROOT}/XESystem/Math/Color.cpp
#  ${SRCROOT}/XESystem/Math/Matrix3.cpp
#  ${SRCROOT}/XESystem/Math/Math.cpp
#  ${SRCROOT}/XESystem/Math/Matrix3x4.cpp
 # ${SRCROOT}/XESystem/Math/Matrix4.cpp
#  ${SRCROOT}/XESystem/Math/Plane.cpp
#  ${SRCROOT}/XESystem/Math/Polyhedron.cpp
#  ${SRCROOT}/XESystem/Math/Quaternion.cpp
#  ${SRCROOT}/XESystem/Math/Random.cpp
#  ${SRCROOT}/XESystem/Math/Rect.cpp
#  ${SRCROOT}/XESystem/Math/Ray.cpp
#  ${SRCROOT}/XESystem/Math/Frustum.cpp
#  ${SRCROOT}/XESystem/Math/Sphere.cpp
#  ${SRCROOT}/XESystem/Math/StringHash.cpp
#  ${SRCROOT}/XESystem/Math/Vector2.cpp
#  ${SRCROOT}/XESystem/Math/Vector3.cpp
#  ${SRCROOT}/XESystem/Math/Vector4.cpp
)
source_group("src\\math" FILES ${XESystemMath_SOURCES})


set(INCROOTSFMLSYS ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include/SFML/System)
set(SRCROOTSFMLSYS ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src/SFML/System)

# all source files
set(SRC
    ${SRCROOTSFMLSYS}/Clock.cpp
    ${INCROOTSFMLSYS}/Clock.hpp
    ${SRCROOTSFMLSYS}/Err.cpp
    ${INCROOTSFMLSYS}/Err.hpp
    ${INCROOTSFMLSYS}/Export.hpp
    ${INCROOTSFMLSYS}/InputStream.hpp
    ${SRCROOTSFMLSYS}/Lock.cpp
    ${INCROOTSFMLSYS}/Lock.hpp
    ${SRCROOTSFMLSYS}/Mutex.cpp
    ${INCROOTSFMLSYS}/Mutex.hpp
    ${INCROOTSFMLSYS}/NonCopyable.hpp
    ${SRCROOTSFMLSYS}/Sleep.cpp
    ${INCROOTSFMLSYS}/Sleep.hpp
    ${SRCROOTSFMLSYS}/String.cpp
    ${INCROOTSFMLSYS}/String.hpp
    ${INCROOTSFMLSYS}/String.inl
    ${SRCROOTSFMLSYS}/Thread.cpp
    ${INCROOTSFMLSYS}/Thread.hpp
    ${INCROOTSFMLSYS}/Thread.inl
    ${SRCROOTSFMLSYS}/ThreadLocal.cpp
    ${INCROOTSFMLSYS}/ThreadLocal.hpp
    ${INCROOTSFMLSYS}/ThreadLocalPtr.hpp
    ${INCROOTSFMLSYS}/ThreadLocalPtr.inl
    ${SRCROOTSFMLSYS}/Time.cpp
    ${INCROOTSFMLSYS}/Time.hpp
    ${INCROOTSFMLSYS}/Utf.hpp
    ${INCROOTSFMLSYS}/Utf.inl
    ${INCROOTSFMLSYS}/Vector2.hpp
    ${INCROOTSFMLSYS}/Vector2.inl
    ${INCROOTSFMLSYS}/Vector3.hpp
    ${INCROOTSFMLSYS}/Vector3.inl
    ${SRCROOTSFMLSYS}/FileInputStream.cpp
    ${INCROOTSFMLSYS}/FileInputStream.hpp
    ${SRCROOTSFMLSYS}/MemoryInputStream.cpp
    ${INCROOTSFMLSYS}/MemoryInputStream.hpp
)
source_group("sfml\\system" FILES ${SRC})

# add platform specific sources
if(SFML_OS_WINDOWS)
    set(PLATFORM_SRC
        ${SRCROOTSFMLSYS}/Win32/ClockImpl.cpp
        ${SRCROOTSFMLSYS}/Win32/ClockImpl.hpp
        ${SRCROOTSFMLSYS}/Win32/MutexImpl.cpp
        ${SRCROOTSFMLSYS}/Win32/MutexImpl.hpp
        ${SRCROOTSFMLSYS}/Win32/SleepImpl.cpp
        ${SRCROOTSFMLSYS}/Win32/SleepImpl.hpp
        ${SRCROOTSFMLSYS}/Win32/ThreadImpl.cpp
        ${SRCROOTSFMLSYS}/Win32/ThreadImpl.hpp
        ${SRCROOTSFMLSYS}/Win32/ThreadLocalImpl.cpp
        ${SRCROOTSFMLSYS}/Win32/ThreadLocalImpl.hpp
    )
    source_group("windows" FILES ${PLATFORM_SRC})
else()
    set(PLATFORM_SRC
        ${SRCROOTSFMLSYS}/Unix/ClockImpl.cpp
        ${SRCROOTSFMLSYS}/Unix/ClockImpl.hpp
        ${SRCROOTSFMLSYS}/Unix/MutexImpl.cpp
        ${SRCROOTSFMLSYS}/Unix/MutexImpl.hpp
        ${SRCROOTSFMLSYS}/Unix/SleepImpl.cpp
        ${SRCROOTSFMLSYS}/Unix/SleepImpl.hpp
        ${SRCROOTSFMLSYS}/Unix/ThreadImpl.cpp
        ${SRCROOTSFMLSYS}/Unix/ThreadImpl.hpp
        ${SRCROOTSFMLSYS}/Unix/ThreadLocalImpl.cpp
        ${SRCROOTSFMLSYS}/Unix/ThreadLocalImpl.hpp
    )

    if(SFML_OS_ANDROID)
        set(PLATFORM_SRC ${PLATFORM_SRC}
            ${SRCROOTSFMLSYS}/Android/Activity.hpp
            ${SRCROOTSFMLSYS}/Android/Activity.cpp
            ${SRCROOTSFMLSYS}/Android/ResourceStream.cpp
            ${SRCROOTSFMLSYS}/Android/ResourceStream.cpp
        )
    endif()

    source_group("sfml\\system\\unix" FILES ${PLATFORM_SRC})
endif()

# build the list of external libraries to link
if(SFML_OS_LINUX OR SFML_OS_FREEBSD OR SFML_OS_MACOSX)
    list(APPEND SYSTEM_EXT_LIBS pthread)
endif()
if(SFML_OS_LINUX)
    list(APPEND SYSTEM_EXT_LIBS rt)
endif()
if(SFML_OS_WINDOWS)
    list(APPEND SYSTEM_EXT_LIBS winmm)
endif()
if(SFML_OS_ANDROID)
    list(APPEND SYSTEM_EXT_LIBS android log)
endif()



# CMake documentation states "We do not recommend using GLOB to collect a list of
# source files from your source tree. If no CMakeLists.txt file changes when a 
# source is added or removed then the generated build system cannot know when to 
# ask CMake to regenerate".

#file(GLOB XESystem_SOURCES *.cpp)
#file(GLOB XESystem_HEADER *.hpp)


# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
#file (GLOB SIMPLE_FUNCTION_SOURCES
#      "simple/*.h",
#      "simple/*.cxx")


set(INC_SYSROOT ${PROJECT_SOURCE_DIR}/src/include/XESystem)
set(SRC_SYSROOT ${PROJECT_SOURCE_DIR}/src/src/XESystem)

# all source files
set(XESystem_SOURCES
    ${SRC_SYSROOT}/QueueManager.cpp 

	${SRC_SYSROOT}/readerwriterqueue.h
	${SRC_SYSROOT}/atomicops.h	
	
)
set(XESystem_HEADER
${INC_SYSROOT}/SystemConfig.hpp
    ${INC_SYSROOT}/QueueManager.hpp
	  ${INC_SYSROOT}/Logging.hpp
    ${INC_SYSROOT}/TransportData.hpp
)
# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("src" FILES ${XESystem_SOURCES})
source_group("include" FILES ${XESystem_HEADER})
#source_group("simple" FILES ${SIMPLE_FUNCTION_SOURCES})
#source_group("advanced" FILES ${ADVANCED_FUNCTION_SOURCES})


# Properties->C/C++->General->Additional Include Directories
# add sfml system headers
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src)
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/XESystem)


# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XESystem 
#                 ${XESystem_SOURCES} ${SRC} ${PLATFORM_SRC})
#                # EXTERNAL_LIBS ${SYSTEM_EXT_LIBS}) 
 


# define the sfml-system target
sfml_add_library(XESystem
                 SOURCES ${XESystem_SOURCES} ${XESystem_HEADER} ${SRC} ${PLATFORM_SRC}
				 ${XESystemEntityINCLUDES} ${XESystemEntitySOURCES} ${XESystemEntitytags_INCLUDES}	${XESystemEntitydeps_INCLUDES}	${XESystemEntityhelp_INCLUDES}	${XESystemEntity3dpartyINCLUDES}	${XESystemEntityhelp_SOURCES}
				${XESystemMath_INCLUDES} ${XESystemMath_SOURCES}
                 EXTERNAL_LIBS ${SYSTEM_EXT_LIBS})

#add_definitions(-SFML_SYSTEM_EXPORTS)
set_target_properties(XESystem PROPERTIES DEFINE_SYMBOL SFML_SYSTEM_EXPORTS)
set_target_properties(XESystem PROPERTIES DEFINE_SYMBOL ELPP_UNICODE)


# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XESystem PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XESystem
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
#		COMPONENT library)

