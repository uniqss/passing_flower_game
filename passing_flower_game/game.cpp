#include "game.h"

#include "fake_rand.h"

game::game() :
	playing(false)
{
}

int game::genPlayerUniqueId()
{
	return (int)FakeRand();
}

void game::init()
{
	FakeRandInit();

	for (int i = 0; i < 5; i++)
	{
		player* p = new player(genPlayerUniqueId(), true);
		p->setGame(this);
		playingQueue.addPlayer(p);
	}
}

void game::start()
{
	playing = true;
	while (playing)
	{
		bool queueFinished = false;
		for (int i = 0; i < playingQueue.getQueueLen(); i++)
		{
			gameMgr.passFlower2Queue(&playingQueue);
			queueFinished = playingQueue.workOnePlayer();
			gameMgr.getFlowerFromQueue(&playingQueue);
			if (queueFinished)
			{
				break;
			}
		}
		// �������������ɺ�
		// �ѵȴ����м��뵽��ǰ���е�β����
		playingQueue.mergeAnotherQueue(&waitingQueue);

		// ���б������к���(�ȴ��˳�)��������������뿪����
		playingQueue.removeLeavingInvitedPlayers();
		// ���������к���(�ȴ��˳�)������뿪���顣
		playingQueue.removeLeavingPlayers();

		// ����Ա�ӵ�����һ��÷����(�غ�id)���Լ����ϡ�
		gameMgr.addRoundId();
	}
}

void game::stop()
{
	playing = false;
}
