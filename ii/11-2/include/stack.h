#ifndef STACK_H
#define STACK_H

typedef struct {
  enum {ERR, OK} status;
} stack_result;

typedef int item_type;

typedef struct {
  unsigned size;
  item_type* items;
} stack;

item_type Peek(stack* stack);
void Push(stack*, item_type);
item_type Pop(stack*);
void Stack_Destroy(stack* stack);
void Duplicate(stack* stack);
void Swap(stack* stack);

#endif // !STACK_H
