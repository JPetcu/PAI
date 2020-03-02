#pragma once
#include <string>
#include "enum.h"
#include <iostream>


BETTER_ENUM(Suit, int,
	SPADE = 0,
	HEART, //1
	DIAMOND,//2
	CLUB)//3

	BETTER_ENUM(FaceValue, int,
		ACE = 0,
		KING,    //1
		QUEEN,   //2
		JACK,    //3
		TEN,	//4	
		NINE,	//5
		EIGHT,	//6
		SEVEN,	//7
		SIX,	//8
		FIVE,	//9
		FOUR,	//10
		THREE,	//11
		TWO)	//12

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

