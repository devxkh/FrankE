#include <XEAudio/SoundHandle.hpp>

#include <XEAudio/SoundManager.hpp>
#include <XEngine/Components/Body.hpp>

#include <Ogre/OgreMain/include/OgreAxisAlignedBox.h>

#include <XESystem/Logging.hpp>

#include <fmod/fmod.hpp>
#include <fmod/fmod_common.h>
#include <fmod/fmod_errors.h>

namespace XE {

	SoundHandle::SoundHandle(const std::string& fileName)
		: _fileName(fileName)
		, _soundPtr(0)
		, _channel (0)
		, _fileStream()
	{
		
	}

	SoundHandle::~SoundHandle(){

		FMOD_RESULT result = _soundPtr->release();  /* Release the parent, not the sound that was retrieved with getSubSound. */
		if (result != FMOD_OK)
			LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";
	}
	
	void SoundHandle::create(SoundManager& soundMgr, SOUND_TYPE soundType)
	{
		FMOD_CREATESOUNDEXINFO exinfo;
		memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
		exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
		
		FMOD_RESULT result;

		switch (soundType)
		{
		case SOUND_TYPE_3D_SOUND:
			result = soundMgr._system->createSound((const char *)this, FMOD_3D, 0, &_soundPtr);
			break;

		case SOUND_TYPE_3D_SOUND_LOOPED:
			result = soundMgr._system->createSound((const char *)this, FMOD_LOOP_NORMAL | FMOD_3D | FMOD_DEFAULT /*FMOD_HARDWARE*/, 0, &_soundPtr);
			break;
		
		case SOUND_TYPE_2D_SOUND_LOOPED:
			result = soundMgr._system->createStream((const char *)this, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_DEFAULT /*FMOD_HARDWARE*/, 0, &_soundPtr);
			break;

		case SOUND_TYPE_2D_SOUND:
			result = soundMgr._system->createStream((const char *)this, FMOD_DEFAULT, 0, &_soundPtr);
			break;
		
		}

		//FMOD_RESULT result = soundMgr._system->createStream((const char*)this, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_DEFAULT, &exinfo, &_soundPtr);

		//FMOD_RESULT result = soundMgr._system->createStream("F:/Projekte/coop/XGame/data/assets/Explosion2.ogg", FMOD_OPENUSER, &exinfo, &_soundPtr);

		//if (result != FMOD_OK)
		//	LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";


	//	if (_fileStream.open("Explosion2.ogg"))
	//	{
	//		//	// Make sure that the stream's reading position is at the beginning
	//		_fileStream.seek(0);

	//		exinfo.length = _fileStream.getSize();
	//		std::vector<char> buffer(_fileStream.getSize());
	//		if (_fileStream.read(buffer.data(), _fileStream.getSize()))
	//		{
	//			//	state.LoadBuffer(&buffer[0], wonderfullStream.getSize(), filename.c_str());
	//			/*
	//			This example uses an FSB file, which is a preferred pack format for fmod containing multiple sounds.
	//			This could just as easily be exchanged with a wav/mp3/ogg file for example, but in this case you wouldnt need to call getSubSound.
	//			Because getNumSubSounds is called here the example would work with both types of sound file (packed vs single).
	//			*/
	//			//	FMOD_RESULT result = _system->createStream("F:/Projekte/coop/XGame/data/assets/Explosion2.ogg", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound._soundPtr);
	//			//	FMOD_RESULT result = _system->createStream("Explosion2.ogg", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound._soundPtr);
	//			FMOD_RESULT result = soundMgr._system->createStream(&buffer[0], FMOD_OPENMEMORY , &exinfo, &_soundPtr);

	//			if (result != FMOD_OK)
	//				LOG(FATAL) << "FMOD error! (" << result << "): " << FMOD_ErrorString(result) << ",SoundManager::PlayStream";

	//		}
	//	}
	}
		////   // Display sound informations
		//std::cout << "electricspark.ogg :" << std::endl;
		//std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
		//std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
		//std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

		///*setLoop(loop);
		//setBuffer(buffer);
		//*/
		//setBuffer(buffer);
		//// sound.play();
		////	 play();
		//// Add to list
		//SoundManager::getSingletonPtr()->addSound(name, this);//mSoundMap[name]=sound;

	std::string& SoundHandle::getFileName() { 
		return _fileName; }

	const Ogre::Vector3& SoundHandle::getDirection() { 
		return mDirection; 
	}

	void SoundHandle::update()
	{
		if (mLocalTransformDirty)
		{
			if (!mDisable3D && _parentBody)
			{
			//	setPosition(sf::Vector3f(_parentBody->_getDerivedPosition().x, _parentBody->_getDerivedPosition().y, _parentBody->_getDerivedPosition().z));
			//	mDirection = -sf::Vector3f(_parentBody->_getDerivedOrientation().zAxis().x, _parentBody->_getDerivedOrientation().zAxis().y, _parentBody->_getDerivedOrientation().zAxis().z);

				mLocalTransformDirty = false;
			}
		}	

		//_updateFade(fTime);
	}

	/*/////////////////////////////////////////////////////////////////*/
	const Ogre::AxisAlignedBox& SoundHandle::getBoundingBox(void) const
	{
		static Ogre::AxisAlignedBox aab;
		return aab;
	}

	/*/////////////////////////////////////////////////////////////////*/
	float SoundHandle::getBoundingRadius(void) const
	{
		return 0;
	}

} //namespace XE