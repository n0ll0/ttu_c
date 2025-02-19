#include "rates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Units {
  UNIT_DM,
  UNIT_M,
  UNIT_KM,
  UNIT_IN,
  UNIT_FT,
  UNIT_YD,
  UNIT_UNKNOWN
};

const char* UNITS[UNIT_UNKNOWN] = {
    [UNIT_DM] = "dm", [UNIT_M] = "m",   [UNIT_KM] = "km",
    [UNIT_IN] = "in", [UNIT_FT] = "ft", [UNIT_YD] = "yd"};

enum Units GetDistanceUnitType(char* unit);
const char* ReturnPrintableUnit(enum Units unit);
double Convert(double length, enum Units unit, enum Units desired_unit);

int main(int argc, char const** argv) {
  if (argc != 3) {
    return 1;
  }
  enum Units desired_unit = GetDistanceUnitType((char*)argv[2]);

  FILE* file = fopen(argv[1], "r");
  if (file != NULL)
    return 1;

  double total = 0;

  char unit_buffer[8];
  double distance = 0;
  size_t count = 0;

  while (fscanf(file, "%lf %s", &distance, unit_buffer) == 2) {
    enum Units unit = GetDistanceUnitType(unit_buffer);
    double convertedDistance = Convert(distance, unit, desired_unit);
    total += convertedDistance;
    ++count;
    printf("%12.2lf %2s -> %12.2lf %2s\n", distance, ReturnPrintableUnit(unit),
           convertedDistance, argv[2]);
  }
  if (count == 0)
    return 1;
  printf("\nTotal: %.2lf.2 %s\nAverage: %.2lf %s\n", total, argv[2],
         total / (double)count, argv[2]);

  fclose(file);
  return 0;
}

enum Units GetDistanceUnitType(char* unit) {
  for (int i = 0; i < UNIT_UNKNOWN; ++i) {
    if (strcmp(UNITS[i], unit) == 0) {
      return (enum Units)i;
    }
  }
  return UNIT_UNKNOWN;
  // if (strcmp(unit, "m") == 0)
  //   return UNIT_M;
  // if (strcmp(unit, "dm") == 0)
  //   return UNIT_DM;
  // if (strcmp(unit, "km") == 0)
  //   return UNIT_KM;
  // if (strcmp(unit, "ft") == 0)
  //   return UNIT_FT;
  // if (strcmp(unit, "yd") == 0)
  //   return UNIT_YD;
  // if (strcmp(unit, "in") == 0)
  //   return UNIT_IN;
  // return UNIT_UNKNOWN;
}

const char* ReturnPrintableUnit(enum Units unit) {
  if (unit == UNIT_UNKNOWN)
    return "??";
  return UNITS[unit];
  // switch (unit) {
  // case UNIT_M:
  //   return (const char*)"m";
  // case UNIT_DM:
  //   return (const char*)"dm";
  // case UNIT_KM:
  //   return (const char*)"km";
  // case UNIT_FT:
  //   return (const char*)"ft";
  // case UNIT_YD:
  //   return (const char*)"yd";
  // case UNIT_IN:
  //   return (const char*)"in";
  // default:
  //   return (const char*)"??";
  // }
}

/*
m->ft 0.3048f
m->km 1000.0f
in->ft 12.0f
ft->yd 3.0f
*/
double Convert(double length, enum Units unit, enum Units desired_unit) {
  if (unit == desired_unit)
    return length;
  switch (unit) {
  case UNIT_M:
    switch (desired_unit) {
    case UNIT_DM:
      return length * M_IN_DM;
    case UNIT_KM:
      return length * M_IN_KM;
    case UNIT_FT:
      return length * M_IN_FT;
    case UNIT_IN:
      return length * M_IN_IN;
    case UNIT_YD:
      return length * M_IN_YD;
    }
  case UNIT_DM:
    switch (desired_unit) {
    case UNIT_M:
      return length * DM_IN_M;
    case UNIT_KM:
      return length * DM_IN_KM;
    case UNIT_FT:
      return length * DM_IN_FT;
    case UNIT_IN:
      return length * DM_IN_IN;
    case UNIT_YD:
      return length * DM_IN_YD;
    }
  case UNIT_FT:
    switch (desired_unit) {
    case UNIT_DM:
      return length * FT_IN_DM;
    case UNIT_M:
      return length * FT_IN_M;
    case UNIT_KM:
      return length * FT_IN_KM;
    case UNIT_IN:
      return length * FT_IN_IN;
    case UNIT_YD:
      return length * FT_IN_YD;
    }
  case UNIT_KM:
    switch (desired_unit) {
    case UNIT_DM:
      return length * KM_IN_DM;
    case UNIT_M:
      return length * KM_IN_M;
    case UNIT_IN:
      return length * KM_IN_IN;
    case UNIT_FT:
      return length * KM_IN_FT;
    case UNIT_YD:
      return length * KM_IN_YD;
    }
  case UNIT_YD:
    switch (desired_unit) {
    case UNIT_DM:
      return length * YD_IN_DM;
    case UNIT_M:
      return length * YD_IN_M;
    case UNIT_KM:
      return length * YD_IN_KM;
    case UNIT_FT:
      return length * YD_IN_FT;
    case UNIT_IN:
      return length * YD_IN_IN;
    }
  case UNIT_IN:
    switch (desired_unit) {
    case UNIT_DM:
      return length * IN_IN_DM;
    case UNIT_M:
      return length * IN_IN_M;
    case UNIT_KM:
      return length * IN_IN_KM;
    case UNIT_FT:
      return length * IN_IN_FT;
    case UNIT_YD:
      return length * IN_IN_YD;
    }
  }
  return 0;
}