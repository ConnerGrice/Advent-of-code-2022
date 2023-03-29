#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "Game.h"
class GameManager {
public:
	//NOTE: fstream must be a reference since it is not copyable
	//Using the reference allows for the objects itself to be modified
	//instead of creating a copy and modifying that.
	GameManager(std::fstream& gameInputs);
	
	int runGames();

private:
	std::vector<std::pair<char,char>> games;
	int score;
};

