#ifndef XE_SOUNDLISTENER_HPP
#define XE_SOUNDLISTENER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre/OgreMain/include/OgreMovableObject.h>
#include <sfml/Audio/Listener.hpp>

namespace XE {

	class SoundListener : public sf::Listener //, public Ogre::MovableObject
	{
		void setOrientation(const Ogre::Quaternion &q);
		/** Gets the orientation of the listener.
		*/
		sf::Vector3f getOrientation() { return sf::Vector3f(mOrientation[0],mOrientation[1],mOrientation[2]); }
	
		/** Updates the listener.
		@remarks
			Handles positional updates to the listener either automatically
			through the SceneGraph attachment or manually using the 
			provided functions.
		 */
		void update();
		/** Gets the movable type string for this object.
		@remarks
			Overridden function from MovableObject, returns a 
			Sound object string for identification.
		 */
		virtual const Ogre::String& getMovableType(void) const;
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
		/** Updates the RenderQueue for this object
		@remarks
			Overridden function from MovableObject.
		 */
		virtual void _updateRenderQueue(Ogre::RenderQueue *queue);
		/** Renderable callback
		@remarks
			Overridden function from MovableObject.
		 */
		virtual void visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables);
		/** Attach callback
		@remarks
			Overridden function from MovableObject.
		 */
		virtual void _notifyAttached(Ogre::Node* node, bool isTagPoint = false);
		/** Moved callback
		@remarks
			Overridden function from MovableObject.
		 */
		virtual void _notifyMoved(void);
	
	private:

		Ogre::Node* mParentNode;

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