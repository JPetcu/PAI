#pragma once
#include "Action.h"
class BetAction :
	public Action
{
public:
	BetAction(int a) { setChips(a); }
	std::string getAction() { return "BetAction"; }
	~BetAction();
};

