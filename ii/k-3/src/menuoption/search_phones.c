#include "../../include/menuoption/search_phones.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/logger.h"
#include "../../include/menuoption/display_all.h"
#include "../../include/phone.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int useMenuOptionField(enum OPTION_PHONE option, char* search_term,
                       Product* p) {
  if (search_term == NULL) {
    return 1;
  }
  int res = 0;
  // if (option == OPTION_PHONE_NAME || option == OPTION_PHONE_OS) {
  //   switch (option) {
  //   }
  //   return res;
  // }

  switch (option) {
  case OPTION_PHONE_OS:
    res = strstr(p->os, search_term) != NULL;
    break;
  case OPTION_PHONE_NAME:
    res = strstr(p->name, search_term) != NULL;
    break;
  case OPTION_PHONE_RAM:
    res = p->ram_mb >= atoi(search_term);
    break;
  case OPTION_PHONE_SCREEN:
    res = p->screen_size > atof(search_term);
    break;
  default:
    break;
  }
  return res;
}

void search_phones() {
  DynamicPtrArray products = {0};
  load_products("./data/products.csv", &products);
  DynamicPtrArray quotes = {0};
  load_quotes("data/quotes.csv", &quotes);

  Menu menu1 = {.title = "program sub menu 1",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

  Menu menu2 = {.title = "program sub menu 2",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

#if defined(__GNUC__) && !defined(__MINGW32__)
  char* search_term_1 = NULL;
  if (MenuPrompt(&menu1) == Ok) {
    log_event("Enter search term (%d)\n", menu1.option);
    scanf("%ms", &search_term_1);
  }
  char* search_term_2 = NULL;
  if (MenuPrompt(&menu2) == Ok) {
    log_event("Enter search term (%d)\n", menu2.option);
    scanf("%ms", &search_term_2);
  }
#else
  char search_term_1[128] = "";
  if (MenuPrompt(&menu1) == Ok) {
    log_event("Enter search term (%d)\n", menu1.option);
    scanf("%127s", search_term_1);
  }
  char search_term_2[128] = "";
  if (MenuPrompt(&menu2) == Ok) {
    log_event("Enter search term (%d)\n", menu2.option);
    scanf("%127s", search_term_2);
  }
#endif

  int found = 0;
  log_event("Search results:\n");
#if defined(__GNUC__) && !defined(__MINGW32__)
  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];
    if (product_has_stock(p, &quotes) &&
        (useMenuOptionField(menu1.option, search_term_1, p) &&
         useMenuOptionField(menu2.option, search_term_2, p))) {
      log_event("Product: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s", p->name,
                p->code, p->ram_mb, p->screen_size, p->os);
      found = 1;
    }
  }
  if (!found) {
    log_event("No matching products found.\n");
  }
  free(search_term_1);
  free(search_term_2);
#else
  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];
    if (product_has_stock(p, &quotes) &&
        (useMenuOptionField(menu1.option, search_term_1, p) &&
         useMenuOptionField(menu2.option, search_term_2, p))) {
      log_event("Product: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s", p->name,
                p->code, p->ram_mb, p->screen_size, p->os);
      found = 1;
    }
  }
  if (!found) {
    log_event("No matching products found.\n");
  }
#endif
  DynamicPtrArrayFree(&products);
  DynamicPtrArrayFree(&quotes);
}
