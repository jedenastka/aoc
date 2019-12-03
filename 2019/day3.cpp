#include <iostream>
#include <utility>
#include <string>
#include <vector>

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

std::vector<std::pair<int, int>> cableCoordinates(Cable cable) {
    std::vector<std::pair<int, int>> coordinates;
    int x = 0;
    int y = 0;
    for (std::pair<Direction, int> step:cable) {
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
            coordinates.push_back(std::make_pair(x, y));
        }
    }
    return coordinates;
}

void findCrossing() {
    
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
    std::vector<std::vector<std::pair<int, int>>> coordinates;
    for (Cable cable: cables) {
        coordinates.push_back(cableCoordinates(cable));
    }
    for (auto i: coordinates) {
        for (auto j: i) {
            std::cout << std::get<0>(j) << ' ' << std::get<1>(j) << '\n';
        }
    }
}
