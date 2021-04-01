#pragma once

#include "handle.h"

class game;
class player : public handle
{
	// 队伍中的id
	//int queueId;
	// 唯一ID 使用handle里面的i
	//int uniqueId;

	// 邀请者 唯一ID
	int invitorUniqueId;

	// heart
	int remainSleepingFrames;
	// black
	bool leaving;

	bool haveFlower;
	game* currGame;
public:
	player(int uniqueId);

	//void setQueueId(int id) { queueId = id; }
	void setGame(game* pGame) { currGame = pGame; }
	void getFlowerFromQueue();
	void work(int queueId);
	void passFlower2Queue();
	void addBlack() { leaving = true; }
	bool isLeaving() { return leaving; }
	void addHeart(int sleepFrames) { remainSleepingFrames += sleepFrames; }

	int playRand();
	void setInvitorUniqueId(int uniqueId) { invitorUniqueId = uniqueId; }
};

