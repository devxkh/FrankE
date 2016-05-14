# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")



sfml_set_option(OGRE_CONFIG_ENABLE_JSON TRUE BOOL "Use rapidjson (needed by Hlms JSON materials)")


# Sub-directories where more CMakeLists.txt exist
add_subdirectory(src)
add_subdirectory (TestXE)
add_subdirectory (Ogre)
#add_subdirectory (Tools)

add_subdirectory (ThirdParty)