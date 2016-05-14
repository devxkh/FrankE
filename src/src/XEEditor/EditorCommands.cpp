#include <XEEditor/EditorCommands.hpp>
#include <XEEditor/Editor.hpp>

#include <XEUI/Widgets/OgreConsoleForGorilla.hpp>

namespace EI {

	EditorCommand::EditorCommand(XE::XEngine* engine, XE::OgreConsole* console) 
		: m_engine(engine),
		m_console(console)
	{

	}

	int EditorCommand::updateObject(Ogre::StringVector& vec)
	{
		unsigned int id;
		int type;

		std::cout << "updateObject" << id << ",type:" << type;

		m_engine->getCurrentState()->pause();

	//	XE::StateData* test = m_engine->getCurrentState()->getStateData();
//		test->mScene->updatePhysicsObject(id);

		m_engine->getCurrentState()->resume();

		return Status::Unknown;
	}

	int EditorCommand::deleteObject(Ogre::StringVector& vec)
	{
		unsigned int id;
		int type;

		std::cout << "updateObject" << id << ",type:" << type;

		m_engine->getCurrentState()->pause();

	//	XE::StateData* test = m_engine->getCurrentState()->getStateData();
	//	test->mScene->updatePhysicsObject(id);

		m_engine->getCurrentState()->resume();

		return Status::Unknown;
	}

	void EditorCommand::createObject(Ogre::StringVector& vec)
	{

		if (vec.size() == 1)
			m_console->print("Make you what?");
		else
		{
			Ogre::String item_to_make = vec[1];
			Ogre::StringUtil::toLowerCase(item_to_make);
			if (item_to_make == "physic")
			{
				m_console->print("Make it yourself!");

				m_engine->getCurrentState()->pause();

				std::cout << "pause";

			//	XE::StateData* test = m_engine->getCurrentState()->getStateData();
			//##	test->mScene->updatePhysicsObject(0);

				m_engine->getCurrentState()->resume();

			}
			/*if (item_to_make == "sandwich")
			console->print("Make it yourself!");
			else if (item_to_make == "universe")
			console->print("Boom!");
			else if (item_to_make == "ogre")
			console->print("I need a Daddy and Mommy Ogre");
			else if (item_to_make == "gorilla")
			console->print("He wouldn't like that");
			else
			console->print("Go check your fridge.");*/
		}
	//	return 0;
	}
}