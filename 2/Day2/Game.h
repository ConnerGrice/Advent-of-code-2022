#pragma once
#include <vector>
#include <map>

#include "WinStates.h"

/*Represents a single game and holds a score that was
taken from the WinStates look up table*/
class Game {
public:
	Game(std::pair<char, char> plays);

	//Get the score of the game
	int playPart1();
	int playPart2();
private:
	std::pair<char, char> round;
	WinStates* table;
};

