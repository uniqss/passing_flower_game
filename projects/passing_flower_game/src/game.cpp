#include "game.h"

#include "fake_rand.h"

#include "gameConstants.h"

#include "timehelper.h"

#include "ulog.h"

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
		playingQueue.addLogicObject(p);
	}
}

void game::start()
{
	playing = true;

	auto lastTimeMS = GetTimeMS();
	decltype(lastTimeMS) exceedTimeMS = 0;
	while (playing)
	{
		bool queueFinished = false;
		// for(i=ilast;i<ilast+framemax&&(i-ilast>playerQueue.size());i++)
		// {player[i%playerqueue.size()].logic};
		// after_logic();
		playingQueue.OnFrameBegin();

		playingQueue.WorkThisFrame();

		playingQueue.OnFrameEnd();

		// todo @uniqs 这里的 merge 有问题，需要往【当前的队尾】插，这个队尾需要计算，而不是直接拼到尾巴上
		// 整队所有玩家完成后
		// 把等待队列加入到当前队列的尾巴上
		playingQueue.mergeAnotherQueue(&waitingQueue);

		// 所有被手上有(等待退出)的玩家邀请的玩家离开队伍
		playingQueue.removeLeavingInvitedLogicObjects();
		// 所有手上有(等待退出)的玩家离开队伍。
		playingQueue.removeLeavingLogicObjects();

		// 回合ID。
		gameMgr.addRoundId();

		// 限帧、补帧
		auto currTimeMS = GetTimeMS();
		auto frameCost = currTimeMS - lastTimeMS;
		auto frameStandardTime = (decltype(currTimeMS))100;
		//ULOG_DEBUG("currTimeMS:{} frameCost:{} exceedTimeMS:{}", currTimeMS, frameCost, exceedTimeMS);
		if (exceedTimeMS + frameCost < frameStandardTime)
		{
			auto sleepMS = (decltype(currTimeMS))100 - frameCost - exceedTimeMS;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS));
			exceedTimeMS = 0;
			lastTimeMS = currTimeMS;
		}
		else
		{
			exceedTimeMS = exceedTimeMS + frameCost - frameStandardTime;

			lastTimeMS = currTimeMS;
		}
	}
}

void game::stop()
{
	playing = false;
}
