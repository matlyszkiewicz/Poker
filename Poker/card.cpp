/**
	Texas holdem poker card class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#include "card.hpp"

Card::Card(int suit = randomInteger(0, 4), int value = randomInteger(0, 12)) {
	this->suit = suit;
	this->value = value;
}

Card::Card(const Card& cardToCopy) {
	this->suit = cardToCopy.getSuit();
	this->value = cardToCopy.getValue();
}

int Card::getSuit() const {
	return suit;
}

int Card::getValue() const {
	return value;
}

std::ostream& operator<<(std::ostream& ostream, const Card& card) {

	std::string suit;
	std::string value;

	switch (card.getSuit()) {
	case Card::Suits::club:
		suit = "club";
		break;
	case Card::Suits::diamond:
		suit = "diamond";
		break;
	case Card::Suits::heart:
		suit = "heart";
		break;
	case Card::Suits::spade:
		suit = "spade";
		break;
	}

	switch (card.getValue()) {
	case Card::Values::ace:
		value = "ace";
		break;
	case Card::Values::king:
		value = "king";
		break;
	case Card::Values::queen:
		value = "queen";
		break;
	case Card::Values::jack:
		value = "jack";
		break;
	case Card::Values::ten:
		value = "ten";
		break;
	case Card::Values::nine:
		value = "nine";
		break;
	case Card::Values::eight:
		value = "eight";
		break;
	case Card::Values::seven:
		value = "seven";
		break;
	case Card::Values::six:
		value = "six";
		break;
	case Card::Values::five:
		value = "five";
		break;
	case Card::Values::four:
		value = "four";
		break;
	case Card::Values::three:
		value = "three";
		break;
	case Card::Values::two:
		value = "two";
		break;
	}

	return ostream << "[Suit: " << suit << ",\tvalue: " << value << "]\n";
}