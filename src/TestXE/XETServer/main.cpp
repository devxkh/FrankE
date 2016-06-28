#include "ServerState.hpp"

#include "../XETCommon/TestDAL.hpp"

int main()
{
	LOG(XE::info) << "start";

	// leaving the scope of 'game' will cleanup the engine
	XE::XEngine game;

	game.settings.load("F:/Projekte/coop/XGame/data/");
	game.setDAL(std::unique_ptr<XET::TestDAL>(new XET::TestDAL(game)));
	game.init();
	game.run(game.build<ServerState>(game, true));

	while (game.running())
	{
		game.update();
	}

	game.quit();
	
	return 0;
}