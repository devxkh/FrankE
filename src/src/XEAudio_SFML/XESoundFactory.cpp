#include <XEAudio/XESoundFactory.hpp>
#include <XEAudio/XESoundHandle.hpp>
#include <XEAudio/XESoundManager.hpp>
#include <XEAudio/XESoundListener.hpp>

namespace XE {

Ogre::String SoundFactory::FACTORY_TYPE_NAME = "XESound";

//-----------------------------------------------------------------------
	const Ogre::String& SoundFactory::getType(void) const
{
	return FACTORY_TYPE_NAME;
}
//-----------------------------------------------------------------------

Ogre::MovableObject* SoundFactory::createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params)
{
	Ogre::String fileName;
	bool loop = false;
	bool stream = false;
	bool preBuffer = false;
	bool immediate = false;
//	XE::SceneManager* scnMgr = 0;

	if (params != 0)
	{
		Ogre::NameValuePairList::const_iterator fileNameIterator = params->find("fileName");
		if (fileNameIterator != params->end())
		{
			// Get filename
			fileName = fileNameIterator->second;
		}

		Ogre::NameValuePairList::const_iterator loopIterator = params->find("loop");
		if (loopIterator != params->end())
		{
			// Get loop setting
			loop = Ogre::StringUtil::match(loopIterator->second, "true", false);
		}

		Ogre::NameValuePairList::const_iterator streamIterator = params->find("stream");
		if (streamIterator != params->end())
		{
			// Get stream flag
			stream = Ogre::StringUtil::match(streamIterator->second, "true", false);
		}

		Ogre::NameValuePairList::const_iterator preBufferIterator = params->find("preBuffer");
		if (preBufferIterator != params->end())
		{
			// Get prebuffer flag
			preBuffer = Ogre::StringUtil::match(preBufferIterator->second, "true", false);
		}

		Ogre::NameValuePairList::const_iterator immediateIterator = params->find("immediate");
		if (immediateIterator != params->end())
		{
			// Get prebuffer flag
			immediate = Ogre::StringUtil::match(immediateIterator->second, "true", false);
		}

		//NameValuePairList::const_iterator sManIterator = params->find("sceneManagerName");
		//if (sManIterator != params->end())
		//{
		//	// Get SceneManager name
		//	scnMgr = XE::Root::getSingletonPtr()->getSceneManager(sManIterator->second);
		//}

		// when no caption is set
		/*if ( !scnMgr || name == StringUtil::BLANK || fileName == StringUtil::BLANK )
		{
			XE_EXCEPT(Exception::ERR_INVALIDPARAMS,
				"'name & fileName & sceneManagerName' parameters required when constructing an OgreOggISound.",
				"OgreOggSoundFactory::createInstance");
		}*/


	//##	return  OGRE_NEW_T(SoundHandle, Ogre::MEMCATEGORY_GENERAL)(name, fileName, "", stream, loop, preBuffer, immediate);
	//	return SoundManager::getSingletonPtr()->_createSoundImpl(*scnMgr, name, fileName, stream, loop, preBuffer, immediate);
	}
	//##else
	//##	return OGRE_NEW_T(SoundListener, Ogre::MEMCATEGORY_GENERAL)();

	return 0;
}

//-----------------------------------------------------------------------
void SoundFactory::destroyInstance(Ogre::MovableObject* obj)
{
	//if ( dynamic_cast<SoundListener*>(obj) )
	//	// destroy the listener
	//	SoundManager::getSingletonPtr()->_destroyListener();
	//else
	//	// destroy the sound
	//	SoundManager::getSingletonPtr()->_releaseSoundImpl(static_cast<Sound*>(obj));
}
//-----------------------------------------------------------------------



}	//namespace XE