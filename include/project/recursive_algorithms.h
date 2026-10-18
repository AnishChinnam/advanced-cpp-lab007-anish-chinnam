#pragma once

#include <vector>

// Students must implement each of the following recursively.
// Do not use loops inside the recursive implementations.
// For each function, identify the base case and recursive case in comments.

int factorial(int n);
int factorialIterative(int n);

int fibonacci(int n);
int fibonacciIterative(int n);

int binarySearch(const std::vector<int>& array, int target);
int binarySearchIterative(const std::vector<int>& array, int target);

int arraySum(const std::vector<int>& array);
int arraySumIterative(const std::vector<int>& array);

void reverseArray(std::vector<int>& array);
void reverseArrayIterative(std::vector<int>& array);

// Contracts for both forms:
// factorial: 0 <= n <= 12; fibonacci: 0 <= n <= 46 (32-bit int).
// Negative inputs throw invalid_argument; unrepresentable results throw overflow_error.
// binarySearch requires ascending sorted input, returns any matching index or -1,
// and throws length_error when the array size exceeds the int index range.
// arraySum returns 0 for empty input and throws overflow_error if the final sum
// cannot fit in int. Intermediate sums must fit in long long.
// reverseArray modifies its input in place; empty and singleton inputs are valid.
