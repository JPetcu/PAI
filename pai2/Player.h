#pragma once
#include "Card.h"
#include <memory>

class Player
{
	std::shared_ptr<Card> mCard1, mCard2;
	int mChips;
public:
	Player();
	void receiveCard(const std::shared_ptr<Card> &card);
	std::shared_ptr<Card> getCard1();
	std::shared_ptr<Card> getCard2();
	std::string showCards();
	void throwCards();
	void updateChips(int a);
	int getChips();
	void printBalance();
	~Player();
};

