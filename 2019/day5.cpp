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

int getParamCount(int optcode);

void executeIntcode(std::vector<int> &intcode) {
    int optcode;
    std::vector<int> params;
    int pos = 0;
    int paramCount;
    for (int i = 0; i < intcode.size(); i++) {
        int current = intcode[i];
        if (pos == 0) {
            optcode = current;
            paramCount = getParamCount(optcode);
        }
        //std::cout << optcode << ' ' << paramCount << ' ' << pos << ' ' << current << '\n';
        if (pos > 0 || paramCount == 0) {
            params.push_back(current);
            if (pos == paramCount) {
                switch (optcode) {
                    case 1:
                       intcode[params[2]] = intcode[params[0]] + intcode[params[1]];
                        break;
                    case 2:
                        intcode[params[2]] = intcode[params[0]] * intcode[params[1]];
                        break;
                    case 99:
                        return;
                    default:
                        std::cout << "Error at " << i << ": " << optcode << " is not a valid optcode.\n";
                        break;
                }
                pos = 0;
                params.clear();
                continue;
            }
        }
        pos++;
    }
}

int getParamCount(int optcode) {
    switch (optcode) {
        case 1:
            return 3;
        case 2:
            return 3;
        case 99:
            return 0;
        default:
            return -1;
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
    for (noun = 0; noun <= 99; noun++) {
        for (verb = 0; verb <= 99; verb++) { 
            tmpIntcode = intcode;
            modify(tmpIntcode, noun, verb);
            executeIntcode(tmpIntcode);
            if (tmpIntcode[0] == wantedValue) {
                return;
            }
        }
    }
}

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    std::vector<int> newIntcode = intcode;
    modify(newIntcode, 12, 2);
    executeIntcode(newIntcode);
    //printIntcode(newIntcode);
    int noun, verb;
    bruteforceNounVerb(intcode, 19690720, noun, verb);
    std::cout << newIntcode[0] << '\n' << 100 * noun + verb << '\n';
}
