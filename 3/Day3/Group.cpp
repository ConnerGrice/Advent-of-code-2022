#include "Group.h"

Group::Group(std::vector<Rucksack>& group){
	first = group.at(0);
	second = group.at(1);
	third = group.at(2);
}

char Group::findBadge() {
	for (char& fChar : first) {
		for (char& sChar : second) {
			if (fChar == sChar) {
				std::string::iterator iter;
				iter = std::find(third.begin(), third.end(), fChar);
				if (iter != third.end()) {
					return *iter;
				} else {
					continue;
				}
			}
			continue;
		}
	}
}
