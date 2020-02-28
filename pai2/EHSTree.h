#pragma once
#include "Card.h"
#include <memory>

class EHSTree
{
	int mCard1, mCard2;
	double ehs;
	std::shared_ptr<EHSTree> mLeft, mRight;
public:
	EHSTree() : mLeft(nullptr), mRight(nullptr), ehs(0), mCard1(-1), mCard2(-1)
	{

	}
	void search()
	{
		
	}
	~EHSTree();
};

