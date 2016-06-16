#ifndef XE_OGRELOGLISTENER_HPP
#define XE_OGRELOGLISTENER_HPP


#include <Ogre/OgreMain/include/OgreLog.h>


namespace XE
{
	class OgreLogListener : public Ogre::LogListener
	{
		void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);
	};
}


#endif