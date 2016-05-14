////////////////////////////////////////////////////////////

#ifndef XE_SOUNDHANDLE_HPP
#define XE_SOUNDHANDLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre/OgreMain/include/OgreMovableObject.h>
#include <sfml/Audio/Sound.hpp>

//test
#include <sfml/Audio/SoundBuffer.hpp>

namespace XE {

	class SoundManager;

	class SoundHandle : public sf::Sound //, public Ogre::MovableObject
	{
	public:
		//SoundHandle();
		~SoundHandle();

		SoundHandle(const Ogre::String& name,
					//XE::SceneManager* sceneMgr,
					const Ogre::String& file,
					const Ogre::String& resourceGroupName,
					bool stream = false, 
					bool loop = false, 
					bool preBuffer = false,
					bool immediate = false);

			/** Gets movable type string
		@remarks
			Overridden from MovableObject.
		 */
		virtual const Ogre::String& getMovableType(void) const;
				/** Gets the sounds name
		 */
		const Ogre::String& getName(void) const { return mName; }
	 
		/** Gets the sounds direction
		 */
		const sf::Vector3f& getDirection() const {return mDirection;}
		/** Updates sund
		@remarks
			Updates sounds position, buffers and state
			@param fTime
				Elapsed frametime.
		*/
		virtual void update(float fTime);
			/** Gets bounding box
		@remarks
			Overridden from MovableObject.
		 */
		virtual const Ogre::AxisAlignedBox& getBoundingBox(void) const;
		/** Gets bounding radius
		@remarks
			Overridden from MovableObject.
		 */
		virtual float getBoundingRadius(void) const;
		/** Gets the SceneManager pointer registered at creation.
		@remarks
			This will only be set if the sound was created through the plugin method
			createMovableobject().
		*/
	//	XE::SceneManager* getSceneManager() const { return &mScnMan; }

		/** Updates RenderQueue
		@remarks
			Overridden from MovableObject.
		 */
		virtual void _updateRenderQueue(Ogre::RenderQueue *queue);
		/** Notifys object its been attached to a node
		@remarks
			Overridden from MovableObject.
		 */
		virtual void _notifyAttached(Ogre::Node* node, bool isTagPoint = false);
		/** Notifys object its been moved
		@remarks
			Overridden from MovableObject.
		 */
		virtual void _notifyMoved(void);
		/** Renderable callback
		@remarks
			Overridden function from MovableObject.
		 */
		virtual void visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables);

	private:
		//XE::SceneManager& mScnMan;	// SceneManager reference for plugin registered sounds
	
		Ogre::Node* mParentNode;
		Ogre::String mName;
		//tod make set direction method in soundsource/soundhandle?
		sf::Vector3f mDirection;		// 3D direction
		bool mLocalTransformDirty;		// Transformation update flag
			bool mDisable3D;				// 3D status

					sf::SoundBuffer buffer;
				//	XE::AL::Sound sound;
	};

} //namespace XE

#endif // XE_SOUNDHANDLE_HPP