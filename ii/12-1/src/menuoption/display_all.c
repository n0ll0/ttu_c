#include "../../include/menuoption/display_all.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/phone.h"
#include "../../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_product_and_quotes(Product* p, DynamicPtrArray* quotes) {
  log_event("Product: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s", p->name,
         p->code, p->ram_mb, p->screen_size, p->os);
  for (size_t j = 0; j < quotes->count; ++j) {
    Quote* q = (Quote*)quotes->data[j];
    if (strcmp(p->code, q->product_code) == 0) {
      log_event("  Quote: %s, Retailer: %s, Price: %.2f, Availability: %s",
             q->quote_id, q->retailer, q->price, q->availability);
    }
  }
}

int product_has_stock(Product* p, DynamicPtrArray* quotes) {
  for (size_t j = 0; j < quotes->count; ++j) {
    Quote* q = (Quote*)quotes->data[j];
    if (strcmp(p->code, q->product_code) == 0 &&
        strcmp(q->availability, "in_stock") == 0) {
      return 1; // Product has stock
    }
  }
  return 0; // Product is out of stock
}

void display_all() {
  DynamicPtrArray products = {0};
  DynamicPtrArray quotes = {0};

  load_products("./data/products.csv", &products);
  load_quotes("./data/quotes.csv", &quotes);

  if (products.count == 0) {
    log_event("No products found.\n");
    DynamicPtrArrayFree(&quotes);
    DynamicPtrArrayFree(&products);
    return;
  }

  printf("Products and Quotes:\n");
  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];
    display_product_and_quotes(p, &quotes);
  }

  DynamicPtrArrayFree(&products);
  DynamicPtrArrayFree(&quotes);
}
