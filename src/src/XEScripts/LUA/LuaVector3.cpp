#include <XEScripts/LUA/LuaVector3.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <ThirdParty/selene/selene.h>

#include <ThirdParty/sol/sol.hpp>

namespace XE {

	void LuaVector3::regClass(sol::state& state)
	{
		state.new_usertype< Ogre::Vector3>("Vector3",

			// 3 constructors
			//sol::constructors<sol::types<>, sol::types<int>, sol::types<int, int>>(),
			sol::constructors<sol::types<>, sol::types<float, float,float>>(),

			// typical member function that returns a variable

			"x", &Ogre::Vector3::x,
			// typical member function
			"y", &Ogre::Vector3::y,
			"z", &Ogre::Vector3::z

			// gets or set the value using member variable syntax
			//"hp", sol::property(&player::get_hp, &player::set_hp),

			//// read and write variable
			//"speed", &player::speed,
			//// can only read from, not write to
			//"bullets", sol::readonly(&player::bullets)
			);

		//state["Vector3"] = Ogre::Vector3();// .set<Ogre::Vector3, float, float, float>("x", &Ogre::Vector3::x, "y", &Ogre::Vector3::y, "z", &Ogre::Vector3::z);
	
		state["multiply"] = &LuaVector3::multiply;
	}

	void LuaVector3::regObj(sol::state& state, Ogre::Vector3& vec)
	{
		//state["foo"].SetObj(foo,"x", &Vector3::x,"y", &Vector3::y);

		state["foo"].set(vec);//.set(vec,"x", &Ogre::Vector3::x, "y", &Ogre::Vector3::y, "z", &Ogre::Vector3::z);
	//	state["multiply"] = &LuaVector3::multiply;
	}

	void LuaVector3::multiply(Ogre::Vector3& left, const Ogre::Vector3& right)
	{
		left *= right;
	}

} //ns XE