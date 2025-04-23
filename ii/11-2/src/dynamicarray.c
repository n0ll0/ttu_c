#include "../include/dynamicarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FUNCTION_STATUS DynamicPtrArrayPop(DynamicPtrArray* dpa) {
  if (dpa->data == NULL) {
    return Ok;
  }

  free(dpa->data[--dpa->count]);

  return Ok;
}

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
