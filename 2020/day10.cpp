#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

void joltageDifference(int x, int y, int &differencesOf1, int &differencesOf3) {
    switch (x - y) {
        case 1:
            ++differencesOf1;
            break;
    
        case 3:
            ++differencesOf3;
            break;
    }
}

std::vector<int> nextAdapters(std::vector<int> &adapterList, int currentJoltage) {
    std::vector<int> next;
    for (int i = 1; i <= 3; ++i) {
        if (std::find(adapterList.begin(), adapterList.end(), currentJoltage + i) != adapterList.end()) {
            next.push_back(currentJoltage + i);
        }
    }
    return next;
}

long int buildPossibleChains(std::vector<int> &adapterList, int end, int start = 0, std::map<int, long int> *cache = nullptr) {
    bool deleteCache = false;
    if (cache == nullptr) {
        deleteCache = true;
        cache = new std::map<int, long int>;
    }

    long int count = 0;

    if (cache->find(start) != cache->end()) {
        return (*cache)[start];
    } else {
        if (start == end) {
            count = 1;
        } else {
            std::vector<int> next = nextAdapters(adapterList, start);
            for (int i: next) {
                count += buildPossibleChains(adapterList, end, i, cache);
            }
        }
        (*cache)[start] = count;
    }

    if (deleteCache) {
        delete cache;
    }

    return count;
}

int main() {
    std::vector<int> adapterList = {0};

    while (!std::cin.eof()) {
        int joltage;
        std::cin >> joltage;
        adapterList.push_back(joltage);
    }
    adapterList.pop_back(); // Fix for strange std::cin behaviour

    std::sort(adapterList.begin(), adapterList.end(), std::less<int>());

    int differencesOf1 = 0, differencesOf3 = 0;
    int maxJoltage = adapterList[0];
    int lastJoltage = adapterList[0];
    for (int i = 1; i < adapterList.size(); ++i) {
        if (adapterList[i] > maxJoltage) {
            maxJoltage = adapterList[i];
        }

        joltageDifference(adapterList[i], lastJoltage, differencesOf1, differencesOf3);

        lastJoltage = adapterList[i];
    }
    adapterList.push_back(maxJoltage + 3);
    joltageDifference(adapterList.back(), lastJoltage, differencesOf1, differencesOf3);

    std::cout << differencesOf1 * differencesOf3 << '\n' << buildPossibleChains(adapterList, adapterList.back()) << '\n';
}