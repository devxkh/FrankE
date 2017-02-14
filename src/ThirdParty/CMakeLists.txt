
##if (SCRIPT_LUAJIT)


#option (SCRIPT_LUAJIT "Enable Luajit scripting support" TRUE)

#add_subdirectory(LuaJIT)
add_subdirectory(Lua)
add_subdirectory(enet)
add_subdirectory(rapidjson)
add_subdirectory(SDL)
add_subdirectory(FreeImage)
##endif ()
