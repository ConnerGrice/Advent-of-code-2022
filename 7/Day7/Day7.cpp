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

/*
Scans the file system and calculates the total memory of each directory
(including their sub directories
*/
void updateStorage(std::vector<Node_ptr> order) {
	//Gets the order to check each node
	for (auto node : order) {
		if (node->getChild()) {
			auto tempNode = node->getChild();
			node->value += tempNode->value;
			while (tempNode->getSibling()) {
				tempNode = tempNode->getSibling();
				node->value += tempNode->value;
			}
		}
		//std::cout << node->getKey() <<":"<< node->value << std::endl;
	}
}

/*
Finds the total memory of all DIRECTORIES that take up more then 100000
*/
int doTask1(std::vector<Node_ptr> order) {
	int result = 0;
	for (auto node : order) {
		//Ignore files
		if (!node->getChild())
			continue;

		if (node->value <= 100000)
			result += node->value;
	}
	return result;
}

/*
Finds the size of the smallest directory that needs to be deleted 
in order to free up enough space for the update
*/
int doTask2(std::vector<Node_ptr> order) {
	int total = 70000000;	//Total space
	int update = 30000000;	//Update size
	int used = order.back()->value;	//Total used space
	int free = total - used;	//Total free space
	int need = update - free;	//Space needed for update

	for (auto node : order) {
		//Ignore files
		if (!node->getChild())
			continue;

		//Since post-order is being used,
		//the first file found will be the smallest
		if (node->value >= need)
			return node->value;
	}
}

int main() {
	//Gets puzzle input
	std::fstream input("../input.txt");
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
				if (words[2] == "..") {
					currentDir = currentDir->getParent();
					currentDirName = currentDir->getKey();
					//std::cout << currentDirName << std::endl;
					continue;
				}

				//Move to new directory
				currentDirName += words[2] + "/";
				currentDir = system.find(GeneralTree::SearchMethods::DFS, currentDirName);
				//std::cout << currentDirName << std::endl;
			}
		//Checks if new directory is present in current directory
		} else if (words[0] == "dir") {
			//Adds new directroy to file system
			auto tempName = currentDirName + words[1] + "/";
			system.addChild(currentDir, tempName,0);
		} else {
			//Adds file to file system
			system.addChild(currentDir, words[1], std::stoi(words[0]));
			//std::cout << currentDirName << words[1] << "(" << words[0] <<" kb)" << std::endl;
		}
	}
	//Gets the nodes inside file system in post-order
	auto iterVector = system.scan();

	//Calculates and sets the size of each file and directory
	updateStorage(iterVector);

	//Complete tasks
	auto task1 = doTask1(iterVector);
	auto task2 = doTask2(iterVector);
	
	std::cout <<"The total space of all directories that take up more than 100000 is "<< task1<<"kB\n";
	std::cout <<"The smallest directory that can be deleted in order to free up enough space for the update has a size of "<< task2 << "kB\n";
	return 0;
}
