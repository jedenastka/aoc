#include <string>
#include <vector>
#include <iostream>
#include <utility>

typedef std::vector<std::vector<bool>> Map;

int countTrees(const std::pair<int, int> step, const std::pair<int, int> start, const Map &map) {
    int x = start.first;
    int y = start.second;

    int trees = 0;
    while (y < map.size()) {

        if (map[y][x]) {
            ++trees;
        }

        x += step.first;
        if (x >= map[0].size()) {
            x -= map[0].size();
        }
        y += step.second;
    }

    return trees;
}

int main() {
    Map map;

    std::string line;
    while (getline(std::cin, line)) {
        std::vector<bool> row;
        for (char ch: line) {
            bool position;
            switch (ch) {
                case '.':
                    position = 0;
                    break;

                case '#':
                    position = 1;
                    break;

                default:
                    continue;
            }
            row.push_back(position);
        }
        map.push_back(row);
    }

    std::cout << countTrees(std::make_pair(3, 1), std::make_pair(0, 0), map) << '\n';
    std::vector<std::pair<int, int>> paths = {
        std::make_pair(1, 1),
        std::make_pair(3, 1),
        std::make_pair(5, 1),
        std::make_pair(7, 1),
        std::make_pair(1, 2)
    };
    long int result = 1;
    for (auto path: paths) {
        result *= countTrees(path, std::make_pair(0, 0), map);
    }
    std::cout << result << '\n';
}