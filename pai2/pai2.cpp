// pai.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "Deck.h"
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Game.h"
int Player::spNo = 1;


int main()
{
	std::srand(unsigned(std::time(0)));
	std::vector<int> winners = { 0 , 0 , 0, 0 };
	int i = 0;

	for (int j = 0; j < 20; j++)
	{
		Player::spNo = 1;
		std::shared_ptr<Game> mGame(new Game());
		while (!mGame->getOver())
		{
			mGame->playRound();
			i++;
		}
		winners[mGame->getWinner()]++;
		std::vector<int> counter = mGame->returnCounter();
		std::cout << "------------------------------\n";
		for (auto a : counter)
			std::cout << a << " ";
		std::cout << "------------------------------\n";
	}
	std::cout << "\n\n";
	for (auto a : winners)
		std::cout << a << " ";
	std::cout << "\nNumber of rounds played: " << i << "\n";

	return 0;
}

