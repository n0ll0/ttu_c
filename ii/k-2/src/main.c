#include "../include/main.h"
#include "../include/cmenu.h"

#include "../include/waitForUser.h"

#include "../include/menuoption/display_all.h"
#include "../include/menuoption/edit.h"
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
      edit();
      break;
    case OPTION_SEARCH:
      search_phones();
      break;
    default:
      break;
    }
    waitForUser();
  }

  return 0;
}
