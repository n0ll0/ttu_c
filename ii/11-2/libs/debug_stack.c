#include "debug_stack.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

void debug_stack(stack st) {
  printf("DEBUG\n");
  printf("\tStack size: %d\n", st.size);
  printf("\tData pointer: %p\n", st.items);

  if (st.size != 0 && st.items == NULL) {
    printf("Sanity check failed!\n");
    printf("Stack is NULL, but size is not 0\n");
    return;
  }

  if (st.size == 0 && st.items != NULL) {
    printf("Sanity check failed!\n");
    printf("Stack data is not NULL, but size is 0\n");
    return;
  }

  printf("\tValues: ");
  for (int i = st.size - 1; i >= 0; i--) {
    printf("%d ", st.items[i]);
  }
  printf("\n\n");
}
