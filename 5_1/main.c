#include <stdio.h>

#define N 6

void ReadIntArray(int nums[], size_t len);
int CountPositiveNumbers(int nums[], size_t len);
int IsInArray(int arr[], size_t len, int num);
void PrintArray(int *arr, size_t len, const char *word);
void PrintPairs(int *arr, size_t len, const char *word);
void RearrangeArr(int *arr, int *arranged, size_t len);
int CountNegNumbers(int *arr, size_t len);
size_t MakeUniqueArr(int *arr, int *unique, size_t len);

int main()
{
  int nums[N];
  int result[N];
  int posArray[N];
  int UniqueValues[N];

  ReadIntArray(nums, N);
  RearrangeArr(nums, result, N);

  int positiveLen = 0;

  for (int i = 0; i < N; i++)
  {
    if (nums[i] > 0)
    {
      posArray[positiveLen] = nums[i];
      positiveLen++;
    }
  }

  size_t UniqueLen = MakeUniqueArr(nums, UniqueValues, N);

  PrintArray(nums, N, "\nNums:\n");
  PrintArray(result, N, "\nResult:\n");
  PrintArray(posArray, positiveLen, "\nPositives\n");
  PrintArray(UniqueValues, UniqueLen, "\nNonrecurrent array%d:\n");

  PrintPairs(UniqueValues, UniqueLen, "\nPairs:\n");

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

size_t MakeUniqueArr(int *arr, int *unique, size_t len)
{
  size_t size = 0;
  for (int i = 0; i < N; i++)
  {
    if (!IsInArray(unique, size, arr[i]))
    {
      unique[size] = arr[i];
      size++;
    }
  }
  return size;
}

void PrintArray(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);
}

int CountNegNumbers(int *arr, size_t len)
{
  int count = 0;
  for (int i = 0; i < len; ++i)
  {
    if (arr[i] < 0)
    {
      count++;
    }
  }
  return count;
}

void RearrangeArr(int *arr, int *arranged, size_t len)
{
  int newPos = 0;
  for (int i = 0; i < len; ++i)
  {
    if (arr[i] < 0)
    {
      arranged[newPos] = arr[i];
      newPos++;
    }
  }

  for (int i = 0; i < len; ++i)
  {
    if (arr[i] >= 0)
    {
      arranged[newPos] = arr[i];
      newPos++;
    }
  }
}

void PrintPairs(int *arr, size_t len, const char *word)
{
  int rearranged[N];

  printf(word, NULL);
  // PrintArray(arr, len, "\nDEBUG! unique: \n");
  RearrangeArr(arr, rearranged, len);

  int negativesLen = CountNegNumbers(rearranged, len);
  // PrintArray(rearranged, negativesLen, "\nDEBUG! sorted: ");

  if (negativesLen > 0)
  {
    for (int i = 0; i < negativesLen; i++)
    {
      if (IsInArray(rearranged + i*4, len - i*4, -rearranged[i]))
      {
        printf("(%d, %d) ", rearranged[i], -rearranged[i]);
      }
    }
  }
}