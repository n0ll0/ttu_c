#include "../../include/menuoption/search_phones.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/phone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_phones() {
  DynamicPtrArray products = {0};
  load_products("./data/products", &products);

  Menu menu1 = {.title = "program sub menu 1",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

  if (MenuPrompt(&menu1) == Error) {
    return;
  }

  switch (menu1.option) {
  case OPTION_PHONE_NAME:
    break;
  case OPTION_PHONE_OS:
    break;
  case OPTION_PHONE_RAM:
    break;
  case OPTION_PHONE_SCREEN:
    break;
  default:
    break;
  }

  Menu menu2 = {.title = "program sub menu 2",
                .option = 0,
                .menu_options = OPTIONS_PHONE,
                .count = OPTION_PHONE_COUNT};

  if (MenuPrompt(&menu2) == Error) {
    return;
  }

  switch (menu2.option) {
  case OPTION_PHONE_NAME:
    break;
  case OPTION_PHONE_OS:
    break;
  case OPTION_PHONE_RAM:
    break;
  case OPTION_PHONE_SCREEN:
    break;
  default:
    break;
  }

  // char search_term[50];
  // printf("Enter search term: ");
  // scanf("%49s", search_term);

  // int found = 0;
  // printf("Search results:\n");
  // for (size_t i = 0; i < products.count; ++i) {
  //   Product* p = (Product*)products.data[i];
  //   if (strstr(p->name, search_term) || strstr(p->os, search_term)) {
  //     printf("Product: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s\n",
  //     p->name,
  //            p->code, p->ram_mb, p->screen_size, p->os);
  //     found = 1;
  //   }
  // }
  // if (!found) {
  //   printf("No matching products found.\n");
  // }
  DynamicPtrArrayFree(&products);
}
