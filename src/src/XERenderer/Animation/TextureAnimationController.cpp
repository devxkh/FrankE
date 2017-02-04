#include <XERenderer/Animation/TextureAnimationController.hpp>

#include "OgreMath.h"
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

namespace XE {

	void XETexCoordModifierControllerValue::recalcTextureMatrix() const
	{
		// Assumption: 2D texture coords
		Ogre::Matrix4 xform;

		xform = Ogre::Matrix4::IDENTITY;
		if (mUScale != 1 || mVScale != 1)
		{
			// Offset to center of texture
			xform[0][0] = 1 / mUScale;
			xform[1][1] = 1 / mVScale;
			// Skip matrix concat since first matrix update
			xform[0][3] = (-0.5f * xform[0][0]) + 0.5f;
			xform[1][3] = (-0.5f * xform[1][1]) + 0.5f;
		}

		if (mUMod || mVMod)
		{
			Ogre::Matrix4 xlate = Ogre::Matrix4::IDENTITY;

			xlate[0][3] = mUMod;
			xlate[1][3] = mVMod;

			xform = xlate * xform;
		}

		if (mRotation != Ogre::Radian(0))
		{
			Ogre::Matrix4 rot = Ogre::Matrix4::IDENTITY;
			Ogre::Radian theta(mRotation);
			Ogre::Real cosTheta = Ogre::Math::Cos(theta);
			Ogre::Real sinTheta = Ogre::Math::Sin(theta);

			rot[0][0] = cosTheta;
			rot[0][1] = -sinTheta;
			rot[1][0] = sinTheta;
			rot[1][1] = cosTheta;
			// Offset center of rotation to center of texture
			rot[0][3] = 0.5f + ((-0.5f * cosTheta) - (-0.5f * sinTheta));
			rot[1][3] = 0.5f + ((-0.5f * sinTheta) + (-0.5f * cosTheta));

			xform = rot * xform;
		}

		mTexModMatrix = xform;
		
		Ogre::HlmsUnlitDatablock *datablockUnlit = (Ogre::HlmsUnlitDatablock*)mdatablock;
		datablockUnlit->setAnimationMatrix(0, mTexModMatrix);
	}

	//-----------------------------------------------------------------------
	// XETexCoordModifierControllerValue
	//-----------------------------------------------------------------------
	XETexCoordModifierControllerValue::XETexCoordModifierControllerValue(Ogre::HlmsDatablock *datablock, Ogre::uint8 textureUnit, 
		bool translateU, bool translateV, bool scaleU, bool scaleV, bool rotate)
		: mdatablock(datablock)
		, mtextureUnit(textureUnit)
		, mTransU(translateU)
		, mTransV(translateV)
		, mScaleU(scaleU)
		, mScaleV(scaleV)
		, mRotate(rotate)
		, mUMod(0)
		, mVMod(0)
		, mUScale(1)
		, mVScale(1)
		, mRotation(0)
		, mTexModMatrix(Ogre::Matrix4::IDENTITY)
	{

	}

	//-----------------------------------------------------------------------
	Ogre::Real XETexCoordModifierControllerValue::getValue() const
	{
		if (mTransU)
		{
			return mTexModMatrix[0][3];
		}
		else if (mTransV)
		{
			return mTexModMatrix[1][3];
		}
		else if (mScaleU)
		{
			return mTexModMatrix[0][0];
		}
		else if (mScaleV)
		{
			return mTexModMatrix[1][1];
		}
		// Shouldn't get here
		return 0;
	}
	//-----------------------------------------------------------------------
	void XETexCoordModifierControllerValue::setValue(Ogre::Real value)
	{
		if (mTransU)
		{
			mUMod = value;
		}
		if (mTransV)
		{
			mVMod = value;
		}
		if (mScaleU)
		{
			mUScale = value;
		}
		if (mScaleV)
		{
			mVScale = value;
		}
		if (mRotate)
		{
			mRotation = Ogre::Radian(value * Ogre::Math::TWO_PI);
		}

		recalcTextureMatrix();
	}
}