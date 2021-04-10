#pragma once
#include "stl.h"
class logicObject;

class logicQueue
{
	int workingIdx;
	bool teamOwnFlower;
	vector<logicObject*> logicObjects;
	//vector<logicObject*> logicObjects;
public:
	logicQueue();

public:
	void addLogicObject(logicObject* p);
	int getQueueLen() { return (int)logicObjects.size(); }
	void getFlower();

	void passFlower();

	void addBlack(int leavingPlayerIdx);

	// merge another queue into this queue.
	void mergeAnotherQueue(logicQueue* anotherQueue);

	void removeLeavingInvitedLogicObjects();

	void removeLeavingLogicObjects();

	void OnFrameBegin();
	void WorkThisFrame();
	void OnFrameEnd();
};

