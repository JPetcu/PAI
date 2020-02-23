#include "stdafx.h"
#include "Card.h"
#include <iostream>


std::string Card::toString()
{
	std::string a(FaceValue::_from_integral(faceValue)._to_string());
	//std::cout << static_cast<std::underlying_type<Suit>::type>((static_cast<Suit>(suit)));
	a = a + " " + Suit::_from_integral(suit)._to_string();

	return a;
}
Card::Card(int i, int j)
{
	suit = i;
	faceValue = j;
	//std::cout << "Created a Card: " << this->toString();

}

Card::Card()
{
}



