#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/* A struct that represents the commands that can be given to the crane*/
struct Command {
    int nCrates;
    int from;
    int to;

    Command(std::vector<int> command):
        nCrates(command[0]), from(command[1]-1), to(command[2]-1) {};
};

/*Takes information from puzzle input and puts it into a Command object*/
Command extractCommand(std::string& line) {
    std::vector<int> command;
    std::stringstream ss;
    ss << line;
    int value;
    std::string temp;

    while (std::getline(ss, temp, ' ')) {
        if (std::stringstream(temp) >> value)
            command.push_back(value);
    }
    return Command(command);
}

/*Represents a number of crate stacks that can be manipulated
by moving crates between stacks*/
class CrateStacks {
    std::vector<std::vector<char>> crates;

public:
    //Constructor
    CrateStacks(std::vector<std::vector<char>> stack) : crates(stack) {};

    void executeCommand(Command step);
    void executeMulti(Command step);
    void showTops();
};

/*Executes a given crane instruction, moving 1 crate at a time*/
void CrateStacks::executeCommand(Command step) {
    for (unsigned int i = 0; i < step.nCrates; i++) {
        crates[step.to].push_back(crates[step.from].back());
        crates[step.from].pop_back();
    }
}

/*Executes a given crane instruction, moving multiple crates at once*/
void CrateStacks::executeMulti(Command step) {
    auto& toStack = crates[step.to];
    auto& fromStack = crates[step.from];

    toStack.insert(toStack.end(), fromStack.end() - step.nCrates, fromStack.end());
    fromStack.erase(fromStack.end() - step.nCrates, fromStack.end());
}

/*Prints the top create of each stack*/
void CrateStacks::showTops() {
    for (const auto& stack : crates)
        std::cout << stack.back();
    std::cout << std::endl;
}

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
            //Ignores empty space
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
    std::vector<Command> instructions{};    //Raw instruction input strings
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

        //Put instructions into command format
        Command command = extractCommand(line);
        instructions.push_back(command);
    }
    //Initislise the crate stacks
    CrateStacks stacks1 = stackCrates(crateStrings);
    CrateStacks stacks2 = stacks1;

    //Executes commands
    for (const auto& command : instructions) {
        stacks1.executeCommand(command);
        stacks2.executeMulti(command);
    }

    //Prints results
    std::cout << "CrateMover 9000: ";
    stacks1.showTops();
    std::cout << std::endl << "CrateMover 9001: ";
    stacks2.showTops();

    return 0;
}