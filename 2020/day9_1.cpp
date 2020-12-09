#include <iostream>
#include <vector>

#define PREAMBLE_LENGHT 25

bool isValid(int number, std::vector<int> &data) {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data.size(); ++j) {
            if (i != j && data[i] + data[j] == number) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int invalid = -1;

    std::vector<int> data;
    while (!std::cin.eof()) {
        if (data.size() > PREAMBLE_LENGHT) {
            if (!isValid(data[PREAMBLE_LENGHT], data)) {
                invalid = data[PREAMBLE_LENGHT];
                break;
            }
            data.erase(data.begin());
        }
        
        int number;
        std::cin >> number;
        data.push_back(number);
    }

    while (!std::cin.eof()) {
        std::cin.ignore();
    }

    std::cout << invalid << '\n';
}