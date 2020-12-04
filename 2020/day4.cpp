#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <iterator>

typedef std::map<std::string, std::string> Passport;

Passport parsePassport(const std::string passportLine) {
    Passport passport;

    std::regex r("(\\S+?):(\\S+)");
    for (std::sregex_iterator itr = std::sregex_iterator(passportLine.begin(), passportLine.end(), r); itr != std::sregex_iterator(); ++itr) {
        std::string tmp;
        for (int i = 1; i < itr->size(); ++i) {
            if (i % 2 == 1) {
                tmp = itr->operator[](i);
            } else {
                passport[tmp] = itr->operator[](i);
            }
        }
    }

    return passport;
}

bool isValid(Passport passport) {
    const std::string requiredFields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    
    for (std::string field: requiredFields) {
        if (passport.find(field) == passport.end()) {
            return false;
        }
    }
    return true;
}

bool isNumeric(std::string string) {
    for (char ch: string) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool isValid2(Passport passport) {
    if (!(passport.find("byr") != passport.end()
        && isNumeric(passport["byr"])
        && stoi(passport["byr"]) >= 1920
        && stoi(passport["byr"]) <= 2002)) {
        return false;
    }
    if (!(passport.find("iyr") != passport.end()
        && isNumeric(passport["iyr"])
        && stoi(passport["iyr"]) >= 2010
        && stoi(passport["iyr"]) <= 2020)) {
        return false;
    }
    if (!(passport.find("eyr") != passport.end()
        && isNumeric(passport["eyr"])
        && stoi(passport["eyr"]) >= 2020
        && stoi(passport["eyr"]) <= 2030)) {
        return false;
    }

    if (passport["hgt"].length() > 2) {
        std::string heightUnit = passport["hgt"].substr(passport["hgt"].length()-2);
        std::string height = passport["hgt"].substr(0, passport["hgt"].length()-2);
        if (isNumeric(height)
            && stoi(height)
            && (heightUnit == "cm" || heightUnit == "in")) {
            if (heightUnit == "cm"
                && !(stoi(height) >= 150
                && stoi(height) <= 193)) {
                return false;
            } else if (heightUnit == "in"
                    && !(stoi(height) >= 59
                    && stoi(height) <= 76)) {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    if (passport["hcl"].length() == 7 && passport["hcl"][0] == '#') {
        for (char ch: passport["hcl"].substr(1)) {
            if (!((ch >= '0' && ch <= '9')
                || (ch >= 'a' && ch <= 'f'))) {
                return false;
            }
        }
    } else {
        return false;
    }

    const std::string validEyeColors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    bool valid = false;
    for (std::string eyeColor: validEyeColors) {
        if (eyeColor == passport["ecl"]) {
            valid = true;
            break;
        }
    }
    if (!valid) {
        return false;
    }

    if (!(isNumeric(passport["pid"])
        && passport["pid"].size() == 9)) {
        return false;
    }

    return true;
}

int main() {
    std::string currentPassportLine;
    int validPassports = 0;
    int validPassports2 = 0;

    while (1) {
        std::string line;
        getline(std::cin, line);


        if (line.length() != 0 || std::cin.eof()) {
            currentPassportLine += " " + line;
        }
        if (line.length() == 0 || std::cin.eof()) {
            Passport passport = parsePassport(currentPassportLine);
            if (isValid(passport)) {
                ++validPassports;
            }
            if (isValid2(passport)) {
                ++validPassports2;
            }
            currentPassportLine.clear();
        }

        if (std::cin.eof()) {
            break;
        }
    }
    std::cout << validPassports << '\n' << validPassports2 << '\n';
}