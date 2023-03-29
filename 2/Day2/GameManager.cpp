#include "GameManager.h"

GameManager::GameManager(std::fstream& gameInputs): score(0) {
	//Checks if file is open
	if (!gameInputs.is_open())
		throw std::runtime_error("Cannot open file!");
	
	//Generates a list of games
	char opponent,player;
	while (gameInputs >> opponent >> player) {;
		games.push_back(std::make_pair(opponent,player));
	}
}

int GameManager::runGames() {
	int score = 0;
	for (std::pair<char, char> round : games) {
		Game game(round);
		score += game.play();
	}
	return score;
}