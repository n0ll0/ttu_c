#include <stdio.h>

int main()
{
  int n;

  printf("Input an integer: ");
  scanf("%d", &n);

  // printf("%d\n", n);

  int mod_3 = n % 3;
  int mod_5 = n % 5;

  if ((mod_5 == 0) && (mod_3 == 0)) {
    printf("Divisible by both 3 and 5.\n");
  } else if (mod_3 == 0) {
    printf("Divisible by 3.\n");
  } else if (mod_5 == 0) {
    printf("Divisible by 5.\n");
  } else {
    printf("Divisible by neither 3 nor 5.\n");
  }

  // to get multiples of 3 and 5, we divide
  int div_3 = n / 3;
  if (n < 3) {
    div_3 = 0;
  }
  int div_5 = n / 5;
  if (n < 5) {
    div_5 = 0;
  }

  printf("Dividing %d by 3, ", n);
  printf("we get %d multiples of 3 ", div_3);
  printf("and a remainder of %d.\n", mod_3);

  printf("Dividing %d by 5, ", n);
  printf("we get %d multiples of 5 ", div_5);
  printf("and a remainder of %d.\n", mod_5);
  // printf("Dividing %d by 3, we get %d multiples of 3 and a remainder of %d.\n", n, div_3, mod_3);
  // printf("Dividing %d by 5, we get %d multiples of 5 and a remainder of %d.\n", n, div_5, mod_5);

  return 0;
}
