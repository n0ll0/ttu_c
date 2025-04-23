#include "../include/stack.h"
#include "../libs/debug_stack.h"
#include "../include/cmenu.h"
#include <stdio.h>
#include <stdlib.h>

enum OPTION {
  OPTION_NOOP,
  OPTION_SWAP,
  OPTION_DUP,
  OPTION_PUSH,
  OPTION_POP,
  OPTION_COUNT
};

#define OPTIONS                                                                \
  {[OPTION_NOOP] = {"No op"},                                                  \
   [OPTION_SWAP] = {"Swap"},                                                   \
   [OPTION_DUP] = {"Duplicate"},                                               \
   [OPTION_PUSH] = {"Push"},                                                   \
   [OPTION_POP] = {"Pop"}}

int main() {
  Menu menu = {.title = "Stack operations", .option = OPTION_NOOP, .count = OPTION_COUNT, .menu_options = OPTIONS};

  stack s = {0};
  item_type input;

  while (MenuPrompt(&menu) == Ok) {
    switch (menu.option) {
    case OPTION_NOOP:
      break;
    case OPTION_SWAP:
      Swap(&s);
      break;
    case OPTION_DUP:
      Duplicate(&s);
      break;
    case OPTION_PUSH:
      printf("(user input)");
      scanf("%d", &input);
      Push(&s, input);
      break;
    case OPTION_POP:
      Pop(&s);
      break;
    default:
      break;
    }
    debug_stack(s);
  }

  // Free stack memory if any left
  Stack_Destroy(&s);
  return 0;
}
