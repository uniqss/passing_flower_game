#pragma once
class playerQueue;
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
	void passFlower2Queue(playerQueue* queue);
	void getFlowerFromQueue(playerQueue* queue);
	void addDimond();
	void addRoundId();
};

