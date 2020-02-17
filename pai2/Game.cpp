#include "stdafx.h"
#include "Game.h"
#include "SevenEval/src/SevenEval.h"
#include <algorithm>


Game::Game() : mDeck(new Deck())
{
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
}

void Game::init()
{
	for (auto player : mPlayers)
		player->receiveCard(mDeck->draw());
	for (auto player : mPlayers)
		player->receiveCard(mDeck->draw());

	std::shared_ptr<Card> deadCard = mDeck->draw();
	mDownCards.emplace_back(mDeck->draw());
	mDownCards.emplace_back(mDeck->draw());
	mDownCards.emplace_back(mDeck->draw());
	deadCard = mDeck->draw();
	mDownCards.emplace_back(mDeck->draw());
	deadCard = mDeck->draw();
	mDownCards.emplace_back(mDeck->draw());

	int i = 0;
	std::vector<int> rank = { 0, 0, 0, 0, 0 };
	for(auto player:mPlayers)
	{
		rank[i++] = SevenEval::GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue(), mDownCards[3]->toValue(), mDownCards[4]->toValue());
	}
	std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());
	showGame();
	std::cout << "\nWinner is Player" << std::distance(rank.begin(), it) + 1 << "\n";
	int k = 0;
	std::cout << "-------------------------------------\n";
	for (auto player : mPlayers)
	{
		if (player->getChips() >= 1600)
			over = true;
		if (k == std::distance(rank.begin(), it))
			player->updateChips((mPlayers.size()-1) * 20);
		else
			player->updateChips(-20);
		player->throwCards();
		k++;

		std::cout << "Player" << k << "has: ";
		player->printBalance();

	}
	std::vector<std::shared_ptr<Player>>::iterator toBeErased = mPlayers.end();
	for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
	{
		if ((*it)->getChips() <= 0)
			toBeErased = it;
	}
	if(toBeErased != mPlayers.end())
		mPlayers.erase(toBeErased);
	std::cout << "-------------------------------------\n";

	mDownCards.clear();
	mDeck->shuffle();
	
	


}

void Game::showGame()
{
	int i = 1;
	for(auto player : mPlayers)
	{
		std::cout << "Player" << i++ << ": " << player->showCards() << "\n";
	}
	std::cout << "Cards: ";
	for (auto card : mDownCards)
		std::cout << card->toString() << ", ";
}

bool Game::getOver()
{
	return over;
}

Game::~Game()
{
}
