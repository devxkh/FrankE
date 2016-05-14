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

message("LuaJIT installed")

find_path(LUAJITFILE_INCLUDE_DIR "luajit/lua.hpp")
#find_path(ZLIBFILE_INCLUDE_DIR "zlib/zlib.h")

find_library(LUAJITFILE_LIBRARY NAMES luajit)
#find_library(ZLIBFILE_LIBRARY NAMES zlib)


message("LUAJITFILE_INCLUDE_DIR:" ${LUAJITFILE_INCLUDE_DIR})

# Handle the QUIETLY and REQUIRED arguments and set PHYSFSFILE_FOUND to TRUE if
# all listed variables are TRUE.
#####include(FindPackageHandleStandardArgs)
#####find_package_handle_standard_args(PHYSFSFILE DEFAULT_MSG PHYSFSFILE_LIBRARY PHYSFSFILE_INCLUDE_DIR)

#if(PHYSFSFILE_FOUND)
  set(LUAJITFILE_LIBRARIES ${LUAJITFILE_LIBRARY} )#${PHYSFSFILE_LIBRARY})
#else(PHYSFSFILE_FOUND)
#  set(PHYSFSFILE_LIBRARIES)
#endif(PHYSFSFILE_FOUND)

mark_as_advanced(LUAJITFILE_INCLUDE_DIR LUAJITFILE_LIBRARY)
