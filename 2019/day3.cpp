#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

typedef std::vector<std::pair<Direction, int>> Cable;

Cable parseCable(std::string cableString) {
    Cable cable;
    std::string tmp;
    Direction direction;
    for (char ch: cableString) {
        switch (ch) {
            case ',':
                cable.push_back(std::make_pair(direction, stoi(tmp)));
                tmp = "";
                break;
            case 'U':
                direction = UP;
                break;
            case 'D':
                direction = DOWN;
                break;
            case 'R':
                direction = RIGHT;
                break;
            case 'L':
                direction = LEFT;
                break;
            default:
                tmp += ch;
                break;
        }
    }
    return cable;
}

std::map<std::pair<int, int>, int> countOccurrences(std::vector<Cable> cables) {
    std::map<std::pair<int, int>, int> occurrences;
    for (Cable cable: cables) {
        int x = 0;
        int y = 0;
        std::vector<std::pair<int, int>> cableFragments;
        for (std::pair<Direction, int> step: cable) {
            for (int i = 0; i < std::get<1>(step); i++) {
                switch (std::get<0>(step)) {
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
                std::pair<int, int> currentCoordinates(x, y);
                if (std::find(cableFragments.begin(), cableFragments.end(), currentCoordinates) == cableFragments.end()) {
                    if (occurrences.find(currentCoordinates) != occurrences.end()) {
                        occurrences[currentCoordinates]++;
                    } else {
                        occurrences[currentCoordinates] = 1;
                    }
                }
                cableFragments.push_back(currentCoordinates);
            }
        }
    }
    return occurrences;
}

std::vector<std::pair<int, int>> findCrossing(std::vector<Cable> cables) {
    std::map<std::pair<int, int>, int> occurrences = countOccurrences(cables);
    std::vector<std::pair<int, int>> crossPoints;
    for (auto itr = occurrences.begin(); itr != occurrences.end(); ++itr) {
        //std::cout << std::get<0>(itr->first) << ' ' << std::get<1>(itr->first) << ' ' << itr->second << '\n';
        if (itr->second == cables.size()) {
            crossPoints.push_back(itr->first);
        }
    }
    return crossPoints;
}

int main() {
    std::string line;
    std::vector<std::string> cableStrings;
    while(getline(std::cin, line, '\n')) {
        cableStrings.push_back(line);
    }
    std::vector<Cable> cables;
    for (std::string cableString: cableStrings) {
        cables.push_back(parseCable(cableString));
    }
    for (auto i: findCrossing(cables)) {
        std::cout << i.first << ' ' << i.second << '\n';
    }
}
