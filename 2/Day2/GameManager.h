#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "Game.h"

/*A class that will collect al the games and
play each one*/
class GameManager {
public:
	//NOTE: fstream must be a reference since it is not copyable
	//Using the reference allows for the objects itself to be modified
	//instead of creating a copy and modifying that.
	GameManager(std::fstream& gameInputs);
	
	//Play all games in the list
	int runGames1();
	int runGames2();

private:
	std::vector<Game> games;
	int score;
};

