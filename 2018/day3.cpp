#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>

struct Field {
    int ID;
    std::pair<int, int> position;
    int key;
};

bool operator<(const Field &l, const Field &r) {
    return l.key < r.key;
}

struct RawInput {
    int ID;
    int startX;
    int startY;
    int sizeX;
    int sizeY;
};

RawInput praseInput(std::string input, RawInput &rawInput) {
    std::vector<std::string> data;
    std::string actualString;
    for (int i = 0; i <= input.size(); i++) {
        if (input[i] == ' ' || i == input.size()) {
            data.push_back(actualString);
            actualString = "";
            continue;
        }
        actualString += input[i];
    }
    rawInput.ID = stoi(data[0].substr(1));
    rawInput.startX = stoi(data[2].substr(0, data[2].find(",")));
    rawInput.startY = stoi(data[2].substr(data[2].find(",") + 1, data[2].find(":")));
    rawInput.sizeX = stoi(data[3].substr(0, data[3].find("x")));
    rawInput.sizeY = stoi(data[3].substr(data[3].find("x") + 1));
    return rawInput;
}

int countClaimCollisions(std::vector<std::string> input) {
    std::set<Field> fields;
    int key = 0;
    for (auto i: input) {
        RawInput rawInput;
        praseInput(i, rawInput);
        for (int j = rawInput.startX; j < rawInput.startX + rawInput.sizeX; j++) {
            for (int k = rawInput.startY; k < rawInput.startY + rawInput.sizeY; k++) {
                Field field;
                field.ID = rawInput.ID;
                field.position = std::make_pair(j, k);
                field.key = key;
                key++;
                fields.insert(field);
            }
        }
    }
    std::cout << "\n";
    std::set<std::pair<int, int>> collisions;
    for (auto i: fields) {
        for (auto j: fields) {
            if (i.position == j.position && i.ID != j.ID && collisions.find(i.position) == collisions.end()) {
                collisions.insert(i.position);
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
