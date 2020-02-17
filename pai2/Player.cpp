#include "stdafx.h"
#include "Player.h"


Player::Player(): mCard1(nullptr), mCard2(nullptr), mChips(400)
{
	pNo = spNo++;
}

void Player::receiveCard(const std::shared_ptr<Card>& card)
{
	if (!mCard1)
		mCard1 = card;
	else
		mCard2 = card;
}

std::shared_ptr<Card> Player::getCard1()
{
	return mCard1;
}

std::shared_ptr<Card> Player::getCard2()
{
	return mCard2;

}

std::string Player::showCards()
{
	return mCard1->toString() + " " + mCard2->toString();
}

void Player::throwCards()
{
	mCard1 = nullptr;
	mCard2 = nullptr;
}

void Player::updateChips(int a)
{
	mChips += a;
}

int Player::getChips()
{
	return mChips;
}

void Player::printBalance()
{
	std::cout << mChips << "coins\n";
}

int Player::getNo()
{
	return pNo;
}


Player::~Player()
{
}
