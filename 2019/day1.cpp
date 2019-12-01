#include <iostream>
#include <vector>

int calculateFuel(int mass);

int fuelSum(std::vector<int> mass) {
    int sum = 0;
    for (int i: mass) {
        sum += calculateFuel(i);
    }
    return sum;
}

int calculateFuel(int mass) {
    return mass / 3 - 2;
}

int calculateFuelRecursively(int mass);

int fuelSumWithFuel(std::vector<int> mass) {
    int sum = 0;
    for (int i: mass) {
        sum += calculateFuelRecursively(i);
    }
    return sum;
}

int calculateFuelRecursively(int mass) {
    int fuel = calculateFuel(mass);
    if (fuel > 0) {
        fuel += calculateFuelRecursively(fuel);
    } else if (fuel < 0) {
        fuel = 0;
    }
    return fuel;
}

int main() {
    std::vector<int> mass;
    int input;
    while(std::cin >> input) {
        mass.push_back(input);
    }
    std::cout << fuelSum(mass) << '\n' << fuelSumWithFuel(mass) << '\n';
}