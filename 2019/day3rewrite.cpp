#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

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
        for (int i = 0; i < inputLine.length(); ++i) {
            char current = inputLine[i];
            if (current != ',') {
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
                            exit(1);
                    }
                } else {
                    stepsStr += current;
                }
            }
            if (current == ',' || i + 1 >= inputLine.length()) {
                pos = 0;
                turn.steps = stoi(stepsStr);
                stepsStr = "";
                cable.push_back(turn);
            } else {
                pos++;
            }
        }
        cables.push_back(cable);
    }
    return cables;
}

std::vector<std::pair<int, int>> findIntersections(std::vector<Cable> cables);

int manhattanDistance(std::pair<int, int> a, std::pair<int, int> b);

int findClosestIntersectionDistance(std::vector<Cable> cables) {
    std::vector<std::pair<int, int>> intersections = findIntersections(cables);
    int leastDistance = -1;
    for (auto intersection: intersections) {
        int distance = manhattanDistance(std::make_pair(0, 0), intersection);
        if (distance < leastDistance || leastDistance == -1) {
            leastDistance = distance;
        }
    }
    return leastDistance;
}

std::map<std::pair<int, int>, std::vector<int>> mapOccurences(std::vector<Cable> cables);

std::vector<std::pair<int, int>> findIntersections(std::vector<Cable> cables) {
    std::map<std::pair<int, int>, std::vector<int>> occurenceMap = mapOccurences(cables);
    std::vector<std::pair<int, int>> intersections;
    for (auto i: occurenceMap) {
        int crossCounter = 0;
        for (int j = 1; j <= cables.size(); ++j) {
            if (std::find(i.second.begin(), i.second.end(), j) != i.second.end()) {
                ++crossCounter;
            }
        }
        if (crossCounter == cables.size()) {
            intersections.push_back(i.first);
        }
    }
    return intersections;
}

std::map<std::pair<int, int>, std::vector<int>> mapOccurences(std::vector<Cable> cables) {
    std::map<std::pair<int, int>, std::vector<int>> occurencesMap;
    for (int i = 1; i <= cables.size(); ++i) {
        int x = 0;
        int y = 0;
        for (Turn turn: cables[i - 1]) {
            for (int j = 0; j < turn.steps; ++j) {
                switch (turn.direction) {
                    case UP:
                        y++;
                        break;
                    case DOWN:
                        y--;
                        break;
                    case RIGHT:
                        x++;
                        break;
                    case LEFT:
                        x--;
                        break;
                }
                occurencesMap[std::make_pair(x, y)].push_back(i);
            }
        }
    }
    return occurencesMap;
}

int substractSmallerFromBigger(int a, int b);

int manhattanDistance(std::pair<int, int> a, std::pair<int, int> b) {
    int xDistance = substractSmallerFromBigger(std::get<0>(a), std::get<0>(b));
    int yDistance = substractSmallerFromBigger(std::get<1>(a), std::get<1>(b));
    return xDistance + yDistance;
}

int substractSmallerFromBigger(int a, int b) {
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int main() {
    std::vector<std::string> input;
    for (int i = 0; i < 2; ++i) {
        std::string inputLine;
        getline(std::cin, inputLine);
        input.push_back(inputLine);
    }
    std::vector<Cable> cables = parseInput(input);
    std::cout <<  findClosestIntersectionDistance(cables) << '\n';
}
