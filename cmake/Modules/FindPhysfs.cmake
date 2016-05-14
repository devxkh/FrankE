# - Find sndfile
# Find the native sndfile includes and libraries
#
#  PHYSFSFILE_INCLUDE_DIR - where to find sndfile.h, etc.
#  PHYSFSFILE_LIBRARIES   - List of libraries when using libsndfile.
#  PHYSFSFILE_FOUND       - True if libsndfile found.

#####if(PHYSFSFILE_INCLUDE_DIR)
    # Already in cache, be silent
#####    set(PHYSFSFILE_FIND_QUIETLY TRUE)
#####endif(PHYSFSFILE_INCLUDE_DIR)

message("------- find physfs -----------")

find_path(PHYSFSFILE_INCLUDE_DIR physfs.h)
#find_path(ZLIBFILE_INCLUDE_DIR "zlib/zlib.h")

find_library(PHYSFSFILE_LIBRARY NAMES physfs)
find_library(ZLIBFILE_LIBRARY NAMES zlib)


message("FNDPHYSFSFILE_LIBRARY:" ${PHYSFSFILE_LIBRARY})

# Handle the QUIETLY and REQUIRED arguments and set PHYSFSFILE_FOUND to TRUE if
# all listed variables are TRUE.
#####include(FindPackageHandleStandardArgs)
#####find_package_handle_standard_args(PHYSFSFILE DEFAULT_MSG PHYSFSFILE_LIBRARY PHYSFSFILE_INCLUDE_DIR)

#if(PHYSFSFILE_FOUND)
  set(PHYSFSFILE_LIBRARIES ${PHYSFSFILE_LIBRARY} ${ZLIBFILE_LIBRARY})#${PHYSFSFILE_LIBRARY})
#else(PHYSFSFILE_FOUND)
#  set(PHYSFSFILE_LIBRARIES)
#endif(PHYSFSFILE_FOUND)

list(APPEND XEngine_EXT_LIBS ${PHYSFSFILE_LIBRARIES})

mark_as_advanced(PHYSFSFILE_INCLUDE_DIR PHYSFSFILE_LIBRARY)
