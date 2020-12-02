#include <iostream>
#include <vector>
#include <string>
#include <regex>

struct Password {
    std::string password;

    int x, y;
    char ch;
};

int countAllowed(const std::vector<Password> &passwords) {
    int allowed = 0;

    for (Password password: passwords) {
        int matchingChars = 0;
        for (char ch: password.password) {
            if (ch == password.ch) {
                ++matchingChars;
            }
        }

        if (matchingChars >= password.x && matchingChars <= password.y) {
            ++allowed;
        }
    }

    return allowed;
}

int countAllowed2(const std::vector<Password> &passwords) {
    int allowed = 0;

    for (Password password: passwords) {
        int matches = 0;
        if (password.password[password.x - 1] == password.ch) {
            ++matches;
        }
        if (password.password[password.y - 1] == password.ch) {
            ++matches;
        }

        if (matches == 1) {
            ++allowed;
        }
    }

    return allowed;
}

Password parseInput(const std::string line) {
    Password password;

    std::smatch match;
    if (std::regex_match(line, match, std::regex("(\\d+)-(\\d+) (\\w): (\\w+)")) && match.size() == 4 + 1) {
        password.x = stoi(match[1].str());
        password.y = stoi(match[2].str());
        password.ch = match[3].str()[0];
        password.password = match[4].str();
    }

    return password;
}

int main() {
    std::vector<Password> passwords;

    std::string line;
    while (getline(std::cin, line)) {
        passwords.push_back(parseInput(line));
    }

    std::cout << countAllowed(passwords) << '\n' << countAllowed2(passwords) << '\n';
}