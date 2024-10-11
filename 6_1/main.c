#include <stdio.h>

#define N 6

void ReadIntArray(int nums[], size_t len);
size_t MakePosArr(int nums[], int pos[], size_t len);
int IsInArray(int arr[], size_t len, int num);
void PrintArray(int *arr, size_t len, const char *word);
void PrintPairs(int *arr, size_t len, const char *word);
void RearrangeArr(int *arr, int *arranged, size_t len);
int CountNegNumbers(int *arr, size_t len);
size_t MakeUniqueArr(int *arr, int *unique, size_t len);

int main()
{
  printf("Ülesanne 1: Uute massiivide koostamine + lisa 1 + lisa 2\n\n");
  int nums[N];
  int result[N];
  int posArray[N];
  int UniqueValues[N];

  ReadIntArray(nums, N);
  RearrangeArr(nums, result, N);

  size_t positiveLen = MakePosArr(nums, posArray, N);

  size_t UniqueLen = MakeUniqueArr(result, UniqueValues, N);

  PrintArray(nums, N, "\nNums:\n");
  PrintArray(result, N, "\nResult:\n");
  PrintArray(posArray, positiveLen, "\nPositives\n");
  PrintArray(UniqueValues, UniqueLen, "\nNonrecurrent array:\n");

  PrintPairs(UniqueValues, UniqueLen, "\nPairs:\n");

  printf("\n");

  return 0;
}

int CountPositiveNumbers(int nums[], size_t len)
{
  int count = 0;
  for (int n = 0; n < len; ++n)
  {
    // printf("+");
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
    // printf("*");
    if (arr[i] == num)
    {
      return 1;
    }
  }
  return 0;
}

size_t MakePosArr(int nums[], int pos[], size_t len)
{
  size_t length = 0;
  for (int i = 0; i < N; i++)
  {
    if (nums[i] > 0)
    {
      pos[length] = nums[i];
      length++;
    }
  }
  return length;
}

size_t MakeUniqueArr(int *arr, int *unique, size_t len)
{
  size_t size = 0;
  for (int i = 0; i < len; i++)
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
    // printf("-");
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

/**
 * Description: Prints unique pairs
 *
 * Parameters:
 * - arr: a rearranged unique array
 * - len: How many elements to print out
 * - word: phrase to print out before the array
 *
 * Returns: -
 */
void PrintPairs(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  // PrintArray(arr, len, "\nDEBUG! begin (must be unique and rearranged): ");

  int negativesLen = CountNegNumbers(arr, len);
  // PrintArray(arr, negativesLen, "\nDEBUG! negatives: ");

  int *posArr = &arr[negativesLen];
  size_t posArrLen = len - negativesLen;
  // PrintArray(posArr, posArrLen, "\nDEBUG! positives: ");

  if (negativesLen > 0)
  {
    for (int i = 0; i < negativesLen; i++)
    {
      // printf("/");
      if (IsInArray(posArr, posArrLen, -arr[i]))
      {
        printf("(%d, %d) ", arr[i], -arr[i]);
      }
    }
  }
}