#include "catch.hpp"
#include "project/recursive_algorithms.h"
#include <limits>
#include <stdexcept>
#include <vector>

TEST_CASE("numeric boundaries and overflow are consistent") {
    REQUIRE(factorial(12) == 479001600);
    REQUIRE(factorialIterative(12) == 479001600);
    REQUIRE(fibonacci(46) == 1836311903);
    REQUIRE(fibonacciIterative(46) == 1836311903);
    REQUIRE_THROWS_AS(factorial(13), std::overflow_error);
    REQUIRE_THROWS_AS(factorialIterative(13), std::overflow_error);
    REQUIRE_THROWS_AS(fibonacci(47), std::overflow_error);
    REQUIRE_THROWS_AS(fibonacciIterative(47), std::overflow_error);
    REQUIRE_THROWS_AS(factorial(std::numeric_limits<int>::min()), std::invalid_argument);
    REQUIRE_THROWS_AS(fibonacci(std::numeric_limits<int>::min()), std::invalid_argument);
}
TEST_CASE("binary search singleton misses and duplicate matches") {
    for (auto search : {binarySearch, binarySearchIterative}) {
        REQUIRE(search({42}, 41) == -1);
        REQUIRE(search({42}, 43) == -1);
        const std::vector<int> values{-5, -2, -2, -2, 7};
        const int index = search(values, -2);
        REQUIRE(index >= 1);
        REQUIRE(index <= 3);
        REQUIRE(values[index] == -2);
        REQUIRE(search(values, 0) == -1);
    }
}
TEST_CASE("array sum detects overflow and allows cancellation") {
    const int maximum = std::numeric_limits<int>::max();
    const int minimum = std::numeric_limits<int>::min();
    for (auto sum : {arraySum, arraySumIterative}) {
        REQUIRE(sum({maximum}) == maximum);
        REQUIRE(sum({minimum}) == minimum);
        REQUIRE(sum({maximum, 1, -1}) == maximum);
        REQUIRE(sum({-1, minimum, 1}) == minimum);
        REQUIRE_THROWS_AS(sum({maximum, 1}), std::overflow_error);
        REQUIRE_THROWS_AS(sum({minimum, -1}), std::overflow_error);
    }
}
TEST_CASE("reversal preserves storage and restores original after two calls") {
    for (auto reverse : {reverseArray, reverseArrayIterative}) {
        for (const auto& original : std::vector<std::vector<int>>{
                 {}, {8}, {1, 2}, {1, 2, 3, 4}, {4, 3, 2, 1}, {2, 2, 2}}) {
            auto values = original;
            const auto* storage = values.data();
            reverse(values);
            REQUIRE(values == std::vector<int>(original.rbegin(), original.rend()));
            REQUIRE(values.data() == storage);
            reverse(values);
            REQUIRE(values == original);
        }
    }
}
