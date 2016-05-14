#include "ServerState.hpp"

int main()
{
	std::cout << "start" << std::endl;

	// leaving the scope of 'game' will cleanup the engine

	XE::XEngine game("F:/Projekte/coop/XEngine/data/Test/XETController/resources.cfg", "Ogre3D v2.0 and SFML v2.2 - XETServer");


	game.run(game.build<ServerState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();
}