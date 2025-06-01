#include "../../include/menuoption/display_all.h"
#include "../../include/menuoption/zone_pricing.h"
#include "../../include/dynamicarray.h"
#include "../../include/zone.h"
#include "../../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float calc_avg_of_type(ZONE_TYPE z, DynamicPtrArray* zones) {
    int total = 0;
    int count = 0;
    for (size_t i = 0; i < zones->count; ++i) {
        Zone* zone = (Zone*)zones->data[i];
        if (detect_zone_type(zone) == z && zone->parking_area != 0) {
            total += zone->parking_space_price;
            ++count;
        }
    }

    return ((float)total) / ((float)count);
}

void zone_pricing() {
    DynamicPtrArray zones = {0};
    load_zones("./data/zoning.txt", &zones);

    if (zones.count == 0) {
        log_event("No zones found.\n");
        DynamicPtrArrayFree(&zones);
        return;
    }


    float avg_mixed = calc_avg_of_type(ZONE_TYPE_MIXED, &zones);
    float avg_residental = calc_avg_of_type(ZONE_TYPE_RESIDENTAL, &zones);

    log_event("average for mixed: %f", avg_mixed);
    log_event("average for avg_residental: %f", avg_residental);
    if (avg_residental == 0) {
        log_error("either something went wrong when calulating average of residental, or there is a 0 average: {division by 0 error}");
        return;
    }
    float diff_pct = avg_mixed / avg_residental;
    log_event("difference in percentage: %f", diff_pct);
    if (diff_pct > 1.05f) { // mixed is expensive
        log_event("mixed is more expensive than residental");
    } else if (diff_pct < 0.95f) { // residental is expensive
        log_event("residental is more expensive than mixed");
    } else { // similar
        log_event("residental and mixed are similarly priced");
    }

}
