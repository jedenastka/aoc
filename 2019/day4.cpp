#include <iostream>
#include <string>
#include <utility>
#include <vector>

int ctoi(char ch) {
    return ch - '0';
}

std::pair<int, int> parseRange(std::string rangeString) {
    int from, to;
    std::string tmp;
    for (int i = 0; i < rangeString.length(); i++) {
        char ch = rangeString[i];
        if (ch == '-') {
            from = stoi(tmp);
            tmp = "";
        } else {
            tmp += ch;
        }
        if (i + 1 >= rangeString.length()) {
            to = stoi(tmp);
            tmp = "";
        }
    }
    return std::make_pair(from, to);
}

std::vector<int> findPasswords(std::pair<int, int> range, bool part2);
bool checkPassword(int password, bool part2);

int countPasswords(std::pair<int, int> range, bool part2) {
    return findPasswords(range, part2).size();
}

std::vector<int> findPasswords(std::pair<int, int> range, bool part2) {
    std::vector<int> passwords;
    for (int password = std::get<0>(range); password <= std::get<1>(range); password++) {
        if (checkPassword(password, part2)) {
            passwords.push_back(password);
        }
    }
    return passwords;
}

bool checkPassword(int password, bool part2) {
    std::string passwordString = std::to_string(password);
    if (passwordString.length() != 6) {
        return 0;
    }
    int inRow;
    bool doubleDigit = 0;
    for (int i = 0; i < passwordString.length(); i++) {
        char digit = passwordString[i];
        if (i > 0 && digit == passwordString[i - 1]) {
            inRow++;
            if (inRow == 2) {
                doubleDigit = 1;
            } else if (inRow > 2 && part2) {
                return 0;
            }
        } else {
            inRow = 1;
        }
        if (i > 0 && ctoi(digit) < ctoi(passwordString[i - 1])) {
            return 0;
        }
    }
    return doubleDigit;
}


int main() {
    std::string rangeString;
    std::cin >> rangeString;
    std::pair<int, int> range = parseRange(rangeString);
    std::cout << countPasswords(range, 0) << '\n' << countPasswords(range, 1) << '\n';
}