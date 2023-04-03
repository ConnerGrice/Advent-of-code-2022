#include "Group.h"

Group::Group(std::vector<Rucksack>& group){
	
	first = group.at(0);
	second = group.at(1);
	third = group.at(2);
}

char Group::findBadge() {
	return '-1';
}