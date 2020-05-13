/**
	Texas holdem poker controller class.

	@author  Mateusz £yszkiewicz
	@version 1.0
	@since   2020 - 02 - 05

	Class provides solutions to poker texas holdem game management.
*/

#include "poker_controller.hpp"


PokerTexasHoldemController::PokerTexasHoldemController() {
	gameCustomization();
	playersCreator();
}

PokerTexasHoldemController::~PokerTexasHoldemController() {
	playersDestructor();
}



void PokerTexasHoldemController::gameCustomization() {
	do {
		std::cout << "Enter number of players <2,9>:\n";
		std::cin >> numberOfPlayers;
		if (std::cin.fail() || numberOfPlayers < 2 || numberOfPlayers > 9) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else {
			std::cout << "\nNumber of players is: " << numberOfPlayers << ".\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	} while (true);

	std::cout << "All the players have: " << moneyPerPlayer << " cash.\n"
		"Big blind is: " << bigBlind << std::endl;
}

void PokerTexasHoldemController::playersCreator() {
	for (int i = 0; i < numberOfPlayers; i++)
		players.push_back(new Player(moneyPerPlayer));
}

void PokerTexasHoldemController::playersDestructor() {
	for (auto playerIterator = players.begin(); playerIterator != players.end(); ++playerIterator) {
		delete* playerIterator;
		*playerIterator = nullptr;
	}
	players.clear();
}




void PokerTexasHoldemController::header(int actualPlayer) {

	std::this_thread::sleep_for(std::chrono::milliseconds(_TIME_FOR_MOVE));

	std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n"
		"Step: " << ++stepCounter << ".\nMoney on the Table: " << table.getMoney() << "\n\n";

	if (_DEBUG) {
		std::cout << "< DEBUG MODE > Players folding: " << foldingPlayers <<
			"\n< DEBUG MODE > Players checking: " << checkingPlayers <<
			"\n< DEBUG MODE > Players all in: " << allinPlayers <<
			"\n< DEBUG MODE > Table bid: " << table.getActualBid() << std::endl;
	}

	if (actualPlayer == 0)
		std::cout << "Your bid is: " << players[0]->getActualBid() << " and you have " << players[actualPlayer]->getMoney() << " money.\n\n";
	else if (_DEBUG)
		std::cout << "< DEBUG MODE > Player bid is: " << players[actualPlayer]->getActualBid() << " and has " << players[actualPlayer]->getMoney() << " money.\n\n";

	if (_DEBUG || actualPlayer == 0) {
		if (_DEBUG && actualPlayer != 0)
			std::cout << "< DEBUG MODE > ";
		auto cardsStack = players[actualPlayer]->getCardStack();
		std::cout << "Player's cards:\n";
		for (Card* card : cardsStack) {
			if (_DEBUG && actualPlayer != 0)
				std::cout << "< DEBUG MODE > ";
			std::cout << *card;
		}
		std::cout << std::endl;

		if (_DEBUG && actualPlayer != 0)
			std::cout << "< DEBUG MODE > ";
		auto cardsOnTable = table.getCardsFromTable();
		std::cout << "Cards on the table:\n";
		if (cardsOnTable.size())
			for (Card* card : cardsOnTable) {
				if (_DEBUG && actualPlayer != 0)
					std::cout << "< DEBUG MODE > ";
				std::cout << *card;
			}
		else {
			if (_DEBUG && actualPlayer != 0)
				std::cout << "< DEBUG MODE > ";
			std::cout << "Lack of cards.\n";
		}
		std::cout << std::endl;

		if (_DEBUG && actualPlayer != 0)
			std::cout << "< DEBUG MODE > ";
		std::cout << "Best hand:\n";
		if (_DEBUG && actualPlayer != 0)
			std::cout << "< DEBUG MODE > ";
		printHand(players[actualPlayer]->getPokerHand().getHand());
		std::cout << std::endl;
	}
}

void PokerTexasHoldemController::setSmallBlind(int actualPlayer) {
	if (actualPlayer == 0)
		std::cout << "You are ";
	else
		std::cout << "Player[" << actualPlayer << "] is ";
	std::cout << "small blind (-" << smallBlind << ").\n";
	table.addMoney(smallBlind);
	players[actualPlayer]->subMoney(smallBlind);
	table.setActualBid(smallBlind);
	isSmallBlind = false;
}

void PokerTexasHoldemController::setBigBlind(int actualPlayer) {
	if (actualPlayer == 0)
		std::cout << "You are ";
	else
		std::cout << "Player[" << actualPlayer << "] is ";
	std::cout << "big blind (-" << bigBlind << ").\n";
	table.addMoney(bigBlind);
	players[actualPlayer]->subMoney(bigBlind);
	table.setActualBid(bigBlind);
	isBigBlind = false;
}

void PokerTexasHoldemController::otherPlayersDecision(int actualPlayer) {

	int putOnTable;

	switch (players[actualPlayer]->getNextStep(table.getActualBid(), table.getCardsFromTable())) {
	case Player::Move::raise:
		putOnTable = table.getActualBid() - players[actualPlayer]->getActualBid();
		if (putOnTable > 0) {
			if (putOnTable >= players[actualPlayer]->getMoney()) {
				putOnTable = players[actualPlayer]->getMoney();
				players[actualPlayer]->setActualStatus(Player::Move::allIn);
				std::cout << "Player[" << actualPlayer << "] is all in ";
				std::cout << "and put on the table: " << putOnTable << " cash.\n";
			}
			table.addMoney(putOnTable);
			players[actualPlayer]->subMoney(putOnTable);
		}
		else
			putOnTable = 0;

		if (players[actualPlayer]->getActualStatus() != Player::Move::allIn) {
			std::cout << "Player[" << actualPlayer << "] ";
			if (!putOnTable)
				std::cout << "is bet...\n";
			else {
				std::cout << "is raise... ";
				std::cout << "and put on the table: " << putOnTable << " cash, to equal bid.\n";
			}
			putOnTable = bigBlind * randomInteger(1, 5);
			table.addMoney(putOnTable);
			players[actualPlayer]->subMoney(putOnTable);
			table.setActualBid(players[actualPlayer]->getActualBid());
			std::cout << "Player[" << actualPlayer << "] " << "put on the table additionally: " << putOnTable << " cash.\n";
		}
		break;
	case Player::Move::call:
		putOnTable = table.getActualBid() - players[actualPlayer]->getActualBid();
		if (putOnTable > 0) {
			if (putOnTable > players[actualPlayer]->getMoney()) {
				putOnTable = players[actualPlayer]->getMoney();
				players[actualPlayer]->setActualStatus(Player::Move::allIn);
				std::cout << "Player[" << actualPlayer << "] is all in ";
				std::cout << "and put on the table: " << putOnTable << " cash.\n";
			}
			table.addMoney(putOnTable);
			players[actualPlayer]->subMoney(putOnTable);
		}
		else
			putOnTable = 0;

		if (players[actualPlayer]->getActualStatus() != Player::Move::allIn) {
			std::cout << "Player[" << actualPlayer << "] is ";
			if (!putOnTable) {
				std::cout << "check...\n";
			}
			else {
				std::cout << "call...\n";
				std::cout << "and put on the table: " << putOnTable << " cash.\n";
			}
		}
		break;
	case Player::Move::fold:
		std::cout << "Player[" << actualPlayer << "] is fold.\n";
		break;
	case Player::Move::allIn:
		putOnTable = players[actualPlayer]->getMoney();
		table.addMoney(putOnTable);
		players[actualPlayer]->subMoney(putOnTable);
		table.setActualBid(players[actualPlayer]->getActualBid());
		std::cout << "Player[" << actualPlayer << "] is all in and put on the table: " << putOnTable << " cash.\n";
	}
}

void PokerTexasHoldemController::mainPlayerDecission() {

	char action;
	int putOnTable;

	do {
		std::cout << "Your turn. Press action button:\n";
		putOnTable = table.getActualBid() - players[0]->getActualBid();
		if (putOnTable == 0) {
			std::cout << "c - check;\n";
			std::cout << "b - bet;\n";
		}
		else {
			std::cout << "c - call;\n";
			std::cout << "r - raise;\n";
		}
		std::cout << "f - fold;\n"
			"a - all in;\n";

		std::cin >> action;
		if (std::cin.fail() || (action != 'c' && action != 'f' && action != 'r' && action != 'a' && action != 'b')) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else if ((action == 'c' || action == 'r' || action == 'b') &&
			putOnTable > players[0]->getMoney()) {
			std::cout << "You have not enough of money. You play all in.\n";
			action = 'a';
		}
		break;
	} while (true);

	switch (action) {
	case 'c':
		if (putOnTable > 0) {
			table.addMoney(putOnTable);
			players[0]->subMoney(putOnTable);
		}
		else
			putOnTable = 0;
		std::cout << "You ";
		if (!putOnTable)
			std::cout << "check...\n";
		else {
			std::cout << "call...\n";
			std::cout << "and put on the table : " << putOnTable << " cash, to equals bid." << std::endl;
		}
		players[0]->setActualStatus(Player::Move::call);
		break;
	case 'f':
		std::cout << "You fold..." << std::endl;
		players[0]->setActualStatus(Player::Move::fold);
		break;
	case 'b':
	case 'r':
		if (putOnTable > 0) {
			table.addMoney(putOnTable);
			players[0]->subMoney(putOnTable);
		}
		else
			putOnTable = 0;
		if (!putOnTable)
			std::cout << "You are bet... \n";
		else {
			std::cout << "You are raise... \n";
			std::cout << "and put on the table: " << putOnTable << " cash, to equal bid.\n";
		}
		do {
			std::cout << "How much money else do you want to put on the table?\n";
			std::cin >> putOnTable;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			else if (putOnTable > players[0]->getMoney()) {
				std::cout << "You have not enough of money. You have: " << players[0]->getMoney() << "money.\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			else if (putOnTable < bigBlind) {
				std::cout << "Minimum bid is big blind.\n";
				table.addMoney(bigBlind);
				players[0]->subMoney(bigBlind);
				table.setActualBid(players[0]->getActualBid());
				std::cout << "You put on the table: " << bigBlind << ".\n";
			}
			else {
				table.addMoney(putOnTable);
				players[0]->subMoney(putOnTable);
				table.setActualBid(players[0]->getActualBid());
				std::cout << "You put on the table: " << putOnTable << " cash.\n";
			}
			players[0]->setActualStatus(Player::Move::raise);
			break;
		} while (true);
		break;
	case 'a':
		putOnTable = players[0]->getMoney();
		table.addMoney(putOnTable);
		players[0]->subMoney(putOnTable);
		table.setActualBid(players[0]->getActualBid());
		std::cout << "You play all in!!!\n"
			"You put on the table: " << putOnTable << " cash!\n";
		players[0]->setActualStatus(Player::Move::allIn);
		break;
	}
}

void PokerTexasHoldemController::updateWaitingPlayers(int actualPlayer) {

	auto status = players[actualPlayer]->getActualStatus();

	if (status == Player::Move::call)
		checkingPlayers++;
	else if (status == Player::Move::raise)
		checkingPlayers = 1;
	else if (status == Player::Move::allIn) {
		allinPlayers++;
		checkingPlayers = 0;
	}
	else if (status == Player::Move::fold)
		foldingPlayers++;
}

void PokerTexasHoldemController::gameLoop() {

	firstPlayer = randomInteger(0, numberOfPlayers - 1);

	do {
		isSmallBlind = true;
		isBigBlind = true;
		flop = false;
		turn = false;
		river = false;

		stepCounter = 0;
		checkingPlayers = 0;
		foldingPlayers = 0;
		allinPlayers = 0;

		table.deleteCardsOnTable();
		table.deleteDeckOfCards();
		table.generateDeckOfCards();

		for (Player* player : players) {
			player->resetActualBid();
			player->resetActualStatus();
			player->deleteStackOfCards();
			player->addCard(2, table.getDeckOfCards());
			player->updateHand(table.getCardsFromTable());
		}

		// First player variable update
		if (firstPlayer < numberOfPlayers - 1)
			firstPlayer++;
		else
			firstPlayer = 0;

		while (true) {
			if (!isEndTurn()) {
				for (int actualPlayer = firstPlayer; ; actualPlayer != (numberOfPlayers - 1) ? actualPlayer++ : actualPlayer = 0) {

					header(actualPlayer);

					if (isEndTurn(actualPlayer))
						continue;

					if (isSmallBlind) {
						setSmallBlind(actualPlayer);
						continue;
					}
					else if (isBigBlind) {
						setBigBlind(actualPlayer);
						continue;
					}

					if (actualPlayer != 0)
						otherPlayersDecision(actualPlayer);
					else
						mainPlayerDecission();

					updateWaitingPlayers(actualPlayer);

					if (isEndTurn()) {
						std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
							"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n"
							"\nEND TURN\n\n";
						break;
					}
				}
			}
			else {
				if (!(foldingPlayers == numberOfPlayers - 1) &&
					!river) {
					if (!flop) {
						table.addCardToTable(3);
						std::cout << "Flop has added on the table.\n";
						flop = true;
					}
					else if (!turn) {
						table.addCardToTable(1);
						std::cout << "Turn has added on the table.\n";
						turn = true;
					}
					else if (!river) {
						table.addCardToTable(1);
						std::cout << "River has added on the table.\n";
						river = true;
					}
					for (Player* player : players)
						player->updateHand(table.getCardsFromTable());
					checkingPlayers = 0;
				}
				else {
					endGame();
					break;
				}
			}
		}
	} while (!isEndGame());
}

void PokerTexasHoldemController::play() {
	gameLoop();
}



bool PokerTexasHoldemController::isEndGame() {

	bool end = false;

	for (Player* player : players) {
		if (player->getMoney() < 1000) {
			end = true;
			break;
		}
	}

	if (end) {
		std::cout << "Players have too little money.\n"
			"Thank you for the game!\n";
	}
	else {
		do {
			std::string answer;
			std::cout << "Do you want to keep playing? Yes or No?\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, answer);
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			else {
				std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
				if (!(answer.compare("yes") && answer.compare("y"))) {
					end = false;
					break;
				}
				else if (!(answer.compare("no") && answer.compare("n"))) {
					end = true;
					break;
				}
				else {
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
			}
		} while (true);
	}

	return end;
}

bool PokerTexasHoldemController::isEndTurn() {

	bool endTurn = false;

	if (checkingPlayers == numberOfPlayers - foldingPlayers - allinPlayers) {
		endTurn = true;
	}

	return endTurn;
}

bool PokerTexasHoldemController::isEndTurn(int actualPlayer) {

	bool end;
	auto status = players[actualPlayer]->getActualStatus();

	if (status == Player::Move::allIn) {
		std::cout << "Player[" << actualPlayer << "] is all in.\n";
		end = true;
	}
	else if (status == Player::Move::fold) {
		std::cout << "Player[" << actualPlayer << "] is fold.\n";
		end = true;
	}
	else
		end = false;

	return end;
}

void PokerTexasHoldemController::endGame() {
	std::cout << "\nEND OF GAME\n\n";
	std::vector<Player*> copyOfPlayers;

	copyOfPlayers = players;
	std::sort(copyOfPlayers.begin(), copyOfPlayers.end(), [](Player* player1, Player* player2) -> bool {

		bool isBetter;

		if (player1->getActualStatus() == Player::Move::fold)
			isBetter = false;
		else if (player2->getActualStatus() == Player::Move::fold)
			isBetter = true;
		else {

			int response = player1->getPokerHand().isBetter(player2->getPokerHand());

			if (response == 1)
				isBetter = true;
			else
				isBetter = false;
		}

		return isBetter;
		});

	int counter = 1;
	do {
		if (copyOfPlayers[counter]->getPokerHand().isBetter(copyOfPlayers[counter + 1]->getPokerHand()) != 0)
			break;
		else
			counter++;
	} while (counter + 1 < (int)copyOfPlayers.size());

	int sumOfBids = 0;
	for (int i = 0; i < counter; i++)
		sumOfBids += copyOfPlayers[i]->getActualBid();

	for (int i = 0; i < counter; i++) {

		float part = (float)copyOfPlayers[0]->getActualBid() / sumOfBids;

		int moneyForPlayer = (int)(part * (float)table.getMoney());
		copyOfPlayers[i]->addMoney(moneyForPlayer);

		if (copyOfPlayers[i] == players[0])
			std::cout << "You win " << moneyForPlayer << " cash!\n\n";
		else {
			for (int j = 1; j < (int)players.size(); j++) {
				if (copyOfPlayers[i] == players[j]) {
					std::cout << "Player [" << j << "] won " << moneyForPlayer << " cash!\n\nHe has the fallowing cards:\n";

					auto cardsStack = players[j]->getCardStack();
					for (Card*& card : cardsStack)
						std::cout << *card;
					std::cout << std::endl;

					std::cout << "Cards on the table:\n";
					auto cardsOnTable = table.getCardsFromTable();
					if (cardsOnTable.size())
						for (Card*& card : cardsOnTable)
							std::cout << *card;
					else
						std::cout << "Lack of cards.\n";
					std::cout << std::endl;

					std::cout << "The winner hand is:\n";
					printHand(players[j]->getPokerHand().getHand());
					std::cout << std::endl;

					break;
				}
			}
		}
	}

	table.resetMoney();
}

void PokerTexasHoldemController::printHand(PokerHand::HandRanking pokerHand) {
	switch (pokerHand) {
	case PokerHand::HandRanking::straightFlush:
		std::cout << "Straight flush!!!\n";
		break;
	case PokerHand::HandRanking::fourOfAKind:
		std::cout << "Four of a kind\n";
		break;
	case PokerHand::HandRanking::flush:
		std::cout << "Flush\n";
		break;
	case PokerHand::HandRanking::straight:
		std::cout << "Straight\n";
		break;
	case PokerHand::HandRanking::threeOfAKind:
		std::cout << "Three of a kind\n";
		break;
	case PokerHand::HandRanking::fullHouse:
		std::cout << "Full house\n";
		break;
	case PokerHand::HandRanking::twoPair:
		std::cout << "Two pair\n";
		break;
	case PokerHand::HandRanking::pair:
		std::cout << "Pair\n";
		break;
	case PokerHand::HandRanking::highCard:
		std::cout << "HighCard\n";
	}
}
