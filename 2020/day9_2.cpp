#include <iostream>
#include <vector>

#define PART1_SOLUTION 138879426

int main() {
    int encryptionWeakness;

    std::vector<int> data;
    bool foundSet = false;
    while (!std::cin.eof()) {
        int number;
        std::cin >> number;
        data.push_back(number);

        for (int i = 0; i < data.size() - 1; ++i) {
            int sum = 0;
            for (int j = i; j < data.size(); ++j) {
                sum += data[j];
            }

            if (sum == PART1_SOLUTION) {
                foundSet = true;

                int smallest = data[i], biggest = data[i];
                for (int j = i + 1; j < data.size(); ++j) {
                    if (data[j] < smallest) {
                        smallest = data[j];
                    } else if (data[j] > biggest) {
                        biggest = data[j];
                    }
                }

                encryptionWeakness = smallest + biggest;
                
                break;
            }
        }
        if (foundSet) {
            break;
        }
    }

    while (!std::cin.eof()) {
        std::cin.ignore();
    }

    if (foundSet) {
        std::cout << encryptionWeakness << '\n';
    }
}