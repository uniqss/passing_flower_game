#pragma once
#include "gamemanager.h"
#include "playerQueue.h"
#include "player.h"
class game
{
	gamemanager gameMgr;
	playerQueue playingQueue;
	playerQueue waitingQueue;
	bool playing;

public:
	game();
public:
	int genPlayerUniqueId();
	void init();
	void start();
	void stop();

	gamemanager* getGameMgr() { return &gameMgr; }
	playerQueue* getPlayingQueue() { return &playingQueue; }
	playerQueue* getWaitingQueue() { return &waitingQueue; }
};

