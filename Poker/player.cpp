/**
	Texas holdem poker player class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05

	Class represents player. The main player can set actual move, the opponent
	for main player has implemented	getNextStep function, which allow simulates
	next move taking into account cards and money on the table.
*/

#include <stdexcept>
#include "player.hpp"



Player::Player(int money = 1000) : actualStatus(none) {
	this->money = money;
}



void Player::addMoney(int money) {
	this->money += money;
}

void Player::subMoney(int money) {
	if (this->money < money)
		throw "enough of money!!!";
	this->money -= money;
	this->actualBid += money;
}

int Player::getMoney() {
	return money;
}



int Player::getActualBid() {
	return actualBid;
}

void Player::resetActualBid() {
	actualBid = 0;
}



int Player::getMoneyCoefficient() {
	return moneyCoefficient;
}

int Player::getStrongCardCoefficient() {
	return strongCardCoefficient;
}

int Player::getLuckCoefficient() {
	return summaryLuckCoefficient;
}

// Member function which updates player's luck coefficient.
void Player::updateLuckCoefficient(int moneyOnTheTable, std::vector<Card*>& cardsOnTheTable) {

	if (moneyOnTheTable > money && money != 0)
		moneyCoefficient = moneyOnTheTable / money;
	else
		moneyCoefficient = moneyOnTheTable / 1000;

	strongCardCoefficient = updateHand(cardsOnTheTable) + randomInteger(0, 6);
	summaryLuckCoefficient = moneyCoefficient + strongCardCoefficient + randomInteger(0, 5);
}



// Manually sets player status.
void Player::setActualStatus(Player::Move status) {
	actualStatus = status;
}

void Player::resetActualStatus() {
	actualStatus = Player::Move::none;
}

Player::Move Player::getActualStatus() {
	return actualStatus;
}

// Simulates player's decision and returns next move.
Player::Move Player::getNextStep(int moneyOnTheTable, std::vector<Card*>& cardsOnTheTable) {

	updateLuckCoefficient(moneyOnTheTable, cardsOnTheTable);

	if (summaryLuckCoefficient > 16 || (moneyOnTheTable / money > 10 && strongCardCoefficient > 10))
		actualStatus = Move::allIn;
	else if (strongCardCoefficient > 6 && moneyOnTheTable / (actualBid + 1) < 4)
		actualStatus = Move::raise;
	else if (summaryLuckCoefficient > 3 && summaryLuckCoefficient * 50 > moneyOnTheTable / 10)
		actualStatus = Move::call;
	else
		actualStatus = Move::fold;

	return actualStatus;
}



// Adds card to player's card stack.
void Player::addCard(int numberOfCards, std::vector<Card*>& deckOfCards) {

	if (numberOfCards < 1 || (int)deckOfCards.size() < numberOfCards) {
		throw std::out_of_range("Not enought of cards!!!");
	}

	std::vector<Card*>::iterator drawnCard;
	for (int i = 0; i < numberOfCards; i++) {
		drawnCard = deckOfCards.begin() + randomInteger(0, (int)deckOfCards.size() - 1);
		playerCardStack.push_back(*drawnCard);
		deckOfCards.erase(drawnCard);
	}
}

std::vector<Card*>& Player::getCardStack() {
	return playerCardStack;
}

void Player::deleteStackOfCards() {
	for (auto cardIterator = playerCardStack.begin(); cardIterator != playerCardStack.end(); ++cardIterator) {
		delete *cardIterator;
		*cardIterator = nullptr;
	}
	playerCardStack.clear();
}



// Updates player's poker hand rank.
PokerHand::HandRanking Player::updateHand(std::vector<Card*>& cardsOnTable) {
	return pokerHand.updateCardStatus(playerCardStack, cardsOnTable);
}

PokerHand& Player::getPokerHand() {
	return pokerHand;
}

Player::~Player() {
	deleteStackOfCards();
}