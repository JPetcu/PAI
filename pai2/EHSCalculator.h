#pragma once
#include <vector>

#include "deck.h"
#include "card.h"
#include <memory>
#include "Player.h"

class Player;
class EHSCalculator
{
	std::vector<std::shared_ptr<Player>> mPlayers;
	std::unique_ptr<Deck> mDeck;

	static std::vector<std::vector<int>> StartingHandRecommendations;
public:
	EHSCalculator(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2);
	int preFlop(std::shared_ptr<Card> card1, std::shared_ptr<Card> card2);
	int decideWinner7(std::vector<std::shared_ptr<Card>> mDownCards);
	int decideWinner5(std::vector<std::shared_ptr<Card>> mDownCards);

	double handStrength(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2 , std::vector<std::shared_ptr<Card>> downCards);
	std::pair<double,double> handPotential(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2, std::vector<std::shared_ptr<Card>> downCards);
	double  handStrengthFlop(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2, std::vector<std::shared_ptr<Card>> downCards);
	void playersReceiveCards();
	void playersThrow();
	double EHS(std::shared_ptr<Card>& card1, std::shared_ptr<Card>& card2, std::vector<std::shared_ptr<Card>> downCards);
	~EHSCalculator() = default;
};

