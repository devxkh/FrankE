set(INCROOTrapidjson ${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include/rapidjson)

# all source files
file(GLOB SRC_rapidjson
        ${INCROOTrapidjson}/*.h
)
source_group("rapidjson" FILES ${SRC_rapidjson})

# Properties->C/C++->General->Additional Include Directories
# add sfml Network headers
include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)

# define the sfml-Network target
sfml_add_library(rapidjson  SOURCES  ${SRC_rapidjson})

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET rapidjson PROPERTY FOLDER "thirdparty")
SET_TARGET_PROPERTIES(rapidjson PROPERTIES LINKER_LANGUAGE C)