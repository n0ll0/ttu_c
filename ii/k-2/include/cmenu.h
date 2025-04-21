#pragma once
#include <stdlib.h>
#include "../include/dynamicarray.h"

enum OPTION {
  OPTION_DISPLAY_ALL,
  OPTION_EDIT_PRODUCT,
  OPTION_SEARCH,
  OPTION_COUNT
};

typedef struct {
  char* preview;
} MenuOption;

typedef struct {
  enum OPTION option;
  MenuOption menu_options[OPTION_COUNT];
} Menu;

FUNCTION_STATUS MenuPrompt(Menu*);