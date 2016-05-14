#ifndef EICOMMANDS_HPP
#define EICOMMANDS_HPP

#include <XEngine.hpp>
#include <Ogre/OgreMain/include/OgreStringVector.h>

namespace XE
{
	class XEngine;
	class OgreConsole;
}

namespace EI {
	class Editor;

	class EditorCommand
	{
	public:
		EditorCommand(XE::XEngine* engine, XE::OgreConsole* console);

		int updateObject(Ogre::StringVector& vec);
		void createObject(Ogre::StringVector& vec);
		int deleteObject(Ogre::StringVector& vec);

	private:		
		XE::XEngine* m_engine;
		XE::OgreConsole* m_console;
	};
}

#endif // EICOMMANDS_HPP