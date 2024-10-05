#include <stdio.h>

#define N 6

void ReadIntArray(int nums[], size_t len);
int CountPositiveNumbers(int nums[], size_t len);
int IsInArray(int arr[], size_t len, int num);
void PrintArray(int *arr, size_t len, const char *word);
void PrintPairs(int *arr, size_t len, const char *word);

int main()
{
  int nums[N];
  int result[N];
  int posArray[N];
  int UniqueValues[N];

  ReadIntArray(nums, N);
  int newPos = 0;
  for (int i = 0; i < N; ++i)
  {
    if (nums[i] < 0)
    {
      result[newPos] = nums[i];
      newPos++;
    }
  }

  for (int i = 0; i < N; ++i)
  {
    if (nums[i] >= 0)
    {
      result[newPos] = nums[i];
      newPos++;
    }
  }

  int positiveLen = (int)CountPositiveNumbers(nums, N);

  if (positiveLen > 0)
  {
    for (int i = 0; i < N; i++)
    {
      if (nums[i] > 0)
        posArray[i] = nums[i];
    }
  }

  size_t j = 0;
  for (int i = 0; i < N; i++)
  {
    if (!IsInArray(UniqueValues, j, nums[i]))
    {
      UniqueValues[j] = nums[i];
      j++;
    }
  }

  PrintArray(nums, N, "\nNums:\n");
  PrintArray(result, N, "\nResult:\n");
  PrintArray(posArray, positiveLen, "\nPositives\n");
  PrintArray(UniqueValues, j, "\nNonrecurrent array%d:\n");
  PrintPairs(result, N, "\nPairs:\n");

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

int IsInArray(int arr[], size_t len, int num)
{
  for (int i = 0; i < len; ++i) // O(n) complexity
  {
    if (arr[i] == num)
    {
      return 1;
    }
  }
  return 0;
}

void PrintArray(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);
}

void PrintPairs(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  int negativesLen = len - CountPositiveNumbers(arr, len);

  if (negativesLen > 0)
  {
    for (int i=0; i< negativesLen;i++)
    {
      if (IsInArray(arr+i, len, -arr[i]))
      {
        printf("(%d, %d) ", arr[i], -arr[i]);
      }
    }
  }
};