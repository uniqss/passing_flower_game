#include "playerQueue.h"
#include "player.h"
#include <unordered_set>

playerQueue::playerQueue() :
	workingIdx(0),
	teamOwnFlower(false)
{

}

void playerQueue::addPlayer(player* p)
{
	//p->setQueueId(players.size());
	players.push_back(p);
}

void playerQueue::getFlower()
{
	teamOwnFlower = true;
}

bool playerQueue::workOnePlayer()
{
	if (players.empty())
	{
		return true;
	}

	// work for current player
	player* p = players[workingIdx];
	p->getFlowerFromQueue();
	p->work(workingIdx);
	p->passFlower2Queue();
	// add workingIdx
	++workingIdx;
	if (workingIdx >= (int)players.size())
	{
		workingIdx = 0;
		return true;
	}

	return false;
}

void playerQueue::passFlower()
{
	teamOwnFlower = false;
}

void playerQueue::addBlack(int leavingPlayerIdx)
{
	if (players.empty())
	{
		return;
	}

	int idx = leavingPlayerIdx % players.size();
	player* p = players[idx];
	p->addBlack();
}

void playerQueue::mergeAnotherQueue(playerQueue* anotherQueue)
{
	for (player* p : anotherQueue->players)
	{
		this->addPlayer(p);
	}
	anotherQueue->players.clear();
}

void playerQueue::removeLeavingInvitedPlayers()
{
	unordered_set<int> leavingHandles;
	for (player* p : players)
	{
		if (p->isLeaving())
		{
			leavingHandles.insert(p->getHandleId());
		}
	}

	players.erase(std::remove_if(players.begin(), players.end(), [&leavingHandles](player* p) {
		return leavingHandles.find(p->getHandleId()) != leavingHandles.end();
		}), players.end());
}

void playerQueue::removeLeavingPlayers()
{
	players.erase(std::remove_if(players.begin(), players.end(), [](player* p) {
		return p->isLeaving();
		}), players.end());
}
