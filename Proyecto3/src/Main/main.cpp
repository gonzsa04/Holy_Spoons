//Nap_Time_Studios

#include <iostream>
#include <OgreRoot.h>
#include <OgreBuildSettings.h>

//#include "checkML.h" //for memory leaks
#include "Game.h"

int main()
{
	//see if there are memory leaks (in debug mode)
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.start();

	system("pause");
	return 0;
}