#include <XEAudio/XESoundListener.hpp>
#include <Ogre/OgreMain/include/OgreNode.h>
#include <XEAudio/XESoundFactory.hpp>

namespace XE {

	using namespace Ogre;

	void SoundListener::setOrientation(const Quaternion &q)
	{
		Vector3 vDirection = q.zAxis();
		Vector3 vUp = q.yAxis();

		mOrientation[0] = -vDirection.x;
		mOrientation[1] = -vDirection.y;
		mOrientation[2] = -vDirection.z;
		mOrientation[3] = vUp.x;
		mOrientation[4] = vUp.y;
		mOrientation[5] = vUp.z;	
	//todo	alListenerfv(AL_ORIENTATION,mOrientation);	
	}

/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::update()
	{
		if(mLocalTransformDirty)
		{
			if ( mParentNode )
			{
				setPosition(sf::Vector3f(mParentNode->_getDerivedPosition().x, mParentNode->_getDerivedPosition().y, mParentNode->_getDerivedPosition().z));
				setOrientation(mParentNode->_getDerivedOrientation());			 
			}
			mLocalTransformDirty=false;
		}
	}
	/*/////////////////////////////////////////////////////////////////*/
	const XE::AxisAlignedBox& SoundListener::getBoundingBox(void) const
	{
		static XE::AxisAlignedBox aab;
		return aab;
	}
	/*/////////////////////////////////////////////////////////////////*/
	float SoundListener::getBoundingRadius(void) const
	{
		return 0;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::_updateRenderQueue(XE::RenderQueue *queue)
	{
		return;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::visitRenderables(XE::Renderable::Visitor* visitor, bool debugRenderables)
	{
		return;
	}
	/*/////////////////////////////////////////////////////////////////*/
	const String& SoundListener::getMovableType(void) const
	{
		return SoundFactory::FACTORY_TYPE_NAME;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::_notifyAttached(XE::Node* node, bool isTagPoint)
	{
		// Call base class notify
	//	XE::MovableObject::_notifyAttached(node, isTagPoint);
		//todo move soundlistener!!

		// Immediately set position/orientation when attached
		if (mParentNode)
		{
			
			setPosition(sf::Vector3f(mParentNode->_getDerivedPosition().x, mParentNode->_getDerivedPosition().y, mParentNode->_getDerivedPosition().z));
			setOrientation(mParentNode->_getDerivedOrientation());
		}

		return;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundListener::_notifyMoved(void) 
	{ 
		// Call base class notify
//		MovableObject::_notifyMoved();

		mLocalTransformDirty=true; 
	}
	
} //namespace XE