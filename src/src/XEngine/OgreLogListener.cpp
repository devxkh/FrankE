#include <XEngine/OgreLogListener.hpp>

#include <ThirdParty/plog/Log.h>

namespace XE
{
	void OgreLogListener::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage)
	{
		LOG(plog::info) << "> OgreLog:" << message;

	}
	
}
