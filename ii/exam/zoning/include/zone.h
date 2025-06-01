#pragma once
#include "../include/dynamicarray.h"

#define MAX_NAME 64
#define MAX_CITY 64

typedef struct {
  char name[MAX_NAME];
  char city[MAX_CITY];
  int residental_area;
  int commercial_area;
  int parking_area;
  int parking_space_count;
  int parking_space_price;
} Zone;

typedef enum {
  ZONE_TYPE_NONE,
  ZONE_TYPE_MIXED,
  ZONE_TYPE_RESIDENTAL,
  ZONE_TYPE_COMMERCIAL,
  ZONE_TYPE_PARKING
} ZONE_TYPE;

int load_zones(const char*, DynamicPtrArray*);
int save_zones(const char*, DynamicPtrArray*);

ZONE_TYPE detect_zone_type(Zone*);