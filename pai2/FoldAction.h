#pragma once
#include "Action.h"
class FoldAction :
	public Action
{
public:
	FoldAction();
	std::string getAction() { return "FoldAction"; }
	~FoldAction();
};

