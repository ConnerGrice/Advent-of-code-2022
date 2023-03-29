#include "Game.h"

Game::Game(std::pair<char, char> round): round(round) {
	table = WinStates::getInstance();
}


int Game::play() {
	return table->getState(round);
}
