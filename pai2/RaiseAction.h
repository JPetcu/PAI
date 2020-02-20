#pragma once
#include "Action.h"
class RaiseAction :
	public Action
{

public:
	RaiseAction();
	std::string getAction() { return "RaiseAction"; }

	~RaiseAction();
};

