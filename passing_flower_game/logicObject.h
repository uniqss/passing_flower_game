#pragma once

#include "handle.h"
#include <unordered_set>

class logicObject : public handle
{
public:
	logicObject(int handleId) : handle(handleId) {}
	virtual ~logicObject() {}

	virtual void getFlowerFromQueue();
	virtual void work(int queueId);
	virtual void passFlower2Queue();
	virtual void setLeaving(bool _leaving);
	virtual bool isLeaving();

	// called on frame end
	virtual bool NeedRemoveOnInvitorLeave(const std::unordered_set<int>& leavingInvitorHandles);
	virtual bool NeedRemoveOnFrameEnd();

	virtual void OnFrameEnd();
};

