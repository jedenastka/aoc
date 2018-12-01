#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int calculateFrequency(std::vector<int> input, int start) {
    int actual = start;
    for (std::vector<int>::iterator itr = input.begin(); itr != input.end(); ++itr) {
        actual += *itr;
    }
    return actual;
}

int findDoubledFrequency(std::vector<int> input, int start) {
    std::set<int> values;
    int actual = start;
    while (1) {
        for (std::vector<int>::iterator itr = input.begin(); itr != input.end(); ++itr) {
            actual += *itr;
            if (values.find(actual) != values.end()) {
                return actual;
            }
            values.insert(actual);
        }
    }
}

int main() {
    std::cout << "Advent of Code 2018 (https://adventofcode.com/2018/)\n" << "Day 1 (https://adventofcode.com/2018/day/1)\n" << "Coded by Grzesiek11.\n";
    //Here you see my stupidness: I wanted to get all these frequencies from keyboard :P
    /*std::cout << "How many input?\n";
    std::cin >> inputSize;
    int input[inputSize];
    for (int i = 0; i < inputSize; i++) {
        std::cout << "Enter frequency " << i+1 << ": ";
        std::cin >> input[i];
    }*/
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
    std::vector<int> rawInput;
    for (std::vector<std::string>::iterator itr = input.begin(); itr != input.end(); ++itr) {
        rawInput.push_back(std::stoi(*itr));
    }
    std::cout << "Final frequency is " << calculateFrequency(rawInput, 0) << ".\n";
    std::cout << "Frequency that doubles is " << findDoubledFrequency(rawInput, 0) << ".\n";
}