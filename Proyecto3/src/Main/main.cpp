//Nap_Time_Studios

#include <iostream>
#include <RenderSystemManager.h>
#include <RenderSystemInterface.h>

//#include "checkML.h" //for memory leaks
#include "Game.h"

int main(int argc, char *argv[])
{
	//see if there are memory leaks (in debug mode)
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.start();

	return 0;
}