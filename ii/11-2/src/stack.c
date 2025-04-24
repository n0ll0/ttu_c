#include "../include/stack.h"
#include <stdlib.h>

stack_result Push(stack* stack, item_type item) {
  stack_result res = {
		.status = OK,
	};
  void* tempP = NULL; // Declare tempP outside the blocks
  if (stack->items == NULL) {
    // use temp pointer if something goes wrong
    tempP = calloc(1, sizeof(*stack->items));
    if (!tempP) {
			res.status = ERR;
      return res;
    }
    stack->items = tempP;
    stack->size = 0; // Initialize size to 0
  } else {
    size_t new_size = stack->size + 1;
    tempP = realloc(stack->items, new_size * sizeof(*stack->items));
    if (tempP == NULL) {
      // Handle memory allocation failure
			res.status = ERR;
      return res;
    }
    stack->items = tempP;
  }
  stack->items[stack->size] = item;
  stack->size++;
  return res;
}

stack_result Pop(stack* stack) {
  if (stack->items == NULL || stack->size <= 0) {
    stack->items = NULL;
    stack->size = 0;
    return (stack_result){.status = ERR};
  }
  stack_result res = {.status = OK, .data = stack->items[stack->size - 1]};
  stack->size--;

  if (stack->size == 0) {
    free(stack->items);
    stack->items = NULL;
  } else {
    stack->items = realloc(stack->items, sizeof(*stack->items) * stack->size);
  }

  return res;
}

stack_result Peek(stack* stack) {
  if (stack->size <= 0 || stack->items == NULL) {
    return (stack_result){.status = ERR};
  }
  return (stack_result){.status = OK, .data = stack->items[stack->size - 1]};
}

void Duplicate(stack* stack) {
  stack_result res = Peek(stack);
  if (res.status == ERR) {
    return;
  }
  Push(stack, res.data);
}
#include <stdio.h>
stack_result Swap(stack* stack) {
  if (stack->items == NULL || stack->size <= 1) {
    return (stack_result){.status = ERR};
  }
  stack_result a = Pop(stack);
  if (a.status == ERR)
    return (stack_result){.status = ERR};
  stack_result b = Pop(stack);
  if (b.status == ERR)
    return (stack_result){.status = ERR};

  printf("%d %d", a.data, b.data);
  Push(stack, a.data);
  Push(stack, b.data);
  return (stack_result){.status = OK};
}

void Stack_Destroy(stack* stack) {
  if (stack->items != NULL) {
    free(stack->items);
  }
}
