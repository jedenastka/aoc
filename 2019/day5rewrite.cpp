#include <iostream>
#include <vector>

struct Command {
    int optcode;
    std::vector<int> params;
    std::vector<int> modes;
};

std::vector<int> parseIntcode(std::string intcodeString) {
    std::vector<int> intcode;
    std::string tmp;
    for (int i = 0; i < intcodeString.length(); i++) {
        char current = intcodeString[i];
        if (current != ',') {
            tmp += current;
        }
        if (current == ',' || i == intcodeString.length() - 1) {
            intcode.push_back(stoi(tmp));
            tmp = "";
        }
    }
    return intcode;
}

int getParamCount(int optcode);

void executeCommand(Command command, std::vector<int> &intcode);

std::vector<int> executeIntcode(std::vector<int> intcode) {
    for (int pointer = 0; pointer < intcode.size(); ++pointer) {
        Command command;
        command.optcode = intcode[pointer];
        for (int i = 0; i < getParamCount(command.optcode); ++i) {
            command.params.push_back(intcode[++pointer]);
        }
        executeCommand(command, intcode);
    }
    return intcode;
}

void executeCommand(Command command, std::vector<int> &intcode) {
    std::cout << command.optcode << ' ';
    for (int i: command.params) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int getParamCount(int optcode) {
    switch (optcode) {
        case 1:
            return 3;
        case 2:
            return 3;
        case 3:
            return 1;
        case 4:
            return 1;
        case 99:
            return 0;
        default:
            std::cout << "Error: requested param count for not existent opcode " << optcode << ".\n";
            exit(1);
    }
}

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    executeIntcode(intcode);
}