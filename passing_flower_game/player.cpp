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
	// 第2步、0号交给管理员1张方片牌(经过的总执行帧数)
	gameMgr->addDimond();

	do 
	{
		// 第3步、如果0号有黑桃(等待退出)，跳到第99步
		if (leaving)
		{
			break;
		}

		// 第4步、如果0号有红桃牌(睡眠)，交给管理员1张红桃牌(睡眠)，跳到第99步
		if (remainSleepingFrames > 0)
		{
			--remainSleepingFrames;
			break;
		}

		// 第5步、如果0号没有黑桃(等待退出)且没有红桃牌(睡眠)，第一轮掷骰子(X)，范围[1,6]结果为randXA，
		// 如果randXA>3(4,5,6)，则再掷randXA-3次骰子，每次结果为randXB，从0号往队尾数randXB个玩家，
		// 管理员交给他一张黑桃(等待退出)。
		int randXA = playRand();
		for (;randXA > 3;--randXA)
		{
			int randXB = playRand();
			int leavingPlayerIdx = (queueId + randXB) % playingQueue->getQueueLen();
			playingQueue->addBlack(leavingPlayerIdx);
		}

		// 第6步、如果0号没有黑桃(等待退出)且没有红桃牌(睡眠)，第二轮掷骰子(Y)，范围[1,6]结果为randYA,
		// 如果randYA>3(4,5,6)，则管理员发给0号randYA-3张红桃牌(睡眠)
		int randYA = playRand();
		if (randYA > 3)
		{
			addHeart(randYA - 3);
		}

		// 第7步、如果0号没有黑桃(等待退出)且没有红桃牌(睡眠)，第三轮掷骰子(Z)，范围[1,6]结果为randZA，
		// 如果randZA>4(5,6)，则邀请randZA-4个新玩家到等待队列，被邀请玩家无邀请人。
		int randZA = playRand();
		for (;randZA > 4;--randZA)
		{
			player* p = new player(currGame->genPlayerUniqueId());
			p->setGame(currGame);
			waitingQueue->addPlayer(p);
		}
		// 如果randZA=4，则邀请一个新玩家到等待队列，被邀请玩家的邀请人为0号。当0号退出时，被邀请玩家退出
		if (randZA == 4)
		{
			player* p = new player(currGame->genPlayerUniqueId());
			p->setGame(currGame);
			p->setInvitorUniqueId(this->getHandleId());
			waitingQueue->addPlayer(p);
		}
	} while (false);

	// 第99步(99记为当前回合的最后一步)、0号玩家结束
}

void player::passFlower2Queue()
{
	haveFlower = false;
}

int player::playRand()
{
	return (int)((FakeRand() % 6) + 1);
}
