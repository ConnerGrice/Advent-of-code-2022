#include <iostream>
#include <fstream>
#include <string>
#include <utility>

struct AssigmentGroup{
    //Assigment IDs for each elf
    std::pair<int, int> elf1;
    std::pair<int, int> elf2;
    bool inside;
    bool overlap;

    //Splits string by a given delimiter
    template <typename T> 
    std::pair<T, T> splitAssignments(std::string& puzzle, char& delimiter) {
        //Gets position of delimiter
        size_t split = puzzle.find(delimiter);
        
        //Generates both substrings
        T one = puzzle.substr(0, split);
        T two = puzzle.substr(split+1,puzzle.size());
        
        //Returns a pair container
        return std::make_pair(one, two);
    }

    //Splits string to integers with a given delimiter
    template <> 
    std::pair<int, int> splitAssignments<int>(std::string& string, char& delimiter) {
        
        //Gets position of delimiter
        size_t split = string.find(delimiter);

        //Splits string into integers
        int one = std::stoi(string.substr(0, split));
        int two = std::stoi(string.substr(split+1, string.size()));

        return std::make_pair(one, two);
    }
    
    bool isInside() {
        //Does elf1 fully contain elf2
        if ((elf1.first <= elf2.first) && (elf1.second >= elf2.second))
            return true;

        //Does elf2 fully contain elf1
        if ((elf1.first >= elf2.first) && (elf1.second <= elf2.second))
            return true;

        return false;
    }

    bool isOverlap() {
        //Do assigments fully overlap
        if (inside)
            return true;

        //Do assigments overlap at all
        if ((elf1.first >= elf2.first) && (elf1.first <= elf2.second))
            return true;
        if ((elf1.first <= elf2.first) && (elf1.second >= elf2.first))
            return true;

        return false;
    }

    AssigmentGroup(std::string& puzzle) {
        //Splits initial string
        char delim1 = ',';
        std::pair<std::string, std::string> bothElves = splitAssignments<std::string>(puzzle, delim1);
        
        //Splits each elf to get assigment ID
        char delim2 = '-';
        elf1 = splitAssignments<int>(bothElves.first, delim2);
        elf2 = splitAssignments<int>(bothElves.second, delim2);

        //Check for overlapping
        inside = isInside();
        overlap = isOverlap();
    }

};



int main() {
    //Open puzzle file
    std::fstream input("../input.txt");
    if (!input.is_open())
        return EXIT_FAILURE;

    std::string line;
    int insideCounter = 0;
    int overlapCounter = 0;
    while (std::getline(input, line)) {
        char delim = ',';  
        AssigmentGroup group(line);
        std::cout << line << ":" << group.inside << std::endl;
        if (group.inside)
            insideCounter++;
        if (group.overlap)
            overlapCounter++;
    }
    std::cout << "Total jobs fully inside: " << insideCounter << std::endl;
    std::cout << "Total jobs Overalpping: " << overlapCounter << std::endl;
    return 0;
}


