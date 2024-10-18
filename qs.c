

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
    qs(arr, low, j);
    qs(arr, i, high);
  }
}
