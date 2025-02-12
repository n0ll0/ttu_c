#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_IN_FT 0.3048f
#define M_IN_KM 1000.00f
#define FT_IN_M 1 / M_IN_FT
#define FT_IN_KM 304.8f
#define KM_IN_M 1 / M_IN_KM
#define KM_IN_FT 1 / FT_IN_KM

#define FT_IN_MI 5280.00f

enum Units { UNIT_M, UNIT_FT, UNIT_KM, UNIT_UNKNOWN };
enum Units GetDistanceUnitType(char* unit);
const char* ReturnPrintableUnit(enum Units unit);
double convert(double length, enum Units unit, enum Units desired_unit);

int main(int argc, char const** argv) {
  if (argc != 3) {
    printf("nigga");
    return 1;
  }
  enum Units desired_unit = GetDistanceUnitType((char*)argv[2]);

  FILE* file = fopen(argv[1], "r");

  char unit_buffer[2];
  double distance = 0;

  while (fscanf(file, "%lf %s", &distance, unit_buffer) == 2) {
    enum Units unit = GetDistanceUnitType(unit_buffer);
    printf("%.2f %s -> %.2f %s\n", distance, ReturnPrintableUnit(unit),
           convert(distance, unit, desired_unit), argv[2]);
  }

  fclose(file);
  return 0;
}

enum Units GetDistanceUnitType(char* unit) {
  // printf("%s",unit);
  if (strcmp(unit, "m")==0)
    return UNIT_M;
  if (strcmp(unit, "ft")==0)
    return UNIT_FT;
  if (strcmp(unit, "km")==0)
    return UNIT_KM;
  return UNIT_UNKNOWN;
}

const char* ReturnPrintableUnit(enum Units unit) {
  switch (unit) {
  case UNIT_M:
    return (const char*) "m";
  case UNIT_FT:
    return (const char*) "ft";
  case UNIT_KM:
    return (const char*) "km";
  default:
    return (const char*) "??";
  }
}

double convert(double length, enum Units unit, enum Units desired_unit) {
  // printf("[%lf-%s-%s]", length, ReturnPrintableUnit(unit),
  //        ReturnPrintableUnit(desired_unit));
  if (unit == desired_unit)
    return length;
  if (unit == UNIT_M) {
    if (desired_unit == UNIT_FT)
      return length * FT_IN_M;
    if (desired_unit == UNIT_KM)
      return length * KM_IN_M;
  }
  if (unit == UNIT_FT) {
    if (desired_unit == UNIT_M)
      return length * M_IN_FT;
    if (desired_unit == UNIT_KM)
      return length * KM_IN_FT;
  }
  if (unit == UNIT_KM) {
    if (desired_unit == UNIT_M)
      return length * M_IN_KM;
    if (desired_unit == UNIT_FT)
      return length * FT_IN_KM;
  }
  return 0;
}