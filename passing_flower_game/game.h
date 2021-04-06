#pragma once
#include "gamemanager.h"
#include "playerQueue.h"
#include "player.h"
class game
{
	gamemanager gameMgr;
	logicQueue playingQueue;
	logicQueue waitingQueue;
	bool playing;

public:
	game();
public:
	int genPlayerUniqueId();
	void init();
	void start();
	void stop();

	gamemanager* getGameMgr() { return &gameMgr; }
	logicQueue* getPlayingQueue() { return &playingQueue; }
	logicQueue* getWaitingQueue() { return &waitingQueue; }
};

