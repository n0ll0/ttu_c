#include "../include/stack.h"
#include <stdlib.h>
void Push(stack* stack, int item) {
  if (stack->items == NULL) {
    stack->items = calloc(1, sizeof(*stack->items));
  } else if (stack->size > 0) {
    size_t new_size = stack->size + 1;
    stack->items = realloc(stack->items, new_size * sizeof(*stack->items));
    stack->size = new_size;
    stack->items[stack->size] = item;
    return;
  }
  if (stack->items == NULL) {
    stack->size = 0;
    return;
  }
  stack->items[stack->size] = item;
  stack->size++;

  return;
}
item_type Pop(stack* stack) {
  if (stack->items == NULL || stack->size <= 0) {
    stack->items = NULL;
    stack->size = 0;
    return 0;
  }

  item_type item = stack->items[stack->size - 1];

  stack->items = realloc(stack->items, sizeof(*stack->items) * (stack->size--));
  stack->size--;

  return item;
}
