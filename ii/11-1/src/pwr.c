#include "pwr.h"


// How to improve:
// 1. Use memoization to store previously computed powers.
// 2. Use an iterative approach to avoid stack overflow for large exponents.
// 3. Use a closed-form expression for constant time computation.
// 4. Use a lookup table for small values of base and exponent to speed up computation.
// 5. Use binary exponentiation for logarithmic time computation.
// 6. Use tail recursion to optimize space complexity.
// 7. Use a generator to yield powers one by one.
// 8. Use a logarithmic approach to compute powers in constant time.
int pwr(int base, int exp) {
	if (exp < 0) {
		return 0;
	}
	if (exp == 0) {
		return 1;
	}
	return base * pwr(base, exp - 1);
}