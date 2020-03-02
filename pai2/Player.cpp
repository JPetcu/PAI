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

std::shared_ptr<Card>& Player::getCard1()
{
	return mCard1;
}

std::shared_ptr<Card>& Player::getCard2()
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
		std::shared_ptr<EHSCalculator> calc(new EHSCalculator(this->getCard1(),this->getCard2()));
		/*if((this->getCard1()->toValue() <6 || this->getCard2()->toValue() <6 || this->getCard1()->getFaceValue() == this->getCard2()->getFaceValue()) && mChips - mBet > 20)
		{
			mAction = std::make_shared<BetAction>(call + 20);
			mBet += call + 20;
			
			return mAction;
		}*/
		double ehs;
		if(mDownCards.size() == 0)
		{
			ehs = calc->preFlop(this->getCard1(), this->getCard2());
			std::cout << "\n EHS preflop is: " << ehs << "\n";

			if(ehs > 70)
			{
				
				mAction = std::make_shared<BetAction>(call + 20);
				mBet += call + 20;
				return mAction;
			}
		}
		else 
		{
			ehs = calc->EHS(this->getCard1(), this->getCard2(), mDownCards) * 100;
			if (mDownCards.size() == 3)
			std::cout << "\nEHS flop is: " << ehs << "\n";
			else if (mDownCards.size() == 4)
				std::cout << "\nEHS turn is: " << ehs << "\n";
			else if (mDownCards.size() == 5)
				std::cout << "\nEHS river is: " << ehs << "\n";




			if (ehs > 90)
			{
				if (call + 20 + mBet <= mChips)
				{
					mAction = std::make_shared<BetAction>(call + 100);
					mBet += call + 100;

					return mAction;
				}
				else
				{
					if (mChips - mBet > 0)
					{
						mAction = std::make_shared<BetAction>(mChips - mBet);
						mBet = mChips;
					}
					else
					{
						mAction = std::make_shared<CheckAction>();
						mBet = mChips;
					}

					return mAction;
				}
			}
			else if (ehs > 80)
			{
				if (call + 60 + mBet <= mChips)
				{
					mAction = std::make_shared<BetAction>(call + 60);
					mBet += call + 60;

					return mAction;
				}
				else
				{
					if (mChips - mBet > 0)
					{
						mAction = std::make_shared<BetAction>(mChips - mBet);
						mBet = mChips;
					}
					else
					{
						mAction = std::make_shared<CheckAction>();
						mBet = mChips;
					}

					return mAction;
				}
			}
			else if (ehs > 70)
			{
				if (call + 40 + mBet <= mChips)
				{
					mAction = std::make_shared<BetAction>(call + 40);
					mBet += call + 40;

					return mAction;
				}
				else
				{
					if (mChips - mBet > 0)
					{
						mAction = std::make_shared<BetAction>(mChips - mBet);
						mBet = mChips;
					}
					else
					{
						mAction = std::make_shared<CheckAction>();
						mBet = mChips;
					}

					return mAction;
				}
			}
			else if(ehs > 60)
			{
				if (call + 20 + mBet <= mChips)
				{
					mAction = std::make_shared<BetAction>(call + 20);
					mBet += call + 20;

					return mAction;
				}
				else
				{
					if (mChips - mBet > 0)
					{
						mAction = std::make_shared<BetAction>(mChips - mBet);
						mBet = mChips;
					}
					else
					{
						mAction = std::make_shared<CheckAction>();
						mBet = mChips;
					}

					return mAction;
				}
			}
			
			
			

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
