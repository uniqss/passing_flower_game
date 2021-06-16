#pragma once

#include "logicObject.h"

class game;
class player : public logicObject
{
	// 是否是初始队伍
	bool initialPlayer;
	// 队伍中的id
	//int queueId;
	// 唯一ID 使用handle里面的i
	//int uniqueId;

	// 邀请者 唯一ID
	int invitorUniqueId;

	bool haveFlower;
	game* currGame;
public:
	player(int uniqueId, bool isInitialPlayer);

	virtual void getFlowerFromQueue();
	virtual void work(int queueId);
	virtual void passFlower2Queue();

	virtual bool NeedRemoveOnInvitorLeave(const std::unordered_set<int>& leavingInvitorHandles);
	virtual bool NeedRemoveOnFrameEnd();
	virtual void OnFrameEnd();

	bool isInitialPlayer() { return initialPlayer; }
	//void setQueueId(int id) { queueId = id; }
	void setGame(game* pGame) { currGame = pGame; }

	int playRand();
	int getInvitorUniqueId() { return invitorUniqueId; }
	void setInvitorUniqueId(int uniqueId) { invitorUniqueId = uniqueId; }
};

