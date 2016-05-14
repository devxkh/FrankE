#include "WindowState.hpp"

int main()
{
	std::cout << "start" << std::endl;

	// leaving the scope of 'game' will cleanup the engine
	
	XE::XEngine game("E:/Projekte/coop/XEngine/data/Test/XETInput/resources.cfg", "Ogre3D v2.0 and SFML v2.2 - XETInput");
	
	game.run(game.build<WindowState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();

	return EXIT_SUCCESS;
}