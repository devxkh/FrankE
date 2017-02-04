#pragma once

#include "OgreController.h"
#include <Ogre/OgreMain/include/OgreMatrix4.h>

namespace XE {

	//-----------------------------------------------------------------------
	/** Predefined controller value for getting / setting a texture coordinate modifications (scales and translates).
	@remarks
	Effects can be applied to the scale or the offset of the u or v coordinates, or both. If separate
	modifications are required to u and v then 2 instances are required to control both independently, or 4
	if you want separate u and v scales as well as separate u and v offsets.
	@par
	Because of the nature of this value, it can accept values outside the 0..1 parametric range.
	*/
	class _OgreExport XETexCoordModifierControllerValue : public Ogre::ControllerValue<Ogre::Real>
	{
	protected:
		bool mTransU, mTransV;
		bool mScaleU, mScaleV;
		bool mRotate;
		
		Ogre::HlmsDatablock *mdatablock;
		Ogre::uint8 mtextureUnit;

		Ogre::Real mUMod, mVMod;
		Ogre::Real mUScale, mVScale;
		Ogre::Radian mRotation;
		mutable Ogre::Matrix4 mTexModMatrix;

	public:
		/** Constructor.
		@param
		t TextureUnitState to apply the modification to.
		@param
		translateU If true, the u coordinates will be translated by the modification.
		@param
		translateV If true, the v coordinates will be translated by the modification.
		@param
		scaleU If true, the u coordinates will be scaled by the modification.
		@param
		scaleV If true, the v coordinates will be scaled by the modification.
		@param
		rotate If true, the texture will be rotated by the modification.
		*/
		XETexCoordModifierControllerValue(Ogre::HlmsDatablock *datablock, Ogre::uint8 textureUnit, bool translateU = false, bool translateV = false,
			bool scaleU = false, bool scaleV = false, bool rotate = false);

		Ogre::Real getValue(void) const;
		void setValue(Ogre::Real value);

	private:
		void recalcTextureMatrix() const;

	};

}