#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5
#define MATRIX_DIMENSION 5

void ReadIntArray(int nums[], size_t len, const char *word);
void PrintArray(int *arr, size_t len, const char *word);

void BubbleSort(int *arr, size_t len);
void SortMatrix(int **matrix, size_t dimensions);

void PrintAscendingArray(int *arr, size_t len);
void PrintDescendingArray(int *arr, size_t len);

void ReadMatrix(int **matrix, size_t dimensions);
void PrintMatrix(int **matrix, size_t dimensions);

int main(int argc, char const *argv[])
{
  int array[ARRAY_LENGTH];

  ReadIntArray(array, ARRAY_LENGTH, "\nEnter array:\n");
  printf("\n\n");

  PrintArray(array, ARRAY_LENGTH, "\nEntered array:\n");
  printf("\n\n");

  BubbleSort(array, ARRAY_LENGTH);

  PrintAscendingArray(array, ARRAY_LENGTH);
  PrintDescendingArray(array, ARRAY_LENGTH);

  printf("\n\nhello\n\n");

  int **matrix = (int **)malloc(MATRIX_DIMENSION * sizeof(int *));
  for (size_t i = 0; i < MATRIX_DIMENSION; i++)
  {
    matrix[i] = (int *)malloc(MATRIX_DIMENSION * sizeof(int));
  }

  printf("\nEnter matrix:\n");
  ReadMatrix(matrix, MATRIX_DIMENSION);
  printf("\nEntered matrix:\n");
  PrintMatrix(matrix, MATRIX_DIMENSION);

  SortMatrix(matrix, MATRIX_DIMENSION);

  printf("\nSorted matrix:\n");
  PrintMatrix(matrix, MATRIX_DIMENSION);
  return 0;
}

void ReadIntArray(int nums[], size_t len, const char *word)
{
  printf("%s", word);
  for (size_t i = 0; i < len; i++)
  {
    int number;
    printf("\tEnter number %ld / %ld: ", i + 1, len);
    scanf("%d", &number);
    nums[i] = number;
  }

  printf("\n");
}

void PrintArray(int *arr, size_t len, const char *word)
{
  printf(word, NULL);
  for (size_t i = 0; i < len; i++)
    printf("%d ", arr[i]);
}

void ReadMatrix(int **matrix, size_t dimensions)
{
  for (size_t y = 0; y < dimensions; ++y)
  {
    char prompt[24];
    sprintf(prompt, "Enter matrix row %ld / %ld\n", y + 1, dimensions);
    ReadIntArray(matrix[y], dimensions, prompt);
  }
}

void PrintMatrix(int **matrix, size_t dimensions)
{
  printf("{\n\t");
  for (size_t y = 0; y < dimensions; ++y)
  {
    PrintArray(matrix[y], dimensions, "{");
    printf("}\n\t");
  }
  printf("}\n");
}

void PrintAscendingArray(int *arr, size_t len)
{
  PrintArray(arr, len, "\nAscending order:\n");
}

void PrintDescendingArray(int *arr, size_t len)
{
  printf("\n\n\nDescending order:\n");
  for (size_t i = len; i >= 0; --i)
    printf("%d ", arr[i]);
}

void Swap(int *a, int *b)
{
  *a = *b ^ *a;
  *b = *a ^ *b;
  *a = *b ^ *a;
}

void BubbleSort(int *arr, size_t len)
{
  size_t i = 0,
         j = 0;
  int n = 0,
      swapped = 0;
  for (; i < len; i++)
  {
    swapped = 0;
    for (j = 0; j < len - i - 1; j++)
    {
      printf("%d ", ++n);
      if (arr[j] > arr[j + 1])
      {
        Swap(&arr[j], &arr[j + 1]);
        swapped = 1;
      }
    }
    if (!swapped)
      break;
  }
  printf("\n");
}

void SortMatrix(int **matrix, size_t dimensions)
{
  for (size_t y = 0; y < dimensions; ++y)
  {
    BubbleSort(matrix[y], dimensions);
  }
}