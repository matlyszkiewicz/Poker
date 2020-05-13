/**
 * Texas holdem poker game table.
 *
 * @author  Mateusz £yszkiewicz
 * @version 1.0
 * @since   2020 - 02 - 05
 * 
 * Class represents deck of the card and cards stack one the table
 * (flop, turn and river). Moreover class encapsulates variables to
 * sorage money on the table and actual bid, which is the highest bid
 * in the game.
 */

#include "table.hpp"



void Table::generateDeckOfCards() {
	for (int i = 0; i < Card::getSuitsSize(); i++)
		for (int j = 0; j < Card::getValuesSize(); j++)
			deckOfCards.push_back(new Card(i, j));
}

void Table::deleteDeckOfCards() {
	for (auto cardIterator = deckOfCards.rbegin(); cardIterator != deckOfCards.rend(); ++cardIterator) {
		delete *cardIterator;
		*cardIterator = nullptr;
	}
	deckOfCards.clear();
}

void Table::deleteCardsOnTable() {
	for (auto cardIterator = cardsOnTable.rbegin(); cardIterator != cardsOnTable.rend(); ++cardIterator) {
		delete *cardIterator;
		*cardIterator = nullptr;
	}
	cardsOnTable.clear();
}



void Table::addMoney(int money) {
	moneyOnTable += money;
}

int Table::getMoney() {
	return moneyOnTable;
}

void Table::resetMoney() {
	moneyOnTable = 0;
}

void Table::setActualBid(int money) {
	actualBid = money;
}

int Table::getActualBid() {
	return actualBid;
}

void Table::resetActualBid() {
	actualBid = 0;
}



void Table::addCardToTable(int numberOfCards) {

	if (numberOfCards < 1 || (int)deckOfCards.size() < numberOfCards)
		throw "Not enought of cards!!!";

	std::vector<Card*>::iterator drawnCard;
	for (int i = 0; i < numberOfCards; i++) {
		drawnCard = deckOfCards.begin() + randomInteger(0, (int)deckOfCards.size() - 1);
		cardsOnTable.push_back(*drawnCard);
		deckOfCards.erase(drawnCard);
	}
}

std::vector<Card*>& Table::getCardsFromTable() {
	return cardsOnTable;
}

std::vector<Card*>& Table::getDeckOfCards() {
	return deckOfCards;
}

Table::~Table() {
	deleteDeckOfCards();
}