#pragma once
#include "Card.h"
#include <memory>
#include <vector>
#include "Action.h"
#include "BetAction.h"
#include "Cashier.h"

class Player
{
	std::shared_ptr<Card> mCard1, mCard2;
	int mChips, pNo;
	std::vector<std::shared_ptr<Card>> mDownCards;
	std::shared_ptr<Action> mAction;
	bool isPlaying, isAllIn;
	int mBet = 0;
//	std::weak_ptr<Cashier> mCashier;
public:
	void setAllIn(bool allIn);
	bool getAllIn();
	static int spNo;
	Player();
	int getBet();
	void clearBet();
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
	std::shared_ptr<Action> getAction(int call = 0);
	~Player();
};

