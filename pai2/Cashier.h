#pragma once
#include <vector>
#include <memory>
#include "Player.h"

class Player;
class Cashier
{
	std::vector<std::shared_ptr<Player>> mPlayers;
	std::vector<int>					 mPlayerBalance;
	std::vector<int>					 mPlayerBet, mAllIn;
	int mPot;
public:
	Cashier(std::vector<std::shared_ptr<Player>>& players);
	void allIn(int who);
	void startOfRound();
	void clearBets();
	void endOfRound(std::vector<int> rank, bool draw, int pot);
	~Cashier();
};

