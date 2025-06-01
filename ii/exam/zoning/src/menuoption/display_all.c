#include "../../include/menuoption/display_all.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/zone.h"
#include "../../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_zone(Zone* z) {
  char residental_area_buf[64];
  if (z->residental_area != 0) {
    snprintf(residental_area_buf,64, "%d", z->residental_area);
  } else {
    snprintf(residental_area_buf,64, "none");
  }
  char commercial_area_buf[64];
  if (z->commercial_area != 0) {
    snprintf(commercial_area_buf,64, "%d", z->commercial_area);
  } else {
    snprintf(commercial_area_buf,64, "none");
  }
  char parking_area_buf[64];
  if (z->parking_area != 0) {
    snprintf(parking_area_buf,64, "%d", z->parking_area);
  } else {
    snprintf(parking_area_buf,64, "none");
  }
  log_event("NAME: %s;\t \
    CITY: %s;\t \
    RESIDENTAL AREA: %sm2;\t \
    COMMERCIAL AREA: %s;\t \
    PARKING AREA: %s;\t \
    PARKING SPACE COUNT: %d;\t \
    PARKING SPACE PRICE: %dEUR\n",
    z->name,
    z->city,
    residental_area_buf,
    commercial_area_buf,
    parking_area_buf,
    z->parking_space_count,
    z->parking_space_price
  );
}

void display_all() {
  DynamicPtrArray zones = {0};

  load_zones("./data/zoning.txt", &zones);

  if (zones.count == 0) {
    log_event("No zones found.\n");
    DynamicPtrArrayFree(&zones);
    return;
  }

  printf("Zones:\n");
  for (size_t i = 0; i < zones.count; ++i) {
    Zone* zone = (Zone*)zones.data[i];
    display_zone(zone);
  }

  DynamicPtrArrayFree(&zones);
}
