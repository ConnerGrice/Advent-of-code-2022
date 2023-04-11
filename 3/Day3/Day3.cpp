// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Rucksack.h"
#include "Group.h"

int main()
{
    //Opens file containing puzzle inputs
    std::fstream input("../input.txt");
    if (!input.is_open())
        return EXIT_FAILURE;

    //Reads each line of the puzzle inputs
    std::string line;
    int totalPriority = 0;
    int totalBadge = 0;
    std::vector<Rucksack> group;
    while (std::getline(input, line)) {
        //Creates a bag for each line
        Rucksack bag(line);
        group.push_back(bag);
    
        if (group.size() == 3) {
            std::cout << std::endl;
            Group bagGroup = Group(group);
            totalBadge += bag.findPriority(bagGroup.findBadge());
            group.clear();
        }
        
        std::cout << bag.full << " : ";
     

        //Sums up the priority of duplicate items within the bag
        totalPriority += bag.findPriority();
    }

    std::cout << "Priority Sum: " << totalPriority << std::endl;
    std::cout << "Badge Sum: " << totalBadge << std::endl;
    return 0;
}