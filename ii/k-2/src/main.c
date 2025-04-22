#include "../include/main.h"
#include "../include/cmenu.h"

#include "../include/menuoption/display_all.h"
#include "../include/menuoption/edit_product.h"
#include "../include/menuoption/search_phones.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  Menu menu = {.title = "Main program menu",
               .option = OPTION_DISPLAY_ALL,
               .menu_options = OPTIONS,
               .count = OPTION_COUNT};

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
