
# XEDAL

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEDAL)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEDAL)

# ----------------------- XEDAL_SOURCES -------------------------------
set(XEDAL_SOURCES
    ${SRCROOT}/IDAL.cpp
	${SRCROOT}/DB.cpp
	${SRCROOT}/IDALObject.cpp
	)
source_group("src" FILES ${XEDAL_SOURCES})

# ----------------------- XEDAL_SqliteArchive_SOURCES -------------------------------
set(XEDAL_SqliteArchive_SOURCES

     ${SRCROOT}/SqliteArchive/OgreSQL.cpp
	 ${SRCROOT}/SqliteArchive/OgreSQLArchiveFactory.cpp
)
source_group("src\\SqliteArchive" FILES ${XEDAL_SqliteArchive_SOURCES})

# ----------------------- XEDAL_PhysFSArchive_SOURCES -------------------------------
set(XEDAL_PhysFSArchive_SOURCES
	 ${SRCROOT}/PhysFS/sfmlphysfs.cpp
	 ${SRCROOT}/PhysFS/PhysFSWrapper.cpp
	 ${SRCROOT}/PhysFS/PhysFSDataStream.cpp 
	 ${SRCROOT}/PhysFS/PhysFSArchive.cpp
)
source_group("src\\PhysFSArchive" FILES ${XEDAL_PhysFSArchive_SOURCES})

# ----------------------- XEDAL_Objects_SOURCES -------------------------------
set(XEDAL_Objects_SOURCES
	 ${INCROOT}/Objects/FBEngineTypes_generated.h
	# ${SRCROOT}/Objects/ProtoType.pb.h
)
source_group("include\\Objects" FILES ${XEDAL_Objects_SOURCES})


# ----------------------- SQLITE_SOURCES -------------------------------
set(SQLITEROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/sqlite)
set(SQLITE_SOURCES
     ${SQLITEROOT}/shell.c
	 ${SQLITEROOT}/sqlite3.c
	 ${SQLITEROOT}/sqlite3.h
	 ${SQLITEROOT}/sqlite3ext.h
)
source_group("src\\Sqlite3" FILES ${SQLITE_SOURCES})



# ----------------------- header files -------------------------------
set(XEDAL_HEADER
#	 ${INCROOT}/Serialize.hpp
     ${INCROOT}/IDAL.hpp
     ${INCROOT}/IDALObject.hpp
     ${INCROOT}/DB.hpp 
)
source_group("include" FILES ${XEDAL_HEADER}) # Create named folders for the sources within the .vcproj


# ----------------------- physfs_header files -------------------------------
set(XEDAL_physfs_HEADER

	 ${INCROOT}/PhysFS/sfmlphysfs.hpp
	 ${INCROOT}/PhysFS/PhysFSWrapper.h
	 ${INCROOT}/PhysFS/PhysFSDataStream.h
	 ${INCROOT}/PhysFS/PhysFsStream.hpp
	 ${INCROOT}/PhysFS/PhysFSArchive.h
)
source_group("include\\physfsArchive" FILES ${XEDAL_physfs_HEADER}) 

# ----------------------- sqlite_header files -------------------------------
set(XEDAL_sqlite_HEADER
	 ${INCROOT}/SqliteArchive/OgreSQLPrereq.hpp
	 ${INCROOT}/SqliteArchive/OgreSQLArchiveFactory.hpp
	 ${INCROOT}/SqliteArchive/OgreSQL.hpp
)
source_group("include\\SqliteArchive" FILES ${XEDAL_sqlite_HEADER}) 


# ----------------------- FlatBuffers_Compiler_SRCS files -------------------------------
set(INCFBROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/google/flatbuffers)


set(FlatBuffers_Compiler_SRCS
  ${INCFBROOT}/include/flatbuffers/flatbuffers.h
  ${INCFBROOT}/include/flatbuffers/idl.h
  ${INCFBROOT}/include/flatbuffers/util.h
  ${INCFBROOT}/src/idl_parser.cpp
  ${INCFBROOT}/src/idl_gen_cpp.cpp
  ${INCFBROOT}/src/idl_gen_general.cpp
  ${INCFBROOT}/src/idl_gen_go.cpp
  ${INCFBROOT}/src/idl_gen_text.cpp
  ${INCFBROOT}/src/idl_gen_fbs.cpp

#  ${INCFBROOT}/src/flatc.cpp
)
source_group("include\\flatbuffers" FILES ${FlatBuffers_Compiler_SRCS}) 


# ----------------------- Properties->C/C++->General->Additional Include Directories -------------------------------
include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/google/flatbuffers/include)
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)

# let CMake know about our additional audio libraries paths (on Windows and OSX)
if(SFML_OS_WINDOWS)
message("CMAKE_INCLUDE_PATH:" ${CMAKE_INCLUDE_PATH})
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})

  #  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/AL")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/physfs")
elseif(SFML_OS_MACOSX)
   # set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/libsndfile/osx")
   # set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-osx/Frameworks")
elseif(SFML_OS_ANDROID)
  #  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/AL")
  #  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/libsndfile/android")
endif()

# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XEDAL ${XEDAL_SOURCES} ${XEDAL_HEADER} ${XEDAL_SqliteArchive_SOURCES}  ${XEDAL_Objects_SOURCES} ${SQLITE_SOURCES} ${XEDAL_PhysFSArchive_SOURCES} ${XEDAL_physfs_HEADER}  ${XEDAL_sqlite_HEADER})

#list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

# find external libraries
if(NOT SFML_OS_ANDROID)
    #find_package(OpenAL REQUIRED)

message("FindPhysFs.cmake - start " ${CMAKE_MODULE_PATH}) 
# findet Physfs nicht !!????
find_package(Physfs REQUIRED)
#find_package(Sndfile REQUIRED)
message("FindPhysFs.cmake - end")

else()
   # find_host_package(OpenAL REQUIRED)
   find_host_package(Physfs REQUIRED)
endif()
include_directories(${PHYSFSFILE_INCLUDE_DIR} ${ZLIBFILE_INCLUDE_DIR})

# build the list of external libraries to link
if(SFML_OS_ANDROID)
 #   list(APPEND AUDIO_EXT_LIBS -landroid -lOpenSLES)
endif()
list(APPEND XEDAL_EXT_LIBS ${PHYSFSFILE_LIBRARIES})

message("PHYSFSFILE_LIBRARIES:" ${PHYSFSFILE_LIBRARIES})


# define the sfml-graphics target
sfml_add_library(XEDAL
	SOURCES ${XEDAL_SOURCES} ${XEDAL_HEADER} ${XEDAL_SqliteArchive_SOURCES} ${XEDAL_Objects_SOURCES} ${SQLITE_SOURCES} ${XEDAL_PhysFSArchive_SOURCES} ${XEDAL_physfs_HEADER} ${XEDAL_sqlite_HEADER} ${FlatBuffers_Compiler_SRCS}
	DEPENDS OgreMain
	EXTERNAL_LIBS ${XEDAL_EXT_LIBS})

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEDAL PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEDAL
		#ARCHIVE DESTINATION lib
        #LIBRARY DESTINATION lib
		#COMPONENT library)


