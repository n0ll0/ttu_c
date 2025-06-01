#include "../../include/menuoption/display_all.h"
#include "../../include/menuoption/display_grouped_zones.h"
#include "../../include/dynamicarray.h"
#include "../../include/zone.h"
#include "../../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display_zones_1_group(ZONE_TYPE z, DynamicPtrArray* zones) {
    for (size_t i = 0; i < zones->count; ++i) {
        Zone* zone = (Zone*)zones->data[i];
        if (detect_zone_type(zone) == z) {
            display_zone(zone);
        }
    }
}

void display_grouped_zones() {
    DynamicPtrArray zones = {0};
    load_zones("./data/zoning.txt", &zones);

    if (zones.count == 0) {
        log_event("No zones found.\n");
        DynamicPtrArrayFree(&zones);
        return;
    }

    log_event("====");
    printf("Zones grouped:\n");
    log_event("Grouping zone MIXED");
    display_zones_1_group(ZONE_TYPE_MIXED, &zones);

    log_event("====");
    printf("Zones grouped:\n");
    log_event("Grouping zone RESIDENTAL");
    display_zones_1_group(ZONE_TYPE_RESIDENTAL, &zones);

    log_event("====");
    printf("Zones grouped:\n");
    log_event("Grouping zone COMMERCIAL");
    display_zones_1_group(ZONE_TYPE_COMMERCIAL, &zones);

    log_event("====");
    printf("Zones grouped:\n");
    log_event("Grouping zone PARKING");
    display_zones_1_group(ZONE_TYPE_PARKING, &zones);

    DynamicPtrArrayFree(&zones);
}
