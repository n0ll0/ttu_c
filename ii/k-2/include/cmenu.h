#pragma once
#include "../include/dynamicarray.h"
#include <stdlib.h>

/** Check this before compilation */
#define MAX_MENU_OPTIONS 5

typedef struct {
  char* preview;
} MenuOption;

typedef struct {
  int option;
  MenuOption menu_options[MAX_MENU_OPTIONS];
  unsigned short int count;
  const char* title;
} Menu;

FUNCTION_STATUS MenuPrompt(Menu*);