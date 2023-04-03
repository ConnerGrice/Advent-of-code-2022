#include "WinStates.h"

/*A singleton class that hold the information about what
games will result in what score and can be used as a look-up-table

|Player  |Rock|Paper|Scissors|
|--------|----|-----|--------|
|Opponent|A   |B    |C       |
|Player  |X	  |Y    |Z       |

Scores:
	Win: 6
	Draw: 3
	Loss: 0

	Rock: 1
	Paper: 2
	Scissors: 3
*/

//Only instance of the class
WinStates* WinStates::_instance = nullptr;

//Construct the look up table
WinStates::WinStates() {
	//Types of plays
	std::vector<char> opp1{ 'A','B','C' };
	std::vector<char> opp2 = opp1;
	std::vector<char> player{ 'X','Y','Z' };
	int winScore;
	int moveScore;
	int playScore = 0;
	int outcomeScore = 0;
	//For each play the player can make
	for (std::size_t i = 0; i < player.size(); i++) {
		playScore++;
		//For each play the opponent can make
		for (std::size_t j = 0; j < opp1.size(); j++) {
			switch (j) {
			case(0):
				winScore = 3;
				moveScore = 3;
				break;
			case(1):
				winScore = 0;
				moveScore = 1;
				break;
			case(2):
				winScore = 6;
				moveScore = 2;
				break;
			}
			//Populate the table
			mPart1[std::make_pair(opp1[j], player[i])] = playScore + winScore;
			mPart2[std::make_pair(opp2[j], player[i])] = outcomeScore + moveScore;
		}
		//Cyclical shift of vector
		std::rotate(opp1.begin(), opp1.begin() + 1, opp1.end());
		std::rotate(opp2.rbegin(), opp2.rbegin() + 1, opp2.rend());
		outcomeScore += 3;
	}


	/*
	X -> Loss
	Y -> Draw
	Z -> Win
	*/
}

/*Get the only instance of the class for usage*/
WinStates* WinStates::getInstance() {
	//Create the object if it doesnt already exist
	if (!_instance) {
		_instance = new WinStates();
	}
	return _instance;
}
