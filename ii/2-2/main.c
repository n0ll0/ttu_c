
#define FT_IN_M 0.3048f
#define FT_IN_MI 5280.00f
#define M_IN_KM 1000.00f

enum Units { UNIT_M, UNIT_FT, UNIT_KM, UNIT_UNKNOWN };
// Conversion using doubles
double GetConvertedDistance(double value, enum Units inputUnit,
                            enum Units destUnit);

enum Unit GetDistanceUnitType(char* unit);

void PrintUnit(enum Units unit) {
  switch (unit) {
  case UNIT_FT:
    printf("ft");
    break;
  }
}

char* ReturnPrintableUnit(enum Units unit) {
  switch (unit) {
  case UNIT_FT:
    return "ft";
  }
}