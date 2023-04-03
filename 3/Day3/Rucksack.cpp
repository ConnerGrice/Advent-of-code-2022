#include "Rucksack.h"
Rucksack::Rucksack() : full(0), first(0), second(0){
    priority = generateMap();
}

Rucksack::Rucksack(std::string items): full(items) {
    std::size_t length = items.size();
    first = items.substr(0, length / 2);
    second = items.substr(length / 2, length);
    priority = generateMap();
}

char Rucksack::getDuplicate() {
    for (auto& fChar : first) {
        for (auto& sChar : second) {
            if (fChar == sChar)
                return fChar;
        }
    }
    return '1';
}

std::map<char,int> Rucksack::generateMap() {
    int i = 1;
    std::map<char, int> temp;
    for (auto& letter : alph) {
        temp[letter] = i;
        temp[std::toupper(letter)] = i + 26;
        i++;
    }
    return temp;
}

int Rucksack::findPriority(char letter) {
    return priority[letter];
}

int Rucksack::findPriority() {
    return priority[getDuplicate()];
}