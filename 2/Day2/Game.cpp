#include "Game.h"

Game::Game(std::pair<char, char> round): round(round) {
	//Get instance of look up table
	table = WinStates::getInstance();
}

int Game::playPart1() {
	//Gets score and prints out game
	int score = table->getPart1(round);
	return score;
}

int Game::playPart2() {
	//Gets score and prints out game
	int score = table->getPart2(round);
	return score;
}
