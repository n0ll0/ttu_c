#include "../include/menuoption/edit.h"
#include "../include/dynamicarray.h"
#include "../include/phone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit() {
  DynamicPtrArray products = {0};
  load_products("./data/products", &products);
  DynamicPtrArray quotes = {0};
  load_quotes("./data/quotes", &quotes);

  if (products.count == 0 || quotes.count == 0) {
    printf("No products found.\n");
    DynamicPtrArrayFree(&products);
    DynamicPtrArrayFree(&quotes);
    return;
  }

  char id[256];
  printf("Enter the id of the product or quote to edit: ");
  scanf("%255s", id);

  int found = 0;

  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];

    if (strcmp(p->code, id) == 0) {
      printf("Current entry: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s\n",
             p->name, p->code, p->ram_mb, p->screen_size, p->os);
      printf("Enter new details (<name> <ram_mb> <screen_size> <os>): ");
      scanf("%s %d %f %s", p->name, &p->ram_mb, &p->screen_size, p->os);
      printf("Product updated successfully.\n");
      found = 1;
      break;
    }
  }

  // Check if it's a quote
  for (size_t i = 0; i < quotes.count; ++i) {
    Quote* q = (Quote*)quotes.data[i];
    if (strcmp(q->quote_id, id) == 0) {
      printf("Current quote: %s, Retailer: %s, Price: %.2f, Availability: %s\n",
             q->quote_id, q->retailer, q->price, q->availability);
      printf("Enter edited quote (<retailer> <price> <availability>): ");
      scanf("%63s %f %15s", q->retailer, &q->price, q->availability);
      save_quotes("./data/quotes", &quotes);
      printf("Quote updated successfully.\n");
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Couldn't find product or quote\n");
  }

  save_products("./data/products", &products);
  save_quotes("./data/quotes", &quotes);

  DynamicPtrArrayFree(&products);
  DynamicPtrArrayFree(&quotes);
}
