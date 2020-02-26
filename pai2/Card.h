#pragma once
#include <string>
#include "enum.h"
#include <iostream>


BETTER_ENUM(Suit, int,
	SPADE = 0,
	HEART,
	DIAMOND,
	CLUB)

	BETTER_ENUM(FaceValue, int,
		ACE = 0,
		KING,
		QUEEN,
		JACK,
		TEN,
		NINE,
		EIGHT,
		SEVEN,
		SIX,
		FIVE,
		FOUR,
		THREE,
		TWO)

	class Card
{
	short suit;
	short faceValue;
public:
	Card();
	Card(int i, int j);
	int getFaceValue() { return faceValue; }
	int getSuit() { return suit; }
	void setFaceValue(int FaceValue) { faceValue = FaceValue; }
	void setSuit(int Suit) { suit = Suit; }
	std::string toString();
	int toValue() { return faceValue * 4 + suit; };
	~Card() = default;
};

