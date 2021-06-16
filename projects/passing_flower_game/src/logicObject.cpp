#include "logicObject.h"

logicObject::logicObject(int handleId) :
	handle(handleId)
	, remainSleepingFrames(0)
	, leaving(false)
{

}

void logicObject::getFlowerFromQueue()
{

}

void logicObject::passFlower2Queue()
{

}

bool logicObject::NeedRemoveOnInvitorLeave(const std::unordered_set<int>& leavingInvitorHandles)
{
	return true;
}

bool logicObject::NeedRemoveOnFrameEnd()
{
	return true;
}

void logicObject::OnFrameEnd()
{

}
