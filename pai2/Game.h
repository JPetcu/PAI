#pragma once
#include <memory>
#include "Deck.h"
#include "Player.h"


class Game
{
	std::unique_ptr<Deck> mDeck;
	std::vector<std::shared_ptr<Player>> mPlayers;
	std::vector<std::shared_ptr<Card>> mDownCards;
	int smallBlind = 10, bigBlind = 20, turn = 0;
	bool over = false;
	int winner;
public:
	Game();
	void init();
	void showGame();
	bool getOver();
	int getWinner();
	~Game();
};

