/**
	Texas holdem poker game.

	@author  Mateusz Łyszkiewicz
	@version 1.0
	@since   2020 - 02 - 05
*/


#include "poker_controller.hpp"

int main() {
	std::ios_base::sync_with_stdio(0);

	PokerTexasHoldemController pokerGame;
	pokerGame.play();

	return 0;
}


