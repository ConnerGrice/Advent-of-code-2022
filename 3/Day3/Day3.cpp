// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Rucksack.h"

int main()
{
    //Opens file containing puzzle inputs
    std::fstream input("../input.txt");
    if (!input.is_open())
        return EXIT_FAILURE;

    //Reads each line of the puzzle inputs
    std::string line;
    int totalPriority = 0;
    while (std::getline(input,line)) {
        //Creates a bag for each line
        Rucksack bag(line);
        //Sums up the priority of duplicate items within the bag
        totalPriority += bag.findPriority();
    }

    std::cout << "Priority Sum: " << totalPriority << std::endl;
    return 0;
}