#ifndef _LuaVector3_hpp_
#define _LuaVector3_hpp_

namespace Ogre
{
	class Vector3;
}

namespace sol
{
	class state;
}

namespace XE {
	
	class LuaVector3 {
	public:
		static void regClass(sol::state& state);
		static void regObj(sol::state& state, Ogre::Vector3& vec);

		static void multiply(Ogre::Vector3& left, const Ogre::Vector3& right);
	};

} //ns XE

#endif // 