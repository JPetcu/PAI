#pragma once
#include"card.h"
#include <vector>
#include <memory>


class Deck
{
	std::vector<std::shared_ptr<Card>> mCards;
	int currentCard;
public:
	Deck();
	~Deck();
	void print();
	void shuffle();
	std::shared_ptr<Card> draw();
};


