#include <iostream>
#include <fstream>
#include <string>

/*Checks if a substring contains a duplicate character*/
bool areDuplicates(std::string& input) {
    for (size_t i = 0; i < input.size() - 1;i++) {
        for (size_t j = 1 + i;j < input.size();j++) {
            if (input[i] == input[j])
                return true;
        }
    }
    return false;
}

/*Counts number of characters until a substring contains duplicates*/
int detectPacket(std::string& input,int packetSize) {
    for (size_t i = 0; i < input.size() - packetSize; i++) {
        std::string packet = input.substr(i, packetSize);
        if (!areDuplicates(packet))
            return i + packetSize;
    }
    return -1;
}

int main() {
    //Open puzzle input
    std::fstream input("../input.txt");
    if (!input.is_open())
        return EXIT_FAILURE;

    //Gets puzzle input as string
    std::string line;
    std::getline(input, line);

    //Find the number of characters until a duplicate is found
    int startPacket = detectPacket(line, 4);
    int startMessage = detectPacket(line, 14);

    //Print results
    std::cout << "First packet after " << startPacket << " characters." << std::endl;
    std::cout << "First message after " << startMessage << " characters." << std::endl;
}

