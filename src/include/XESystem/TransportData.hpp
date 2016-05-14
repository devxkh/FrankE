#ifndef XE_TRANSPORTDATA_HPP
#define XE_TRANSPORTDATA_HPP

#include <sfml/Config.hpp>
#include <sfml/System/Vector3.hpp>

namespace XE
{
	//using namespace sf; //sf should be usable with XE

	enum Cam_Type
	{
		CA_NONE,
		CA_FREE,
		CA_FIXED,
		CA_MANUAL,
		CA_ORBIT,
		CA_CHARACTER,

		CA_PERSPECTIVE,
		CA_ORTHOGRAPHIC
	};


	struct AABB{
		AABB(){}
		AABB(sf::Vector3f min_aabb,
			sf::Vector3f maxaabb) : min_aabb(min_aabb), maxaabb(maxaabb){}
		sf::Vector3f min_aabb;
		sf::Vector3f maxaabb;
	};
}

#endif // XE_TRANSPORTDATA_HPP

//http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer
//Some useful(normalized) quaternions
//
//
//
//w	x	y	z	Description
//1	0	0	0	Identity quaternion, no rotation
//0	1	0	0	180° turn around X axis
//0	0	1	0	180° turn around Y axis
//0	0	0	1	180° turn around Z axis
//sqrt(0.5)	sqrt(0.5)	0	0	90° rotation around X axis
//sqrt(0.5)	0	sqrt(0.5)	0	90° rotation around Y axis
//sqrt(0.5)	0	0	sqrt(0.5)	90° rotation around Z axis
//sqrt(0.5) - sqrt(0.5)	0	0 - 90° rotation around X axis
//sqrt(0.5)	0 - sqrt(0.5)	0 - 90° rotation around Y axis
//sqrt(0.5)	0	0 - sqrt(0.5) - 90° rotation around Z axis
