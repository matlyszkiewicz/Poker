/**
	Texas holdem poker card class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#ifndef _card
#define _card

#include <iostream>
#include <string>
#include "random_integer.hpp"



class Card {

	static const int suitsSize{ 4 };
	static const int valuesSize{ 12 };

	int suit;
	int value;

	friend std::ostream& operator<<(std::ostream& ostream, const Card& card);

public:

	enum Suits {
		club = 0,
		diamond = 1,
		heart = 2,
		spade = 3
	};
	enum Values {
		two = 0,
		three = 1,
		four = 2,
		five = 3,
		six = 4,
		seven = 5,
		eight = 6,
		nine = 7,
		ten = 8,
		jack = 9,
		queen = 10,
		king = 11,
		ace = 12
	};

	Card(int suit, int value);

	Card(const Card&);

	int getSuit() const;

	int getValue() const;

	inline static constexpr int getSuitsSize() {
		return suitsSize;
	}

	inline static constexpr int getValuesSize() {
		return valuesSize;
	}
};

#endif