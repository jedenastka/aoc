#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

std::map<char, int> countChars(std::string box) {
    std::map<char, int> charCount;
    for (int i = 0; i < box.length(); i++) {
        char actualChar = box[i];
        if (charCount.find(actualChar) != charCount.end()) {
            charCount[actualChar]++;
        } else {
            charCount[actualChar] = 1;
        }
    }
    return charCount;
}

void isDoubleOrTriple(std::map<char, int> charCount, bool &isDouble, bool &isTriple) {
    for (std::map<char, int>::iterator itr = charCount.begin(); itr != charCount.end(); ++itr) {
        if (itr->second == 2) {
            isDouble = 1;
        } else if (itr->second == 3) {
            isTriple = 1;
        }
        if (isDouble & isTriple) {
            return;
        }
    }
}

int calculateChecksum(std::vector<std::string> input) {
    int doubled = 0;
    int tripled = 0;
    for (std::vector<std::string>::iterator itr = input.begin(); itr != input.end(); ++itr) {
        std::map<char, int> charCount = countChars(*itr);
        bool isDouble = 0;
        bool isTriple = 0;
        isDoubleOrTriple(charCount, isDouble, isTriple);
        doubled += isDouble;
        tripled += isTriple;
    }
    int checksum = doubled * tripled;
    return checksum;
}

int main() {
    std::cout << "Advent of Code 2018 (https://adventofcode.com/2018/)\n" << "Day 2 (https://adventofcode.com/2018/day/2)\n" << "Coded by Grzesiek11.\n";
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
    std::cout << "The final checksum of the boxes is " << calculateChecksum(input) << ".\n";
}