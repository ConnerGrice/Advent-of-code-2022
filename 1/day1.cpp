#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	//Opens input file
	std::fstream input("input.txt");

	//Checks if file is open
	if (!input.is_open())
		return EXIT_FAILURE;

	//Initialise variables
	std::vector<int> totals;	//Contain total calories for each elf
	int calories = 0; //Calorie counter
	std::string line;	//Line from input file
	while (std::getline(input,line)) {
		if (line == "") {
			totals.push_back(calories);
			calories = 0;
			continue;
		}
		//Converts string into integer
		calories += std::stoi(line);
	}

	//Sorts vector into ascending order
	std::sort(totals.begin(), totals.end());

	std::cout << "The elf with the most food has: ";
	std::cout << totals.back() << std::endl;
	
	//Counts the last values then removes it to get the top 3
	int counter = 0;
	for (int i = 0;i < 3;i++) {
		counter += totals.back();
		totals.pop_back();
	}
	std::cout << "The top 3 elves have a total calorie count of: " << counter << std::endl;

	return 0;
}