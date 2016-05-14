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
#include <XEPhysics/Util/gkMathUtils.hpp>


//XE::Matrix3 gkMathUtils::getMat3FromEuler(const XE::Vector3& eul, bool isDegree)
//{
//	XE::Matrix3 rx, ry, rz;
//
//	gkRadian Rx, Ry, Rz;
//
//	if (gkFuzzyVec(eul))
//		return XE::Matrix3::IDENTITY;
//
//	if (isDegree)
//	{
//		if (!gkFuzzy(eul.x)) Rx = gkRadian(gkDegree(eul.x));
//		if (!gkFuzzy(eul.y)) Ry = gkRadian(gkDegree(eul.y));
//		if (!gkFuzzy(eul.z)) Rz = gkRadian(gkDegree(eul.z));
//	}
//
//	else
//	{
//		if (!gkFuzzy(eul.x)) Rx = gkRadian(eul.x);
//		if (!gkFuzzy(eul.y)) Ry = gkRadian(eul.y);
//		if (!gkFuzzy(eul.z)) Rz = gkRadian(eul.z);
//	}
//
//	if (!gkFuzzy(eul.x)) rx.FromAngleAxis(XE::Vector3::UNIT_X, Rx);
//	else rx = XE::Matrix3::IDENTITY;
//
//	if (!gkFuzzy(eul.y)) ry.FromAngleAxis(XE::Vector3::UNIT_Y, Ry);
//	else ry = XE::Matrix3::IDENTITY;
//
//	if (!gkFuzzy(eul.z)) rz.FromAngleAxis(XE::Vector3::UNIT_Z, Rz);
//	else rz = XE::Matrix3::IDENTITY;
//
//	return XE::Matrix3(rz * ry * rx);
//}
//
//
//XE::Quaternion gkMathUtils::getQuatFromEuler(const XE::Vector3& eul, bool isDegree)
//{
//	if (gkFuzzyVec(eul))
//		return XE::Quaternion::IDENTITY;
//
//	return XE::Quaternion(getMat3FromEuler(eul, isDegree));
//}
//
//
//
//XE::Vector3 gkMathUtils::getEulerFromQuat(const XE::Quaternion& q, bool toDegree)
//{
//	XE::Matrix3 matr;
//	q.ToRotationMatrix(matr);
//
//	gkScalar x, y, z; gkRadian rx, ry, rz;
//	matr.ToEulerAnglesZYX(rz, ry, rx);
//
//	if (toDegree)
//	{
//		x = rx.valueDegrees();
//		y = ry.valueDegrees();
//		z = rz.valueDegrees();
//	}
//	else
//	{
//		x = rx.valueRadians();
//		y = ry.valueRadians();
//		z = rz.valueRadians();
//	}
//
//	if (gkFuzzy(x)) x = 0.0;
//	if (gkFuzzy(y)) y = 0.0;
//	if (gkFuzzy(z)) z = 0.0;
//
//	return XE::Vector3(x, y, z);
//}
//
//
//XE::Matrix4 gkMathUtils::getFromFloat(const float m[][4])
//{
//	// convert a Blender4x4 matrix to XE4x4
//	return XE::Matrix4(
//	           m[0][0], m[1][0], m[2][0], m[3][0],
//	           m[0][1], m[1][1], m[2][1], m[3][1],
//	           m[0][2], m[1][2], m[2][2], m[3][2],
//	           m[0][3], m[1][3], m[2][3], m[3][3]
//	       );
//}
//
//
//XE::Matrix4 gkMathUtils::getFromFloat3(const float m[][3])
//{
//	// convert a Blender3x3 matrix to XE4x4
//	return XE::Matrix4(
//	           m[0][0], m[1][0], m[2][0], 0.0,
//	           m[0][1], m[1][1], m[2][1], 0.0,
//	           m[0][2], m[1][2], m[2][2], 0.0,
//	           0.0,     0.0,     0.0,     1.0
//	       );
//}
//
//
//XE::Matrix4 gkMathUtils::getFromFloatNorm(const float m[][4])
//{
//	XE::Vector3 l, s;
//	XE::Quaternion r;
//	extractMatrix(m, l, r, s);
//
//	XE::Matrix4 ret;
//	ret.makeTransform(l, s, r);
//	return ret;
//}
//
//
//void gkMathUtils::extractLocEulScale(const XE::Matrix4& m, XE::Vector3& loc, XE::Vector3& eul, XE::Vector3& scale, bool inDegrees)
//{
//	// extract translation
//	loc = m.getTrans();
//
//	// extract rotation
//	XE::Matrix3 matr;
//	m.extract3x3Matrix(matr);
//
//	XE::Quaternion rot(matr);
//	rot.normalise();
//	eul = getEulerFromQuat(rot, inDegrees);
//
//	// extract scale
//	XE::Matrix4 invRot(rot.Inverse());
//	XE::Matrix4 t = invRot * m;
//	scale = XE::Vector3(t[0][0], t[1][1], t[2][2]);
//}
//
//
//
//void gkMathUtils::makeLocEulScale(XE::Matrix4& dest, const XE::Vector3& loc, const XE::Vector3& eul, const XE::Vector3& scale, bool inDegrees)
//{
//	dest.makeTransform(loc, scale, getQuatFromEuler(eul, inDegrees));
//}
//
//
//void gkMathUtils::makeLocQuatScale(XE::Matrix4& dest, const XE::Vector3& loc, const XE::Quaternion& q, const XE::Vector3& scale)
//{
//	dest.makeTransform(loc, scale, q);
//}
//
//XE::Quaternion gkMathUtils::interp(const XE::Quaternion& a, const XE::Quaternion& b, gkScalar t, bool fast)
//{
//	return fast ? XE::Quaternion::nlerp(t, a, b, a.Dot(b) < 0.0) : XE::Quaternion::Slerp(t, a, b, a.Dot(b) < 0.0);
//}
//
//
//XE::Vector3 gkMathUtils::interp(const XE::Vector3& a, const XE::Vector3& b, gkScalar t)
//{
//	gkScalar s = 1.f - t;
//	XE::Vector3 ret;
//	ret.x = s * a.x + t * b.x;
//	ret.y = s * a.y + t * b.y;
//	ret.z = s * a.z + t * b.z;
//	return ret;
//}
//
//
//gkVector2 gkMathUtils::interp(const gkVector2& a, const gkVector2& b, gkScalar t)
//{
//	gkScalar s = 1.f - t;
//	gkVector2 ret;
//	ret.x = s * a.x + t * b.x;
//	ret.y = s * a.y + t * b.y;
//	return ret;
//}
//
//
//gkScalar gkMathUtils::interp(const gkScalar& a, const gkScalar& b, gkScalar t)
//{
//	gkScalar s = 1.f - t;
//	return s * a + t * b;
//}
//

//void MathUtils::extractTransform(const XE::Matrix4& m, XE::Vector3& loc, XE::Quaternion& quat, XE::Vector3& scale)
//{
//	// extract translation
//	loc = m.Translation();
//
//	// extract rotation
//	XE::Matrix3 matr;
//	m.extract3x3Matrix(matr);
//	matr.Orthonormalize();
//
//	XE::Quaternion rot(matr);
//	if (quat.Norm() == 0.0)
//		rot = XE::Quaternion::IDENTITY;
//	quat = rot;
//
//	// extract scale
//	XE::Matrix4 invRot(rot.Inverse());
//	XE::Matrix4 T = invRot * m;
//	scale = XE::Vector3(T[0][0], T[1][1], T[2][2]);
//}
//
//
//
//void MathUtils::extractTransformFast(const XE::Matrix4& m, XE::Vector3& loc, XE::Quaternion& quat, XE::Vector3& scale, bool getScale)
//{
//	// extract translation
//	loc = m.getTrans();
//	quat = m.extractQuaternion();
//
//	if (getScale)
//	{
//		// extract scale
//		XE::Matrix4 invRot(quat.Inverse());
//		XE::Matrix4 T = invRot * m;
//		scale = XE::Vector3(T[0][0], T[1][1], T[2][2]);
//	}
//	else scale = XE::Vector3::UNIT_SCALE;
//}



//void gkMathUtils::blendMatrixFast(XE::Matrix4& dest, const XE::Matrix4& A, const XE::Matrix4& B, gkScalar fact, bool fastRot, bool getScale)
//{
//	if (fact <= 0)
//	{
//		dest = A;
//		return;
//	}
//	if (fact >= 1)
//	{
//		dest = B;
//		return;
//	}
//
//	XE::Vector3 aloc, ascale, bloc, bscale;
//	XE::Quaternion aquat, bquat;
//
//	extractTransformFast(A, aloc, aquat, ascale, getScale);
//	extractTransformFast(B, bloc, bquat, bscale, getScale);
//
//	XE::Vector3 dloc = bloc, dscale = bscale;
//	XE::Quaternion drot = bquat;
//
//	if (aloc != bloc)
//		dloc = interp(aloc, bloc, fact);
//
//	if (aquat != bquat)
//		drot = interp(aquat, bquat, fact, fastRot);
//
//	if (ascale != bscale)
//		dscale = interp(ascale, bscale, fact);
//
//	dest.makeTransform(dloc, dscale, drot);
//}
//
//
//void gkMathUtils::extractMatrix(const float m[][4], XE::Vector3& loc, XE::Quaternion& quat, XE::Vector3& scale)
//{
//	// Used for extracting transforms from a Blender4x4 matrix
//	XE::Matrix4 btomat = getFromFloat(m);
//
//	// extract translation
//	loc = btomat.getTrans();
//
//	// extract rotation
//	XE::Matrix3 matr;
//	btomat.extract3x3Matrix(matr);
//	matr.Orthonormalize();
//
//	XE::Quaternion rot(matr);
//	if (rot.Norm() != 1.0)
//		rot.normalise();
//	quat = rot;
//
//	// extract scale
//	XE::Matrix4 invRot(rot.Inverse());
//	btomat = invRot * btomat;
//	scale = XE::Vector3(btomat[0][0], btomat[1][1], btomat[2][2]);
//}
