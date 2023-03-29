#pragma once

#include <vector>
#include <iostream>
#include <map>

class WinStates {
	//Private instances of the look-up-table
	static WinStates* _instance;
	std::map<std::pair<char, char>, int> mStates;

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
	int getState(std::pair<char, char> play) { return mStates[play]; };
};