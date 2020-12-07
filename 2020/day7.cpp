#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <regex>
#include <utility>

typedef std::pair<std::string, int> Bag;
typedef std::map<std::string, std::vector<Bag>> Bags;

std::vector<std::string> findBagsFor(std::string baseBag, Bags &allBags, std::vector<std::string> *alreadySearched = nullptr) {
    bool freeAlreadySearched = false;
    if (alreadySearched == nullptr) {
        alreadySearched = new std::vector<std::string>;
        freeAlreadySearched = true;
    }

    alreadySearched->push_back(baseBag);

    std::vector<std::string> foundBags;

    for (Bag bag: allBags[baseBag]) {
        if (std::find(alreadySearched->begin(), alreadySearched->end(), bag.first) == alreadySearched->end()) {
            foundBags.push_back(bag.first);
            std::vector<std::string> recursiveBags = findBagsFor(bag.first, allBags, alreadySearched);
            foundBags.insert(foundBags.end(), recursiveBags.begin(), recursiveBags.end());
        }
    }

    if (freeAlreadySearched) {
        delete alreadySearched;
    }

    return foundBags;
}

int countContainedBagsFor(std::string baseBag, Bags &allBags, bool firstIteration = true) {
    int sum = 1;
    if (firstIteration) {
        sum = 0;
    }

    for (Bag bag: allBags[baseBag]) {
        sum += bag.second * countContainedBagsFor(bag.first, allBags, false);
    }

    return sum;
}

std::string parse(std::string line, std::vector<Bag> &containedBags) {
    std::string bag;

    std::regex bagRegex("(.+) bags contain");
    std::smatch bagMatch;
    if (std::regex_search(line, bagMatch, bagRegex)) {
        bag = bagMatch[1];
    }

    std::regex containedRegex("(?:,? ?(\\d+) (.+?) bags?\\.?)");
    for (std::sregex_iterator itr = std::sregex_iterator(line.begin(), line.end(), containedRegex); itr != std::sregex_iterator(); ++itr) {
        containedBags.push_back(std::make_pair(itr->operator[](2), stoi(itr->operator[](1))));
    }

    return bag;
}

int main() {
    Bags bags;

    std::string line;
    while (getline(std::cin, line)) {
        std::vector<Bag> containedBags;
        bags[parse(line, containedBags)] = containedBags;
    }

    int bagSum = 0;

    for (auto bag: bags) {
        std::vector<std::string> foundBags = findBagsFor(bag.first, bags);
        if (std::find(foundBags.begin(), foundBags.end(), "shiny gold") != foundBags.end()) {
            ++bagSum;
        }
    }
    
    std::cout << bagSum << '\n' << countContainedBagsFor("shiny gold", bags) << '\n';
}