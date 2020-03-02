#include "stdafx.h"
#include "EHSCalculator.h"
#include <algorithm>
#include "SevenEval/src/SevenEval.h"
#include "SevenEval/src/FiveEval.h"
#include "Card.h"


EHSCalculator::EHSCalculator(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2)
{
	mPlayers.emplace_back(std::make_shared<Player>());
	mPlayers.emplace_back(std::make_shared<Player>());
	mDeck = ::std::make_unique<Deck>();

}

int EHSCalculator::preFlop(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2)
{
	int maxCard = 12;

	int value = card1->getSuit() == card2->getSuit()
		? (card1->getFaceValue() > card2->getFaceValue()
			? StartingHandRecommendations[ (int)card1->getFaceValue()][ (int)card2->getFaceValue()]
			: StartingHandRecommendations[  (int)card2->getFaceValue()][   (int)card1->getFaceValue()])
		: (card1->getFaceValue() > card2->getFaceValue()
			? StartingHandRecommendations[  (int)card2->getFaceValue()][   (int)card1->getFaceValue()]
			: StartingHandRecommendations[  (int)card1->getFaceValue()][   (int)card2->getFaceValue()]);

	return value;
}

int EHSCalculator::decideWinner7(std::vector<std::shared_ptr<Card>> mDownCards)
{
	std::vector<uint16_t> rank;
	for (auto player : mPlayers)
	{
		rank.emplace_back( SevenEval::GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue(), mDownCards[3]->toValue(), mDownCards[4]->toValue()));
	}
	std::vector<uint16_t>::iterator it = std::max_element(rank.begin(), rank.end());
	if(std::distance(rank.begin(), it) != 0)
	{
		return 3;
	}
	bool draw = false;
	for (auto it2 = rank.begin(); it2 != rank.end(); it2++)
	{
		if (*it == *it2 && mPlayers.size() != 1 && it2 != it)
			return -1;

	}
	return 0;
	
}

int EHSCalculator::decideWinner5(std::vector<std::shared_ptr<Card>> mDownCards)
{

	std::vector<int> rank;
	for (auto player : mPlayers)
	{
		std::shared_ptr<FiveEval> five(new FiveEval());
		
		rank.emplace_back(five->GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue()));
	}
	std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());
	if (std::distance(rank.begin(), it) != 0)
	{
		return 3;
	}
	bool draw = false;
	for (auto it2 = rank.begin(); it2 != rank.end(); it2++)
	{
		if (*it == *it2 && mPlayers.size() != 1 && it2 != it)
			return -1;

	}
	return 0;
}

double EHSCalculator::handStrength(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2,
	std::vector<std::shared_ptr<Card>> downCards)
{
	double ahead = 0, tied = 0, behind = 0;
	int i = 0;
	mPlayers[0]->receiveCard(card1);
	mPlayers[0]->receiveCard(card2);

	while(i<500)
	{
		mDeck->shuffle();
		playersReceiveCards();
		
		int winner = decideWinner5(downCards);
		if(winner == 0)
		{
			ahead++;
		}
		else if(winner == -1)
		{
			tied++;
		}
		else
		{
			behind++;
		}
		playersThrow();
		i++;
	}

	return (ahead + tied/2) / (ahead + tied+ behind);
}

std::pair<double,double> EHSCalculator::handPotential(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2,
	std::vector<std::shared_ptr<Card>> downCards)
{
	int i = 0;
	int ahead = 0, tied = 1, behind = 2;
	double HP[3][3] =  { {0 , 0, 0},{ 0 , 0, 0 },{ 0 , 0, 0 }};
	double HPTotal[3] = { 0, 0 , 0};
	mPlayers[0]->receiveCard(card1);
	mPlayers[0]->receiveCard(card2);
	int index;
	int size = downCards.size();
	std::vector<std::shared_ptr<Card>> mDownCards = downCards;
	

	while (i < 100)
	{
		mDeck->shuffle();
		playersReceiveCards();

		if (preFlop(mPlayers[0]->getCard1(), mPlayers[0]->getCard2()) > preFlop(mPlayers[1]->getCard1(), mPlayers[1]->getCard2()))
			index = 0;
		else if (preFlop(mPlayers[0]->getCard1(), mPlayers[0]->getCard2()) == preFlop(mPlayers[1]->getCard1(), mPlayers[1]->getCard2()))
			index = 1;
		else if (preFlop(mPlayers[0]->getCard1(), mPlayers[0]->getCard2()) < preFlop(mPlayers[1]->getCard1(), mPlayers[1]->getCard2()))
			index = 2;
		HPTotal[index] += 1;

		int j = 0;
		while (j < 25)
		{
			while (mDownCards.size() < 5)
			{
				mDownCards.emplace_back(mDeck->draw());
			}
			int winner = decideWinner7(mDownCards);
			if (winner == 0)
				HP[index][0] += 1;
			else if (winner == -1)
				HP[index][1] += 1;
			else
				HP[index][2] += 1;



			mDownCards = downCards;
			j++;

		}

		playersThrow();


		i++;
	}
	double  Ppot = 0, Npot = 0;
	if(HPTotal[behind] + HPTotal[tied] != 0)
	  Ppot = double((HP[behind][ahead] + HP[behind][tied] / 2 + HP[tied][ahead] / 2) / (HPTotal[behind] + HPTotal[tied]));
		// Npot: were ahead but fell behind
	if(HPTotal[ahead] + HPTotal[tied] != 0 )
	 	Npot = (HP[ahead][behind] + HP[tied][behind] / 2 + HP[ahead][tied] / 2) / (HPTotal[ahead] + HPTotal[tied]);

	return std::make_pair(Ppot, Npot);
}

double EHSCalculator::handStrengthFlop(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2,
	std::vector<std::shared_ptr<Card>> downCards)
{
	double ahead = 0, tied = 0, behind = 0;
	int i = 0;
	mPlayers[0]->receiveCard(card1);
	mPlayers[0]->receiveCard(card2);

	while (i<1000)
	{
		mDeck->shuffle();
		playersReceiveCards();
		while (downCards.size() < 5)
		{
			downCards.emplace_back(mDeck->draw());
		}
		int winner = decideWinner5(downCards);
		if (winner == 0)
		{
			ahead++;
		}
		else if (winner == -1)
		{
			tied++;
		}
		else
		{
			behind++;
		}
		playersThrow();
		i++;
	}

	return (ahead + tied / 2) / (ahead + tied + behind);
}

void EHSCalculator::playersReceiveCards()
{
	for(int i =1; i<mPlayers.size();i++)
	{
		mPlayers[i]->receiveCard(mDeck->draw());
	}
	for (int i = 1; i<mPlayers.size(); i++)
	{
		mPlayers[i]->receiveCard(mDeck->draw());
	}
}

void EHSCalculator::playersThrow()
{
	for (int i = 1; i<mPlayers.size(); i++)
	{
		mPlayers[i]->throwCards();
	}
}

double EHSCalculator::EHS(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2,
	std::vector<std::shared_ptr<Card>> downCards)
{
	double HS = handStrength(card1, card2, downCards);
	std::pair<double, double> Pot = handPotential(card1, card2, downCards);
	std::cout << "\n Positive potential: " << Pot.first << "\nNegative potential: " << Pot.second << "\n";

	return HS * (1 - Pot.second) + (1 - HS) * Pot.first;
}

