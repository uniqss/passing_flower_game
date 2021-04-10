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

		// todo @uniqs ����� merge �����⣬��Ҫ������ǰ�Ķ�β���壬�����β��Ҫ���㣬������ֱ��ƴ��β����
		// �������������ɺ�
		// �ѵȴ����м��뵽��ǰ���е�β����
		playingQueue.mergeAnotherQueue(&waitingQueue);

		// ���б�������(�ȴ��˳�)��������������뿪����
		playingQueue.removeLeavingInvitedLogicObjects();
		// ����������(�ȴ��˳�)������뿪���顣
		playingQueue.removeLeavingLogicObjects();

		// �غ�ID��
		gameMgr.addRoundId();

		// ��֡����֡
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
