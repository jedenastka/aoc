#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

struct Field {
    int ID;
    std::pair<int, int> position;
    bool operator== (const Field & right) {
        return right.ID == ID && right.position == position;
    }
};

struct RawInput {
    int ID;
    int startX;
    int startY;
    int sizeX;
    int sizeY;
};

RawInput praseInput(std::string input) {
    RawInput rawInput;
    std::string data[4];
    for (int i = 0, j = 0; i < 4; i++) {
        while (input[j] != '\n' | input[j] == ' ') {
            data[i] += input[j];
            j++;
        }
        j++;
    }
    rawInput.ID = stoi(data[0].substr(1));
    rawInput.startX = stoi(data[2].substr(0, data[2].find(",")));
    rawInput.startY = stoi(data[2].substr(data[2].find(",") + 1, data[2].find(":")));
    rawInput.sizeX = stoi(data[3].substr(0, data[3].find("x")));
    rawInput.sizeY = stoi(data[3].substr(data[3].find("x") + 1));
    return rawInput;
}

int countClaimCollisions(std::vector<std::string> input) {
    std::vector<Field> fields;
    for (std::vector<std::string>::iterator itr = input.begin(); itr != input.end(); ++itr) {
        RawInput rawInput = praseInput(*itr);
        for (int i = rawInput.startX; i < rawInput.startX + rawInput.sizeX; i++) {
            for (int j = rawInput.startY; j < rawInput.startY + rawInput.sizeY; j++) {
                Field field;
                field.ID = rawInput.ID;
                field.position = std::make_pair(i, j);
                fields.push_back(field);
            }
        }
    }
    std::vector<Field> collisions;
    for (std::vector<Field>::iterator itr = fields.begin(); itr != fields.end(); ++itr) {
        for (std::vector<Field>::iterator itr2 = fields.begin()+1; itr2 != fields.end(); ++itr2) {
            if (*itr == *itr2) {
                bool isDoubled = 0;
                for (std::vector<Field>::iterator itr3 = collisions.begin(); itr3 != collisions.end(); ++itr3) {
                    if (*itr2 == *itr3) {
                        isDoubled = 1;
                        break;
                    }
                }
                if (isDoubled) {
                    break;
                }
                collisions.push_back(*itr);
                break;
            }
        }
    }
    int collisionCount = collisions.size();
    return collisionCount;
}

int main() {
    std::cout << "Advent of Code 2018 (https://adventofcode.com/2018/)\n" << "Day 3 (https://adventofcode.com/2018/day/3)\n" << "Coded by Grzesiek11.\n";
    std::string inputFileName;
    std::cout << "Input file: ";
    std::cin >> inputFileName;
    std::ifstream inputFile(inputFileName.c_str());
    if (!inputFile) {
        throw "File not found.";
    }
    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }
    std::cout << "Raw paste values:\n" << countClaimCollisions(input) << "\n";
}