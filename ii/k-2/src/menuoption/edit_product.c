#include "../include/menuoption/edit_product.h"
#include "../include/dynamicarray.h"
#include "../include/phone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_product_quotes(const char*, DynamicPtrArray*);

void edit_product() {
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

  for (size_t i = 0; i < products.count; ++i) {
    Product* p = (Product*)products.data[i];
    DynamicPtrArray q = {0};

    if (strcmp(p->code, id) == 0 || strcmp(p->code, id) == 0) {
      printf("Current entry: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s\n",
             p->name, p->code, p->ram_mb, p->screen_size, p->os);
      printf("Enter new details (name ram_mb screen_size os): ");
      scanf("%s %d %f %s", p->name, &p->ram_mb, &p->screen_size, p->os);
      save_products("./data/products", &products);
      printf("Product updated successfully.\n");
      DynamicPtrArrayFree(&products);
      return;
    }
  }

  printf("Product not found.\n");
  DynamicPtrArrayFree(&products);
}
