#pragma once

#include "handle.h"
#include <unordered_set>

class logicObject : public handle
{
private:
	// heart
	int remainSleepingFrames;
	// black
	bool leaving;

public:
	logicObject(int handleId);

	void addSleepingFrames(int sleepFrames) { remainSleepingFrames += sleepFrames; }
	bool isSleeping() { return remainSleepingFrames > 0; }
	void sleepOneFrame() { --remainSleepingFrames; }
	void setLeaving(bool _leaving) { leaving = _leaving; }
	bool isLeaving() { return leaving; }
public:
	virtual ~logicObject() {}

	virtual void getFlowerFromQueue();
	virtual void work(int queueId) = 0;
	virtual void passFlower2Queue();

	// called on frame end
	virtual bool NeedRemoveOnInvitorLeave(const std::unordered_set<int>& leavingInvitorHandles);
	virtual bool NeedRemoveOnFrameEnd();

	virtual void OnFrameEnd();
};

