#include <XEAudio/SoundManager.hpp>

#include <XEAudio/SoundListener.hpp>
#include <XEAudio/SoundHandle.hpp>


#include <XEDAL/PhysFS/PhysFsStream.hpp>

#include <XESystem/Logging.hpp>

#include <fmod/fmod_errors.h>

#define INITIAL_VECTOR_SIZE   100
#define INCREASE_VECTOR_SIZE  20

#define DOPPLER_SCALE         1.0
#define DISTANCE_FACTOR       1.0
#define ROLLOFF_SCALE         0.5

namespace XE {

	SoundManager::SoundManager() :
		mListener(0)
		, mGlobalPitch(1.f)
		, mFadeVolume(false)
		, mFadeIn(false)
		, mFadeTime(0.f)
		, mFadeTimer(0.f)
	{
		FMOD_RESULT result;

		// Create the main system object.
		result = FMOD::System_Create(&_system);
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::Initialize";


		result = _system->init(MAX_SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::Initialize";


		_system->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);

		result = _system->setFileSystem(&fmodFileOpenCallback, &fmodFileCloseCallback, &fmodFileReadCallback, &fmodFileSeekCallback, NULL, NULL, 2048);
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::Initialize";
	}

	/*/////////////////////////////////////////////////////////////////*/
	SoundManager::~SoundManager()
	{
		FMOD_RESULT result = _system->close();
		
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::~SoundManager";
		
		result = _system->release();
		
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::~SoundManager";
	}

	void SoundManager::playSound(SoundHandle& sound)
	{
		int          channelsplaying = 0;

		_system->getChannelsPlaying(&channelsplaying, NULL);

		if (sound._channel)
		{
			bool         playing = 0;
			FMOD::Sound *currentsound = 0;

			FMOD_RESULT result = sound._channel->isPlaying(&playing);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			}

			if (playing)
				return;
		}

		/*
		Play the sound.
		*/
		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool         playing = 0;
		bool         paused = 0;

		if (sound._channel)
		{
			FMOD::Sound *currentsound = 0;

			FMOD_RESULT result = sound._channel->isPlaying(&playing);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			}

			result = sound._channel->getPaused(&paused);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			}

			result = sound._channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			}

			//sound._channel->getCurrentSound(&currentsound);
			//if (currentsound)
			//{
			//	result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
			//	if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			//	{
			//		LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			//	}
			//	else
			//	{
			if (!playing)
			{
				FMOD_RESULT result = _system->playSound(sound._soundPtr, 0, false, &sound._channel); //play sound
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
				{
					LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
				}
			}


		}
		else
		{
			FMOD_RESULT result = _system->playSound(sound._soundPtr, 0, false, &sound._channel); //sets the channel first time
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				LOG(ERROR) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
			}
		}

		_system->getChannelsPlaying(&channelsplaying, NULL);

	}

	/// fileName is actually a pointer to a SoundInstance, passed in from CreateSound().
	FMOD_RESULT SoundManager::fmodFileOpenCallback(const char *fileName, /*int unicode,*/ unsigned int *filesize, void **handle, void *userdata)
	{
		SoundHandle* soundInstance = (SoundHandle *)fileName;

		if (soundInstance->_fileStream.open(soundInstance->getFileName().c_str()))
		{
			*filesize = soundInstance->_fileStream.getSize();
			*handle = soundInstance;

			return FMOD_OK;
		}
		else
			return FMOD_ERR_FILE_NOTFOUND;

	}


	FMOD_RESULT SoundManager::fmodFileCloseCallback(void *handle, void *userdata)
	{

		return FMOD_OK;
	}


	FMOD_RESULT SoundManager::fmodFileReadCallback(void *handle, void *buffer, unsigned int sizeBytes, unsigned int *bytesRead, void *userData)
	{
		SoundHandle *soundInstance;

		soundInstance = (SoundHandle *)handle;
		*bytesRead = (unsigned int)soundInstance->_fileStream.read(buffer, (size_t)sizeBytes);
		if (*bytesRead == 0)
			return FMOD_ERR_FILE_EOF;

		return FMOD_OK;
	}


	FMOD_RESULT SoundManager::fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata)
	{
		SoundHandle *soundInstance;

		soundInstance = (SoundHandle *)handle;
		soundInstance->_fileStream.seek((size_t)pos);
		return FMOD_OK;
	}



	void SoundManager::update(float fTime)
	{
		FMOD_VECTOR    listenerPosition;
		FMOD_VECTOR    listenerForward;
		FMOD_VECTOR    listenerUp;
		FMOD_VECTOR    listenerVelocity;

		// update 'ears'
		_system->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, &listenerForward, &listenerUp);
		_system->update();
	}

	SoundHandle* SoundManager::createSound(const XE::Uint16 id, const std::string& file, SOUND_TYPE soundType)
	{
		auto it = _soundMap.find(id);
		if (it != _soundMap.end())
			return _soundMap[id].get();
		else
		{
			std::unique_ptr<SoundHandle> sound = std::unique_ptr<SoundHandle>(new SoundHandle(file));
			sound->create(*this, soundType);
			//todo set properties!

			return (_soundMap[id] = std::move(sound)).get();
		}
	}

	SoundHandle* SoundManager::getSound(const XE::Uint16 id)
	{
		auto it = _soundMap.find(id);

		if (it != _soundMap.end())
			return it->second.get();			//element found;

		return nullptr;
	}

	/*/////////////////////////////////////////////////////////////////*/
	void SoundManager::destroySound(const XE::Uint16 id)
	{
		SoundHandle* sound = 0;
		if (!(sound = getSound(id))) return;
		//todo	_destroySoundImpl(sound);
	}

	/*/////////////////////////////////////////////////////////////////*/
	void SoundManager::destroySound(SoundHandle* sound)
	{
		if (!sound) return;

		//todo	_destroySoundImpl(sound);
	}

} // namespace XE