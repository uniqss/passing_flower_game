#pragma once
class logicQueue;
class gamemanager
{
public:
	// dimond
	int totalLogicFrameCount;
	// 
	int roundId;

	bool haveFlower;

public:
	gamemanager();
	void passFlower2Queue(logicQueue* queue);
	void getFlowerFromQueue(logicQueue* queue);
	
	void addTotalLogicFrameCount();
	void addRoundId();
};

