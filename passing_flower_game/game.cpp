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
		// 整队所有玩家完成后
		// 把等待队列加入到当前队列的尾巴上
		playingQueue.mergeAnotherQueue(&waitingQueue);

		// 所有被手上有黑桃(等待退出)的玩家邀请的玩家离开队伍
		playingQueue.removeLeavingInvitedPlayers();
		// 所有手上有黑桃(等待退出)的玩家离开队伍。
		playingQueue.removeLeavingPlayers();

		// 管理员从地上拿一张梅花牌(回合id)到自己手上。
		gameMgr.addRoundId();
	}
}

void game::stop()
{
	playing = false;
}
