#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "GeneralTree.h"
#include "GeneralTree.cpp"

typedef std::shared_ptr<GeneralTree::Node<int>> Node_ptr;
typedef GeneralTree::Node<int> Node;

/*
Splits every puzzle input string into its componant words
*/
std::vector<std::string> splitString(const std::string& input, const char delim) {
	std::stringstream ss;
	ss << input;
	std::string result;
	std::vector<std::string> output;
	while (std::getline(ss, result, delim)) {
		output.push_back(result);
	}
	return output;
}

int main() {
	//Gets puzzle input
	std::fstream input("../testing.txt");
	if (!input.is_open())
		return EXIT_FAILURE;
	
	//Initialises empty file system and initial directory
	GeneralTree::Tree<int> system("/", 0);
	auto currentDir = system.getRoot();
	std::string currentDirName = currentDir->getKey();

	//Loops through each line of puzzle input
	std::string line;
	while (std::getline(input, line)) {
		auto words = splitString(line, ' ');
		//Checks if command is being executed
		if (words[0] == "$") {
			//Checks is current directory needs to be moved
			if (words[1] == "cd") {
				//Ignores moving into home directory
				if (words[2] == "/")
					continue;

				//Move to parent directory
				else if (words[2] == "..") {
					currentDir = currentDir->getParent();
					currentDirName = currentDir->getKey();
					std::cout << currentDirName << std::endl;
					continue;
				}

				//Move to new directory
				currentDirName += words[2] + "/";
				currentDir = system.find(GeneralTree::SearchMethods::DFS, currentDirName);
				std::cout << currentDirName << std::endl;
			}
		//Checks if new directory is present in current directory
		} else if (words[0] == "dir") {
			//Adds new directroy to file system
			auto tempName = currentDirName + words[1] + "/";
			system.addChild(currentDir, tempName,0);
		} else {
			//Adds file to file system
			system.addChild(currentDir, words[1], std::stoi(words[0]));
		}
	}

	return 0;
}
