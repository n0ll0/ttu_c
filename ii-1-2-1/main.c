#include <stdio.h>
#define ARR_SIZE 10

void ReadArray(int *arr, size_t len);
void PrintArray(int *arr, size_t len);
void GetMinMax(int *arr, size_t len, int **min, int **max);

int main(int argc, char const *argv[])
{
  int arr[ARR_SIZE];
  int *min = arr,
      *max = arr;

  ReadArray(arr, ARR_SIZE);
  printf("read\n");
  PrintArray(arr, ARR_SIZE);
  printf("printed\n");
  // printf("%p\n", arr);
  // printf("%ld\n", ARR_SIZE);
  // printf("%p\n", min);
  // printf("%p\n", max);
  GetMinMax(arr, ARR_SIZE, &min, &max);
  printf("[ min:%p[%ld]{%d} | max:%p[%ld]{%d} ]", 
            min, (size_t)(min - arr), *min,
            max, (size_t)(max - arr), *max);

  printf("\n2. osa\n");
  printf("kogu arr:\n");
  PrintArray(arr, ARR_SIZE);
  printf("0 - 4\n");
  PrintArray(arr, 5); // inclusive
  printf("3 - 7\n");
  PrintArray(arr + 3, 8 - 3 - 1); // inclusive
  return 0;
}

void ReadArray(int *arr, size_t len)
{
  for (size_t i = 0; i < len; ++i)
  {
    scanf("%d", (arr + i));
  }
}

void PrintArray(int *arr, size_t len)
{
  for (size_t i = 0; i < len; ++i)
    printf("\t[%p] %d\n", (arr + i), *(arr + i));
}

void GetMinMax(int *arr, size_t len, int **min, int **max)
{
  // if (len <= 0) return;
  printf("start");
  *min = (arr);
  *max = (arr);
  for (size_t i = 0; i < len; ++i)
  {
    // printf("at:%ld [min:%p{%d}|max:%p{%d}]", i, *min, **min, *max, **max);
    if (*(arr + i) < **min)
      *min = (arr + i);
    if (*(arr + i) > **max)
      *max = (arr + i);
  }
  printf("end\n");
}
