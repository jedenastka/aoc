#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <string>

typedef std::pair<std::vector<bool>, std::vector<bool>> Pass;

int binarySearch(std::vector<bool> instructions, std::pair<int, int> range) {
    for (bool instruction: instructions) {
        if (instruction) {
            range.first = (range.second - range.first) / 2 + 1 + range.first;
        } else {
            range.second = (range.second - range.first) / 2 + range.first;
        }
    }
    
    return range.first;
}

Pass parsePass(std::string instructionString) {
    Pass pass;

    for (char instructionChar: instructionString) {
        switch (instructionChar) {

            case 'F':
                pass.first.push_back(false);
                break;
            
            case 'B':
                pass.first.push_back(true);
                break;
            
            case 'L':
                pass.second.push_back(false);
                break;
            
            case 'R':
                pass.second.push_back(true);
                break;

        }
    }

    return pass;
}

int main() {
    int maxId;
    std::vector<int> passIds;

    std::string line;
    for (int i = 0; getline(std::cin, line); ++i) {
        Pass pass = parsePass(line);
        int id = binarySearch(pass.first, std::make_pair(0, 127)) * 8 + binarySearch(pass.second, std::make_pair(0, 7));
        if (i == 0 || id > maxId) {
            maxId = id;
        }
        passIds.push_back(id);
    }
    std::cout << maxId << '\n';

    std::sort(passIds.begin(), passIds.end(), std::less<int>());
    for (int i = 1; i < passIds.size(); ++i) {
        if (passIds[i] - passIds[0] != i) {
            std::cout << passIds[i] - 1 << '\n';
            break;
        }
    }
}