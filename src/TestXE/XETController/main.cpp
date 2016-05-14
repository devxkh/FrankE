#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"

int main()
{
	std::cout << "start" << std::endl;

	// leaving the scope of 'game' will cleanup the engine

	XE::XEngine game("F:/Projekte/coop/XEngine/data/Test/XETController/resources.cfg", "Ogre3D v2.0 and SFML v2.2 - XETController");

	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));

	game.run(game.build<ControllerState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();
}