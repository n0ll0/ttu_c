#include "../include/main.h"
#include "../include/cmenu.h"

#include "../include/waitForUser.h"

#include "../include/menuoption/display_all.h"
#include "../include/menuoption/zone_pricing.h"
#include "../include/menuoption/search_zones.h"
#include "../include/menuoption/display_grouped_zones.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  Menu menu = MAIN_MENU;

  while (MenuPrompt(&menu) == Ok) {
    switch (menu.option) {
    case OPTION_DISPLAY_ALL:
      display_all();
      break;
    case OPTION_SEARCH:
      search_zones();
      break;
    case OPTION_GROUP_BY_TYPE:
      display_grouped_zones();
      break;
    case OPTION_PRICES:
      zone_pricing();
      break;
    default:
      break;
    }
    waitForUser();
  }

  return 0;
}
