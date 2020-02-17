// pai.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "Deck.h"
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Game.h"


int main()
{
	std::srand(unsigned(std::time(0)));
	std::shared_ptr<Game> mGame(new Game());
	int i = 0;
	while (!mGame->getOver())
	{
		mGame->init();
		i++;
	}
	std::cout << "\nNumber of rounds played: " << i<<"\n";
	return 0;
}

