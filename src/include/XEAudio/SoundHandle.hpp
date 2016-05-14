////////////////////////////////////////////////////////////

#ifndef XE_SOUNDHANDLE_HPP
#define XE_SOUNDHANDLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <XESystem/SystemConfig.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEDAL/PhysFS/PhysFsStream.hpp>

#include <string>

namespace FMOD {
	class Sound;
	class Channel;
}

namespace XE {

	class SoundManager;
	class BodyComponent;

	enum SOUND_TYPE
	{
		SOUND_TYPE_2D_SOUND,
		SOUND_TYPE_2D_SOUND_LOOPED, 
		SOUND_TYPE_3D_SOUND,
		SOUND_TYPE_3D_SOUND_LOOPED,		
	};

	class SoundHandle 
	{
	public:
		SoundHandle(const std::string& fileName);
		~SoundHandle();

		/** Gets the sounds direction
		 */
		const Ogre::Vector3& getDirection() ;
		
		/** Updates sund
		@remarks
			Updates sounds position, buffers and state
			@param fTime
				Elapsed frametime.
		*/
		virtual void update();
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

		void create(SoundManager& soundMgr, SOUND_TYPE soundType = SOUND_TYPE_2D_SOUND);

		std::string& getFileName();

		FMOD::Sound   * _soundPtr;
		FMOD::Channel * _channel;

		PhysFsStream _fileStream;

	private:
		

		std::string _fileName;
		
		BodyComponent* _parentBody;
		//tod make set direction method in soundsource/soundhandle?
		Ogre::Vector3 mDirection;		// 3D direction
		bool mLocalTransformDirty;		// Transformation update flag
		bool mDisable3D;				// 3D status




				//	sf::SoundBuffer buffer;
				//	XE::AL::Sound sound;
	};

} //namespace XE

#endif // XE_SOUNDHANDLE_HPP