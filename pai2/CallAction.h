#pragma once
#include "Action.h"
class CallAction :
	public Action
{
public:
	CallAction(int a);
	std::string getAction() { return "CallAction"; }

	~CallAction();
};

