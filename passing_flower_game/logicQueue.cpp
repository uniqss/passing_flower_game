#include "logicQueue.h"
#include "player.h"
#include <unordered_set>

#include "ulog.h"

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

bool logicQueue::workOnePlayer()
{
	if (logicObjects.empty())
	{
		return true;
	}

	// work for current player
	logicObject* p = logicObjects[workingIdx];
	p->getFlowerFromQueue();
	p->work(workingIdx);
	p->passFlower2Queue();
	// add workingIdx
	++workingIdx;
	if (workingIdx >= (int)logicObjects.size())
	{
		workingIdx = 0;
		return true;
	}

	return false;
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

void logicQueue::removeLeavingInvitedPlayers()
{
	unordered_set<int> leavingHandles;
	for (auto* p : logicObjects)
	{
		if (p->isLeaving())
		{
			leavingHandles.insert(p->getHandleId());
		}
	}

	logicObjects.erase(std::remove_if(logicObjects.begin(), logicObjects.end(), [&leavingHandles](player* p) {
		return leavingHandles.find(p->getInvitorUniqueId()) != leavingHandles.end();
		}), logicObjects.end());
}

void logicQueue::removeLeavingPlayers()
{
	auto playerCountPre = logicObjects.size();

	logicObjects.erase(std::remove_if(logicObjects.begin(), logicObjects.end(), [](player* p) {
		return !p->isInitialPlayer() && p->isLeaving();
		}), logicObjects.end());

	auto playerCountPost = logicObjects.size();
	ULOG_DEBUG("removeLeavingPlayers playerCountPre:{} playerCountPost:{}", playerCountPre, playerCountPost);
	std::for_each(logicObjects.begin(), logicObjects.end(), [](player* p) {p->setLeaving(false); });
}
