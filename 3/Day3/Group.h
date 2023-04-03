#pragma once
#include <vector>

#include "Rucksack.h"
class Group {
	Rucksack first, second, third;
public:
	Group(std::vector<Rucksack>& group);
	char findBadge();
};

