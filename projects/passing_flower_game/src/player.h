#pragma once

#include "logicObject.h"

class game;
class player : public logicObject
{
	// �Ƿ��ǳ�ʼ����
	bool initialPlayer;
	// �����е�id
	//int queueId;
	// ΨһID ʹ��handle�����i
	//int uniqueId;

	// ������ ΨһID
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

