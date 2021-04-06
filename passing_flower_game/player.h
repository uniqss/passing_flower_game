#pragma once

#include "handle.h"

class game;
class player : public handle
{
	// 是否是初始队伍
	bool initialPlayer;
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
	player(int uniqueId, bool isInitialPlayer);

	bool isInitialPlayer() { return initialPlayer; }
	//void setQueueId(int id) { queueId = id; }
	void setGame(game* pGame) { currGame = pGame; }
	void getFlowerFromQueue();
	void work(int queueId);
	void passFlower2Queue();
	bool isLeaving() { return leaving; }
	void setLeaving(bool _leaving) { leaving = _leaving; }
	void addHeart(int sleepFrames) { remainSleepingFrames += sleepFrames; }

	int playRand();
	int getInvitorUniqueId() { return invitorUniqueId; }
	void setInvitorUniqueId(int uniqueId) { invitorUniqueId = uniqueId; }
};

