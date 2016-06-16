#include "ServerState.hpp"

int main()
{
	std::cout << "start" << std::endl;

	// leaving the scope of 'game' will cleanup the engine

	XE::XEngine game;

	//game.settings.dbDataFolder = "F:\\Projekte\\coop\\XGame\\data\\dbData";
	//game.settings.assetsFolder = "F:\\Projekte\\coop\\XGame\\data\\assets";
	//game.settings.dbFileName = "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db";
	//game.settings.windowTitle = "Ogre3D v2.0 and SDL 2 - XETServer";
	
	game.settings.load("F:/Projekte/coop/XGame/data/");
	game.init();
	game.run(game.build<ServerState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();


	return 0;
}