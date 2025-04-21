#pragma once
#include "../include/dynamicarray.h"

#define MAX_NAME 128
#define MAX_OS 32
#define MAX_RETAILER 64
#define MAX_AVAIL 16

typedef struct {
  char code[16];
  char name[MAX_NAME];
  int ram_mb;
  float screen_size;
  char os[MAX_OS];
} Product;

typedef struct {
  char quote_id[16];
  char product_code[16];
  char retailer[MAX_RETAILER];
  float price;
  char availability[MAX_AVAIL];
} Quote;

int load_products(const char*, DynamicPtrArray*);
int load_quotes(const char*, DynamicPtrArray*);
int save_products(const char* filename, DynamicPtrArray*);
