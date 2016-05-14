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

message("-------- find FMOD -----------")

unset(FMODFILE_INCLUDE_DIR CACHE)
unset(FMODFILE_LIBRARY CACHE)

find_path(FMODFILE_INCLUDE_DIR  fmod/fmod.hpp)

message("FMOD_INCLUDE_DIR:" ${FMODFILE_INCLUDE_DIR})
#find_path(ZLIBFILE_INCLUDE_DIR "zlib/zlib.h")

find_library(FMODFILE_LIBRARY NAMES fmod)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(fmod DEFAULT_MSG FMODFILE_LIBRARY FMODFILE_INCLUDE_DIR)


#message("FNDFMODFILE_LIBRARY:" ${FMODFILE_LIBRARY})

#if(PHYSFSFILE_FOUND)
# set(FMODFILE_INLCUDE_DIRS ${FMODFILE_INCLUDE_DIR})
#  set(FMODFILE_LIBRARIES ${FMODFILE_LIBRARY})#${PHYSFSFILE_LIBRARY})
#else(PHYSFSFILE_FOUND)
#  set(PHYSFSFILE_LIBRARIES)
#endif(PHYSFSFILE_FOUND)

# Handle the QUIETLY and REQUIRED arguments and set PHYSFSFILE_FOUND to TRUE if
# all listed variables are TRUE.
#####include(FindPackageHandleStandardArgs)
#####find_package_handle_standard_args(PHYSFSFILE DEFAULT_MSG PHYSFSFILE_LIBRARY PHYSFSFILE_INCLUDE_DIR)

#if(PHYSFSFILE_FOUND)
 # set(PHYSFSFILE_LIBRARIES ${PHYSFSFILE_LIBRARY} ${ZLIBFILE_LIBRARY})#${PHYSFSFILE_LIBRARY})
#else(PHYSFSFILE_FOUND)
#  set(PHYSFSFILE_LIBRARIES)
#endif(PHYSFSFILE_FOUND)

mark_as_advanced(FMODFILE_INCLUDE_DIR FMODFILE_LIBRARY)

list(APPEND XEngine_EXT_LIBS ${FMODFILE_LIBRARY})
