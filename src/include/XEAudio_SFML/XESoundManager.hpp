#ifndef XE_SOUNDMANAGER_HPP
#define XE_SOUNDMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre/OgreMain/include/OgreStringVector.h>
#include <Ogre/OgreMain/include/OgreSingleton.h>

#include <map>
#include <list>
#include <deque>

namespace XE {

	//forward declaration
	class SoundListener;
	class SoundFactory;
	class SoundHandle;

	typedef std::map<Ogre::String, SoundHandle*> SoundMap;
//	typedef std::map<String, ALuint> EffectList;
//	typedef std::map<ALenum, bool> FeatureList;
	typedef std::list<SoundHandle*> ActiveList;
//	typedef std::deque<ALuint> SourceList;

		//! Various sound commands
	enum SOUND_ACTION
	{
		LQ_PLAY,
		LQ_STOP,
		LQ_PAUSE,
		LQ_LOAD,
		LQ_GLOBAL_PITCH,
		LQ_STOP_ALL,
		LQ_PAUSE_ALL,
		LQ_RESUME_ALL,
		LQ_REACTIVATE,
		LQ_DESTROY_TEMPORARY,
		LQ_ATTACH_EFX,
		LQ_DETACH_EFX,
		LQ_SET_EFX_PROPERTY
	};

	//! Holds information about a sound action
	struct SoundAction
	{
		Ogre::String	mSound;
		SOUND_ACTION	mAction;
		bool			mImmediately;
		void*			mParams;
	};

	//! Holds information about a create sound request.
	struct cSound
	{
		bool mPrebuffer;
		Ogre::String mFileName;
		Ogre::uint32 mBuffer;
	//	Ogre::DataStreamPtr mStream;
	};

	//! Holds information about a EFX effect.
	struct efxProperty
	{
		Ogre::String mEffectName;
		Ogre::String mFilterName;
		Ogre::Real mAirAbsorption;
		Ogre::Real mRolloff;
		Ogre::Real mConeHF;
		Ogre::uint32 mSlotID;
	};

	//! Holds information about a static shared audio buffer.
	struct sharedAudioBuffer
	{
		Ogre::uint32 mAudioBuffer;
		Ogre::uint32 mRefCount;
	};

	typedef std::map<Ogre::String, sharedAudioBuffer*> SharedBufferList;

	////////////////////////////////////////////////////////////
	/// \brief The audio listener is the point in the scene
	///        from where all the sounds are heard
	///
	////////////////////////////////////////////////////////////
	class SoundManager : public Ogre::Singleton<SoundManager>
	{
	public :
		 
		////////////////////////////////////////////////////////////
		/// \brief Creates a manager for all sounds within the application.
		////////////////////////////////////////////////////////////
		SoundManager();

		////////////////////////////////////////////////////////////
		/// \brief Destroys this manager.
		/// 	Destroys all sound objects and thread if defined. Cleans up
		/// 	all OpenAL objects, buffers and devices and closes down the
		/// 	audio device.
		////////////////////////////////////////////////////////////	
		~SoundManager();

				/** Gets a singleton reference.
		 */
		static SoundManager& getSingleton(void);
		/** Gets a singleton reference.
		 */
		static SoundManager* getSingletonPtr(void);

		////////////////////////////////////////////////////////////
		/// \brief Creates a listener object for the system
		///			Only needed when clearScene or similar is used which destroys listener object automatically 
		///			without the manager knowing. You can therefore use this function to recreate a listener
		///			object for the system.
		////////////////////////////////////////////////////////////	
		bool createListener();

		SoundListener* _createListener();

		/** Returns pointer to listener.
		 */
		SoundListener* getListener() { return mListener; }
			/** Initialises the audio device.
		@remarks
			Attempts to initialise the audio device for sound playback.
			Internally some logging is done to list features supported as
			well as creating a pool of sources from which sounds can be
			attached and played.
			@param deviceName
				Audio device string to open, will use default device if not found.
			@param maxSources
				maximum number of sources to allocate (optional)
			@param queueListSize
				Desired size of queue list (optional | Multi-threaded ONLY)
		 */
		bool init(const Ogre::String &deviceName = "", Ogre::uint32 maxSources = 100, Ogre::uint32 queueListSize = 100, Ogre::SceneManager* sMan = 0);
		/** Sets the global volume for all sounds
			@param vol 
				global attenuation for all sounds.
		 */
		//void setMasterVolume(Float vol);
		/** Sets the default SceneManager for creation of sound objects
		 */
		void setSceneManager(Ogre::SceneManager* sMan) { mSceneMgr = sMan; }
		/** Gets the default SceneManager for creation of sound objects
		 */
		Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
		/** Gets number of currently created sounds
		 */
		Ogre::uint32 getNumSounds() const { return static_cast<Ogre::Real>(mSoundMap.size()); }
		/** Gets the current global volume for all sounds
		 */
		//Float getMasterVolume();
		/** Creates a single sound object.
		@remarks
			Plugin specific version of createSound, uses createMovableObject() to instantiate
			a sound automatically registered with the supplied SceneManager, allows OGRE to automatically
			cleanup/manage this sound.
			Each sound must have a unique name within the manager.
			@param name 
				Unique name of sound
			@param file 
				Audio file path string
			@param stream 
				Flag indicating if the sound sound be streamed.
			@param loop 
				Flag indicating if the file should loop.
			@param preBuffer 
				Flag indicating if a source should be attached at creation.
			@param scnMgr
				Pointer to SceneManager this sound belongs - 0 defaults to first SceneManager defined.
			@param immediately
				Optional flag to indicate creation should occur immediately and not be passed to background thread
				for queueing. Can be used to overcome the random creation time which might not be acceptable (MULTI-THREADED ONLY)
		 */
		SoundHandle* createSound(const Ogre::String& name, const Ogre::String& file, bool stream = false, bool loop = false, bool preBuffer = false, Ogre::SceneManager* scnMgr = 0, bool immediate = false);
		/** Gets a named sound.
		@remarks
			Returns a named sound object if defined, NULL otherwise.
			@param name 
				Sound name.
		 */
		SoundHandle* getSound(const Ogre::String& name);

		bool addSound(const Ogre::String& name, SoundHandle* sound);
		/** Gets list of created sounds.
		@remarks
			Returns a vector of sound name strings.
		 */
		const Ogre::StringVector getSoundList() const;
		/** Returns whether named sound exists.
		@remarks
			Checks sound map for a named sound.
			@param name 
				Sound name.
		 */
		bool hasSound(const Ogre::String& name);
		/** Sets the pitch of all sounds.
		@remarks
			Sets the pitch modifier applied to all sounds.
			@param pitch
				new pitch for all sounds (positive value)
		 */
		void setGlobalPitch(Ogre::Real pitch);
		/** Gets the current global pitch.
		 */
		const Ogre::Real getGlobalPitch() const { return mGlobalPitch; }
		/** Stops all currently playing sounds.
		 */
		void stopAllSounds();
		/** Pauses all currently playing sounds.
		 */
		void pauseAllSounds();
		/** Mutes all sounds.
		 */
		void muteAllSounds();
		/** Un mutes all sounds.
		 */
		void unmuteAllSounds();
		/** Resumes all previously playing sounds.
		 */
		void resumeAllPausedSounds();
		/** Destroys all sounds within manager.
		 */
		void destroyAllSounds();
		/** Destroys a single sound.
		@remarks
			Destroys a single sound object.
			@param name 
				Sound name to destroy.
		 */
		void destroySound(const Ogre::String& name = "");
		/** Destroys a single sound.
		@remarks
			Destroys a single sound object.
			@param name 
				Sound name to destroy.
		 */
		void destroySound(SoundHandle* sound);

		/** Updates system.
		@remarks
			Iterates all sounds and updates them.
			@param fTime 
				Elapsed frametime.
		 */
		void update(Ogre::Real fTime = 0.f);
	private:
			
		/** Sound lists
		 */
		SoundMap mSoundMap;						// Map of all sounds
		ActiveList mActiveSounds;				// list of sounds currently active
		ActiveList mPausedSounds;				// list of sounds currently paused
		ActiveList mSoundsToReactivate;			// list of sounds that need re-activating when sources become available
		ActiveList mWaitingSounds;				// list of sounds that need playing when sources become available
	//	SourceList mSourcePool;					// List of available sources
	//	FeatureList mEFXSupportList;			// List of supported EFX effects by OpenAL ID
		SharedBufferList mSharedBuffers;		// List of shared static buffers

		/** Fading vars
		*/																  
		Ogre::Real mFadeTime;					// Time over which to fade
		Ogre::Real mFadeTimer;					// Timer for fade
		bool mFadeIn;							// Direction fade in/out
		bool mFadeVolume;						// Flag for fading

	//	ALCchar* mDeviceStrings;				// List of available devices strings
	//	Uint32 mNumSources;				// Number of sources available for sounds
	//	Uint32 mMaxSources;				// Maximum Number of sources to allocate

		Ogre::Real mGlobalPitch;						// Global pitch modifier

		//! sorts sound list by distance
		struct _sortNearToFar;
		//! sorts sound list by distance
		struct _sortFarToNear;

		Ogre::ObjectMemoryManager* mObjManager;
		SoundListener *mListener;				// Listener object
		Ogre::SceneManager* mSceneMgr;		// SceneManager reference for plugin registered sounds
		Ogre::String mResourceGroupName;		// Resource group name to search for all sounds

		friend class SoundFactory;
	};

} // namespace XE



#endif // XE_SOUNDMANAGER_HPP