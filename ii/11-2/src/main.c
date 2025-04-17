#include "../include/stack.h"
#include "../libs/debug_stack.h"
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

typedef struct {
  char* preview;
  char* prompt;
} MenuOption;
#define OPTIONS                                                                \
  {                                                                            \
    [OPTION_NOOP] = {.preview = "No op", .prompt = NULL},                      \
    [OPTION_SWAP] = {.preview = "Swap", .prompt = NULL},                       \
    [OPTION_DUP] = {.preview = "Duplicate", .prompt = NULL},                   \
    [OPTION_PUSH] = {.preview = "Push", .prompt = "%d"}, [OPTION_POP] = {      \
      .preview = "Pop",                                                        \
      .prompt = NULL                                                           \
    }                                                                          \
  }

typedef struct {
  enum OPTION option;
  MenuOption menu_options[OPTION_COUNT];
} Menu;

enum OPTION mainLoop(Menu* m);

int main() {
  Menu menu = {.option = OPTION_NOOP, .menu_options = OPTIONS};

  stack s = {0};
  item_type input;

  while ((menu.option = mainLoop(&menu)) != OPTION_COUNT) {
    if (menu.menu_options[menu.option].prompt != NULL) {
      printf("(user input)");
      scanf(menu.menu_options[menu.option].prompt, &input);
    }
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

enum OPTION mainLoop(Menu* m) {
  printf("\nProgram menu:\n");
  for (int i = 0; i < OPTION_COUNT; ++i) {
    printf("\t%d - %s\n", i, m->menu_options[i].preview);
  }
  int opt;
  while (scanf("%d", &opt) != 1 || opt < 0 || opt > OPTION_COUNT)
    ;
  return opt;
}
