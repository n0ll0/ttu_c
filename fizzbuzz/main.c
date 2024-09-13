#include <stdio.h>
#include <stdlib.h>

int better_int_div(int numerator, int denominator) // only for positive integers!
{
  if (abs(numerator) < denominator)
    return 0;
  return numerator / denominator;
};

int main()
{
  int n;

  printf("Input an integer: ");
  scanf("%d", &n);

  int mod_3 = n % 3;
  int mod_5 = n % 5;

  if ((mod_5 == 0) && (mod_3 == 0))
  {
    printf("Divisible by both 3 and 5.\n");
  }
  else if (mod_3 == 0)
  {
    printf("Divisible by 3.\n");
  }
  else if (mod_5 == 0)
  {
    printf("Divisible by 5.\n");
  }
  else
  {
    printf("Divisible by neither 3 nor 5.\n");
  }

  // to get multiples of 3 and 5, we divide accordingly
  int div_3 = better_int_div(n, 3);
  int div_5 = better_int_div(n, 5);

  printf("Dividing %d by 3, ", n);
  printf("we get %d multiples of 3 ", div_3);
  printf("and a remainder of %d.\n", mod_3);

  printf("Dividing %d by 5, ", n);
  printf("we get %d multiples of 5 ", div_5);
  printf("and a remainder of %d.\n", mod_5);

  return 0;
}
