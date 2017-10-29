#include <XEngine/Extern/Extern.h>

#include <XEngine.hpp>

#include <iostream>


//#include "TestMenuState.hpp"
#include "../XETCommon/TestScene.hpp"
#include "../XETCommon/TestDAL.hpp"

//int main(int argc, char **argv)
//{
//	LOG(XE::info) << "main()";
//
//	// leaving the scope of 'game' will cleanup the engine
//	XE::XEngine game;
//
//	game.settings.load("F:/Projekte/coop/FrankE/data/");
//	game.setDAL(std::unique_ptr<XET::TestDAL>(new XET::TestDAL(game)));
//	game.init();
//	game.setScene(std::unique_ptr<XET::TestScene>(new XET::TestScene(game)));
//	game.run(game.build<TestMenuState>(game, true));
//
//	while (game.running())
//	{
//		game.update();
//	}
//
//	game.destroy();
//
//	return EXIT_SUCCESS;
//}


bool xEngine_test(bool test)
{
	//std::cout << "xEngine_test" << std::endl;
	return test;
}

XE::XEngine* xEngine_create(const char* title, const char* resourceFile)
{
	XE::XEngine* game = new XE::XEngine(); // resourceFile, title);//resourceFile, title);
	game->settings.load("F:/Projekte/coop/XGame/data/");
	
	return game;
}


void xEngine_destroy(XE::XEngine* ptr)
{
	ptr->quit();

	delete ptr;
}