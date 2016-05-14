
//#include <XEEditor/Event/ConvertEvent.hpp>
#include <XEEditor/IEditor.hpp>

#include <XEngine/Extern/Extern.h>

int main()
{

	xEngine_test(true); //without using this, the extern functions seems to be not compiled into the dll -> in c# entrypoint not found ???
	auto testfkt =  xEngine_create("E:/Projekte/coop/XEngine/data/Test/XETController/resources.cfg", "Ogre3D v2.1 and SFML v2.2 - XETController");
	return 0;


	std::cout << "start" << std::endl;


	EI::stateInit("", 200, 200);

	char* test = new char[3];
	//###		EI::getStates(test);

	std::cout << "EI::getStates:" << test;

	bool running = true;
	while (running)
	{

		sfEvent event;
		event.type = sfEventType::sfEvtKeyPressed;
		event.key.code = sfKeyW;

		//###		EI::pushEvent(event);

	//###	EI::stateUpdate();


		//		EI::quit();
		//	// handle events
		//	sf::Event event;
		//	while (window.pollEvent(event))
		//	{
		//		if (event.type == sf::Event::Closed)
		//		{
		//			// end the program
		//			running = false;
		//		}
	}

	// leaving the scope of 'game' will cleanup the engine

	//XE::XEngine game("E:/Projekte/coop/XEngine/data/Test/XETController/resources.cfg", "Ogre3D v2.0 and SFML v2.2 - XETEditor");


	//game.run(game.build<EditorState>(&game, true));

	//while (game.running())
	//{
	//	game.update();
	//}

	//game.quit();
}