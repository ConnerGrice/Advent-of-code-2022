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
		GameManager gameManager(inputs);
		gameManager.runGames();

	} catch (const std::exception& err) {
		std::cout << "ERROR: " << err.what();
		return EXIT_FAILURE;
	}

	return 0;
}