#include <XEngine/OgreLogListener.hpp>

#include <XESystem/Logging.hpp>

namespace XE
{
	void OgreLogListener::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage)
	{
		LOG(INFO) << "> OgreLog:" << message;

	}
	
}
