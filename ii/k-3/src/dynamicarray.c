#include "../include/dynamicarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Pushes a pointer onto the dynamic pointer array.
 *
 * Adds the pointer referenced by `ptr` to the end of the `DynamicPtrArray`.
 * If the array is full, its capacity is increased.
 *
 * @param dpa Pointer to the DynamicPtrArray structure.
 * @param ptr Address of the pointer to be added (i.e., pointer to void*).
 * @return FUNCTION_STATUS Ok if successful, Error if `ptr` is NULL.
 */
FUNCTION_STATUS DynamicPtrArrayPush(DynamicPtrArray* dpa, void** ptr) {
  // printf("push %p\n", ptr);
  if (ptr == NULL) {
    return Error;
  }
  if (dpa->data == NULL) {
    dpa->capacity = 1;
    dpa->data = calloc(dpa->capacity, sizeof(void*));
  }
  if (dpa->count == dpa->capacity) {
    dpa->capacity += 1;
    dpa->capacity *= 2;
    dpa->data = realloc(dpa->data, dpa->capacity * sizeof(void*));
  }

  dpa->data[dpa->count++] = *ptr;

  return Ok;
}

/**
 * @brief Pops (removes and frees) the last pointer from the dynamic pointer
 * array.
 *
 * Frees the memory pointed to by the last element in the array and removes it
 * from the array. If the array is empty, does nothing.
 *
 * @param dpa Pointer to the DynamicPtrArray structure.
 * @return FUNCTION_STATUS Ok.
 */
FUNCTION_STATUS DynamicPtrArrayPop(DynamicPtrArray* dpa) {
  if (dpa->data == NULL) {
    return Ok;
  }

  free(dpa->data[--dpa->count]);

  return Ok;
}

/**
 * @brief Frees all pointers and memory associated with the dynamic pointer
 * array.
 *
 * Iteratively pops and frees all pointers stored in the array, then frees the
 * array itself. Resets the array's data pointer, capacity, and count to zero.
 *
 * @param dpa Pointer to the DynamicPtrArray structure.
 * @return FUNCTION_STATUS Ok.
 */
FUNCTION_STATUS DynamicPtrArrayFree(DynamicPtrArray* dpa) {
  if (dpa->data == NULL) {
    return Ok;
  }
  while (dpa->count > 0) {
    DynamicPtrArrayPop(dpa);
  }

  free(dpa->data);
  dpa->data = NULL;
  dpa->capacity = dpa->count = 0;

  return Ok;
}
