#include <iostream>
#include <string>
#include <vector>

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

void executeIntcode(std::vector<int> &intcode) {
    int optcode;
    int input1, input2;
    int output;
    int pos = 0;
    for (int i = 0; i < intcode.size(); i++) {
        int current = intcode[i];
        switch (pos) {
            case 0:
                optcode = current;
                break;
            case 1:
                input1 = current;
                break;
            case 2:
                input2 = current;
                break;
            case 3:
                output = current;
                break;
        }
        if (pos == 3 || optcode == 99) {
            pos = 0;
            switch (optcode) {
                case 1:
                    intcode[output] = intcode[input1] + intcode[input2];
                    break;
                case 2:
                    intcode[output] = intcode[input1] * intcode[input2];
                    break;
                case 99:
                    return;
                default:
                    std::cout << "Error at " << i << ": " << optcode << " is not a valid optcode.\n";
                    break;
            }
        } else {
            pos++;
        }
    }
}

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

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    executeIntcode(intcode);
    //printIntcode(intcode);
    std::cout << intcode[0] << '\n';
}
