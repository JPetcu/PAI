#include "stdafx.h"
#include "Player.h"


#include "CallAction.h"
#include "CheckAction.h"


void Player::setAllIn(bool allIn)
{
	isAllIn = allIn;
}

bool Player::getAllIn()
{
	return isAllIn;
}

Player::Player(): mCard1(nullptr), mCard2(nullptr), mChips(400)
{
	pNo = spNo++;
}

int Player::getBet()
{
	return mBet;
}

void Player::clearBet()
{
	mBet = 0;
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

void Player::getDownCards(std::vector<std::shared_ptr<Card>> downCards)
{
	mDownCards = downCards;
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

std::shared_ptr<Action> Player::getAction(const int call )
{
	
	if(this->getNo() == 1)
	{
		if((this->getCard1()->toValue() <6 || this->getCard2()->toValue() <6 || this->getCard1()->getFaceValue() == this->getCard2()->getFaceValue()) && mChips - mBet > 20)
		{
			mAction = std::make_shared<BetAction>(call + 20);
			mBet += call + 20;
			
			return mAction;
		}
	}
	
	if (call == 0)
		mAction = std::make_shared<CheckAction>();
	else
	{
		
		//mBet += call;
		if (mChips <= call+mBet)
		{
			if (this->getAllIn() == false)
			{
				mAction = std::make_shared<CallAction>(mChips - mBet);
				mBet = mChips;
				setAllIn(true);
			}
			else
			{
				mAction = std::make_shared<CallAction>(0);

			}
		}
		else
		{
			mBet += call;
			mAction = std::make_shared<CallAction>(call);
		}

	}
	if (mAction)
		return mAction;
	return nullptr;
}


Player::~Player()
{
}
