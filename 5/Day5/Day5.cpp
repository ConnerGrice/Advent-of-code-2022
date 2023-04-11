#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*Represents a number of crate stacks that can be manipulated
by moving crates between stacks*/
class CrateStacks {
    std::vector<std::vector<char>> crates;

public:
    //Constructor
    CrateStacks(std::vector<std::vector<char>> stack) : crates(stack) {};
};

/*Processes puzzle input to a compatable format for the CrateStack class*/
CrateStacks stackCrates(std::vector<std::string>& input) {
    //Table that will hold the crates in each stack
    std::vector<std::vector<char>> stacks(9);

    //Iterate through puzzle input backwards
    for (auto i = input.rbegin(); i != input.rend(); ++i) {
        std::string layer = *i;

        //Remove all non-alpha characters and replace them with white space
        std::replace_if(layer.begin(), layer.end(), [](char const& c) { return !std::isalpha(c); }, ' ');
        
        //Loop through crate layer
        for (size_t j = 0; j < layer.size(); j++) {
            if (!std::isalpha(layer[j]))
                continue;
            
            //Populate the stacks with the creates relative to their position in the layer string
            int nStack = (j - 1) / 4.0;
            stacks[nStack].push_back(layer[j]);

        }
    }

    //Output crate
    return CrateStacks(stacks);
}

int main() {
    //Gets input file
    std::fstream input("../input.txt");
    if (!input.is_open())
        return EXIT_FAILURE;

    std::vector<std::string> crateStrings{};    //Raw crate input strings
    std::vector<std::string> instructions{};    //Raw instruction input strings
    std::string line;   //Contents of the line
    bool built = false; //Stack recorded flag
    
    while (std::getline(input, line)) {
    
        //The only empty line represents the end of the stack diagram
        if (line == "") {
            built = true;
            continue;
        }

        //Construct stack initial position strings
        if (!built) {
            crateStrings.push_back(line);
            continue;
        }

        //Construct the instruction strings
        instructions.push_back(line);
    }
    
    //Initislise the crate stacks
    CrateStacks stacks = stackCrates(crateStrings);

    return 0;
}