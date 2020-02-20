#pragma once
#include <memory>
#include "Deck.h"
#include "Player.h"


class Game
{
	std::unique_ptr<Deck> mDeck;
	std::vector<std::shared_ptr<Player>> mPlayers;
	std::vector<std::shared_ptr<Card>> mDownCards;
	std::vector<int> cardCounter;
	int smallBlind = 10, bigBlind = 20, turn = 0;
	bool over = false;
	int winner,mPot = 0, playerTurn = 0;
	

public:
	Game();
	std::vector<int> returnCounter()  { return cardCounter; }
	void initGame();
	void dealFlop();
	void dealTurn();
	void dealRiver();
	void erasePlayers();
	void clearRound();
	void playRound();
	int decideWinner();
	void showWinner();
	void updateChips();
	void showGame();
	bool getOver();
	int getWinner();
	std::shared_ptr<Action> requestAction(std::shared_ptr<Player> player);
	void requestAction();
	void sendDownCards();
	bool canContinue(std::vector<std::shared_ptr<Action>> actions);
	int getTurn();
	int currentTurn();
	~Game();
};

