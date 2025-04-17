#ifndef STACK_H
#define STACK_H

typedef int item_type;

typedef struct {
  unsigned size;
  item_type* items;
} stack;


void Push(stack*, item_type);
item_type Pop(stack*);

#endif // !STACK_H
