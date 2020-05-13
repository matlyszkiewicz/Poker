/**
	Getting best hand from player's card stack.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05

	This class provides best hand from player and table cards.
	Class require manual update result by call member function.

	Additionally, class allows to compare two players' results. Better
	result will be chosen with better cards of hand ranking (from two
	straights better is this one, which has the strongest card).
*/

#include "poker_hand.hpp"


// Static table with temporary player's all cards present binary by bool type.
bool PokerHand::cardStatus[Card::getSuitsSize()][Card::getValuesSize()];

// Clears binary table with cards status.
void PokerHand::clearCardStatus() {
	for (int i = 0; i < Card::getSuitsSize(); i++)
		for (int j = 0; j < Card::getValuesSize(); j++)
			cardStatus[i][j] = false;
}

// Checks which hand is the best of player's cards.
void PokerHand::handChecker() {

	if (isRoyalFlush(true))
		hand = HandRanking::royalFlush;
	else if (isStraightFlush(true))
		hand = HandRanking::straightFlush;
	else if (isFourOfAKind(true))
		hand = HandRanking::fourOfAKind;
	else if (isFullHouse(true))
		hand = HandRanking::fullHouse;
	else if (isFlush(true))
		hand = HandRanking::flush;
	else if (isStraight(true))
		hand = HandRanking::straight;
	else if (isThreeOfAKind(true))
		hand = HandRanking::threeOfAKind;
	else if (isTwoPair(true))
		hand = HandRanking::twoPair;
	else if (isOnePair(true))
		hand = HandRanking::pair;
	else {
		updateBestPlayerCard();
		hand = HandRanking::highCard;
	}
}

// Checks if royal flush is hand.
bool PokerHand::isRoyalFlush(bool update = false) {

	bool isRoyalFlush;

	for (int i = 0; i < Card::getSuitsSize(); i++) {
		for (int j = Card::Values::ten; j < Card::getValuesSize(); j++) {

			if (!cardStatus[i][j]) {
				isRoyalFlush = false;
				break;
			}
			else if (j == Card::Values::ten && cardStatus[i][j])
				isRoyalFlush = true;
			else
				isRoyalFlush &= true;
		}
		if (isRoyalFlush)
			break;
	}

	return isRoyalFlush;
}

// Checks if straight flush is hand.
bool PokerHand::isStraightFlush(bool update = false) {

	bool isStraightlFlush = false;

	int cardsInRow = 0;
	bool firstCard = true;

	for (int i = 0; i < Card::getSuitsSize(); i++) {
		for (int j = Card::Values::ace; j >= 0; j--) {
			if (cardStatus[i][j])
				cardsInRow++;
			else {
				cardsInRow = 0;
				continue;
			}

			if (cardsInRow == 5) {
				isStraightlFlush = true;
				if (update)
					firstRankValue = j + 4;
				break;
			}
		}
		if (isStraightlFlush) {
			break;
		}
		else
			cardsInRow = 0;

	}

	return isStraightlFlush;
}

// Checks if four of a kind is hand.
bool PokerHand::isFourOfAKind(bool update = false) {

	bool isFourOfAKind = false;

	int cardsInRow = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {
			if (cardStatus[i][j]) {
				if (cardsInRow < 3)
					cardsInRow++;
				else {
					isFourOfAKind = true;
					if (update)
						firstRankValue = j;
					break;
				}
			}
			else
				break;
		}

		if (isFourOfAKind)
			break;
		else
			cardsInRow = 0;
	}

	return isFourOfAKind;
}

// Checks if full house is hand.
bool PokerHand::isFullHouse(bool update = false) {

	bool isFullHouse = false;
	bool twoPair = false;
	bool threeOfAKind = false;

	int cardsInRow = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {
			if (cardStatus[i][j]) {
				if (cardsInRow < 2)
					cardsInRow++;
				else {
					cardsInRow++;
					threeOfAKind = true;
					if (update)
						firstRankValue = j;
					break;
				}
			}
		}

		if (cardsInRow >= 2 && threeOfAKind) {
			twoPair = true;
			if (update)
				secondRankValue = j;
		}

		if (threeOfAKind && twoPair) {
			isFullHouse = true;
			break;
		}
		else
			cardsInRow = 0;
	}

	return isFullHouse;
}

//Checks if flush is hand.
bool PokerHand::isFlush(bool update = false) {

	bool isFlush = false;

	bool firstCard = true;
	int colorCount = 0;

	for (int i = 0; i < Card::getSuitsSize(); i++) {
		for (int j = Card::Values::ace; j >= 0; j--) {
			if (cardStatus[i][j]) {
				if (firstCard) {
					if (update)
						firstRankValue = j;
					firstCard = false;
				}
				colorCount++;
			}
			if (colorCount == 5) {
				isFlush = true;
				break;
			}

		}

		if (isFlush)
			break;
		else {
			colorCount = 0;
			firstCard = true;
		}
	}

	return isFlush;
}

// Checks if straight is hand.
bool PokerHand::isStraight(bool update = false) {

	bool isStraight = false;

	int cardsInRow = 0;
	int cardsInRowPrev = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {

			if (cardStatus[i][j]) {
				cardsInRow++;
				break;
			}
		}

		if (cardsInRow == 5) {
			isStraight = true;
			if (update)
				firstRankValue = j;
			break;
		}

		if (isStraight)
			break;
		else if (cardsInRow == cardsInRowPrev)
			cardsInRow = 0;

		cardsInRowPrev = cardsInRow;
	}

	return isStraight;
}

// Checks if three of a kind is hand.
bool PokerHand::isThreeOfAKind(bool update = false) {

	bool isThreeOfAKind = false;

	int cardsInRow = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {
			if (cardStatus[i][j]) {
				if (cardsInRow < 2)
					cardsInRow++;
				else {
					isThreeOfAKind = true;
					if (update)
						firstRankValue = j;
					break;
				}
			}
		}

		if (isThreeOfAKind)
			break;
		else
			cardsInRow = 0;
	}

	return isThreeOfAKind;
}

// Checks if two pair is hand.
bool PokerHand::isTwoPair(bool update = false) {

	bool isTwoPair = false;
	bool firstPair = false;
	bool secondPair = false;

	int cardsInRow = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {
			if (cardStatus[i][j]) {
				if (cardsInRow < 1)
					cardsInRow++;
				else {
					if (!firstPair) {
						firstPair = true;
						if (update)
							firstRankValue = j;
						cardsInRow = 0;
					}
					else if (firstPair && !secondPair) {
						secondPair = true;
						if (update)
							secondRankValue = j;
						break;
					}
				}
			}
		}

		if (firstPair && secondPair) {
			isTwoPair = true;
			break;
		}
		else
			cardsInRow = 0;
	}

	return isTwoPair;
}

// Checks if one pair is hand.
bool PokerHand::isOnePair(bool update = false) {

	bool isOnePair = false;

	bool firstCard = true;
	int cardsInRow = 0;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++) {
			if (cardStatus[i][j]) {
				if (firstCard) {
					firstCard = false;
					if (update)
						secondRankValue = j;
				}
				if (cardsInRow < 1)
					cardsInRow++;
				else {
					isOnePair = true;
					if (update)
						firstRankValue = j;
					break;
				}
			}
		}

		if (isOnePair)
			break;
		else
			cardsInRow = 0;
	}

	return isOnePair;
}

// Checks player's the best card.
void PokerHand::updateBestPlayerCard() {

	bool isUpdate = false;

	for (int j = Card::Values::ace; j >= 0; j--) {
		for (int i = 0; i < Card::getSuitsSize(); i++)
			if (cardStatus[i][j]) {
				firstRankValue = j;
				isUpdate = true;
				break;
			}
		if (isUpdate)
			break;
	}
}

// Updates the best hand. 
PokerHand::HandRanking PokerHand::updateCardStatus(std::vector<Card*>& cardStack) {

	clearCardStatus();

	for (Card*& card : cardStack)
		cardStatus[card->getSuit()][card->getValue()] = true;

	handChecker();

	return hand;
}

// Updates the best hand. 
PokerHand::HandRanking PokerHand::updateCardStatus(std::vector<Card*>& playerCardStack, std::vector<Card*>& cardsOnTable) {

	clearCardStatus();

	for (Card*& card : playerCardStack)
		cardStatus[card->getSuit()][card->getValue()] = true;

	for (Card*& card : cardsOnTable)
		cardStatus[card->getSuit()][card->getValue()] = true;

	handChecker();

	return hand;
}

// Comparates two player's poker hands.
int PokerHand::isBetter(PokerHand& pokerHandRanking) {

	int isBetter = 0;

	if (hand > pokerHandRanking.hand)
		isBetter = 1;
	else if (hand < pokerHandRanking.hand)
		isBetter = -1;
	else
		switch (hand) {
		case HandRanking::straightFlush:
		case HandRanking::fourOfAKind:
		case HandRanking::flush:
		case HandRanking::straight:
		case HandRanking::threeOfAKind:
		case HandRanking::highCard:
			if (firstRankValue > pokerHandRanking.getFirstRankValue())
				isBetter = 1;
			else if (firstRankValue == pokerHandRanking.getFirstRankValue())
				isBetter = 0;
			else
				isBetter = -1;
			break;
		case HandRanking::fullHouse:
		case HandRanking::twoPair:
		case HandRanking::pair:
			if (firstRankValue > pokerHandRanking.getFirstRankValue())
				isBetter = 1;
			else if (firstRankValue == pokerHandRanking.getFirstRankValue()) {
				if (secondRankValue > pokerHandRanking.getSecondRankValue())
					isBetter = 1;
				else if (secondRankValue == pokerHandRanking.getSecondRankValue())
					isBetter = 0;
				else
					isBetter = -1;
			}
			else
				isBetter = -1;
			break;
		}

	return isBetter;
}

PokerHand::HandRanking PokerHand::getHand() {
	return hand;
}

int PokerHand::getFirstRankValue() {
	return firstRankValue;
}

int PokerHand::getSecondRankValue() {
	return secondRankValue;
}