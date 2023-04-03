#include "GameManager.h"

GameManager::GameManager(std::fstream& gameInputs): score(0) {
	//Checks if file is open
	//Catches error in Day2.cpp
	if (!gameInputs.is_open())
		throw std::runtime_error("Cannot open file!");
	
	//Generates a list of games
	char opponent,player;
	while (gameInputs >> opponent >> player) {;
		games.push_back(Game(std::make_pair(opponent,player)));
	}
}

int GameManager::runGames1() {
	//Plays each game in the list
	int score = 0;
	for (Game& game : games) {
		score += game.playPart1();
	}
	return score;
}

int GameManager::runGames2() {
	//Plays each game in the list
	int score = 0;
	for (Game& game : games) {
		score += game.playPart2();
	}
	return score;
}