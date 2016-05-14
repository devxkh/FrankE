#include <XEngine/Extern/Extern.h>

#include <XEngine.hpp>

#include <iostream>

bool xEngine_test(bool test)
{
	//std::cout << "xEngine_test" << std::endl;
	return test;
}

XE::XEngine* xEngine_create(const char* title, const char* resourceFile)
{
	XE::XEngine* game = new XE::XEngine(resourceFile, title);//resourceFile, title);
	return game;
}


void xEngine_destroy(XE::XEngine* ptr)
{
	ptr->quit();

	delete ptr;
}