
// Recursive binary search function.
// Parameters:
//   arr  - the sorted array of integers
//   low  - the current lower index of the search interval
//   high - the current higher index of the search interval
//   key  - the integer value to search for
// Returns:
//   1 if the key is found in the array, 0 if not.
int binarySearch(int arr[], int low, int high, int key) {
  // Base case: if the low index exceeds the high index,
  // the search interval is empty; thus, key wasn't found.
  if (low > high) {
    return 0;
  }

  // Find the middle index (using floor division, as in C integer division).
  int mid = (low + high) / 2;

  // Check if the key is at the middle index.
  if (arr[mid] == key) {
    return 1;
  }
  // If key is less than arr[mid], search in the left half.
  else if (arr[mid] > key) {
    return binarySearch(arr, low, mid - 1, key);
  }
  // Otherwise, search in the right half.
  else {
    return binarySearch(arr, mid + 1, high, key);
  }
}

/**
 *
 * Summary
 * Number of Comparisons (Worst-Case):
 *         16 elements: ~5 comparisons.
 *         256 elements: ~9 comparisons.
 *         100,000 elements: ~17 comparisons.
 * Time Complexity: The recursive binary search is logarithmic
 * (𝑂(log⁡𝑛)), which is far more efficient than the linear (𝑂(𝑛))
 * time complexity of a standard linear search. Requirement of Sorting: The
 * algorithm only works on sorted arrays. Without sortation, the binary search’s
 * decision-making process collapses, rendering the algorithm ineffective. This
 * analysis should provide you with a clear understanding of why binary search
 * is much preferred over linear search for sorted data and how dramatic the
 * improvement can be in terms of the number of comparisons, especially as the
 * size of the data grows.
 *
 */