/**
	Texas holdem poker player class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#ifndef _player
#define _player

#include <vector>
#include "random_integer.hpp"
#include "poker_hand.hpp"

#include <iostream>

/*
	Class represents player. The main player can set actual move, the opponent
	for main player has implemented	getNextStep function, which allow simulates
	next move taking into account cards and money on the table.
 */
class Player {

public:

	/**
		Enum with kinds of player move.
	*/
	enum Move {
		none,
		call,
		raise,
		allIn,
		fold
	};

private:

	int money;
	int actualBid;

	int moneyCoefficient;
	int strongCardCoefficient;
	int summaryLuckCoefficient;

	std::vector<Card*> playerCardStack;
	PokerHand pokerHand;
	Move actualStatus;

public:

	Player(int money);



	void addMoney(int money);

	void subMoney(int money);

	int getMoney();

	int getActualBid();

	void resetActualBid();



	/**
		Member function which updates player's luck coefficient.
		@param moneyOnTheTable - Amount of money which is actual on the table.
		@param cardsOnTheTable - Stack od cards from table.
	*/
	void updateLuckCoefficient(int moneyOnTheTable, std::vector<Card*>& cardsOnTheTable);

	int getMoneyCoefficient();

	int getStrongCardCoefficient();

	int getLuckCoefficient();



	/**
		Manually sets player status.
		@param status - New player status.
	*/
	void setActualStatus(Move status);

	void resetActualStatus();

	Move getActualStatus();

	/**
		Simulates player's decision and returns next move.
		@param moneyOnTheTable - Amount of money which is actual on the table.
		@param cardsOnTheTable - Stack od cards from table.
		@return - Next player's move.
	*/
	Move getNextStep(int moneyOnTheTable, std::vector<Card*>& cardsOnTheTable);



	/**
		Adds card to player's card stack.
		@param numberOfCards - Number of new cards.
		@param deckOfCards - Cards from which new cards will be selected.
	*/
	void addCard(int numberOfCards, std::vector<Card*>& deckOfCards);

	std::vector<Card*>& getCardStack();

	void deleteStackOfCards();



	/**
		Updates player's poker hand rank.
		@param cardsOnTable - Additional cards from table.
		@return Player's poker hand.
	*/
	PokerHand::HandRanking updateHand(std::vector<Card*>& cardsOnTable);

	PokerHand& getPokerHand();

	~Player();
};

#endif