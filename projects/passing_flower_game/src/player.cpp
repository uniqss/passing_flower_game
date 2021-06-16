#include "player.h"
#include "gamemanager.h"
#include "logicQueue.h"
#include "game.h"
#include "fake_rand.h"

player::player(int uniqueId, bool _isInitialPlayer) :
	logicObject(uniqueId),
	initialPlayer(_isInitialPlayer),
	//queueId(0),
	invitorUniqueId(0),
	haveFlower(false),
	currGame(nullptr)
{

}

void player::getFlowerFromQueue()
{
	haveFlower = true;
}

void player::work(int queueId)
{
	gamemanager* gameMgr = currGame->getGameMgr();
	logicQueue* playingQueue = currGame->getPlayingQueue();
	logicQueue* waitingQueue = currGame->getWaitingQueue();
	// ��2������������ִ��֡��
	gameMgr->addTotalLogicFrameCount();

	do
	{
		// ��3����leaving
		if (isLeaving())
		{
			break;
		}

		// ��4����sleep�ж�
		if (isSleeping())
		{
			sleepOneFrame();
			break;
		}

		// ��5�������0�ŷ�(�ȴ��˳�)�ҷ�(˯��)����һ��������(X)����Χ[1,6]���ΪrandXA��
		// ���randXA>3(4,5,6)��������randXA-3�����ӣ�ÿ�ν��ΪrandXB����0������β��randXB����ң�
		// ����Ա������һ��(�ȴ��˳�)��
		int randXA = playRand();
		for (; randXA > 300; --randXA)
		{
			int randXB = playRand();
			int leavingPlayerIdx = (queueId + randXB) % playingQueue->getQueueLen();
			playingQueue->addBlack(leavingPlayerIdx);
		}

		// ��6�������0�ŷ�(�ȴ��˳�)�ҷ�(˯��)���ڶ���������(Y)����Χ[1,6]���ΪrandYA,
		// ���randYA>3(4,5,6)�������Ա����0��randYA-3��(˯��)
		int randYA = playRand();
		if (randYA > 300)
		{
			addSleepingFrames(randYA / 100 - 3);
		}

		// ��7�������0�ŷ�(�ȴ��˳�)�ҷ�(˯��)��������������(Z)����Χ[1,6]���ΪrandZA��
		// ���randZA>4(5,6)��������randZA-4������ҵ��ȴ����У�����������������ˡ�
		int randZA = playRand();
		for (; randZA > 400; randZA -= 100)
		{
			player* p = new player(currGame->genPlayerUniqueId(), false);
			p->setGame(currGame);
			waitingQueue->addLogicObject(p);
		}
		// ���randZA=4��������һ������ҵ��ȴ����У���������ҵ�������Ϊ0�š���0���˳�ʱ������������˳�
		if (randZA == 400)
		{
			player* p = new player(currGame->genPlayerUniqueId(), false);
			p->setGame(currGame);
			p->setInvitorUniqueId(this->getHandleId());
			waitingQueue->addLogicObject(p);
		}
	} while (false);

	// ��99��(99��Ϊ��ǰ�غϵ����һ��)��0����ҽ���
}

void player::passFlower2Queue()
{
	haveFlower = false;
}

bool player::NeedRemoveOnInvitorLeave(const std::unordered_set<int>& leavingInvitorHandles)
{
	return leavingInvitorHandles.find(this->getInvitorUniqueId()) != leavingInvitorHandles.end();
}

bool player::NeedRemoveOnFrameEnd()
{
	return !this->isInitialPlayer() && this->isLeaving();
}

void player::OnFrameEnd()
{
	this->setLeaving(false);
}

int player::playRand()
{
	return (int)((FakeRand() % 600) + 1);
}
