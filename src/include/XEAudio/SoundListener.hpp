#ifndef XE_SOUNDLISTENER_HPP
#define XE_SOUNDLISTENER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <XESystem/SystemConfig.hpp>

namespace Ogre
{
	class Quaternion;
	class Vector3;
	class AxisAlignedBox;
	class SceneNode;
}

namespace XE {
	class BodyComponent;

	class SoundListener 
	{
		void setOrientation(const Ogre::Quaternion &q);
		
		/** Gets the orientation of the listener.
		*/
		Ogre::Vector3 getOrientation();
	
		/** Updates the listener.
		@remarks
			Handles positional updates to the listener either automatically
			through the SceneGraph attachment or manually using the 
			provided functions.
		 */
		void update(BodyComponent* parentBody,float fTime = 0.f);
	

		/** Gets the bounding box of this object.
		@remarks
			Overridden function from MovableObject, provides a
			bounding box for this object.
		 */
		virtual const Ogre::AxisAlignedBox& getBoundingBox(void) const;
		/** Gets the bounding radius of this object.
		@remarks
			Overridden function from MovableObject, provides the
			bounding radius for this object.
		 */
		virtual float getBoundingRadius(void) const;

	private:

		/**
		 * Positional variables
		 */
		//Ogre::Vector3 mPosition;		// 3D position
		//Ogre::Vector3 mVelocity;		// 3D velocity
		float mOrientation[6];			// 3D orientation
		bool mLocalTransformDirty;		// Dirty transforms flag

	};

}	// namespace XE
#endif // XE_SOUNDLISTENER_HPP