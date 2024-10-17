#include <stdio.h>
#define ARRAY_LENGTH 10
#define MATRIX_DIMENSION 5

void ReadIntArray(int nums[], size_t len, const char *word);
void PrintArray(int *arr, size_t len, const char *word);
void Sort(int *arr, size_t len);

int main(int argc, char const *argv[])
{
  int i;
  int array[ARRAY_LENGTH];
  ReadIntArray(array, ARRAY_LENGTH, "\nEnter array:\n");
  printf("\n\n");
  PrintArray(array, ARRAY_LENGTH, "\nEntered array:\n");
  printf("\n\n");

  Sort(array, ARRAY_LENGTH);

  PrintArray(array, ARRAY_LENGTH, "\nAscending order:\n");
  printf("\n\n\nDescending order:\n");
  for (int i = 1; i <= ARRAY_LENGTH; i++)
  {
    printf("%d ", array[ARRAY_LENGTH - i]);
  }

  printf("\nhello\n\n");

  int matrix[MATRIX_DIMENSION][MATRIX_DIMENSION];

  for (int y = 0; y < MATRIX_DIMENSION; ++y)
  {
    char prompt[24];
    sprintf(prompt, "Enter matrix row %d / %d", y + 1, MATRIX_DIMENSION);
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
    Sort(matrix[y], MATRIX_DIMENSION);
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

void Swap(int *a, int *b)
{
  *a = *b ^ *a;
  *b = *a ^ *b;
  *a = *b ^ *a;
}

void Sort(int *arr, size_t len)
{
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len; j++)
    {
      if (arr[i] < arr[j])
      {
        Swap(&arr[i], &arr[j]);
      }
    }
  }
}
