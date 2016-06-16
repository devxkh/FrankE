#ifndef _LUAENGINE_h_
#define _LUAENGINE_h_

#include <iostream>

#include <XESystem/SystemConfig.hpp>
//#include "lua.hpp" //needed for Lua
//#include <ThirdParty/selene/selene.h>

#include <ThirdParty/sol/sol.hpp>

#include <map>

namespace XE {

	class LuaVector3;
	class XEngine;

/************************************************************************/
/*  LuaEngine class
/*
/*  implements a wrapper around the lua state object required
/*  to run user defined lua scripts. It is a non-copyable class
/*  as the application should only include one instance of the engine
/*  and execute scripts on that engine's state
/************************************************************************/
class LuaEngine
{
public:
	//Constructor
	LuaEngine(XEngine& engine); // : _L(luaL_newstate()) { luaL_openlibs(_L); }
//	LuaEngine(const LuaEngine& other);  //non-construction copy
//	LuaEngine& operator=(const LuaEngine&); //non-copy
//	~LuaEngine(void) { lua_close(_L); } //Destructor clean-up

	//void init();

	sol::load_result loadFile(const std::string& filename);

	void executeScript(const std::string& filepath);
	void removeScript(const std::string& filepath);
	void reloadScript(const std::string& filepath);
	
	sol::state state;

private:

	XEngine& m_engine;

private:

};

} // ns XE

#endif