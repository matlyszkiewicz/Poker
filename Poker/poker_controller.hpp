/**
	Texas holdem poker controller class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/

#ifndef _poker_controller
#define _poker_controller

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "random_integer.hpp"
#include "card.hpp"
#include "poker_hand.hpp"
#include "table.hpp"
#include "player.hpp"

#define _DEBUG true
#define _TIME_FOR_MOVE 0

/*
	Class provides solutions to poker texas holdem game management.
*/
class PokerTexasHoldemController {

	std::vector<Player*> players;

	Table table;
	int stepCounter;

	int numberOfPlayers;
	int firstPlayer;
	const int moneyPerPlayer = 10000;

	const int smallBlind = 50;
	const int bigBlind = 100;
	bool isSmallBlind;
	bool isBigBlind;

	bool flop;
	bool turn;
	bool river;

	int checkingPlayers;
	int foldingPlayers;
	int allinPlayers;



	void gameCustomization();

	void playersCreator();

	void playersDestructor();

	void header(int actualPlayer);

	void setSmallBlind(int actualPlayer);

	void setBigBlind(int actualPlayer);

	void otherPlayersDecision(int actualPlayer);

	void mainPlayerDecission();

	void updateWaitingPlayers(int actualPlayer);

	void gameLoop();

	void printHand(PokerHand::HandRanking pokerHand);

	bool isEndGame();

	bool isEndTurn();

	bool isEndTurn(int actualPlayer);

	void endGame();

public:

	PokerTexasHoldemController();

	void play();

	~PokerTexasHoldemController();
};

#endif