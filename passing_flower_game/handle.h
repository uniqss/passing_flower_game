#pragma once
class handle
{
	int i;
public:
	handle(int ii) : i(ii) {}
	virtual ~handle() {}
	int getHandleId() { return i; }
};

