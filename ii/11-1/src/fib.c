#include "fib.h"

// How to improve:
// 1. Use memoization to store previously computed Fibonacci numbers.
// 2. Use an iterative approach to avoid stack overflow for large n.
// 3. Use a bottom-up approach to compute Fibonacci numbers in linear time.
// 4. Use a closed-form expression (Binet's formula) for constant time computation.
// 5. Use matrix exponentiation for logarithmic time computation.
// 6. Use a lookup table for small values of n to speed up computation.
// 7. Use tail recursion to optimize space complexity.
// 8. Use a generator to yield Fibonacci numbers one by one.
int fib(int n) {
	if (n <= 0) {
		return 0;
	}
	if (n == 1) {
			return n;
	}
	return fib(n - 1) + fib(n - 2);
}