#pragma once
#include <vector>
#include <algorithm>

#include "Rucksack.h"

/* A class that represents a group of 3 elves with their own bags*/
class Group {
	std::vector<Rucksack> group;
	Rucksack first, second, third;
public:
	Group(std::vector<Rucksack>& group);
	char findBadge();
};

