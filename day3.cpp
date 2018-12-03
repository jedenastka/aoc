#include <iostream>
#include <fstream>
#include <vector>

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
    std::cout << "Raw paste values:\n" << "nthng" << "\n";
}