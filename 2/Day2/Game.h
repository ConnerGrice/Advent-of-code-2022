#pragma once
#include <vector>
#include <map>

#include "WinStates.h"

class Game {
public:
	Game(std::pair<char, char> plays);

	int play();
private:
	std::pair<char, char> round;
	WinStates* table;
};

