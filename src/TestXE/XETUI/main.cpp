#include "TestMenuState.hpp"
#include "../XETCommon/TestScene.hpp"


int main(int argc, char **argv) 
{
	LOG(INFO) << "main()";

	// leaving the scope of 'game' will cleanup the engine
	
	XE::XEngine game;

	/*game.settings.hlmsDataFolder = "F:\\Projekte\\coop\\XGame\\data\\Hlms";
	game.settings.dbDataFolder = "F:\\Projekte\\coop\\XGame\\data\\dbData";
	game.settings.assetsFolder = "F:\\Projekte\\coop\\XGame\\data\\assets";
	game.settings.dbFileName = "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db";
	game.settings.windowTitle = "Ogre3D v2.0 and SDL 2 - XETUI";*/
	game.settings.load("F:/Projekte/coop/XGame/data/");
	game.init();
	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));
	game.run(game.build<TestMenuState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();

	return EXIT_SUCCESS;
}