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

void modify(std::vector<int> &intcode, int noun, int verb) {
    intcode[1] = noun;
    intcode[2] = verb;
}

void bruteforceNounVerb(std::vector<int> intcode, int wantedValue, int &noun, int &verb) {
    std::vector<int> tmpIntcode;
    for (int i = 0; i <= 99; i++) {
        for (int j = 0; j <= 99; j++) { 
            for (int k = 0; k < 2; k++) {
                if (k == 0) {
                    verb = i;
                    noun = j;
                } else {
                    noun = j;
                    verb = i;
                }
                tmpIntcode = intcode;
                modify(tmpIntcode, noun, verb);
                executeIntcode(tmpIntcode);
                if (tmpIntcode[0] == wantedValue) {
                    return;
                }
            }
        }
    }
    /*for (int i = 0; 1; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < 2; k++) {
                if (k == 0) {
                    verb = i;
                    noun = j;
                } else {
                    noun = j;
                    verb = i;
                }
                std::vector<int> tmpintcode = intcode;
                modify(tmpintcode, noun, verb);
                executeIntcode(tmpIntcode);
                if (tmpIntcode[0] == wantedValue) {
                    return;
                }
            }
        }
    }*/
}

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    std::vector<int> newIntcode = intcode;
    modify(newIntcode, 12, 2);
    executeIntcode(newIntcode);
    int noun, verb;
    bruteforceNounVerb(intcode, 19690720, noun, verb);
    std::cout << newIntcode[0] << '\n' << 100 * noun + verb << '\n';
}
