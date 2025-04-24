#ifndef STACK_H
#define STACK_H

typedef int item_type;

typedef struct result {
  enum {ERR, OK} status;
  item_type data;
} stack_result;


typedef struct {
  unsigned size;
  item_type* items;
} stack;

stack_result Peek(stack* stack);
stack_result Push(stack*, item_type);
stack_result Pop(stack*);
void Stack_Destroy(stack* stack);
void Duplicate(stack* stack);
stack_result Swap(stack* stack);

#endif // !STACK_H
