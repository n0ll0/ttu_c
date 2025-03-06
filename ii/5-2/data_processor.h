#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H
#include "file_helper.h"

#define DATE_LENGTH 11 // e.g., "2023-02-07"
#define MAX_ENTRIES 5000

typedef struct {
  char date[DATE_LENGTH];
  int cases;
} CovidData;

void processCovidData(const char* filename, enum Type fileType);
int countCases(CovidData* data, int len);
void PrintCovid(CovidData* data, int len);
int compareCases(const void* a, const void* b);
int ReadFile(CovidData* data, const char* filename, enum Type fileType);
void PrintStatistics(char* last7DaysFrom, char* last7DaysTo,
  char* other7DaysFrom, char* other7DaysTo, int last7Days,
  int other7Days);

#endif
