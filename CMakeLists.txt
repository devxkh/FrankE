cmake_minimum_required (VERSION 2.8)


#--------------------------- START SFML -----------------------------------


# set a default build type if none was provided
# this has to be done before the project() instruction!
#KH   sfml_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

# Maps to Visual Studio solution file (XEngineSln.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (FrankE)

  set(SDL_STATIC TRUE)
    set(SDL_SHARED FALSE)
	  set(BUILD_SHARED_LIBS FALSE)
	    set(OGRE_STATIC TRUE)
		  set(SFML_USE_STATIC_STD_LIBS TRUE)
		    set(OGRE_BUILD_COMPONENT_OVERLAY FALSE)
			  set(OGRE_BUILD_TOOLS FALSE)
			    set(OGRE_INSTALL_SAMPLES FALSE)
				  set(OGRE_CONFIG_ENABLE_STBI TRUE)
 
message("ProjectsourceDir- start " ${PROJECT_SOURCE_DIR})

set(FrankESource ${PROJECT_SOURCE_DIR})

# include XEngine commons
include(cmake/Common.cmake)

# define a macro that helps defining an option
macro(sfml_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()


# include the configuration file
include(${PROJECT_SOURCE_DIR}/cmake/Config.cmake)


# add an option for choosing the build type (shared or static)
if(NOT (SFML_OS_IOS OR SFML_OS_ANDROID))
    sfml_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")
else()
    if(SFML_OS_IOS)
        set(BUILD_SHARED_LIBS FALSE)
    elseif(SFML_OS_ANDROID)
        set(BUILD_SHARED_LIBS TRUE)
    endif()
endif()

# ------- important !!!!! ---------
# define SFML_STATIC if the build type is not set to 'shared'
if(NOT BUILD_SHARED_LIBS)
    add_definitions(-DSFML_STATIC)

add_definitions(-DOGRE_STATIC)
add_definitions(-DOGRE_STATIC_LIB)

#cmake_dependent_option(OGRE_STATIC "Static build X" FALSE "" TRUE)
endif()


# include the SFML specific macros
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

# define an option for choosing between static and dynamic C runtime (Windows only)
if(SFML_OS_WINDOWS)
    sfml_set_option(SFML_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

    # the following combination of flags is not valid
    if (BUILD_SHARED_LIBS AND SFML_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "BUILD_SHARED_LIBS and SFML_USE_STATIC_STD_LIBS cannot be used together")
    endif()

    # for VC++, we can apply it globally by modifying the compiler flags
    #if(SFML_COMPILER_MSVC AND SFML_USE_STATIC_STD_LIBS)
    #    foreach(flag
    #            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    #            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    #        if(${flag} MATCHES "/MD")
    #            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
    #        endif()
    #    endforeach()
    #endif()
endif()

# let CMake know about our additional libraries paths
if (SFML_OS_WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    if(SFML_COMPILER_GCC)
        if(ARCH_32BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw/x86")
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/bin/x86")
        elseif(ARCH_64BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw/x64")
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/bin/x64")
        endif()
    elseif(SFML_COMPILER_MSVC)
       if(SFML_MSVC_VERSION LESS 14)
            if(ARCH_32BITS)
                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc/x86")
            elseif(ARCH_64BITS)
                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc/x64")
            endif()
        else()
            if(ARCH_32BITS)
                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc-universal/x86")
            elseif(ARCH_64BITS)
                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc-universal/x64")
            endif()
        endif()
    endif()
elseif(SFML_OS_MACOSX)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-osx/lib/")
elseif(SFML_OS_IOS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-ios/")
elseif(SFML_OS_ANDROID)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-android/${ANDROID_ABI}")
endif()

# add the SFML sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")


include(cotire)


# set the output directory for SFML libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# install 3rd-party libraries and tools
if(SFML_OS_WINDOWS)

    # install the binaries of SFML dependencies
    if(ARCH_32BITS)
        install(DIRECTORY extlibs/bin/x86/ DESTINATION bin)
       if(SFML_COMPILER_MSVC AND SFML_MSVC_VERSION LESS 14)        
			 install(DIRECTORY extlibs/libs-msvc/x86/ DESTINATION lib)
        elseif(SFML_COMPILER_MSVC)
            install(DIRECTORY extlibs/libs-msvc-universal/x86/ DESTINATION lib)
        else()
            install(DIRECTORY extlibs/libs-mingw/x86/ DESTINATION lib)
        endif()
    elseif(ARCH_64BITS)
        install(DIRECTORY extlibs/bin/x64/ DESTINATION bin)
        if(SFML_COMPILER_MSVC AND SFML_MSVC_VERSION LESS 14)
             install(DIRECTORY extlibs/libs-msvc/x64/ DESTINATION lib)		
        elseif(SFML_COMPILER_MSVC)
            install(DIRECTORY extlibs/libs-msvc-universal/x64/ DESTINATION lib)
        else()
            install(DIRECTORY extlibs/libs-mingw/x64/ DESTINATION lib)
        endif()
    endif()

elseif(SFML_OS_MACOSX)

    # install the non-standard frameworks SFML depends on
    install(DIRECTORY extlibs/libs-osx/Frameworks/sndfile.framework DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX})
    install(DIRECTORY extlibs/libs-osx/Frameworks/freetype.framework DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX})

    # install the Xcode templates if requested
    if(SFML_INSTALL_XCODE_TEMPLATES)
        configure_file(
                    "tools/xcode/templates/SFML/SFML Compiler.xctemplate/TemplateInfo.plist.in"
                    "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML/SFML Compiler.xctemplate/TemplateInfo.plist"
                    @ONLY)
        install(DIRECTORY "tools/xcode/templates/SFML" "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML"
                DESTINATION /Library/Developer/Xcode/Templates
                PATTERN "*.in" EXCLUDE)
    endif()

elseif(SFML_OS_IOS)

    # fix CMake install rules broken for iOS (see http://public.kitware.com/Bug/view.php?id=12506)
    if(SFML_OS_IOS)
        install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/\$ENV{CONFIGURATION}/" DESTINATION lib${LIB_SUFFIX})
    endif()

    # since the iOS libraries are built as static, we must install the SFML dependencies
    # too so that the end user can easily link them to its final application
    install(FILES extlibs/libs-ios/libfreetype.a extlibs/libs-ios/libjpeg.a DESTINATION lib)

elseif(SFML_OS_ANDROID)

    # install extlibs
    install(DIRECTORY extlibs/libs-android/${ANDROID_ABI} DESTINATION extlibs/lib)
    install(FILES extlibs/Android.mk DESTINATION extlibs)

    # install Android.mk so the NDK knows how to set up SFML
    install(FILES src/SFML/Android.mk DESTINATION .)

endif()

# wichtig ad sub directory vor install!!
# Sub-directories where more CMakeLists.txt exist
add_subdirectory(src)

# include XEngine commons
include(${PROJECT_SOURCE_DIR}/cmake/Common.cmake)



message("FindFMOD.cmake - start " ${CMAKE_MODULE_PATH}) 
# findet Physfs nicht !!????
find_package(FMOD REQUIRED)
#find_package(Sndfile REQUIRED)
message("FindFMOD.cmake - end")


# remove SL security warnings with Visual C++
if(SFML_COMPILER_MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

# define SFML_OPENGL_ES if needed
if(SFML_OPENGL_ES)
    add_definitions(-DSFML_OPENGL_ES)
    add_definitions(-DGL_GLEXT_PROTOTYPES)
endif()

# define an option for choosing between static and dynamic C runtime (Windows only)
#if(SFML_OS_WINDOWS)
#    sfml_set_option(SFML_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")
#
#    # the following combination of flags is not valid
#    if (BUILD_SHARED_LIBS AND SFML_USE_STATIC_STD_LIBS)
#        message(FATAL_ERROR "BUILD_SHARED_LIBS and SFML_USE_STATIC_STD_LIBS cannot be used together")
#    endif()
#
#    # for VC++, we can apply it globally by modifying the compiler flags
#    #if(SFML_COMPILER_MSVC AND SFML_USE_STATIC_STD_LIBS)
#    #    foreach(flag
#    #            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
#    #            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
#    #        if(${flag} MATCHES "/MD")
#    #            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
#    #        endif()
#    #    endforeach()
#    #endif()
#endif()

# setup Mac OS X stuff
if(SFML_OS_MACOSX)
    # SFML_BUILD_FRAMEWORKS needs two things:
    # first, it's available only for release
    #    (because cmake currently doesn't allow specifying a custom framework name so XXX-d is not possible)
    # secondly, it works only with BUILD_SHARED_LIBS enabled
    if(SFML_BUILD_FRAMEWORKS)
        # requirement #1
        if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
            message(FATAL_ERROR "CMAKE_BUILD_TYPE should be \"Release\" when SFML_BUILD_FRAMEWORKS is TRUE")
            return()
        endif()

        # requirement #2
        if(NOT BUILD_SHARED_LIBS)
            message(FATAL_ERROR "BUILD_SHARED_LIBS should be TRUE when SFML_BUILD_FRAMEWORKS is TRUE")
            return()
        endif()
    endif()

    # configure Xcode templates
    if(CMAKE_OSX_ARCHITECTURES)
        # maybe multiple arches are present in CMAKE_OSX_ARCHITECTURES
        # we simply need to replace ';' by ' ' (space) and store the result in XCODE_TEMPLATES_ARCH
        string(REPLACE ";" " " XCODE_TEMPLATES_ARCH "${CMAKE_OSX_ARCHITECTURES}")
    else()
        # no arch was provided to cmake, so we use the default one
        set(XCODE_TEMPLATES_ARCH "\$(NATIVE_ARCH_ACTUAL)")
    endif()
endif()

if(SFML_OS_LINUX OR SFML_OS_FREEBSD)
    set(PKGCONFIG_DIR lib${LIB_SUFFIX}/pkgconfig)
    if(SFML_OS_FREEBSD)
        set(PKGCONFIG_DIR libdata/pkgconfig)
    endif()
    if(BUILD_SHARED_LIBS)
        sfml_set_option(SFML_INSTALL_PKGCONFIG_FILES FALSE BOOL "TRUE to automatically install pkg-config files so other projects can find SFML")
        if(SFML_INSTALL_PKGCONFIG_FILES)
            foreach(sfml_module IN ITEMS all system window graphics audio network)
                CONFIGURE_FILE(
                    "tools/pkg-config/sfml-${sfml_module}.pc.in"
                    "tools/pkg-config/sfml-${sfml_module}.pc"
                    @ONLY)
                INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/tools/pkg-config/sfml-${sfml_module}.pc"
                    DESTINATION "${CMAKE_INSTALL_PREFIX}/${PKGCONFIG_DIR}")
            endforeach()
        endif()
    else()
        if(SFML_INSTALL_PKGCONFIG_FILES)
            message(WARNING "No pkg-config files are provided for the static SFML libraries (SFML_INSTALL_PKGCONFIG_FILES will be ignored).")
        endif()
    endif()
endif()

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")


# setup the install rules
if(NOT SFML_BUILD_FRAMEWORKS)
    install(DIRECTORY include
            DESTINATION .
            COMPONENT devel
            FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
else()
    # find only "root" headers
    file(GLOB SFML_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/SFML/*")

    # in fact we have to fool cmake to copy all the headers in subdirectories
    # to do that we have to add the "root" headers to the PUBLIC_HEADER
    # then we can run a post script to copy the remaining headers

    # we need a dummy file in order to compile the framework
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp
                       COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)

    set(SFML_SOURCES ${SFML_HEADERS})
    list(APPEND SFML_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)

    # create SFML.framework
    add_library(SFML ${SFML_SOURCES})

    # edit target properties
    set_target_properties(SFML PROPERTIES
                          FRAMEWORK TRUE
                          FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
                          MACOSX_FRAMEWORK_IDENTIFIER org.sfml-dev.SFML
                          MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
                          MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
                          PUBLIC_HEADER "${SFML_HEADERS}")

    # add the remaining headers
    add_custom_command(TARGET SFML
                       POST_BUILD
                       COMMAND cp -r ${PROJECT_SOURCE_DIR}/include/SFML/* $<TARGET_FILE_DIR:SFML>/Headers)

    # adapt install directory to allow distributing dylibs/frameworks in user�s frameworks/application bundle
    # NOTE: it's not required to link agains SFML.framework
    set_target_properties(SFML PROPERTIES
                          BUILD_WITH_INSTALL_RPATH 1
                          INSTALL_NAME_DIR "@rpath")

    # install rule
    install(TARGETS SFML
            FRAMEWORK DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX}
            COMPONENT devel)
endif()


#install(FILES license.txt DESTINATION ${INSTALL_MISC_DIR})
#install(FILES readme.txt DESTINATION ${INSTALL_MISC_DIR})
if(NOT SFML_OS_ANDROID)
    install(FILES cmake/Modules/FindSFML.cmake DESTINATION ${INSTALL_MISC_DIR}/cmake/Modules)
#KH
 # message("installdir:" ${INSTALL_MISC_DIR} "/cmake/Modules")

#  install(FILES cmake/Modules/FindPhysfs.cmake DESTINATION ${INSTALL_MISC_DIR}/cmake/Modules)

endif()

# install 3rd-party libraries and tools


if(SFML_OS_WINDOWS)

    # install the binaries of SFML dependencies
    if(ARCH_32BITS)
        install(DIRECTORY extlibs/bin/x86/ DESTINATION bin)
        if(SFML_COMPILER_MSVC)
            install(DIRECTORY extlibs/libs-msvc/x86/ DESTINATION lib)
        else()
            install(DIRECTORY extlibs/libs-mingw/x86/ DESTINATION lib)
        endif()
    elseif(ARCH_64BITS)
        install(DIRECTORY extlibs/bin/x64/ DESTINATION bin)
        if(SFML_COMPILER_MSVC)
		install(DIRECTORY extlibs/libs-msvc/x64/ DESTINATION lib)
        else()
            install(DIRECTORY extlibs/libs-mingw/x64/ DESTINATION lib)
        endif()
    endif()

elseif(SFML_OS_MACOSX)

    # install the non-standard frameworks SFML depends on
    install(DIRECTORY extlibs/libs-osx/Frameworks/sndfile.framework DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX})
    install(DIRECTORY extlibs/libs-osx/Frameworks/freetype.framework DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX})

    # install the Xcode templates if requested
    if(SFML_INSTALL_XCODE_TEMPLATES)
        configure_file(
                    "tools/xcode/templates/SFML/SFML Compiler.xctemplate/TemplateInfo.plist.in"
                    "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML/SFML Compiler.xctemplate/TemplateInfo.plist"
                    @ONLY)
        install(DIRECTORY "tools/xcode/templates/SFML" "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML"
                DESTINATION /Library/Developer/Xcode/Templates
                PATTERN "*.in" EXCLUDE)
    endif()

elseif(SFML_OS_IOS)

    # fix CMake install rules broken for iOS (see http://public.kitware.com/Bug/view.php?id=12506)
    if(SFML_OS_IOS)
        install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/\$ENV{CONFIGURATION}/" DESTINATION lib${LIB_SUFFIX})
    endif()

    # since the iOS libraries are built as static, we must install the SFML dependencies
    # too so that the end user can easily link them to its final application
    install(FILES extlibs/libs-ios/libfreetype.a extlibs/libs-ios/libjpeg.a DESTINATION lib)

elseif(SFML_OS_ANDROID)

    # install extlibs
    install(DIRECTORY extlibs/libs-android/${ANDROID_ABI} DESTINATION extlibs/lib)
    install(FILES extlibs/Android.mk DESTINATION extlibs)

    # install Android.mk so the NDK knows how to set up SFML
    install(FILES src/SFML/Android.mk DESTINATION .)

endif()


#--------------------------------- END SFML -----------------------------------


# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")


# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

