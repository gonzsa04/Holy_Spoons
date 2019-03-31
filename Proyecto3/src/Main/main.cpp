//Nap_Time_Studios

//#include "checkML.h" //for memory leaks
#include "Game.h"
#include <SoundManager.h>

using namespace irrklang;

int main(int argc, char *argv[])
{
	//see if there are memory leaks (in debug mode)
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// musiquita que venia de ejemplo jeje. Si quereis ver el 3D modificad la z y lo oireis por la izq o der
	// siempre hacer el setListenerTransform y como parametro un puntero a la pos&rot del player (o de lo que vaya a escuchar)
	// la primera vez que se llame al getSingleton
	SoundManager::getSingleton()->setListenerTransform(new nap_transform());
	SoundManager::getSingleton()->play3DSound("ophelia.mp3", new nap_vector3(0,0,10), true, false);

	Game game;
	game.start();

	SoundManager::shutdownSingleton();

	return 0;
}