#include "logicQueue.h"
#include "player.h"
#include <unordered_set>

#include "ulog.h"

#include "gameConstants.h"

logicQueue::logicQueue() :
	workingIdx(0),
	teamOwnFlower(false)
{

}

void logicQueue::addLogicObject(logicObject* p)
{
	//p->setQueueId(logicObjects.size());
	logicObjects.push_back(p);
}

void logicQueue::getFlower()
{
	teamOwnFlower = true;
}

void logicQueue::passFlower()
{
	teamOwnFlower = false;
}

void logicQueue::addBlack(int leavingPlayerIdx)
{
	if (logicObjects.empty())
	{
		return;
	}

	int idx = leavingPlayerIdx % logicObjects.size();
	logicObject* p = logicObjects[idx];
	p->setLeaving(true);
}

void logicQueue::mergeAnotherQueue(logicQueue* anotherQueue)
{
	for (auto* p : anotherQueue->logicObjects)
	{
		this->addLogicObject(p);
	}
	anotherQueue->logicObjects.clear();
}

void logicQueue::removeLeavingInvitedLogicObjects()
{
	unordered_set<int> leavingObjectHandles;
	for (auto* p : logicObjects)
	{
		if (p->isLeaving())
		{
			leavingObjectHandles.insert(p->getHandleId());
		}
	}

	logicObjects.erase(std::remove_if(logicObjects.begin(), logicObjects.end(), [&leavingObjectHandles](logicObject* p) {
		return p->NeedRemoveOnInvitorLeave(leavingObjectHandles);
		}), logicObjects.end());
}

void logicQueue::removeLeavingLogicObjects()
{
	auto playerCountPre = logicObjects.size();

	logicObjects.erase(std::remove_if(logicObjects.begin(), logicObjects.end(), [](logicObject* p) {
		return p->NeedRemoveOnFrameEnd();
		}), logicObjects.end());

	auto playerCountPost = logicObjects.size();
	ULOG_DEBUG("playerCountPre:{} playerCountPost:{}", playerCountPre, playerCountPost);
	std::for_each(logicObjects.begin(), logicObjects.end(), [](logicObject* p) {
		p->OnFrameEnd();
		});
}

void logicQueue::OnFrameBegin()
{
}

void logicQueue::WorkThisFrame()
{
	if (logicObjects.empty())
	{
		return;
	}

	int i = 0;
	for (i = 0; i < FRAME_LOGICOBJECT_WORK_MAX && i < getQueueLen(); i++)
	{
		// work for current player
		int idx = (workingIdx + i) % logicObjects.size();
		logicObject* p = logicObjects[idx];
		p->getFlowerFromQueue();
		p->work(idx);
		p->passFlower2Queue();
	}
	workingIdx = (workingIdx + i) % logicObjects.size();
}

void logicQueue::OnFrameEnd()
{

}
