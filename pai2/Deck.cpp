#include "stdafx.h"
#include "deck.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <memory>

long long myrandom(int i) { return ((std::rand()*std::rand() % i)*std::rand() % i)*std::rand()*12%i; }
Deck::Deck() : currentCard(0)
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<13; j++)
		{
			mCards.emplace_back(new Card(i, j));
		}
	}

	this->shuffle();

}
void Deck::print()
{
	for (auto card : mCards)
		std::cout << card->toString() << "\n";
}

void Deck::shuffle()
{
	std::random_shuffle(mCards.begin(), mCards.end(), myrandom);
	currentCard = 0;
}

std::shared_ptr<Card> Deck::draw()
{
	if(currentCard!=53)
		return mCards[currentCard++];
	return nullptr;
}


Deck::~Deck()
{
}
