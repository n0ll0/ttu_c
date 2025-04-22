#include "../include/menuoption/edit.h"
#include "../include/dynamicarray.h"
#include "../include/phone.h"
#include "../../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit() {
  DynamicPtrArray products = {0};
  load_products("./data/products.csv", &products);
  DynamicPtrArray quotes = {0};
  load_quotes("./data/quotes.csv", &quotes);

  if (products.count == 0 || quotes.count == 0) {
    log_error("No products found.\n");
    DynamicPtrArrayFree(&products);
    DynamicPtrArrayFree(&quotes);
    return;
  }

  char id[256];
  log_event("Enter the id of the product or quote to edit: ");
  scanf("%255s", id);

  int found = 0;

  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];

    if (strcmp(p->code, id) == 0) {
      log_event("Current entry: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s\n",
             p->name, p->code, p->ram_mb, p->screen_size, p->os);
      log_event("Enter new details (<name> <ram_mb> <screen_size> <os>): ");
      scanf("%s %d %f %s", p->name, &p->ram_mb, &p->screen_size, p->os);
      save_products("./data/products.csv", &products);
      log_event("Product updated successfully.\n");
      found = 1;
      break;
    }
  }

  // Check if it's a quote
  for (size_t i = 0; i < quotes.count; ++i) {
    Quote* q = (Quote*)quotes.data[i];
    if (strcmp(q->quote_id, id) == 0) {
      log_event("Current quote: %s, Retailer: %s, Price: %.2f, Availability: %s\n",
             q->quote_id, q->retailer, q->price, q->availability);
      log_event("Enter edited quote (<retailer> <price> <availability>): ");
      scanf("%63s %f %15s", q->retailer, &q->price, q->availability);
      save_quotes("./data/quotes.csv", &quotes);
      log_event("Quote updated successfully.\n");
      found = 1;
      break;
    }
  }

  if (!found) {
    log_event("Couldn't find product or quote\n");
  }


  DynamicPtrArrayFree(&products);
  DynamicPtrArrayFree(&quotes);
}
