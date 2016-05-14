#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <sfml/Config.hpp>
#include <XEEffect/Decal/OgreDecal.hpp>
#include <XERenderer/OgreSceneManager.hpp>
#include <XEDAL/IDALObject.hpp>

#include <XESystem/Entityx/entityx.h>

#include <memory>

class gkDynamicsWorld;
class gkDebugger;

namespace XFBType
{
	class Node;
}


namespace XE {

	/// Transform space for translations and rotations.
	//enum TransformSpace
	//{
	//	TS_LOCAL = 0,
	//	TS_PARENT,
	//	TS_WORLD
	//};

} // ns XE


#endif // __NODE_HPP__