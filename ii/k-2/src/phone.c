#include "../include/phone.h"
#include "../include/dynamicarray.h"
#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Loads products from file into a DynamicPtrArray
int load_products(const char* filename, DynamicPtrArray* arr) {
  FILE* f = fopen(filename, "r");
  if (!f)
    return 0;
  while (1) {
    Product* p = malloc(sizeof(Product));
    int res = fscanf(f, "%15[^,],%127[^,],%d,%f,%31[^,],\n", p->code, p->name,
                     &p->ram_mb, &p->screen_size, p->os);
    if (res != 5) {
      free(p);
      break;
    }
    DynamicPtrArrayPush(arr, (void**)&p);
    int c;
    while ((c = fgetc(f)) != EOF && (c == '\n' || c == '\r')) {
    }
    if (c != EOF)
      ungetc(c, f);
  }
  fclose(f);
  return arr->count;
}

// Loads quotes from file into a DynamicPtrArray
int load_quotes(const char* filename, DynamicPtrArray* arr) {
  FILE* f = fopen(filename, "r");
  if (!f)
    return 0;
  int count = 0;
  while (1) {
    Quote* q = malloc(sizeof(Quote));
    int res = fscanf(f, "%15[^,],%15[^,],%63[^,],%f,%15[^,],\n", q->quote_id,
                     q->product_code, q->retailer, &q->price, q->availability);
    if (res != 5) {
      free(q);
      break;
    }
    DynamicPtrArrayPush(arr, (void**)&q);
    count++;
    int c;
    while ((c = fgetc(f)) != EOF && (c == '\n' || c == '\r')) {
    }
    if (c != EOF)
      ungetc(c, f);
  }
  fclose(f);
  return count;
}

// Writes products from DynamicPtrArray to file
int save_products(const char* filename, DynamicPtrArray* arr) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    log_error("Error: Could not open %s for writing.\n", filename);
    return 0;
  }
  for (size_t i = 0; i < arr->count; ++i) {
    Product* p = (Product*)arr->data[i];
    fprintf(file, "%s,%s,%d,%.1f,%s;\n", p->code, p->name, p->ram_mb,
            p->screen_size, p->os);
  }
  fclose(file);
  return 1;
}

// Writes quotes from DynamicPtrArray to file
int save_quotes(const char* filename, DynamicPtrArray* arr) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    log_error("Error: Could not open %s for writing.\n", filename);
    return 0;
  }
  for (size_t i = 0; i < arr->count; ++i) {
    Quote* q = (Quote*)arr->data[i];
    fprintf(file, "%s,%s,%s,%.2f,%s;\n", q->quote_id, q->product_code,
            q->retailer, q->price, q->availability);
  }
  fclose(file);
  return 1;
}