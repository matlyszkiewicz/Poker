/**
	Getting best hand from player's card stack.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#ifndef _poker_hand
#define _poker_hand

#include <vector>
#include "card.hpp"

/**
	This class provides best hand from player and table cards.
	Class require manual update result by calling member function.

	Additionally, class allows to compare two players' results. Better
	result will be chosen with better cards of hand ranking (from two
	straights better is this one, which has the strongest card).
*/
class PokerHand {
public:

	/** 
		Enum with the kind of the card hands.
	*/
	enum HandRanking {
		none = 0,
		highCard = 1,
		pair = 2,
		twoPair = 3,
		threeOfAKind = 4,
		straight = 5,
		flush = 6,
		fullHouse = 7,
		fourOfAKind = 8,
		straightFlush = 9,
		royalFlush = 10
	};

private:
	/**
		Static table with temporary player's all cards presented binary by bool type.
	*/
	static bool cardStatus[Card::getSuitsSize()][Card::getValuesSize()];

	HandRanking hand;

	int firstRankValue;
	int secondRankValue;

	/**
		Clears binary table with cards status.
	*/
	void clearCardStatus();

	/**
		Checks which hand is the best of player's cards.
		Member function call functions with update firstRankValue and secondRankValue.
	*/
	void handChecker();

	/**
		Checks if royal flush is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return-  Royal flush is hand.
	*/
	bool isRoyalFlush(bool update);

	/**
		Checks if straight flush is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Straight flush is hand.
	*/
	bool isStraightFlush(bool update);


	/**
		Checks if four of a kind is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Four of a kind is hand.
	*/
	bool isFourOfAKind(bool update);

	/**
		Checks if full house is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Full house is hand.
	*/
	bool isFullHouse(bool update);

	/**
		Checks if flush is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Flush is hand.
	*/
	bool isFlush(bool update);

	/**
		Checks if straight is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Straight is hand.
	*/
	bool isStraight(bool update);

	/**
		Checks if three of a kind is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Three of a kind is hand.
	*/
	bool isThreeOfAKind(bool update);
	
	/**
		Checks if two pair is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - Two pair is hand.
	*/
	bool isTwoPair(bool update);

	/**
		Checks if one pair is hand.
		@param update - Update firstRankValue and secondRankValue.
		@return - One pair is hand.
	*/
	bool isOnePair(bool update);

	/**
		Checks player's the best card.
	*/
	void updateBestPlayerCard();

public:

	/**
		Updates the best hand. 
		@param cardStack - Player's card stack std::vector.
		@return - The best hand.
	*/
	HandRanking updateCardStatus(std::vector<Card*>& cardStack);

	/**
		Updates the best hand.
		@param cardStack - Player's card stack std::vector.
		@param cardsOnTable - Table card stack std::vector.
		@return - The best hand.
	*/
	HandRanking updateCardStatus(std::vector<Card*>& playerCardStack, std::vector<Card*>& cardsOnTable);

	/**
		Comparates two player's poker hands.
		@param pokerHandRanking - Player's hand.
		@return - Comparison status.
	*/
	int isBetter(PokerHand& pokerHandRanking);

	/**
		Returns actual hand.
		@return - Actual hand.
	*/
	HandRanking getHand();

	/**
		Returns the value of the best card from hand.
		@return - Value of the best card.
	*/
	int getFirstRankValue();

	/**
		Returns the value of second the best card from hand.
		@return - Value of the second best card.
	*/
	int getSecondRankValue();

};

#endif