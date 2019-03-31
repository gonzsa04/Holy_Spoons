#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <string>
#include <map>
using namespace std;

namespace irrklang {
	class ISoundEngine;
	class ISound;
}

// interface for irrklang (SoundManager)
class SoundManager
{
private:
	static SoundManager* instance_;             //singleton pattern
	const string soundsRoute = ".\\Assets\\Sound\\";
	std::map<string, irrklang::ISound*> sounds; // sounds already played

	irrklang::ISoundEngine* engine;             // it plays the sounds, etc

	SoundManager();
	virtual ~SoundManager();
public:
	static SoundManager* getSingleton(); // you can obtain/shutdown the instance of the singleton 
	static void shutdownSingleton();

	// playing 3D/2D sounds... (3D will need a pointer to the emitter position
	irrklang::ISound* play3DSound(const string& name, float x, float y, float z, 
		bool playLooped = false, bool startPaused = false, bool track = false);

	irrklang::ISound* play2DSound(const string& name,
		bool playLooped = false, bool startPaused = false, bool track = false);

	bool isPlaying(const string& name);

	irrklang::ISound* findByName(const string& name);

	irrklang::ISoundEngine* getEngine();
};

#endif /* SOUND_MANAGER_H_ */

/*
// SOUND MANAGER EXAMPLE: playing a 3d sound in movement

#include <SoundManager.h>
#include <irrKlang.h>
#include <windows.h>

using namespace irrklang;

	SoundManager* soundManager = SoundManager::getSingleton();

	if (!soundManager) return 0; // error starting up the engine

	soundManager->play3DSound("ophelia.mp3", 0,0,0, true, false);
	Sleep(2000);
	ISound* m = soundManager->play3DSound("ophelia.mp3", 0,0,0, true, false, true);
	ISound* music = soundManager->findByName("ophelia.mp3"); m->setVolume(0);

	if (music) music->setMinDistance(10.0f);

	printf("\nPlaying streamed sound in 3D.");
	printf("\nPress ESCAPE to quit, any other key to play sound at random position.\n\n");

	printf("+ = Listener position\n");
	printf("o = Playing sound\n");

	float posOnCircle = 0;
	const float radius = 15;

	while (true) // endless loop until user exits
	{
		posOnCircle += 0.04f;
		vec3df pos3d(radius * cosf(posOnCircle), 0,
			radius * sinf(posOnCircle * 0.5f));

		soundManager->getEngine()->setListenerPosition(vec3df(0, 0, 0), vec3df(0, 0, 1));

		if (music)
			music->setPosition(pos3d);

		char stringForDisplay[] = "          +         ";
		int charpos = (int)((pos3d.X + radius) / radius * 10.0f);
		if (charpos >= 0 && charpos < 20)
			stringForDisplay[charpos] = 'o';
		int playPos = music ? music->getPlayPosition() : 0;

		printf("\rx:(%s)   3dpos: %.1f %.1f %.1f, playpos:%d:%.2d    ",
			stringForDisplay, pos3d.X, pos3d.Y, pos3d.Z,
			playPos / 60000, (playPos % 60000) / 1000);

		Sleep(100);
	}

	SoundManager::shutdownSingleton();
	return 0;
*/
