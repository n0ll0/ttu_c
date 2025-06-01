#include "../include/zone.h"
#include "../include/dynamicarray.h"
#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Loads quotes from file into a DynamicPtrArray
int load_zones(const char* filename, DynamicPtrArray* arr) {
  FILE* f = fopen(filename, "r");
  if (!f)
    return 0;
  int count = 0;
  while (1) {
    Zone* q = malloc(sizeof(Zone));
    if (!q) continue;
    int res = fscanf(f, "%s %s %d %d %d %d %d\n",
                    q->name,
                    q->city,
                    &q->residental_area,
                    &q->commercial_area,
                    &q->parking_area,
                    &q->parking_space_count,
                    &q->parking_space_price);
    if (res != 7) {
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
int save_zones(const char* filename, DynamicPtrArray* arr) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    log_error("Error: Could not open %s for writing.\n", filename);
    return 0;
  }
  for (size_t i = 0; i < arr->count; ++i) {
    Zone* q = (Zone*)arr->data[i];
    fprintf(file, "%s %s %d %d %d %d %d\n",
                    q->name,
                    q->city,
                    q->residental_area,
                    q->commercial_area,
                    q->parking_area,
                    q->parking_space_count,
                    q->parking_space_price);
  }
  fclose(file);
  return 1;
}

ZONE_TYPE detect_zone_type(Zone* z) {
  ZONE_TYPE type = ZONE_TYPE_NONE;

  if (z->residental_area != 0) {
    type = ZONE_TYPE_RESIDENTAL;
  }
  if (z->commercial_area != 0) {
    if (type != ZONE_TYPE_NONE) {
      return ZONE_TYPE_MIXED;
    }
    return ZONE_TYPE_COMMERCIAL;
  }
  if (z->parking_area != 0) {
    if (type == ZONE_TYPE_NONE) {
      return ZONE_TYPE_PARKING;
    }
    return type;
  }
  return type;
}