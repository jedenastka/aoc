#include <iostream>
#include <vector>
#include <string>
#include <utility>

typedef std::vector<std::pair<std::string, std::string>> OrbitMap;

OrbitMap parseInput(std::vector<std::string> input) {
    OrbitMap orbitMap;
    for (std::string line: input) {
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == ')') {
                orbitMap.push_back(std::make_pair(line.substr(0, i), line.substr(i + 1)));
                break;
            }
        }
    }
    return orbitMap;
}

int main() {
    std::vector<std::string> input;
    std::string line;
    while (getline(std::cin, line)) {
        input.push_back(line);
    }
    OrbitMap orbitMap = parseInput(input);
}