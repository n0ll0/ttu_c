#include <stdio.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *arr, size_t low, size_t high)
{
  int pivot = arr[high]; // Choosing the last element as the pivot
  int i = (low - 1);     // Index of smaller element

  for (int j = low; j <= high - 1; j++)
  {
    // If current element is smaller than or equal to pivot
    if (arr[j] <= pivot)
    {
      i++; // Increment index of smaller element
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void qs(int *arr, size_t low, size_t high)
{
  if (low < high)
  {
    // pi is partitioning index, arr[pi] is now at right place
    int pi = partition(arr, low, high);

    // Separately sort elements before partition and after partition
    qs(arr, low, pi - 1);
    qs(arr, pi + 1, high);
  }
}