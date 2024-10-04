#include <stdio.h>

int main(int argc, char const *argv[])
{

  return 0;
}

/**
 * Description:  Reads values from the user and stores them into the
 *               integer array provided
 *
 * Parameters:   nums - location to store values at
 *               len - length of the array
 *
 * Return:       -
 */
void ReadIntArray(int nums[], size_t len)
{
  for (int i = 0; i < len; i++)
  {
    int number;
    printf("Enter number %d / %ld: ", i + 1, len);
    scanf("%d", &number);
    nums[i] = number;
  }

  printf("\n");
}

int clearBuffer(int boolean, void (*ErrorFunction)())
{
  if (boolean)
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    (*ErrorFunction)();
  }
  return boolean;
}

int IsNumInRange(int n, int min, int max)
{
  return n >= min && n < max;
}

void PrintComparisson(int a, int b)
{
  if (a == b)
    printf("a & b are equal");

  if (a > b)
    printf("a is greater");

  if (a < b)
    printf("b is greater");

  printf("\n");
}

int read_int_in_range(void (*askFn)(), void (*ErrorFunction)(), int min, int max)
{
  int i;
  do
  {
    askFn();
  } while (clearBuffer((scanf("%d", &i) != 1) || !IsNumInRange(i, min, max), ErrorFunction));

  return i;
}
