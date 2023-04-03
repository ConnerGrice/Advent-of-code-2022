#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

/*A singleton that contains data on what score should be
give during a single can og rock paper scissors*/
class WinStates {
	//Private instances of the look-up-table
	static WinStates* _instance;
	std::map<std::pair<char, char>, int> mPart1;
	std::map<std::pair<char, char>, int> mPart2;


	//Construct table in constructor
	WinStates();
	//Default destructor
	~WinStates() = default;
public:
	//Does not allow copy or assignment of more than 1 instance
	WinStates(const WinStates&) = delete;
	WinStates& operator=(const WinStates&) = delete;

	//Gets the single instance of this class
	static WinStates* getInstance();

	//Gets the score of a given game
	int getPart1(std::pair<char, char> play) { return mPart1[play]; };
	int getPart2(std::pair<char, char> play) { return mPart2[play]; };
};