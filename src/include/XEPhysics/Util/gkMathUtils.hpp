/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
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
#ifndef _gkMathUtils_h_
#define _gkMathUtils_h_

//#include "gkCommon.h"
#include <bullet/LinearMath/btTransform.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreQuaternion.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/OgreMain/include/OgreMatrix3.h>
//#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <Ogre/OgreMain/include/OgreVector2.h>
//#include "OgreMatrix3.h"
//#include <Ogre/OgreMain/include/OgreMatrix4.h>
//#include "OgreRay.h"
//#include <Ogre/OgreMain/include/OgreMath.h>
//#include <Ogre/OgreMain/include/OgreQuaternion.h>
//#include "OgreColourValue.h"
//#include "OgreAxisAlignedBox.h"

//#include <sfml/System/Vector2.hpp>
//#include <sfml/System/Vector3.hpp>
#include <float.h>

#if OGRE_DOUBLE_PRECISION == 1
# define GK_EPSILON   DBL_EPSILON
# define GK_INFINITY  DBL_MAX
#else
# define GK_EPSILON   FLT_EPSILON
# define GK_INFINITY  FLT_MAX
# pragma warning(disable :4305)
# pragma warning(disable :4244)
#endif

// Rotation in degrees true, else false
#define GK_ROTUNIT true


// Reusing math functions for simplicity
//typedef Ogre::Math              gkMath;
//typedef float              float;
//typedef Ogre::Degree            Ogre::Degree;
//typedef Ogre::Radian            Ogre::Radian;
//typedef Ogre::Vector2           Ogre::Vector2;
//typedef Ogre::Vector3           Ogre::Vector3;
//typedef Ogre::Vector4           gkVector4;
//typedef Ogre::Quaternion        Ogre::Quaternion;
//typedef Ogre::Matrix3           Ogre::Matrix3;
//typedef Ogre::Matrix4           Ogre::Matrix4;
//typedef Ogre::ColourValue       gkColor;
//typedef Ogre::AxisAlignedBox    gkBoundingBox;
//typedef Ogre::Ray               gkRay;


#define gkPi        float(3.141592653589793238)
#define gkPi2       float(6.283185307179586476)
#define gkPih       float(1.570796326794896619)
#define gkRPD       float(0.017453292519943295)
#define gkDPR       float(57.295779513082320876)


inline float  gkAbs(const float& v)                                { return v < float(0.0) ? -v : v;}
inline bool      gkNan(const float& v)                                { return v != v;}
inline bool      gkFinite(const float& v)                             { return gkAbs(v) < GK_INFINITY;}
inline bool      gkFuzzy(const float& v)                              { return gkAbs(v) < GK_EPSILON;}
inline bool      gkFuzzyT(const float& v, const float& tol)        { return gkAbs(v) < tol;}
inline bool      gkFuzzyEq(const float& a, const float& b)         { return gkAbs(a - b) < GK_EPSILON;}
inline bool      gkIsInf(const float& v)                              { return gkAbs(v) >= GK_INFINITY; }
inline bool      gkFuzzyVec(const Ogre::Vector2& v)                          { return gkFuzzy(v.squaredLength()); }
inline bool      gkFuzzyVec(const Ogre::Vector3& v)                          { return gkFuzzy(v.squaredLength()); }
//inline float  Ogre::Degree(const float& v)                            { return v * gkDPR;}
//inline float  Ogre::Radians(const float& v)                            { return v * gkRPD;}


// Min / Max utils

template <typename T> inline T gkMax(const T& a, const T& b)                         {return a < b ? b : a; }
template <typename T> inline T gkMin(const T& a, const T& b)                         {return a < b ? a : b; }
template <typename T> inline T gkClamp(const T& v, const T& a, const T& b)           {return v < a ? a : v > b ? b : v; }
inline float gkMaxf(const float& a, const float& b)                         {return gkMax<float>(a, b); }
inline float gkMinf(const float& a, const float& b)                         {return gkMin<float>(a, b); }
inline float gkClampf(const float& v, const float& a, const float& b)    {return gkClamp<float>(v, a, b); }


//class gkEuler
//{
//public:
//	inline gkEuler() {}
//
//	inline gkEuler(const Ogre::Degree& dx, const Ogre::Degree& dy, const Ogre::Degree& dz)
//		:       x(dx.valueDegrees()), y(dy.valueDegrees()), z(dz.valueDegrees())
//	{
//	}
//
//	inline gkEuler(float dx, float dy, float dz)
//		:       x(Ogre::Degree(dx)), y(Ogre::Degree(dy)), z(Ogre::Degree(dz))
//	{
//	}
//
//	inline gkEuler(const Ogre::Vector3& v)
//		:       x(Ogre::Degree(v.x)), y(Ogre::Degree(v.y)), z(Ogre::Degree(v.z))
//	{
//	}
//
//	inline gkEuler(const Ogre::Radian& rx, const Ogre::Radian& ry, const Ogre::Radian& rz)
//		:       x(rx.valueDegrees()), y(ry.valueDegrees()), z(rz.valueDegrees())
//	{
//	}
//
//	//inline gkEuler(const Ogre::Quaternion& q)
//	//{
//	//	Ogre::Matrix3 matr;
//	//	q.ToRotationMatrix(matr);
//	//	matr.ToEulerAnglesZYX(z, y, x);
//	//}
//
//	inline gkEuler(const Ogre::Matrix3& v)           { v.ToEulerAnglesZYX(z, y, x); }
//	inline Ogre::Vector3 toVector3(void) const       { return Ogre::Vector3(x.valueDegrees(), y.valueDegrees(), z.valueDegrees()); }
//	inline Ogre::Quaternion toQuaternion(void) const { return Ogre::Quaternion(toMatrix3());}
//
//	inline Ogre::Matrix3 toMatrix3(void) const
//	{
//		Ogre::Matrix3 rx, ry, rz;
//		rx.FromAngleAxis(Ogre::Vector3::UNIT_X, x);
//		ry.FromAngleAxis(Ogre::Vector3::UNIT_Y, y);
//		rz.FromAngleAxis(Ogre::Vector3::UNIT_Z, z);
//		return Ogre::Matrix3(rz * ry * rx);
//	}
//
//	Ogre::Radian x, y, z;
//};


//class gkRectangle
//{
//public:
//	gkRectangle() {}
//	gkRectangle(float xv, float yv, float wv, float hv)
//	{
//		x = xv;
//		y = yv;
//		width = wv;
//		height = hv;
//	}
//	gkRectangle(const gkRectangle& o) { *this = o; }
//
//	gkRectangle& operator= (const gkRectangle& o)
//	{
//		x = o.x;
//		y = o.y;
//		width = o.width;
//		height = o.height;
//		return *this;
//	}
//	float x, y;
//	float width, height;
//};




class MathUtils
{
public:

	static Ogre::Matrix3 getMat3FromEuler(const Ogre::Vector3& eul, bool isDegree = GK_ROTUNIT);
	static Ogre::Quaternion getQuatFromEuler(const Ogre::Vector3& eul, bool isDegree = GK_ROTUNIT);
	static Ogre::Vector3 getEulerFromQuat(const Ogre::Quaternion& q, bool toDegree = GK_ROTUNIT);

	static Ogre::Matrix4 getFromFloat(const float m[][4]);
	static Ogre::Matrix4 getFromFloat3(const float m[][3]);
	static Ogre::Matrix4 getFromFloatNorm(const float m[][4]);

	static void extractLocEulScale(const Ogre::Matrix4& m, Ogre::Vector3& loc, Ogre::Vector3& eul, Ogre::Vector3& scale, bool inDegrees = true);
	static void makeLocEulScale(Ogre::Matrix4& dest, const Ogre::Vector3& loc, const Ogre::Vector3& eul, const Ogre::Vector3& scale, bool inDegrees = true);
	static void makeLocQuatScale(Ogre::Matrix4& dest, const Ogre::Vector3& loc, const Ogre::Quaternion& q, const Ogre::Vector3& scale);

	static Ogre::Quaternion interp(const Ogre::Quaternion& a, const Ogre::Quaternion& b, float t, bool fast = true);
	static Ogre::Vector2 interp(const Ogre::Vector2& a, const Ogre::Vector2& b, float t);
	static Ogre::Vector3 interp(const Ogre::Vector3& a, const Ogre::Vector3& b, float t);
	static float interp(const float& a, const float& b, float t);

	static void extractTransform(const Ogre::Matrix4& m, Ogre::Vector3& loc, Ogre::Quaternion& quat, Ogre::Vector3& scale);
	static void extractTransformFast(const Ogre::Matrix4& m, Ogre::Vector3& loc, Ogre::Quaternion& quat, Ogre::Vector3& scale, bool getScale = true);
	static void blendMatrixFast(Ogre::Matrix4& dest, const Ogre::Matrix4& A, const Ogre::Matrix4& B, float fact, bool fastRot = true, bool getScale = true);

	static void extractMatrix(const float m[][4], Ogre::Vector3& loc, Ogre::Quaternion& quat, Ogre::Vector3& scale);



	// Bullet converters
	static inline Ogre::Vector3      get(const btVector3& v)     { return Ogre::Vector3(v.x(), v.y(), v.z()); }
	static inline btVector3      get(const Ogre::Vector3& v)     { return btVector3(v.x, v.y, v.z); }
	static inline Ogre::Quaternion   get(const btQuaternion& v)  { return Ogre::Quaternion(v.w(), v.x(), v.y(), v.z()); }
	static inline btQuaternion   get(const Ogre::Quaternion& v)  { return btQuaternion(v.x, v.y, v.z, v.w); }
	static inline btTransform	get(const Ogre::Matrix3& m)		{ return btTransform(get(Ogre::Quaternion(m))); }
//	static inline btTransform	get(const Ogre::Matrix4& m)		{ return btTransform(get(m.extractQuaternion()), get(m.getTrans())); }
//	static inline btVector3      get(const Ogre::Vector3& v)     { return btVector3(v.x, v.y, v.z); }
};





#endif//_gkMathUtils_h_
