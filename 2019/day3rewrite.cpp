#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Turn {
    Direction direction;
    int steps;
};

typedef std::vector<Turn> Cable;

std::vector<Cable> parseInput(std::vector<std::string> input) {
    std::vector<Cable> cables;
    for (std::string inputLine: input) {
        Cable cable;
        Turn turn;
        std::string stepsStr;
        int pos = 0;
        for (int i = 0; i < inputLine.lenght(); ++i) {
            char current = inputLine[i];
            if (current == ',' || i + 1 >= inputLine.lenght()) {
                pos = 0;
                turn.steps = stoi(stepsStr);
                stepsStr = "";
                cable.push_back(turn);
                if (current == ',') {
                    continue;
                }
            }
            if (pos == 0) {
                switch (current) {
                    case 'U':
                        turn.direction = UP;
                        break;
                    case 'D':
                        turn.direction = DOWN;
                        break;
                    case 'L':
                        turn.direction = LEFT;
                        break;
                    case 'R':
                        turn.direction = RIGHT;
                        break;
                    default:
                        std::cout << "Error: direction is neither U, D, L nor R.\n";
                        exit();
                }
            } else {
                stepsStr += current;
            }
            pos++;
        }
        rawInput.push_back(rawInputLine);
    }
    return rawInput;
}

std::pair<int, int> findClosestIntersection(std::vector<std::vector<Turn>> rawInput) {
    std::map<std::pair<int, int>, int> occurenceCount = countOccurences(rawInput);
    std::vector<std::pair<int, int>> intersections;
    for (auto i: occurenceCount) {
        if (i.second == 3) {
            
}

int main() {
    std::vector<std::string> input;
    for (int i = 0; i < 2; ++i) {
        std::string inputLine;
        getline(std::cin, inputLine);
        input.push_back(inputLine);
    }
    std::vector<Turn> rawInput = parseInput(input);
    std::pair<int, int> closestIntersection = findClosestIntersection(rawInput);
}
