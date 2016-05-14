#ifndef XE_SOUNDMANAGER_HPP
#define XE_SOUNDMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <XESystem/SystemConfig.hpp>

#include <fmod/fmod.hpp>
#include <fmod/fmod_common.h>

#include <map>
#include <list>
#include <deque>

#include <memory>


#define MAX_SOUND_CHANNELS       200

#define INVALID_SOUND_INDEX      0
#define INVALID_SOUND_CHANNEL    -1

namespace XE {

	enum SOUND_TYPE;
	//forward declaration
	class SoundListener;
	class SoundHandle;

	typedef std::map<XE::Uint16, std::unique_ptr<SoundHandle>> SoundMap;
	typedef std::list<SoundHandle*> ActiveList;

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
		std::string		mSound;
		SOUND_ACTION	mAction;
		bool			mImmediately;
		void*			mParams;
	};

	//! Holds information about a create sound request.
	struct cSound
	{
		bool mPrebuffer;
		std::string mFileName;
		XE::Uint32 mBuffer;
	//	Ogre::DataStreamPtr mStream;
	};

	//! Holds information about a EFX effect.
	struct efxProperty
	{
		std::string mEffectName;
		std::string mFilterName;
		float mAirAbsorption;
		float mRolloff;
		float mConeHF;
		XE::Uint32 mSlotID;
	};

	//! Holds information about a static shared audio buffer.
	struct sharedAudioBuffer
	{
		XE::Uint32 mAudioBuffer;
		XE::Uint32 mRefCount;
	};

	typedef std::map<std::string, sharedAudioBuffer*> SharedBufferList;

	////////////////////////////////////////////////////////////
	/// \brief The audio listener is the point in the scene
	///        from where all the sounds are heard
	///
	////////////////////////////////////////////////////////////
	class SoundManager 
	{
	public :
		 
		SoundManager();

		~SoundManager();

		/** Sets the global volume for all sounds
			@param vol 
				global attenuation for all sounds.
		 */
		//void setMasterVolume(Float vol);

		/** Gets the current global volume for all sounds
		 */
		//Float getMasterVolume();

		void playSound(SoundHandle& sound);

		SoundHandle* createSound(const XE::Uint16 id, const std::string& file, SOUND_TYPE soundType);

		SoundHandle* getSound(const XE::Uint16 id);

		void destroySound(const XE::Uint16 id);
		
		void destroySound(SoundHandle* sound);

		void update(float fTime = 0.f);


		FMOD::System *       _system;

	private:


		/** Sound lists
		 */
		SoundMap _soundMap;						// Map of all sounds
		ActiveList mActiveSounds;				// list of sounds currently active
		ActiveList mPausedSounds;				// list of sounds currently paused
		ActiveList mSoundsToReactivate;			// list of sounds that need re-activating when sources become available
		ActiveList mWaitingSounds;				// list of sounds that need playing when sources become available
	//	SourceList mSourcePool;					// List of available sources
	//	FeatureList mEFXSupportList;			// List of supported EFX effects by OpenAL ID
		SharedBufferList mSharedBuffers;		// List of shared static buffers

		/** Fading vars
		*/																  
		float mFadeTime;					// Time over which to fade
		float mFadeTimer;					// Timer for fade
		bool mFadeIn;							// Direction fade in/out
		bool mFadeVolume;						// Flag for fading

	//	ALCchar* mDeviceStrings;				// List of available devices strings
	//	Uint32 mNumSources;				// Number of sources available for sounds
	//	Uint32 mMaxSources;				// Maximum Number of sources to allocate

		float mGlobalPitch;						// Global pitch modifier

		//! sorts sound list by distance
		struct _sortNearToFar;
		//! sorts sound list by distance
		struct _sortFarToNear;

		SoundListener *mListener;				// Listener object

		static FMOD_RESULT F_CALLBACK  fmodFileOpenCallback(const char *fileName/*, int unicode*/, unsigned int *filesize, void **handle, void *userdata);
		static FMOD_RESULT F_CALLBACK  fmodFileCloseCallback(void *handle, void *userdata);
		static FMOD_RESULT F_CALLBACK  fmodFileReadCallback(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
		static FMOD_RESULT F_CALLBACK  fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata);
	};

} // namespace XE



#endif // XE_SOUNDMANAGER_HPP