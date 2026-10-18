# Recursive and iterative algorithm comparison

Build the demo with `make`, run it with `make run`, and run the tests with
`make test`. All implementations use the supplied public interface.

## Contracts and design

Factorial and Fibonacci reject negative inputs with `std::invalid_argument`
(which derives from `std::logic_error`). With the project's 32-bit `int`,
factorial supports 0 through 12 and Fibonacci supports 0 through 46. Larger
inputs throw `std::overflow_error` before arithmetic can overflow.

Binary search requires ascending sorted input. Both versions return a matching
index or -1; with duplicates, any matching index is valid. Sorting is a caller
precondition, not a linear validation pass, so search stays logarithmic. Arrays
whose size exceeds the return type's index range are rejected. Half-open ranges
avoid unsigned underflow on empty arrays and when searching below the minimum.

Array sum uses `long long` intermediates and checks the final result before
converting to `int`. This permits cancellation even when an intermediate sum
exceeds `int`. The sum of intermediate values must fit in `long long`.
Reversal swaps elements in the original vector without allocating a copy.
The recursive implementations and their helpers contain no loops.

## Complexity and recursive calls

Here n is the numeric argument or array length. Space is auxiliary storage,
excluding the input vector. Bounds describe the algorithms as n grows; the
public integer limits make factorial and Fibonacci bounded in this API.

| Algorithm | Recursive time | Recursive space/depth | Calls | Iterative time | Iterative space |
| --- | --- | --- | --- | --- | --- |
| Factorial | O(n) | O(n) stack | n calls for n >= 1; one for 0 | O(n) | O(1) |
| Fibonacci with memoization | O(n) | O(n) stack and cache | 2n - 1 helper calls for n >= 2; one for 0 or 1 | O(n) | O(1) |
| Binary search | O(log n) worst case; O(1) best | O(log n) stack | At most floor(log2 n) + 2 helper calls for n >= 1, including an empty-range call | O(log n) worst; O(1) best | O(1) |
| Array sum | O(n) | O(n) stack | n + 1 helper calls, including empty suffix | O(n) | O(1) |
| In-place reversal | O(n) | O(n) stack | floor(n / 2) + 1 helper calls | O(n) | O(1) |

The Fibonacci cache is a fixed 47-element array in this implementation because
of the integer range limit. Conceptually it stores O(n) computed values; its
actual allocation here is constant. Each non-base Fibonacci value is expanded
once, then reused. Without memoization, the direct two-branch recurrence takes
O(phi^n) time (also bounded by O(2^n)), with O(n) stack depth. The iterative
version avoids both the cache and recursive calls by retaining two values.

## Readability, maintainability, and tradeoffs

Factorial closely matches its mathematical recurrence, making the recursive
version easy to inspect. The iterative accumulator is equally short and avoids
a stack frame for each multiplication. Here the maximum depth is only 12.

Fibonacci's recursive recurrence is clear, but memoization adds a helper and
cache state. It makes the solution practical through F(46). The iterative
version is simpler and uses less memory. Removing memoization would preserve
correctness but duplicate an exponential amount of work.

Binary search naturally reduces a problem to one smaller half. The recursive
helper makes this structure explicit; the iterative version updates the same
range in a loop and is preferable when minimizing overhead. Both avoid copying
subarrays and use a midpoint expression that cannot overflow the range.

Array sum's recursive base case and suffix reduction are concise. However,
its call depth grows with every element. The iterative loop is just as readable
and is safer for large vectors. Neither version changes the array.

Recursive reversal exposes the symmetric structure: swap the ends, then solve
the middle. The iterative version is a straightforward two-pointer loop and
uses constant storage. Both preserve the vector's size and allocation.

C++ does not guarantee tail-call optimization. Recursive sum and reversal can
overflow the call stack for large arrays; their iterative counterparts avoid
this risk. Search depth grows logarithmically, so its stack risk is far smaller.
Factorial and Fibonacci depth is restricted by input validation. In general,
recursion is useful when the smaller subproblem mirrors the original problem,
but iteration is preferable for simple linear traversals with large inputs.

## Testing

The supplied tests are retained. Additional cases cover the largest supported
numeric values, overflow rejection, singleton misses, duplicates, even and odd
reversals, empty vectors, double reversal, and sum cancellation. Each scenario
is named so a failure identifies the affected algorithm and boundary.
