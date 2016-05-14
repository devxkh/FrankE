
# XEAudio

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEAudio)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEAudio)

# all source files
set(XEAudio_SOURCES
    ${SRCROOT}/XEResourceStream.cpp
	 
	 ${SRCROOT}/XEResourceStream.hpp
     ${SRCROOT}/XESoundFactory.cpp
	 ${SRCROOT}/XESoundHandle.cpp
	 ${SRCROOT}/XESoundListener.cpp
	 ${SRCROOT}/XESoundManager.cpp
)

source_group("src" FILES ${XEAudio_SOURCES})

# all header files
set(XEAudio_HEADER
	 ${INCROOT}/XESoundFactory.hpp
     ${INCROOT}/XESoundHandle.hpp
     ${INCROOT}/XESoundListener.hpp
	 ${INCROOT}/XESoundManager.hpp
)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XEAudio_HEADER})

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)
#file(GLOB XEAudio_SOURCES *.cpp)
#file(GLOB XEAudio_HEADER *.hpp)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
#source_group("source" FILES ${XEAudio})
#source_group("header" FILES ${XEAudio_HEADER})
#source_group("simple" FILES ${SIMPLE_FUNCTION_SOURCES})
#source_group("advanced" FILES ${ADVANCED_FUNCTION_SOURCES})


# Properties->C/C++->General->Additional Include Directories
#include_directories (.)


# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XEAudio ${XEAudio_SOURCES} ${XEAudio_HEADER}) 
                     #   ${SIMPLE_FUNCTION_SOURCES} 
                    #    ${ADVANCED_FUNCTION_SOURCES})


set(INCROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include/SFML/Audio)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src/SFML/Audio)

# all source files
set(SRC
    ${SRCROOT}/ALCheck.cpp
    ${SRCROOT}/ALCheck.hpp
    ${SRCROOT}/AlResource.cpp
    ${INCROOT}/AlResource.hpp
    ${SRCROOT}/AudioDevice.cpp
    ${SRCROOT}/AudioDevice.hpp
    ${INCROOT}/Export.hpp
    ${SRCROOT}/Listener.cpp
    ${INCROOT}/Listener.hpp
    ${SRCROOT}/Music.cpp
    ${INCROOT}/Music.hpp
    ${SRCROOT}/Sound.cpp
    ${INCROOT}/Sound.hpp
    ${SRCROOT}/SoundBuffer.cpp
    ${INCROOT}/SoundBuffer.hpp
    ${SRCROOT}/SoundBufferRecorder.cpp
    ${INCROOT}/SoundBufferRecorder.hpp
    ${SRCROOT}/InputSoundFile.cpp
    ${INCROOT}/InputSoundFile.hpp
    ${SRCROOT}/OutputSoundFile.cpp
    ${INCROOT}/OutputSoundFile.hpp
    ${SRCROOT}/SoundRecorder.cpp
    ${INCROOT}/SoundRecorder.hpp
    ${SRCROOT}/SoundSource.cpp
    ${INCROOT}/SoundSource.hpp
    ${SRCROOT}/SoundStream.cpp
    ${INCROOT}/SoundStream.hpp
)
source_group("sfml\\Audio" FILES ${SRC})

set(CODECS_SRC
    ${SRCROOT}/SoundFileFactory.cpp
    ${INCROOT}/SoundFileFactory.hpp
    ${INCROOT}/SoundFileFactory.inl
    ${INCROOT}/SoundFileReader.hpp
    ${SRCROOT}/SoundFileReaderFlac.hpp
    ${SRCROOT}/SoundFileReaderFlac.cpp
    ${SRCROOT}/SoundFileReaderOgg.hpp
    ${SRCROOT}/SoundFileReaderOgg.cpp
    ${SRCROOT}/SoundFileReaderWav.hpp
    ${SRCROOT}/SoundFileReaderWav.cpp
    ${INCROOT}/SoundFileWriter.hpp
    ${SRCROOT}/SoundFileWriterFlac.hpp
    ${SRCROOT}/SoundFileWriterFlac.cpp
    ${SRCROOT}/SoundFileWriterOgg.hpp
    ${SRCROOT}/SoundFileWriterOgg.cpp
    ${SRCROOT}/SoundFileWriterWav.hpp
    ${SRCROOT}/SoundFileWriterWav.cpp
)
source_group("sfml\\Audio\\codecs" FILES ${CODECS_SRC})

# let CMake know about our additional audio libraries paths (on Windows and OSX)
if(SFML_OS_WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/AL")
elseif(SFML_OS_MACOSX)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-osx/Frameworks")
elseif(SFML_OS_ANDROID)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/AL")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/android")
endif()

# find external libraries
if(NOT SFML_OS_ANDROID)
    if(NOT SFML_OS_IOS)
        find_package(OpenAL REQUIRED)
    endif()
    find_package(Vorbis REQUIRED)
    find_package(FLAC REQUIRED)
else()
    find_host_package(OpenAL REQUIRED)
    find_host_package(Vorbis REQUIRED)
    find_host_package(FLAC REQUIRED)
endif()

if(NOT SFML_OS_IOS)
    include_directories(${OPENAL_INCLUDE_DIR})
endif()
include_directories(${VORBIS_INCLUDE_DIRS})
include_directories(${FLAC_INCLUDE_DIR})
add_definitions(-DOV_EXCLUDE_STATIC_CALLBACKS) # avoids warnings in vorbisfile.h
add_definitions(-DFLAC__NO_DLL)

# build the list of external libraries to link
if(SFML_OS_IOS)
    list(APPEND XEAudio_EXT_LIBS "-framework OpenAL")
else()
    list(APPEND XEAudio_EXT_LIBS ${OPENAL_LIBRARY})
endif()
if(SFML_OS_ANDROID)
    list(APPEND XEAudio_EXT_LIBS android OpenSLES)
endif()
list(APPEND XEAudio_EXT_LIBS ${VORBIS_LIBRARIES} ${FLAC_LIBRARY})


# define the sfml-graphics target
sfml_add_library(XEAudio 
	SOURCES ${SRC} ${CODECS_SRC} ${XEAudio_SOURCES} ${XEAudio_HEADER} 
	DEPENDS OgreMain XESystem
	EXTERNAL_LIBS ${XEAudio_EXT_LIBS})


#set_target_properties(XEAudio PROPERTIES DEFINE_SYMBOL SFML_AUDIO_EXPORTS)
target_compile_definitions(XEAudio PUBLIC SFML_AUDIO_EXPORTS)

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEAudio PROPERTY FOLDER "libraries")


# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEAudio
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)