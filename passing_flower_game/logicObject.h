#pragma once

#include "handle.h"

class logicObject : public handle
{
public:
	virtual void getFlowerFromQueue();
	virtual void work(int queueId);
	virtual void passFlower2Queue();
	virtual void setLeaving(bool _leaving);
	virtual bool isLeaving();
};

