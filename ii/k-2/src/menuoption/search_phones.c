#include "../../include/menuoption/search_phones.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/menuoption/display_all.h"
#include "../../include/phone.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int useMenuOptionField(enum OPTION_PHONE option, char* search_term,
                       Product* p) {
  int res = 0;
  if (option == OPTION_PHONE_NAME || option == OPTION_PHONE_OS) {
    switch (option) {
    case OPTION_PHONE_OS:
      res = strstr(p->os, search_term) != NULL;
      break;
    case OPTION_PHONE_NAME:
      res = strstr(p->name, search_term) != NULL;
      break;
    }
    return res;
  }

  switch (option) {
  case OPTION_PHONE_RAM:
    res = p->ram_mb >= atoi(search_term);
    break;
  case OPTION_PHONE_SCREEN:
    res = p->screen_size > atof(search_term);
    break;
  }
  return res;
}

void search_phones() {
  DynamicPtrArray products = {0};
  load_products("./data/products", &products);
  DynamicPtrArray quotes = {0};
  load_quotes("data/quotes", &quotes);

  Menu menu1 = {.title = "program sub menu 1",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

  Menu menu2 = {.title = "program sub menu 2",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

  if (MenuPrompt(&menu1) == Error) {
    return;
  }
  char* search_term_1;
  printf("Enter search term (%d)\n", menu1.option);
  scanf("%ms", &search_term_1);
  if (MenuPrompt(&menu2) == Error) {
    return;
  }
  char* search_term_2;
  printf("Enter search term (%d)\n", menu2.option);
  scanf("%ms", &search_term_2);

    int found = 0;
  printf("Search results:\n");
  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];

    if (product_has_stock(p, &quotes) &&
        (useMenuOptionField(menu1.option, search_term_1, p) &&
         useMenuOptionField(menu2.option, search_term_2, p))) {
      printf("Product: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s\n", p->name,
             p->code, p->ram_mb, p->screen_size, p->os);
      found = 1;
    }
  }
  if (!found) {
    printf("No matching products found.\n");
  }
  free(search_term_1);
  free(search_term_2);
  DynamicPtrArrayFree(&products);
  DynamicPtrArrayFree(&quotes);
}
