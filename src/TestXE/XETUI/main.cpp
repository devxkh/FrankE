#include "TestMenuState.hpp"
#include "../XETCommon/TestScene.hpp"

int main()
{
	std::cout << "start" << std::endl;

	// leaving the scope of 'game' will cleanup the engine

	XE::XEngine game("F:/Projekte/coop/XEngine/data/Test/XETUI/resources.cfg", "Ogre3D v2.0 and SFML v2.2 - XETUI");

	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));

	game.run(game.build<TestMenuState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();

	return EXIT_SUCCESS;
}