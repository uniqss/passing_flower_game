#include "gamemanager.h"
#include "logicQueue.h"

gamemanager::gamemanager() :
	totalLogicFrameCount(0),
	roundId(0),
	haveFlower(true)
{

}

void gamemanager::passFlower2Queue(logicQueue* queue)
{
	haveFlower = false;
	queue->getFlower();
}

void gamemanager::getFlowerFromQueue(logicQueue* queue)
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
