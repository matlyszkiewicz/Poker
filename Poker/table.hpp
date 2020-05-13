/**
	Texas holdem poker game table.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#ifndef _table
#define _table

#include <vector>
#include "card.hpp"
#include "player.hpp"
#include "poker_hand.hpp"

/*
	Class represents deck of the card and cards stack one the table
	(flop, turn and river). Moreover class encapsulates variables to
	sorage money on the table and actual bid, which is the highest bid
	in the game.
*/
class Table {

	int moneyOnTable;
	int actualBid;
	std::vector<Card*> deckOfCards;
	std::vector<Card*> cardsOnTable;

public:

	void generateDeckOfCards();

	void deleteDeckOfCards();

	void deleteCardsOnTable();

	void addMoney(int money);

	int getMoney();

	void resetMoney();

	int getActualBid();

	void setActualBid(int money);

	void resetActualBid();

	void addCardToTable(int numberOfCards);

	std::vector<Card*>& getCardsFromTable();

	std::vector<Card*>& getDeckOfCards();

	~Table();
};

#endif