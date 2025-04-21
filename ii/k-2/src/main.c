#include "../include/cmenu.h"
#include <stdio.h>
#include <stdlib.h>

#include "../include/menuoptions.h"

#define OPTIONS                                                                \
  {{.preview = "Display all"},                                                 \
   {.preview = "Edit product (more commands)"},                                \
   {.preview = "Search phones"}}

int main() {
  Menu menu = {.option = OPTION_DISPLAY_ALL, .menu_options = OPTIONS};

  while (MenuPrompt(&menu) == Ok) {
    switch (menu.option) {
    case OPTION_DISPLAY_ALL:
      display_all();
      break;
    case OPTION_EDIT_PRODUCT:
      edit_product();
      break;
    case OPTION_SEARCH:
      search_phones();
      break;
    default:
      break;
    }
  }

  return 0;
}
