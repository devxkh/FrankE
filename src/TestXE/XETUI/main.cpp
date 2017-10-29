#include "TestMenuState.hpp"
#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestDAL.hpp"

int main(int argc, char **argv) 
{
	LOG(XE::info) << "main()";

	// leaving the scope of 'game' will cleanup the engine
	XE::XEngine game;

	game.settings.load("F:/Projekte/coop/FrankE/data/settings.json");
	game.setDAL(std::unique_ptr<XET::TestDAL>(new XET::TestDAL(game)));
	game.init();
	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));
	game.run(game.build<TestMenuState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.destroy();

	return EXIT_SUCCESS;
}