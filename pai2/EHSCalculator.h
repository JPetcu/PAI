#pragma once
#include <vector>
#include "Player.h"
#include "deck.h"
#include "card.h"

class EHSCalculator
{
	std::vector<std::shared_ptr<Player>> mPlayers;
	std::unique_ptr<Deck> mDeck;

	static std::vector<std::vector<int>> StartingHandRecommendations;
public:
	EHSCalculator(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2);
	int preFlop(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2);
	int decideWinner(std::vector<std::shared_ptr<Card>> mDownCards);
	int handStrength(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2 , std::vector<std::shared_ptr<Card>> downCards);
	void playersReceiveCards();
	void playersThrow();
	~EHSCalculator() = default;
};

