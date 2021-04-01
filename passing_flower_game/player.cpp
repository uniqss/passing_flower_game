#include "player.h"
#include "gamemanager.h"
#include "playerQueue.h"
#include "game.h"
#include "fake_rand.h"

player::player(int uniqueId) :
	handle(uniqueId),
	//queueId(0),
	invitorUniqueId(0),
	remainSleepingFrames(0),
	leaving(false),
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
	playerQueue* playingQueue = currGame->getPlayingQueue();
	playerQueue* waitingQueue = currGame->getWaitingQueue();
	// ��2����0�Ž�������Ա1�ŷ�Ƭ��(��������ִ��֡��)
	gameMgr->addDimond();

	do 
	{
		// ��3�������0���к���(�ȴ��˳�)��������99��
		if (leaving)
		{
			break;
		}

		// ��4�������0���к�����(˯��)����������Ա1�ź�����(˯��)��������99��
		if (remainSleepingFrames > 0)
		{
			--remainSleepingFrames;
			break;
		}

		// ��5�������0��û�к���(�ȴ��˳�)��û�к�����(˯��)����һ��������(X)����Χ[1,6]���ΪrandXA��
		// ���randXA>3(4,5,6)��������randXA-3�����ӣ�ÿ�ν��ΪrandXB����0������β��randXB����ң�
		// ����Ա������һ�ź���(�ȴ��˳�)��
		int randXA = playRand();
		for (;randXA > 3;--randXA)
		{
			int randXB = playRand();
			int leavingPlayerIdx = (queueId + randXB) % playingQueue->getQueueLen();
			playingQueue->addBlack(leavingPlayerIdx);
		}

		// ��6�������0��û�к���(�ȴ��˳�)��û�к�����(˯��)���ڶ���������(Y)����Χ[1,6]���ΪrandYA,
		// ���randYA>3(4,5,6)�������Ա����0��randYA-3�ź�����(˯��)
		int randYA = playRand();
		if (randYA > 3)
		{
			addHeart(randYA - 3);
		}

		// ��7�������0��û�к���(�ȴ��˳�)��û�к�����(˯��)��������������(Z)����Χ[1,6]���ΪrandZA��
		// ���randZA>4(5,6)��������randZA-4������ҵ��ȴ����У�����������������ˡ�
		int randZA = playRand();
		for (;randZA > 4;--randZA)
		{
			player* p = new player(currGame->genPlayerUniqueId());
			p->setGame(currGame);
			waitingQueue->addPlayer(p);
		}
		// ���randZA=4��������һ������ҵ��ȴ����У���������ҵ�������Ϊ0�š���0���˳�ʱ������������˳�
		if (randZA == 4)
		{
			player* p = new player(currGame->genPlayerUniqueId());
			p->setGame(currGame);
			p->setInvitorUniqueId(this->getHandleId());
			waitingQueue->addPlayer(p);
		}
	} while (false);

	// ��99��(99��Ϊ��ǰ�غϵ����һ��)��0����ҽ���
}

void player::passFlower2Queue()
{
	haveFlower = false;
}

int player::playRand()
{
	return (int)((FakeRand() % 6) + 1);
}
