#include <stdio.h>

#define N 6

void ReadIntArray(int nums[], size_t len);
int CountPositiveNumbers(int nums[], size_t len);
int GetPositiveInt();

int main()
{
  int nums[N];
  int result[N];

  ReadIntArray(nums, N);
  int newPos = 0;
  for (size_t i = 0; i < N; ++i)
  {
    if (nums[i] < 0)
    {
      result[newPos] = nums[i];
      newPos++;
    }
  }

  for (size_t i = 0; i < N; ++i)
  {
    if (nums[i] >= 0)
    {
      result[newPos] = nums[i];
      newPos++;
    }
  }

  size_t positiveLen = (size_t)CountPositiveNumbers(nums, N);
  int posArray[positiveLen];

  if (positiveLen > 0)
  {
    for (size_t i = 0; i < N; i++)
    {
      if (nums[i] > 0)
        posArray[i] = nums[i];
    }
  }

  printf("\nNums:\n");
  for (int i = 0; i < N; i++)
    printf("%d ", nums[i]);
  printf("\nResult:\n");
  for (int i = 0; i < N; i++)
    printf("%d ", result[i]);
  printf("\nPositives:\n");
  if (positiveLen > 0)
  {
    for (int i = 0; i < positiveLen; i++)
      printf("%d ", posArray[i]);
  }
  else
  {
    printf("Empty Array");
  }
  printf("\n");
  return 0;
}

int CountPositiveNumbers(int nums[], size_t len)
{
  int count = 0;
  for (int n = 0; n < len; ++n)
  {
    if (nums[n] > 0)
      count++;
  }
  return count;
}

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

int GetPositiveInt()
{
  int result;

  while (scanf("%d", &result) != 1 || result < 1)
  {
    printf("Please enter a positive integer: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
  }

  return result;
}