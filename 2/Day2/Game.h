#pragma once
#include <vector>
#include <map>

class Game {
public:
	Game(std::pair<char, char> plays);

private:
	std::map<std::pair<char, char>, int> winConditions;
};

