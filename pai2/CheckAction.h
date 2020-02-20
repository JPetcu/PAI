#pragma once
#include "Action.h"
class CheckAction :
	public Action
{
public:
	CheckAction()
	{
		this->setChips(0);
	}
	std::string getAction() { return "CheckAction"; }

	~CheckAction();
};

