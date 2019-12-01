#include <iostream>
#include <fstream>
#include <vector>
#include <map>

enum MessageType {
    BEGIN,
    FALL_ASLEEP,
    WAKE_UP
};

struct RawLog {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    MessageType messageType;
    int guard;
};

void sortLogs(std::vector<RawLog> &rawLogs) {
    for (int i = 0; i < rawLogs.size(); i++) {
        int maxValIndex = 0;
        for (int j = i; j < rawLogs.size(); j++) {
            auto l = rawLogs[j];
            auto r = rawLogs[maxValIndex];
            if (l.year > r.year || (
            l.year == r.year && l.month > r.month || (
            l.month == r.month && l.day > r.day || (
            l.day == r.day && l.hour > r.hour || (
            l.hour == r.hour && l.minute > r.minute
            ))))) {
                maxValIndex = j;
            }
        }
        RawLog tmp = rawLogs[i];
        rawLogs[i] = rawLogs[maxValIndex];
        rawLogs[maxValIndex] = tmp;
    }
}

std::vector<RawLog> praseInput(std::vector<std::string> input) {
    std::vector<RawLog> rawLogs;
    for (auto i: input) {
        RawLog rawLog;
        rawLog.year = stoi(i.substr(i.find('[') + 1, i.find('-')));
        rawLog.month = stoi(i.substr(i.find('-') + 1, i.find('-', i.find('-') + 1)));
        rawLog.day = stoi(i.substr(i.find('-', i.find('-') + 1) + 1, i.find(' ')));
        rawLog.hour = stoi(i.substr(i.find(' ') + 1, i.find(':')));
        rawLog.minute = stoi(i.substr(i.find(':') + 1, i.find(']')));
        std::string message = i.substr(i.find(' ', i.find(' ')) + 1);
        if (message.find('#') != -1) {
            rawLog.guard = stoi(message.substr(message.find('#') + 1, message.find(' ', message.find(' '))));
            rawLog.messageType = BEGIN;
        } else if (message == "falls asleep") {
            rawLog.messageType = FALL_ASLEEP;
        } else if (message == "wakes up") {
            rawLog.messageType = WAKE_UP;
        } else {
            throw "Bad input, message type doesn't match.";
        }
        rawLogs.push_back(rawLog);
    }
    sortLogs(rawLogs);
    for (auto i: input) {
        int guard;
        switch (i.messageType) {
            case BEGIN:
                guard = i.guard;
                break;
            case FALL_ASLEEP:
            case WAKE_UP:
                i.guard = guard;
                break;
        }
    }
    return rawLogs;
}



int findMostSleepyGuard(std::vector<RawLog> rawLogs) {
    //...
}

int findMostSleepyMinute(std::vector<RawLog> rawLogs, int guard) {
    //...
}

int strategy1(std::vector<std::string> input) {
    std::vector<RawLog> rawLogs = praseInput(input);
    int guard = findMostSleepyGuard(rawLogs);
    int minute = findMostSleepyMinute(rawLogs, guard);
    int checksum = guard * minute;
    return checksum;
}

int main() {
    std::cout << "Advent of Code 2018 (https://adventofcode.com/2018/)\n" << "Day 4 (https://adventofcode.com/2018/day/3)\n" << "Coded by Grzesiek11.\n";
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
    std::cout << "Raw paste values:\n" << countClaimCollisions(input) << "\n";
}