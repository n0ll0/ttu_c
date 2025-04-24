#pragma once
#include <stdlib.h>

typedef struct {
  void** data;
  size_t capacity;
  size_t count;
} DynamicPtrArray;

typedef enum { Error, Ok } FUNCTION_STATUS;

FUNCTION_STATUS DynamicPtrArrayPush(DynamicPtrArray*, void**);
FUNCTION_STATUS DynamicPtrArrayPop(DynamicPtrArray*);
FUNCTION_STATUS DynamicPtrArrayFree(DynamicPtrArray*);
