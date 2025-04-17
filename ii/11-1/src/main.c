#include <stdio.h>
#include <stdlib.h>
#include "fib.h"
#include "pwr.h"
#include "sum.h"


int main(int argc, char const *argv[])
{
	fprintf(stderr, "This program runs 3 recursive funtions: \n\tfibonacci sequence to number\n\tBase to power of exponent\n\tsum of positive integert until provided value\n");
	if (argc != 3) {
			fprintf(stderr, "Usage: %s <number {base or number}> <number {exponent}>\n", argv[0]);
			return 1;
	}

	int base = atoi(argv[1]);
	int exp = atoi(argv[2]);
	if (base < 0 || exp < 0) {
			fprintf(stderr, "Error: numbers must be non-negative\n");
			return 1;
	}

	printf("Fibonacci of %d is %d\n", base, fib(base));
	printf("%d to the power of %d is %d\n", base, exp, pwr(base, exp));
	printf("Sum of first %d numbers is %d\n", base, sum(base));
	return 0;
}


