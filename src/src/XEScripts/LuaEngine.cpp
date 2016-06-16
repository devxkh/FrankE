#include <XEScripts/LUAEngine.h>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEScripts/LUA/LuaVector3.hpp>
#include <XEDAL/PhysFS/PhysFsStream.hpp>

namespace XE {

	LuaEngine::LuaEngine(XEngine& engine)
		: m_engine(engine)
		, state()
	{
		state.open_libraries(sol::lib::base, sol::lib::package);
	}

	//void LuaEngine::init()
	//{
	//	sol::state state;
	//					 
	//	// open some common libraries
	//	state.open_libraries(sol::lib::base, sol::lib::package);

	//	Ogre::Vector3 foo(2,2,2);

	//	LuaVector3::regClass(state);
	//	LuaVector3::regObj(state, foo);

	//	// load file without execute
	//	sol::load_result script1 = state.load_file("F:\\Projekte\\coop\\XGame\\data\\lua\\test.lua");
	//	script1.call();
	//	//script1(); //execute
	//}

	void LuaEngine::executeScript(const std::string& filepath)
	{
		auto result = loadFile( filepath);
		result(); //execute
	}

	void LuaEngine::reloadScript(const std::string& filepath)
	{
		//FIXME
		auto result = loadFile(filepath);
		result(); //execute
	}

	void LuaEngine::removeScript(const std::string& filepath)
	{
		//todo
	}

	sol::load_result LuaEngine::loadFile(const std::string& filename)
	{
		XE::PhysFsStream wonderfullStream;
		if (wonderfullStream.open(filename.c_str()))
		{
			// Make sure that the stream's reading position is at the beginning
			wonderfullStream.seek(0);

			std::vector<char> buffer(wonderfullStream.getSize());
			if (wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
			{
				return state.load_buffer(&buffer[0], wonderfullStream.getSize(), filename.c_str());
			}
		}
		return 0;
	}

} // ns XE