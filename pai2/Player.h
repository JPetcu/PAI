#pragma once
#include "Card.h"
#include <memory>
#include <vector>
#include "Action.h"
#include "BetAction.h"

class Player
{
	std::shared_ptr<Card> mCard1, mCard2;
	int mChips, pNo;
	std::vector<std::shared_ptr<Card>> mDownCards;
	std::shared_ptr<Action> mAction;
	bool isPlaying;
public:
	static int spNo;
	Player();
	void receiveCard(const std::shared_ptr<Card> &card);
	std::shared_ptr<Card> getCard1();
	std::shared_ptr<Card> getCard2();
	std::string showCards();
	void getDownCards(std::vector<std::shared_ptr<Card>> downCards);
	void throwCards();
	void updateChips(int a);
	int getChips();
	void printBalance();
	int getNo();
	std::shared_ptr<Action> getAction();
	~Player();
};

