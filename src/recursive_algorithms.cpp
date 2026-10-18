#include "project/recursive_algorithms.h"

#include <array>
#include <limits>
#include <stdexcept>
#include <utility>

namespace {
void validateFactorial(int n) {
    if (n < 0) throw std::invalid_argument("factorial requires n >= 0");
    if (n > 12) throw std::overflow_error("factorial exceeds int range");
}
void validateFibonacci(int n) {
    if (n < 0) throw std::invalid_argument("fibonacci requires n >= 0");
    if (n > 46) throw std::overflow_error("fibonacci exceeds int range");
}
int fibonacciMemo(int n, std::array<int, 47>& memo) {
    // Base cases: F(0) = 0, F(1) = 1, or an already computed value.
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];
    // Recursive case: compute and cache the two preceding Fibonacci values.
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}
void validateSearchSize(const std::vector<int>& array) {
    if (array.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw std::length_error("search index cannot fit in int");
}
int searchRange(const std::vector<int>& array, int target,
                std::size_t first, std::size_t last) {
    // Base cases: empty half-open range, or a matching midpoint.
    if (first == last) return -1;
    const auto middle = first + (last - first) / 2;
    if (array[middle] == target) return static_cast<int>(middle);
    // Recursive case: search only the half that can contain the target.
    if (target < array[middle]) return searchRange(array, target, first, middle);
    return searchRange(array, target, middle + 1, last);
}
long long sumFrom(const std::vector<int>& array, std::size_t index) {
    // Base case: no remaining elements contribute zero.
    if (index == array.size()) return 0;
    // Recursive case: add the current element to the remaining sum.
    return static_cast<long long>(array[index]) + sumFrom(array, index + 1);
}
int checkedSum(long long sum) {
    if (sum < std::numeric_limits<int>::min() || sum > std::numeric_limits<int>::max())
        throw std::overflow_error("array sum exceeds int range");
    return static_cast<int>(sum);
}
void reverseRange(std::vector<int>& array, std::size_t first, std::size_t last) {
    // Base case: a half-open range with zero or one element is reversed.
    if (last - first <= 1) return;
    // Recursive case: swap endpoints and reverse the inner range in place.
    std::swap(array[first], array[last - 1]);
    reverseRange(array, first + 1, last - 1);
}
} // namespace

int factorial(int n) {
    validateFactorial(n);
    // Base case: 0! and 1! are 1.
    if (n <= 1) return 1;
    // Recursive case: n! = n * (n - 1)!.
    return n * factorial(n - 1);
}
int factorialIterative(int n) {
    validateFactorial(n);
    int result = 1;
    for (int factor = 2; factor <= n; ++factor) result *= factor;
    return result;
}
int fibonacci(int n) {
    validateFibonacci(n);
    // A fresh cache belongs to this call; no global state or loops are needed.
    std::array<int, 47> memo{};
    return fibonacciMemo(n, memo);
}
int fibonacciIterative(int n) {
    validateFibonacci(n);
    if (n <= 1) return n;
    int previous = 0;
    int current = 1;
    for (int index = 2; index <= n; ++index) {
        const int next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}
int binarySearch(const std::vector<int>& array, int target) {
    validateSearchSize(array);
    return searchRange(array, target, 0, array.size());
}
int binarySearchIterative(const std::vector<int>& array, int target) {
    validateSearchSize(array);
    std::size_t first = 0;
    std::size_t last = array.size();
    while (first < last) {
        const auto middle = first + (last - first) / 2;
        if (array[middle] == target) return static_cast<int>(middle);
        if (target < array[middle]) last = middle;
        else first = middle + 1;
    }
    return -1;
}
int arraySum(const std::vector<int>& array) {
    return checkedSum(sumFrom(array, 0));
}
int arraySumIterative(const std::vector<int>& array) {
    long long sum = 0;
    for (int value : array) sum += value;
    return checkedSum(sum);
}
void reverseArray(std::vector<int>& array) {
    reverseRange(array, 0, array.size());
}
void reverseArrayIterative(std::vector<int>& array) {
    std::size_t first = 0;
    std::size_t last = array.size();
    while (last - first > 1) {
        std::swap(array[first], array[last - 1]);
        ++first;
        --last;
    }
}
