#include "project/recursive_algorithms.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values{1, 3, 5, 7, 9};
    std::cout << "5! = " << factorial(5) << '\n'
              << "F(10) = " << fibonacci(10) << '\n'
              << "Index of 7 = " << binarySearch(values, 7) << '\n'
              << "Sum = " << arraySum(values) << '\n';
    reverseArray(values);
    std::cout << "Reversed:";
    for (int value : values) std::cout << ' ' << value;
    std::cout << '\n';
}
