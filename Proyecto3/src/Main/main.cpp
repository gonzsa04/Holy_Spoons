//Nap_Time_Studios
#include "checkML.h" //for memory leaks

#include "Game.h"
#include <GlobalConfig.h>

int main(int argc, char *argv[]) {
	//see if there are memory leaks (in debug mode)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GlobalCFG::loadIniCFG();

	Game game;
	game.start();

	return 0;
}