#include <iostream>
#include <fstream>

#include "GameManager.h"
/*
Opponent
A -> Rock
B -> Paper
C -> Scissors

Player
X -> Rock
Y -> Paper
Z -> Scissors

Scores
Rock -> 1
Paper -> 2
Scissors -> 3
Loss -> 0
Draw -> 3
Win -> 6
*/

int main() {
	std::fstream inputs("../input.txt");
	
	try {
		//Fill the game manager with games
		GameManager gameManager(inputs);

		//Runs all games and prints out final score
		std::cout << "Final Score 1: " << gameManager.runGames1() << std::endl;
		std::cout << "Final Score 2: " << gameManager.runGames2() << std::endl;

	} catch (const std::exception& err) {
		//Error is file cannot be open
		std::cout << "ERROR: " << err.what();
		return EXIT_FAILURE;
	}
	return 0;
}