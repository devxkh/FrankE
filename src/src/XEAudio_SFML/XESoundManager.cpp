#include <XEAudio/XESoundManager.hpp>

#include <Ogre/OgreMain/include/OgreLogManager.h>
#include <Ogre/OgreMain/include/OgreException.h>
#include <Ogre/OgreMain/include/OgreSceneManager.h>
#include <XEAudio/XESoundFactory.hpp>
#include <XEAudio/XESoundListener.hpp>
#include <XEAudio/XESoundHandle.hpp>
//#include <Ogre/OgreMain/include/OgreSceneManager.h>

template<> XE::SoundManager* Ogre::Singleton<XE::SoundManager>::msSingleton = 0;

namespace XE {

	using namespace Ogre;

	SoundManager::SoundManager() :
	//	mNumSources(0)
		//,mOrigVolume(1.f)
		//,mDevice(0)
		//,mContext(0),
		mListener(0)
		/*,mRecorder(0)
		,mDeviceStrings(0)*/
	//	,mMaxSources(100)
		,mResourceGroupName("")
		,mGlobalPitch(1.f)
		//,mSoundsToDestroy(0)
		,mFadeVolume(false)
		,mFadeIn(false)
		,mFadeTime(0.f)
		,mFadeTimer(0.f)
		, mObjManager()
		{
		}
	/*/////////////////////////////////////////////////////////////////*/
	SoundManager::~SoundManager()
	{
		/*if ( mSoundsToDestroy )
		{
			delete mSoundsToDestroy;
			mSoundsToDestroy=0;
		}*/

	//	_releaseAll();

	//	if ( mRecorder ) { OGRE_DELETE_T(mRecorder, OgreOggSoundRecord, Ogre::MEMCATEGORY_GENERAL); mRecorder=0; }

	/*	alcMakeContextCurrent(0);
		alcDestroyContext(mContext);*/
	//	mContext=0;
		//alcCloseDevice(mDevice);
	//	mDevice=0;

		if ( mListener )
		{
		//	XE::SceneManager* s = mListener->getSceneManager();
		//	s->destroyAllMovableObjectsByType("Sound");
		}
	}

	SoundManager* SoundManager::getSingletonPtr(void)
	{
		return msSingleton;
	}

	/*/////////////////////////////////////////////////////////////////*/
	SoundManager& SoundManager::getSingleton(void)
	{
		if ( !msSingleton )
			OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND, "'OgreOggSound[_d]' plugin NOT loaded! - use loadPlugin()", "OgreOggSoundManager::getSingleton()");  
		return ( *msSingleton );
	}

	bool SoundManager::init(const String &deviceName, 
						uint32 maxSources, 
						uint32 queueListSize, 
						SceneManager* scnMgr)
	{
		LogManager::getSingleton().logMessage("*** --- Initialising SoundManager --- ***", LML_NORMAL);

		if ( !scnMgr )
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "No SceneManager's created - a valid SceneManager is required to create sounds", "OgreOggSoundManager::init()");
			return false;
		}

		mSceneMgr = scnMgr;

		if ( !createListener() ) 
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Unable to create a listener object", "OgreOggSoundManager::init()");
			return false;
		}

		LogManager::getSingleton().logMessage("*** ---  OgreOggSound Initialised --- ***", LML_NORMAL);
	
		return true;
	}

	/*/////////////////////////////////////////////////////////////////*/
	bool SoundManager::createListener() 
	{
		if ( mListener ) return true;

		// Create a listener
		return ( (mListener = dynamic_cast<SoundListener*>(mSceneMgr->createMovableObject("SoundListener", mObjManager, 0)))!=0);
	}

	/*/////////////////////////////////////////////////////////////////*/
	const StringVector SoundManager::getSoundList() const
	{
		StringVector list;
		for ( SoundMap::const_iterator iter=mSoundMap.begin(); iter!=mSoundMap.end(); ++iter )
			list.push_back((*iter).first);
		return list;
	}
	
	//Soll Listerner machen!!!
	//void SoundManager::setMasterVolume(Real vol)
	//Real SoundManager::getMasterVolume()
	
	bool  SoundManager::addSound(const String& name,SoundHandle* sound)
	{
		mSoundMap[name]=sound;

		return true;
	}
	
	void SoundManager::update(Real fTime)
	{
		// Fade volume
		if ( mFadeVolume )
		{
			mFadeTimer+=fTime;

			if ( mFadeTimer > mFadeTime )
			{
				mFadeVolume = false;
				mListener->setGlobalVolume(mFadeIn ? 1.f : 0.f);
			}
			else
			{
				Real vol = 1.f;
				if ( mFadeIn )
					vol = (mFadeTimer/mFadeTime);
				else
					vol = 1.f - (mFadeTimer/mFadeTime);

				mListener->setGlobalVolume(vol);
			}
		}

		// Destroy sounds
		//if ( mSoundsToDestroy )
		//{
		//	if (!mSoundsToDestroy->empty() )
		//	{
		//		SoundHandle* s=0;
		//		//if ( mSoundsToDestroy->pop(s) )
		//		//todo	_destroySoundImpl(s);
		//	}
		//}
	}

	SoundHandle* SoundManager::createSound(const String& name, 
													const String& file, 
													bool stream, 
													bool loop, 
													bool preBuffer, 
													XE::SceneManager* scnMgr,
													bool immediate)
	{
		/*NameValuePairList params;
		

		params["fileName"]	= file;
		params["stream"]	= stream	? "true" : "false";
		params["loop"]		= loop		? "true" : "false";
		params["preBuffer"]	= preBuffer ? "true" : "false";
		params["immediate"]	= immediate ? "true" : "false";*/

		// Get first SceneManager if defined
		if ( !scnMgr ) 
		{
			if ( mSceneMgr ) 
				scnMgr = mSceneMgr;
			else
			{
				OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "No SceneManager defined!", "OgreOggSoundManager::createSound()");
				return 0;
			}
		}

		// Catch exception when plugin hasn't been registered
		try
		{
			//params["sceneManagerName"]=scnMgr->getName();
			//todo: Sound muss von movableobject abgeleitet werden
			//sound = static_cast<Sound*>(scnMgr->createMovableObject( name, SoundFactory::FACTORY_TYPE_NAME, &params ));
			//SoundHandle soundHandle(name,, &params);
			return  OGRE_NEW_T(SoundHandle, Ogre::MEMCATEGORY_GENERAL)(name, file, "", stream, loop, preBuffer, immediate);
		}
		catch (Exception& e)
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, e.getFullDescription(), "OgreOggSoundManager::createSound()");
		}
		// create Movable Sound
	
	}

	SoundHandle* SoundManager::getSound(const String& name)
	{
		SoundMap::iterator i = mSoundMap.find(name);
		if(i == mSoundMap.end()) return 0;
		return i->second;
	}

	bool SoundManager::hasSound(const String& name)
	{
		SoundMap::iterator i = mSoundMap.find(name);
		if(i == mSoundMap.end())
			return false;
		return true;
	}

	/*/////////////////////////////////////////////////////////////////*/
	void SoundManager::destroySound(const String& sName)
	{
		SoundHandle* sound=0;
		if ( !(sound = getSound(sName)) ) return;
	//todo	_destroySoundImpl(sound);
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundManager::destroySound(SoundHandle* sound)
	{
		if ( !sound ) return;

	//todo	_destroySoundImpl(sound);
	}

	/*/////////////////////////////////////////////////////////////////*/
	struct SoundManager::_sortFarToNear
	{
		bool operator()(SoundHandle*& sound1, SoundHandle*& sound2)
		{
			float	d1=0.f,
					d2=0.f;
			Vector3	lPos = Vector3(SoundManager::getSingleton().getListener()->getPosition().x,
									SoundManager::getSingleton().getListener()->getPosition().y,
									SoundManager::getSingleton().getListener()->getPosition().z);

		//	if ( !sound1->isMono() ) return false;
			Vector3	posS1 = Vector3(sound1->getPosition().x,
									sound1->getPosition().y,
									sound1->getPosition().z);
			Vector3	posS2 = Vector3(sound2->getPosition().x,
									sound2->getPosition().y,
									sound2->getPosition().z);


			if ( sound1->isRelativeToListener() )
				d1 = posS1.length();
			else
				d1 = posS1.distance(lPos);

			if ( sound2->isRelativeToListener() )
				d2 = posS2.length();
			else
				d2 = posS2.distance(lPos);

			// Check sort order
		//	if ( !sound1->isMono() && sound2->isMono() ) return true;
			if ( d1>d2 )	return true;
			if ( d1<d2 )	return false;

			// Equal - don't sort
			return false;
		}
	};

} // namespace XE