#pragma once
#include "stl.h"
class player;

class playerQueue
{
	int workingIdx;
	bool teamOwnFlower;
	vector<player*> players;
public:
	playerQueue();

public:
	void addPlayer(player* p);
	int getQueueLen() { return (int)players.size(); }
	void getFlower();

	// return whether all queue players already got flower.
	bool workOnePlayer();

	void passFlower();

	void addBlack(int leavingPlayerIdx);

	// merge another queue into this queue.
	void mergeAnotherQueue(playerQueue* anotherQueue);

	void removeLeavingInvitedPlayers();

	void removeLeavingPlayers();
};

