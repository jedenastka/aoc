#include <iostream>
#include <utility>
#include <cmath>

int main() {
    // Part 1
    std::pair<int, int> position = {0, 0};
    int rotation = 1;
    const std::pair<int, int> directions[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Part 2
    std::pair<int, int> shipPosition = {0, 0};
    std::pair<int, int> waypointPosition = {10, 1};

    std::string line;
    while (getline(std::cin, line)) {
        int parameter = stoi(line.substr(1));
        switch (line[0]) {
            case 'N':
                position.second += parameter;

                waypointPosition.second += parameter;
                break;
            
            case 'E':
                position.first += parameter;

                waypointPosition.first += parameter;
                break;
            
            case 'S':
                position.second -= parameter;

                waypointPosition.second -= parameter;
                break;
            
            case 'W':
                position.first -= parameter;

                waypointPosition.first -= parameter;
                break;
            
            case 'L':
                rotation -= parameter / 90;
                while (rotation < 0) {
                    rotation += 4 ;
                }

                for (int i = 0; i < parameter / 90; ++i) {
                    waypointPosition.second *= -1;
                    std::swap(waypointPosition.first, waypointPosition.second);
                }
                break;
            
            case 'R':
                rotation += parameter / 90;
                while (rotation >= 4) {
                    rotation -= 4;
                }

                for (int i = 0; i < parameter / 90; ++i) {
                    waypointPosition.first *= -1;
                    std::swap(waypointPosition.first, waypointPosition.second);
                }
                break;

            case 'F':
                position.first += parameter * directions[rotation].first;
                position.second += parameter * directions[rotation].second;

                shipPosition.first += parameter * waypointPosition.first;
                shipPosition.second += parameter * waypointPosition.second;
                break;
        }
    }

    std::cout << abs(position.first) + abs(position.second) << '\n' << abs(shipPosition.first) + abs(shipPosition.second) << '\n';
}