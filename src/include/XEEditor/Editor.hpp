#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <XEngine.hpp>

#include <XEEditor/Event/Event.h>

namespace EI {

	class EditorCommand;

	enum ObjType
	{
		Physic = 0,
		GameEntity = 1,
	};
	
	enum Status
	{
		Unknown = 0,
		OK = 1,
		Error = 2,
	};

	class Editor
	{
	public:
		Editor();

		inline XE::XEngine* getEngine() { return m_engine; }

		void* InitState(const char* stateName, int width, int height);
		unsigned char* consoleCmd(const char* command, unsigned char* data, int len);
		bool moveToState(const char* stateName);
		void renderTargetSize(const char* rtName, Ogre::Real x, Ogre::Real y);
	//	void test(sf::String str, std::function<void()> fkttest);
		int pushEvent(const sfEvent& event);

	private :
	//	std::unordered_map<std::string, std::function<void(std::string)>> command_map;
		XE::XEngine* m_engine;
		//todo ####################	XE::OgreConsole* m_console;
		EditorCommand* mEditorCommand;
	};
}

#endif //EDITOR_HPP