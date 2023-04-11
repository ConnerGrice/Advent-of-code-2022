#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <iostream>

/*A class that represents as bag with a list of items.
Seperates items into 2 halves and finds the duplicates*/
class Rucksack {
	std::string full;	//Entire item list
	std::string first;	//First half
	std::string second;	//Second half


	std::string alph = "abcdefghijklmnopqrstuvwxyz";	//Alphabet
	std::map<char,int> priority; //Map of letter -> priority pairs

	//Finds the letter that is inside both sides
	char getDuplicate();

	//Generates priority map
	std::map<char,int> generateMap();

public:
	//Constructor
	Rucksack();
	Rucksack(std::string& items);

	//Imlementing iterators for the entire bag contents
	typedef std::string::iterator iter;
	typedef std::string::const_iterator const_iter;
	inline iter begin() { return full.begin(); };
	inline iter end() { return full.end(); };
	
	//Returns the priority value of a given letter
	int findPriority(char letter);
	//Returns the priority value of the duplicate item
	int findPriority();

	//Gets an item within the bag
	inline char getItem(int i) { return full.at(i); };
};

