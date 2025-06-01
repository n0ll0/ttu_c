#include "../../include/menuoption/search_zones.h"
#include "../../include/cmenu.h"
#include "../../include/dynamicarray.h"
#include "../../include/menuoption/display_all.h"
#include "../../include/zone.h"
#include "../../include/logger.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_zones() {
  DynamicPtrArray zones = {0};
  load_zones("./data/zoning.txt", &zones);

  log_event("Enter search term:");
  char search_term_1[64];
  scanf("%64s", search_term_1);

  int found = 0;
  log_event("Search results:\n");
  for (size_t i = 0; i < zones.count; ++i) {
    Zone* p = (Zone*)zones.data[i];

    if (strstr(p->city, search_term_1)) {

      //log_event("Zone: %s (%s), RAM: %dMB, Screen: %.1f\", OS: %s", p->name,
      //       p->code, p->ram_mb, p->screen_size, p->os);
      display_zone(p);
      found = 1;
    }
  }
  if (!found) {
    log_event("No matching zones found.\n");
  }
  //free(search_term_1);
  DynamicPtrArrayFree(&zones);
}
