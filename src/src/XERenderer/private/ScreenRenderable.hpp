#pragma once

#include <Ogre/OgreMain/include/OgreRenderable.h>

namespace XE {

	class ScreenRenderable : public Ogre::Renderable
	{
	public:
		ScreenRenderable()
			: mUseCustomProjectionMatrix(false)
		{

		}
		
		void setCustomProjectionMatrix(bool enable, const Ogre::Matrix4& projMatrix = Ogre::Matrix4::IDENTITY)
		{
			mUseCustomProjectionMatrix = enable;
			if (enable)
			{
				mProjMatrix = projMatrix;
			}
		}

		Ogre::Matrix4& getCustomProjectionMatrix() { return mProjMatrix; };

		bool getUseCustomProjectionMatrix(void) const { return mUseCustomProjectionMatrix; }
		
	protected:
		Ogre::Matrix4 mProjMatrix;
		bool mUseCustomProjectionMatrix;

	};

}