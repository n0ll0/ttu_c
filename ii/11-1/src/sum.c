#include "sum.h"


// How to improve:
// 1. Use memoization to store previously computed sums.
// 2. Use an iterative approach to avoid stack overflow for large n.
// 3. Use a closed-form expression for constant time computation.
// 4. Use a lookup table for small values of n to speed up computation.
// 5. Use a generator to yield sums one by one.
// 6. Use a logarithmic approach to compute sums in constant time.
// 7. Use tail recursion to optimize space complexity.
// 8. Use a divide-and-conquer approach to compute sums in logarithmic time.
int sum(int n) {
	if (n <= 0) {
		return 0;
	}

	return n + sum(n - 1);
}