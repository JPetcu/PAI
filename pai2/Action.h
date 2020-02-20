#pragma once
#include <string>

class Action
{
	int mChips;
public:
	Action() ;
	int getChips() { return mChips; }
	void setChips() { mChips = 0; };
	void setChips(int chips) { mChips = chips; };
	virtual std::string getAction() = 0;

	virtual ~Action() = 0;
};

