#include <stdio.h>
#define ARRAY_LENGTH 10
#define MATRIX_DIMENSION 5

void qs(int *arr, int low, int high)
{
  if (low < high)
  {
    int pivot = arr[(low + high) / 2]; // Selecting the middle element as the pivot
    int i = low;
    int j = high;
    int temp;

    while (i <= j)
    {
      // printf("1");
      while (arr[i] < pivot)
        i++; // Moving elements smaller than pivot to the left
      while (arr[j] > pivot)
        j--; // Moving elements greater than pivot to the right
      if (i <= j)
      {
        temp = arr[i]; // Swapping elements
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
      }
    }

    // Recursively sort the two partitions
    if (low < j)
      qs(arr, low, j);
    if (i < high)
      qs(arr, i, high);
  }
}

void ReadIntArray(int nums[], size_t len, const char *word)
{
  printf("%s", word);
  for (int i = 0; i < len; i++)
  {
    int number;
    printf("Enter number %d / %ld: ", i + 1, len);
    scanf("%d", &number);
    nums[i] = number;
  }

  printf("\n");
}

void PrintArray(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);
}

int main(int argc, char const *argv[])
{
  int i;
  int array[ARRAY_LENGTH];
  ReadIntArray(array, ARRAY_LENGTH, "\nEnter array:\n");
  printf("\n\n");
  PrintArray(array, ARRAY_LENGTH, "\nEntered array:\n");
  printf("\n\n");
  qs(array, 0, ARRAY_LENGTH - 1);
  PrintArray(array, ARRAY_LENGTH, "\nAscending order:\n");
  printf("\n\n");
  printf("\nDescending order:\n");
  for (int i = 1; i <= ARRAY_LENGTH; i++)
  {
    printf("%d ", array[ARRAY_LENGTH - i]);
  }

  printf("\nhello\n\n");

  int matrix[MATRIX_DIMENSION][MATRIX_DIMENSION];

  for (int y = 0; y < MATRIX_DIMENSION; ++y)
  {
    char prompt[24];
    sprintf(prompt, "Enter matrix row %d / %d", y+1, MATRIX_DIMENSION);
    ReadIntArray(matrix[y], MATRIX_DIMENSION, prompt);
  }

  printf("\nEntered matrix:\n{\n\t");

  for (int y = 0; y < MATRIX_DIMENSION; ++y)
  {
    PrintArray(matrix[y], MATRIX_DIMENSION, "{");
    printf("}\n\t");
  }
  printf("}\n");

  for (int y = 0; y < MATRIX_DIMENSION; ++y)
  {
    qs(matrix[y], 0, MATRIX_DIMENSION-1);
  }

  printf("\nSorted matrix:\n{\n\t");

  for (int y = 0; y < MATRIX_DIMENSION; ++y)
  {
    PrintArray(matrix[y], MATRIX_DIMENSION, "{");
    printf("}\n\t");
  }
  printf("\n}\n");
  return 0;
}
