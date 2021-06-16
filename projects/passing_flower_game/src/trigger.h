#pragma once

#include "stl.h"

class condition;
class action;
class trigger
{
public:
	vector<condition*> conditions;
	vector<action*> actions;
};
