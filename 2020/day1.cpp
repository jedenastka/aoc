#include <iostream>
#include <vector>

int sumVector(std::vector<int> numbers) {
    int sum = 0;
    for (int number: numbers) {
        sum += number;
    }
    return sum;
}

std::vector<int> findNSummingTo(const int n, const int sum, const std::vector<int> &numbers, int currentNumber = -1) {
    if (n < 1) {
        return std::vector<int>();
    }
    for (int i = 0; i < numbers.size(); ++i) {
        if (currentNumber != i) {
            std::vector<int> summing = findNSummingTo(n - 1, sum - numbers[i], numbers, i);
            if (sumVector(summing) + numbers[i] == sum) {
                summing.push_back(numbers[i]);
                return summing;
            }
        }
    }
    return std::vector<int>();
}

int multiplyVector(std::vector<int> numbers) {
    int result = 1;
    for (int number: numbers) {
        result *= number;
    }
    return result;
}

int main() {
    std::vector<int> numbers;
    while (!std::cin.eof()) {
        int number;
        std::cin >> number;
        numbers.push_back(number);
    }

    std::cout << multiplyVector(findNSummingTo(2, 2020, numbers)) << '\n' << multiplyVector(findNSummingTo(3, 2020, numbers)) << '\n';
}