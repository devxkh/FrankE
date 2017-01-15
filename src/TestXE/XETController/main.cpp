#include "ControllerState.hpp"

#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestDAL.hpp"

int main()
{
	LOG(XE::info) << "start";

	// leaving the scope of 'game' will cleanup the engine
	XE::XEngine game;

	game.settings.load("F:/Projekte/coop/FrankE/data/");
	game.setDAL(std::unique_ptr<XET::TestDAL>(new XET::TestDAL(game)));
	game.init();
	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));

	game.run(game.build<ControllerState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.destroy();

	return EXIT_SUCCESS; 
}