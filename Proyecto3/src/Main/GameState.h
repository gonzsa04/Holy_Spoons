//Nap_Time_Studios

#pragma once

#include "Entity.h"

#include <iostream> //debugging for now
#include <string>
#include <list>

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void handleEvents(float time, const Event evt);
	virtual void update(float time);

	//void sendToGSM(Message* msg);

	inline string setStateID(string id) { stateID_ = id; };
	inline string getStateID() { stateID_; };

protected:
	virtual void initState() = 0;
	virtual void closeState() = 0;

	//void killDeadObjects();

	list<Entity*> entities_;

	string stateID_ = "undefinedID";
};