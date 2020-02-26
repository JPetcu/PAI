#include "stdafx.h"
#include "EHSCalculator.h"
#include <algorithm>
#include "SevenEval/src/SevenEval.h"


EHSCalculator::EHSCalculator(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2)
{
	mPlayers.emplace_back(std::make_shared<Player>());
	mPlayers.emplace_back(std::make_shared<Player>());
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

int EHSCalculator::decideWinner(std::vector<Card> mDownCards)
{
	std::vector<int> rank;
	for (auto player : mPlayers)
	{
		rank.emplace_back( SevenEval::GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue(), mDownCards[3]->toValue(), mDownCards[4]->toValue()));
	}
	std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());
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

int EHSCalculator::handStrength(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2,
	std::vector<std::shared_ptr<Card>> downCards)
{
	int ahead = 0, tied = 0, behind = 0;
	int i = 0;
	mPlayers[0]->receiveCard(card1);
	mPlayers[0]->receiveCard(card2);

	while(i<2000)
	{
		mDeck->shuffle();
		playersReceiveCards();
		while(downCards.size() < 5)
		{
			downCards.emplace_back(mDeck->draw());
		}
		int winner = decideWinner(downCards);
		playersThrow();
		i++;
	}

	return 0;
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

