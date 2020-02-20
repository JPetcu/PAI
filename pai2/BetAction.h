#pragma once
#include "Action.h"
class BetAction :
	public Action
{
public:
	BetAction();
	std::string getAction() { return "BetAction"; }
	~BetAction();
};

