#include <iostream>
#include <vector>
#include <string>
#include <utility>

struct Command {
    int optcode;
    std::vector<int> params;
    std::vector<int> modes;
};

void printIntcode(std::vector<int> intcode) {
    for (int i = 0; i < intcode.size(); i++) {
        std::cout << intcode[i];
        if (i == intcode.size() - 1) {
            std::cout << '\n';
        } else {
            std::cout << ',';
        }
    }
}

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

bool executeCommand(Command command, std::vector<int> &intcode, int &pointer);

std::pair<int, std::vector<int>> extractFirstPosition(int firstPosition);

std::vector<int> executeIntcode(std::vector<int> intcode) {
    for (int pointer = 0; pointer < intcode.size(); ++pointer) {
        std::pair<int, std::vector<int>> extracted = extractFirstPosition(intcode[pointer]);
        Command command;
        command.optcode = std::get<0>(extracted);
        command.modes = std::get<1>(extracted);
        for (int i = 0; i < getParamCount(command.optcode); ++i) {
            command.params.push_back(intcode[++pointer]);
        }
        if (executeCommand(command, intcode, pointer)) {
            break;
        }
    }
    return intcode;
}

int getParam(int param, Command command, std::vector<int> &intcode);

bool executeCommand(Command command, std::vector<int> &intcode, int &pointer) {
    switch (command.optcode) {
        case 1:
            intcode[command.params[2]] = getParam(0, command, intcode) + getParam(1, command, intcode);
            break;
        case 2:
            intcode[command.params[2]] = getParam(0, command, intcode) * getParam(1, command, intcode);
            break;
        case 3:
            std::cin >> intcode[command.params[0]];
            break;
        case 4:
            std::cout << getParam(0, command, intcode) << '\n';
            break;
        case 5:
            if (getParam(0, command, intcode)) {
                pointer = intcode[command.params[1]];
            }
            break;
        case 6:
            if (!getParam(0, command, intcode)) {
                pointer = intcode[command.params[1]];
            }
            break;
        case 7:
            intcode[command.params[2]] = getParam(0, command, intcode) < getParam(1, command, intcode);
            break;
        case 8:
            intcode[command.params[2]] = getParam(0, command, intcode) == getParam(1, command, intcode);
            break;
        case 99:
            return 1;
            break;
        default:
            std::cout << "Error: tried to execute not exsistent optcode " << command.optcode << ".\n";
            exit(1);
    }
    return 0;
}

int getParam(int param, Command command, std::vector<int> &intcode) {
    if (command.modes[param] == 0) {
        return intcode[command.params[param]];
    } else if (command.modes[param] == 1) {
        return command.params[param];
    } else {
        std::cout << "Error: mode " << command.modes[param] << " does not exist.\n";
        exit(1);
    }
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
        case 5:
            return 2;
        case 6: 
            return 2;
        case 7:
            return 3;
        case 8:
            return 3;
        case 99:
            return 0;
        default:
            std::cout << "Error: requested param count for not existent opcode " << optcode << ".\n";
            exit(1);
    }
}

int chtoi(char ch);

std::string reverse(std::string str);

std::pair<int, std::vector<int>> extractFirstPosition(int firstPosition) {
    std::string firstPositionStr = std::to_string(firstPosition);
    int firstPositionLen = firstPositionStr.length();
    std::string optcodeString;
    std::vector<int> modes;
    for (int i = firstPositionLen - 1; i >= 0; --i) {
        if (i > firstPositionLen - 1 - 2) {
            optcodeString += firstPositionStr[i];
        } else {
            modes.push_back(chtoi(firstPositionStr[i]));
        }
    }
    optcodeString = reverse(optcodeString);
    int optcode = stoi(optcodeString);
    while (getParamCount(optcode) - modes.size() > 0) {
        modes.push_back(0);
    }
    return std::make_pair(optcode, modes);
}

int chtoi(char ch) {
    return ch - '0';
}

std::string reverse(std::string str) {
    std::string reversedStr;
    for (int i = str.length() - 1; i >= 0; --i) {
        reversedStr += str[i];
    }
    return reversedStr;
}

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    executeIntcode(intcode);
}