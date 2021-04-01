#include "gamemanager.h"
#include "playerQueue.h"

gamemanager::gamemanager() :
	totalLogicFrameCount(0),
	roundId(0),
	haveFlower(true)
{

}

void gamemanager::passFlower2Queue(playerQueue* queue)
{
	haveFlower = false;
	queue->getFlower();
}

void gamemanager::getFlowerFromQueue(playerQueue* queue)
{
	queue->passFlower();
	haveFlower = true;
}

void gamemanager::addDimond()
{
	totalLogicFrameCount++;
}

void gamemanager::addRoundId()
{
	roundId++;
}
