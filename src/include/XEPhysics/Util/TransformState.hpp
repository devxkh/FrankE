/*
-------------------------------------------------------------------------------
    This file is part of XEKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _TransformState_h_
#define _TransformState_h_

//#include "gkCommon.h"
#include "gkMathUtils.hpp"


#include <XEDAL/Objects/FBEngineTypes_generated.h>

enum gkTransformSpace
{
	TRANSFORM_LOCAL,
	TRANSFORM_PARENT,
	TRANSFORM_WORLD,
};


class TransformState
{
public:


	TransformState(const Ogre::Matrix4& mat)
	{
		MathUtils::extractTransform(mat, loc, rot, scl);

		//GK_ASSERT(!isNaN() && "Invalid vector supplied as parameter");
	}
	
	TransformState(const XFBType::TransformStateData&  tvs)
	{
		rot.w = tvs.rot()->w();
		rot.x = tvs.rot()->x(); rot.y = tvs.rot()->y(); rot.z = tvs.rot()->z();
		loc.x = tvs.loc()->x(); loc.y = tvs.loc()->y(); loc.z = tvs.loc()->z();
		scl.x = tvs.scl()->x(); scl.y = tvs.scl()->y(); scl.z = tvs.scl()->z();

		//GK_ASSERT(!isNaN() && "Invalid vector supplied as parameter");
	}

	TransformState(const Ogre::Vector3&    oloc = Ogre::Vector3::ZERO,
	                 const Ogre::Quaternion& orot = Ogre::Quaternion::IDENTITY,
	                 const Ogre::Vector3&    oscl = Ogre::Vector3::UNIT_SCALE)
	{
		rot.w = orot.w;
		rot.x = orot.x; rot.y = orot.y; rot.z = orot.z;
		loc.x = oloc.x; loc.y = oloc.y; loc.z = oloc.z;
		scl.x = oscl.x; scl.y = oscl.y; scl.z = oscl.z;

		//GK_ASSERT(!isNaN() && "Invalid vector supplied as parameter");
	}

	inline const TransformState& operator= (const TransformState& o)
	{
		//GK_ASSERT(!o.isNaN() && "Invalid vector supplied as parameter");

		rot.w = o.rot.w;
		rot.x = o.rot.x; rot.y = o.rot.y; rot.z = o.rot.z;
		loc.x = o.loc.x; loc.y = o.loc.y; loc.z = o.loc.z;
		scl.x = o.scl.x; scl.y = o.scl.y; scl.z = o.scl.z;

		return *this;
	}


	inline bool operator != (const TransformState& o) const
	{
		return ((rot.w != o.rot.w) ||
		        (rot.x != o.rot.x) ||
		        (rot.y != o.rot.y) ||
		        (rot.z != o.rot.z) ||
		        (loc.x != o.loc.x) ||
		        (loc.y != o.loc.y) ||
		        (loc.z != o.loc.z) ||
		        (scl.x != o.scl.x) ||
		        (scl.y != o.scl.y) ||
		        (scl.z != o.scl.z)
		       );
	}

	void set(const Ogre::Vector3& oloc, const Ogre::Quaternion& orot, const Ogre::Vector3& oscl)
	{
		rot.w = orot.w;
		rot.x = orot.x; rot.y = orot.y; rot.z = orot.z;
		loc.x = oloc.x; loc.y = oloc.y; loc.z = oloc.z;
		scl.x = oscl.x; scl.y = oscl.y; scl.z = oscl.z;

		//GK_ASSERT(!isNaN() && "Invalid vector supplied as parameter");
	}

	inline void setIdentity(void)
	{
		rot.w = 1.0f;
		rot.x = 0.0f; rot.y = 0.0f; rot.z =  0.0f;
		loc.x = 0.0f; loc.y =  0.0f; loc.z =  0.0f;
		scl.x = 1.0f; scl.y =  1.0f; scl.z = 1.0f;
	}

	inline bool isNaN(void) const
	{
		return loc.isNaN() || rot.isNaN() || scl.isNaN();
	}

//	inline void      toMatrix(Ogre::Matrix4& m) const    { m.makeTransform(loc, scl, rot); }
//	inline Ogre::Matrix4 toMatrix(void) const            { Ogre::Matrix4 m; m.makeTransform(loc, scl, rot); return m;}


	inline btQuaternion  toRotation(void)        const { return btQuaternion(rot.x, rot.y, rot.z, rot.w);}
	inline btVector3     toOrigin(void)          const { return btVector3(loc.x, loc.y, loc.z); }
	inline btVector3     toLocalScaling(void)    const { return btVector3(scl.x, scl.y, scl.z); }
	inline btTransform   toTransform(void)       const { btTransform t; toTransform(t); return t; }

	inline void toTransform(btTransform& trans)  const
	{
		trans.setIdentity();
		trans.setOrigin(toOrigin());
		trans.setRotation(toRotation());
	}


	Ogre::Quaternion        rot;
	Ogre::Vector3           loc;
	Ogre::Vector3           scl;
};


#endif//_TransformState_h_
