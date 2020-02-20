#pragma once
#include "Action.h"
class CallAction :
	public Action
{
public:
	CallAction();
	std::string getAction() { return "CallAction"; }

	~CallAction();
};

