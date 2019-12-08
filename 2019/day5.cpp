#include <iostream>
#include <string>
#include <vector>

int ctoi(char ch) {
    return ch - '0';
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

int getParam(std::vector<int> intcode, std::vector<int> params, std::vector<int> modes, int num);

void executeIntcode(std::vector<int> &intcode) {
    int optcode;
    std::vector<int> params;
    std::vector<int> paramModes;
    int pos = 0;
    int paramCount;
    for (int i = 0; i < intcode.size(); i++) {
        int current = intcode[i];
        if (pos == 0) {
            std::string currentString = std::to_string(current);
            int optcodeStart;
            if (currentString.length() >= 2) {
                optcodeStart = currentString.length() - 2;
            } else {
                optcodeStart = currentString.length() - 1;
            }
            optcode = stoi(currentString.substr(optcodeStart, 2));
            paramCount = getParamCount(optcode);
            if (currentString.length() > 2) {
                for (int i = optcodeStart - 1; i >= 0; i--) {
                    paramModes.push_back(ctoi(currentString[i]));
                }
            }
            paramModes.resize(paramModes.size() + (paramCount - paramModes.size()));
        }
        //std::cout << optcode << ' ' << paramCount << ' ' << pos << ' ' << current << '\n';
        if (pos > 0 || paramCount == 0) {
            params.push_back(current);
            if (pos == paramCount) {
                switch (optcode) {
                    case 1:
                        intcode[params[2]] = getParam(intcode, params, paramModes, 0) + getParam(intcode, params, paramModes, 1);
                        break;
                    case 2:
                        intcode[params[2]] = getParam(intcode, params, paramModes, 0) * getParam(intcode, params, paramModes, 1);
                        break;
                    case 3:
                        std::cin >> intcode[params[0]];
                        break;
                    case 4:
                        std::cout << getParam(intcode, params, paramModes, 0);
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
        case 3:
            return 1;
        case 4:
            return 1;
        case 99:
            return 0;
        default:
            std::cout << "Error: Requested parameter code for non existent " << optcode << " optcode.\n";
            return -1;
    }
}

int getParam(std::vector<int> intcode, std::vector<int> params, std::vector<int> modes, int num) {
    switch (modes[num]) {
        case 0:
            return intcode[params[num]];

        case 1:
            return params[num];

        default:
            std::cout << "Error: mode " << modes[num] << " is invalid.\n";
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

int main() {
    std::string intcodeString;
    getline(std::cin, intcodeString, '\n');
    std::vector<int> intcode = parseIntcode(intcodeString);
    std::vector<int> newIntcode = intcode;
    executeIntcode(newIntcode);
    //printIntcode(newIntcode);
}
