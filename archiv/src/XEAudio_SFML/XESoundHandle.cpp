#include <XEAudio/XESoundHandle.hpp>

#include <ogre/OgreMain/include/OgreResourceGroupManager.h>
#include <Ogre/OgreMain/include/OgreDataStream.h>
#include <Ogre/OgreMain/include/OgreLogManager.h>

#include <XEAudio/XESoundManager.hpp>
#include <Ogre/OgreMain/include/OgreNode.h>

#include <XEAudio/XESoundFactory.hpp>

#include <sfml/Audio/SoundBuffer.hpp>
#include <sfml/Audio/Sound.hpp>

//test
#include <XEAudio/XEResourceStream.hpp>

#include <iostream>

namespace XE {

	using namespace Ogre;

	//SoundHandle::SoundHandle(){}
	SoundHandle::~SoundHandle(){}
	
	SoundHandle::SoundHandle(const Ogre::String& name, 
								//XE::SceneManager* sceneMgr,
								const Ogre::String& file,
								const Ogre::String& resourceGroupName,
										bool stream, 
										bool loop, 
										bool preBuffer,
										bool immediate) :
										mLocalTransformDirty(true)
	{
		Ogre::ResourceGroupManager* groupManager = 0;
		String group;
		XE::DataStreamPtr soundData;
		
		try
		{
			if (groupManager = XE::ResourceGroupManager::getSingletonPtr())
			{
				if (!resourceGroupName.empty())
				{
					soundData = groupManager->openResource(file, resourceGroupName);
				}
				else
				{
					group = groupManager->findGroupContainingResource(file);
					soundData = groupManager->openResource(file, group);
				}
			}
			else
			{
				OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, "Unable to find Ogre::ResourceGroupManager", "OgreOggSoundManager::createSound()");
				return;
			}
		}
		catch (Exception& e)
		{
			OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, e.getFullDescription(), "OgreOggSoundManager::_createSoundImpl()");
			return;
		}

		/*if		( file.find(".ogg")!=file.npos || file.find(".OGG")!=file.npos )
		{*/
		// MUST be unique
		if (SoundManager::getSingletonPtr()->hasSound(name))
		{
			String msg = "*** OgreOggSoundManager::createSound() - Sound with name: " + name + " already exists!";
			LogManager::getSingleton().logMessage(msg);
			return;
		}

		//if(stream)
		// Sound(
		// //sound = OGRE_NEW_T(OgreOggStreamSound, Ogre::MEMCATEGORY_GENERAL)(name, scnMgr);
		//else	sound = OGRE_NEW_T(OgreOggStaticSound, Ogre::MEMCATEGORY_GENERAL)(name, scnMgr);

		//	sound	= OGRE_NEW_T(Sound, MEMCATEGORY_GENERAL);

		ResourceStream tmpResStream(&soundData);

		//	SoundBuffer buffer;
		if (!buffer.loadFromStream(tmpResStream))
		{
			OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, "Stream not Found", "OgreOggSoundManager::_createSoundImpl()");
			return;
		}


		//   buffer.loadFromFile("F:/Projekte/Src Game/_Engine/XEngine/resources/XETAudio/electricspark.ogg");

		//   // Display sound informations
		std::cout << "electricspark.ogg :" << std::endl;
		std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
		std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
		std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

		/*setLoop(loop);
		setBuffer(buffer);
		*/
		setBuffer(buffer);
		// sound.play();
		//	 play();
		// Add to list
		SoundManager::getSingletonPtr()->addSound(name, this);//mSoundMap[name]=sound;

		//ALuint buffer=AL_NONE;

		//if ( !sound->mStream )
		//	// Is there a shared buffer?
		//	buffer = _getSharedBuffer(file);

		//if (buffer==AL_NONE)
		//{	// Load audio file
		//	
		//	sound->_openImpl(stream);
		//}
		//else
		//	// Use shared buffer if available
		//	sound->_openImpl(file, buffer);

		//// If requested to preBuffer - grab free source and init
		//if (prebuffer)
		//{
		//	if ( !_requestSoundSource(sound) )
		//	{
		//		Ogre::String msg="*** OgreOggSoundManager::createSound() - Failed to preBuffer sound: "+sound->getName();
		//		Ogre::LogManager::getSingleton().logMessage(msg);
		//	}
		//}

		//		}
		//		else if	( file.find(".wav")!=file.npos || file.find(".WAV")!=file.npos )
		//		{
		//			// MUST be unique
		//			if ( hasSound(name) )
		//			{
		//				Ogre::String msg="*** OgreOggSoundManager::createSound() - Sound with name: "+name+" already exists!";
		//				Ogre::LogManager::getSingleton().logMessage(msg);
		//				return 0;
		//			}
		//
		//			if(stream)
		//				sound = OGRE_NEW_T(OgreOggStreamWavSound, Ogre::MEMCATEGORY_GENERAL)(name, scnMgr);
		//			else
		//				sound = OGRE_NEW_T(OgreOggStaticWavSound, Ogre::MEMCATEGORY_GENERAL)(name, scnMgr);
		//
		//			// Set loop flag
		//			sound->loop(loop);
		//
		//			// Add to list
		//			mSoundMap[name]=sound;
		//
		//#if OGGSOUND_THREADED
		//			SoundAction action;
		//			cSound* c		= OGRE_NEW_T(cSound, Ogre::MEMCATEGORY_GENERAL);
		//			c->mFileName	= file;
		//			c->mPrebuffer	= preBuffer; 
		//			c->mStream		= soundData;
		//			action.mAction	= LQ_LOAD;
		//			action.mParams	= c;
		//			action.mImmediately = immediate;
		//			action.mSound	= sound->getName();
		//			_requestSoundAction(action);
		//#else
		//			// Load audio file
		//			_loadSoundImpl(sound, file, soundData, preBuffer);
		//#endif
		//			return sound;
		/*}
		else
		{
		Ogre::String msg="*** OgreOggSoundManager::createSound() - Sound does not have (.ogg | .wav) extension: "+name;
		Ogre::LogManager::getSingleton().logMessage(msg);
		return 0;
		}*/

	}
				/*/////////////////////////////////////////////////////////////////*/
	void SoundHandle::update(float fTime)
	{
		if (mLocalTransformDirty)
		{
			if (!mDisable3D && mParentNode)
			{
				setPosition(sf::Vector3f(mParentNode->_getDerivedPosition().x, mParentNode->_getDerivedPosition().y, mParentNode->_getDerivedPosition().z));
				mDirection = -sf::Vector3f(mParentNode->_getDerivedOrientation().zAxis().x, mParentNode->_getDerivedOrientation().zAxis().y,mParentNode->_getDerivedOrientation().zAxis().z);

				mLocalTransformDirty = false;
			}
		}	

		//_updateFade(fTime);
	}
	/*/////////////////////////////////////////////////////////////////*/
	const String& SoundHandle::getMovableType(void) const
	{
		return SoundFactory::FACTORY_TYPE_NAME;
	}
	/*/////////////////////////////////////////////////////////////////*/
	const XE::AxisAlignedBox& SoundHandle::getBoundingBox(void) const
	{
		static XE::AxisAlignedBox aab;
		return aab;
	}
	/*/////////////////////////////////////////////////////////////////*/
	float SoundHandle::getBoundingRadius(void) const
	{
		return 0;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundHandle::_updateRenderQueue(XE::RenderQueue *queue)
	{
		return;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundHandle::_notifyAttached(XE::Node* node, bool isTagPoint)
	{
		// Call base class notify
		//todo !! move node manuall ! XE::MovableObject::_notifyAttached(node); //todo ?? , isTagPoint);

		// Immediately set position/orientation when attached
		if (mParentNode)
		{
			setPosition(sf::Vector3f(mParentNode->_getDerivedPosition().x, mParentNode->_getDerivedPosition().y, mParentNode->_getDerivedPosition().z));
			mDirection = -sf::Vector3f(mParentNode->_getDerivedOrientation().zAxis().x, mParentNode->_getDerivedOrientation().zAxis().y, mParentNode->_getDerivedOrientation().zAxis().z);
		}

		return;
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundHandle::_notifyMoved(void) 
	{ 
		// Call base class notify
		//todo ?? XE::MovableObject::_notifyMoved();

		mLocalTransformDirty=true; 
	}
	/*/////////////////////////////////////////////////////////////////*/
	void SoundHandle::visitRenderables(XE::Renderable::Visitor* visitor, bool debugRenderables)
	{
		return;
	}

} //namespace XE