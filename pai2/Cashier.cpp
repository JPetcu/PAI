#include "stdafx.h"
#include "Cashier.h"
#include <algorithm>


Cashier::Cashier(std::vector<std::shared_ptr<Player>>& players) : mPlayerBalance(players.size(), 0), mAllIn(players.size(), 0)
{
	mPlayers = players;
	for(int i=0; i<mPlayers.size();i++)
	{
		mPlayerBalance[i] = mPlayers[i]->getChips();
		mAllIn[i] = 0;
	}
}

void Cashier::allIn(int who)
{
	mAllIn[who - 1] = 1;
}

void Cashier::startOfRound()
{
	for (int i = 0; i<mPlayers.size(); i++)
	{
		mPlayerBalance[i] = mPlayers[i]->getChips();
	}
}

void Cashier::clearBets()
{
	mPlayerBet = std::vector<int>(mPlayerBet.size(), 0);
}

void Cashier::endOfRound(std::vector<int> rank, bool draw, int pot)
{
	
	
	if(!draw) //not draw
	{
		std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());;
		int winner = std::distance(rank.begin(), it);
		if(!mPlayers[winner]->getAllIn())
		{
			for(int i=0;i<mPlayers.size();i++)
			{
				if(i == winner)
				{
					mPlayers[i]->updateChips(pot - mPlayers[i]->getBet());
					for (auto player : mPlayers)
					{
						if (player->getChips() < 0)
						{
							int a = 5;
							std::cout << a;
						}
					}
				}
				else
				{
					for (auto player : mPlayers)
					{
						if (player->getChips() < 0)
						{
							int a = 5;
							std::cout << a;
						}
					}
					if(mPlayers[i]->getChips() - mPlayers[i]->getBet() < 0)
					{
						int a = 5;
						std::cout << a;
					}
					mPlayers[i]->updateChips(mPlayers[i]->getBet()*-1);
					
				}
			}
		}
		else
		{
			rank.erase(it);
			std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());;
			int winner2 = std::distance(rank.begin(), it);
			int allInCounter = 1;
			for(auto player:mPlayers)
			{
				if (player->getAllIn())
					allInCounter++;
			}

			if(allInCounter == 1)
			{
				int winningP1 = 0;
				for (int i = 0; i<mPlayers.size(); i++)
				{
					if (i != winner)
					{
						winningP1 += std::min(mPlayers[i]->getBet(),mPlayers[winner]->getBet());
					}
					else if(i != winner2)
					{
						mPlayers[i]->updateChips(mPlayers[i]->getBet()*-1);
						for (auto player : mPlayers)
						{
							if (player->getChips() < 0)
							{
								int a = 5;
								std::cout << a;
							}
						}
					}
				}
				mPlayers[winner]->updateChips(winningP1);
				for (auto player : mPlayers)
				{
					if (player->getChips() < 0)
					{
						int a = 5;
						std::cout << a;
					}
				}
				mPlayers[winner2]->updateChips(pot - winningP1 - mPlayers[winner2]->getBet());
				for (auto player : mPlayers)
				{
					if (player->getChips() < 0)
					{
						int a = 5;
						std::cout << a;
					}
				}
			}

		}
	}


	mPlayerBet = std::vector<int>(mPlayerBet.size(), 0);
}


Cashier::~Cashier()
{
}
