#pragma once
#include "stl.h"
class logicObject;

class logicQueue
{
	int workingIdx;
	bool teamOwnFlower;
	vector<logicObject*> logicObjects;
public:
	logicQueue();

public:
	void addLogicObject(logicObject* p);
	int getQueueLen() { return (int)logicObjects.size(); }
	void getFlower();

	// return whether all queue players already got flower.
	bool workOnePlayer();

	void passFlower();

	void addBlack(int leavingPlayerIdx);

	// merge another queue into this queue.
	void mergeAnotherQueue(logicQueue* anotherQueue);

	void removeLeavingInvitedLogicObjects();

	void removeLeavingLogicObjects();
};

