


#include_directories (F:/Projekte/boost_1_60_0)

#message("${PROJECT_SOURCE_DIR}:"  ${PROJECT_SOURCE_DIR})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/include)

# Properties->C/C++->General->Additional Include Directories
include_directories (${FrankESource}/src/TestXE/XETController)
include_directories (${FrankESource})
include_directories (${FrankESource}/src/include)
include_directories (${FrankESource}/src/include/XEDAL/Objects) #flatbuffer file
include_directories (${FrankESource}/src)
include_directories (${FrankESource}/src/src)
include_directories (${FrankESource}/src/ThirdParty)
include_directories (${FrankESource}/src/ThirdParty/sfml/include)
include_directories (${FrankESource}/src/ThirdParty/thor/include)
include_directories (${FrankESource}/src/include/XEAnimation)
include_directories (${FrankESource}/src/Ogre/OgreMain/include)
include_directories (${FrankESource}/src/Ogre/Components/Terrain/include)
include_directories (${FrankESource}/src/ThirdParty/bullet)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/Recast/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DebugUtils/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/Detour/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DetourCrowd/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/DetourTileCache/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav/OgreCrowd/Include)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/recastnav)

include_directories (${FrankESource}/src/ThirdParty/Lua/src)
include_directories (${FrankESource}/src/ThirdParty/LuaJIT/src)
include_directories (${FrankESource}/src/ThirdParty/google/flatbuffers/include)

include_directories (${FrankESource}/src/include/XESystem/Math)

include_directories(${FrankESource}/src/ThirdParty/rapidjson/include)

include_directories(${FrankESource}/src/ThirdParty/enet/include)
include_directories(${FrankESource}/src/ThirdParty/SDL/include)

include_directories(${FrankESource}/extlibs/headers)

#include_directories (${FrankESource}/extlibs/headers/fmod)

# ogre buildsettings
include_directories (${PROJECT_BINARY_DIR}/FrankE/src/Ogre/include)  # need for external projects referencing FrankE
include_directories (${PROJECT_BINARY_DIR}/src/Ogre/include)

#sdl build settings
include_directories (${PROJECT_BINARY_DIR}/FrankE/src/ThirdParty/SDL/include)   # need for external projects referencing FrankE
include_directories (${PROJECT_BINARY_DIR}/src/ThirdParty/SDL/include) 

include_directories (${FrankESource}/src/ThirdParty/SDL/include)
