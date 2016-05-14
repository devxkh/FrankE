#include <XEAudio/SoundListener.hpp>

#include <XEngine/Components/Body.hpp>

#include <Ogre/OgreMain/include/OgreAxisAlignedBox.h>

namespace XE {


	Ogre::Vector3 SoundListener::getOrientation() { 
		return Ogre::Vector3(mOrientation[0], mOrientation[1], mOrientation[2]); 
	}

	void SoundListener::setOrientation(const Ogre::Quaternion &q)
	{
		Ogre::Vector3 vDirection = q.zAxis();
		Ogre::Vector3 vUp = q.yAxis();

		mOrientation[0] = -vDirection.x;
		mOrientation[1] = -vDirection.y;
		mOrientation[2] = -vDirection.z;
		mOrientation[3] = vUp.x;
		mOrientation[4] = vUp.y;
		mOrientation[5] = vUp.z;	
	//todo	alListenerfv(AL_ORIENTATION,mOrientation);	
	}

/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::update(BodyComponent* parentBody, float fTime)
	{
		if(mLocalTransformDirty)
		{
			if (parentBody)
			{
				/*setPosition(sf::Vector3f(mParentNode->_getDerivedPosition().x, mParentNode->_getDerivedPosition().y, mParentNode->_getDerivedPosition().z));
				setOrientation(mParentNode->_getDerivedOrientation());		*/	 
			}
			mLocalTransformDirty=false;
		}
	}
	/*/////////////////////////////////////////////////////////////////*/
	const Ogre::AxisAlignedBox& SoundListener::getBoundingBox(void) const
	{
		Ogre::AxisAlignedBox aab;
		return aab;
	}
	/*/////////////////////////////////////////////////////////////////*/
	float SoundListener::getBoundingRadius(void) const
	{
		return 0;
	}

} //namespace XE