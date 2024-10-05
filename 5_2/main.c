#include <stdio.h>

#define LENGTH 5

#define MIN_INT (int)0x80000000
#define MAX_INT (int)0x7fffffff

int GetIntInRange(int min, int max, char prompt[], char error[]);
int IsNumInRange(int num, int min, int max);
void ReadIntArray(int nums[], size_t len);
void PrintComparisson(int a, int b);
void DivideValues(int a, int b);

int main(int argc, char const *argv[])
{
  int nums[LENGTH];
  ReadIntArray(nums, LENGTH);

  char error[50];
  sprintf(error, "Error! Index must be between 1 and %d", LENGTH);
  int firstIndex = GetIntInRange(1, LENGTH, "Enter first index: ", error) - 1;
  printf("DEBUG: first corresponding value: %d\n", nums[firstIndex]);
  int secondIndex = GetIntInRange(1, LENGTH, "Enter second index: ", error) - 1;
  printf("DEBUG: second corresponding value: %d\n", nums[secondIndex]);

  PrintComparisson(nums[firstIndex], nums[secondIndex]);
  DivideValues(nums[firstIndex], nums[secondIndex]);
  return 0;
}

int IsNumInRange(int num, int min, int max)
{
  return num >= min && num <= max;
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Repeats until requirements are met and returns the number.
 *
 * Parameters:     min - lower bound for the user input (inclusive)
 *                 max - upper bound for the user input (inclusive)
 *                 prompt - prompt for user input, printed before entry
 *
 * Return:         number within the specified limits
 */
int GetIntInRange(int min, int max, char prompt[], char error[])
{
  printf("\n%s", prompt);
  int num;
  while (scanf("%d", &num) != 1 || !IsNumInRange(num, min, max))
  {
    printf("\n%s\n\n%s", error, prompt);
    while (getchar() != 10)
      ;
  }
  return num;
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
  char prompt[50];
  char *error = "Please enter an integer";

  for (int i = 0; i < len; ++i)
  {
    int number;
    sprintf(prompt, "Enter number %d / %ld: ", i + 1, len);
    nums[i] = GetIntInRange(MIN_INT, MAX_INT, prompt, error);
  }

  printf("\n");
}

/**
 * Description:    Compares the given values (val1 and val2) and prints
 *                 results of the comparison (which is greater; or equal)
 *
 * Parameters:     a - first value being compared
 *                 b - second value being compared
 *
 * Return:         -
 */
void PrintComparisson(int a, int b)
{
  if (a == b)
    printf("first = second");

  if (a > b)
    printf("first > second");

  if (a < b)
    printf("first < second");

  printf("\n");
}

/**
 * Description:    Compares the given values (a and b). Performs the
 *                 division by dividing greater number with the smaller number.
 *                 Both division operation and result are printed.
 *
 * Parameters:     a - first value
 *                 b - second value
 *
 * Return:         -
 */
void DivideValues(int a, int b)
{
  if (a == b)
  {
    if (b == 0)
    {
      printf("Cannot divide with 0!\n");
    }
    else
    {
      printf("%d / %d = 1\n", a, b);
    }
  }
  else if (a > b)
  {
    if (b == 0)
    {
      printf("Cannot divide with 0!\n");
    }
    else
    {
      printf("%d / %d = %lf\n", a, b, (double)a / (double)b);
    }
  }
  else if (b > a)
  {
    if (a == 0)
    {
      printf("Cannot divide with 0!\n");
    }
    else
    {
      printf("%d / %d = %lf\n", b, a, (double)b / (double)a);
    }
  }
}
