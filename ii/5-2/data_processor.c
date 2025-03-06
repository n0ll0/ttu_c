#include "data_processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void processCovidData(const char* filename, enum Type fileType) {
  CovidData data[MAX_ENTRIES];
  int count = ReadFile(data, filename, fileType);

  CovidData* dataEnd = data + count;

  char* last7DaysFrom = strdup((*(dataEnd - 7)).date);
  char* last7DaysTo = strdup((*(dataEnd - 1)).date);
  char* other7DaysFrom = strdup((*(dataEnd - 7 - 7)).date);
  char* other7DaysTo = strdup((*(dataEnd - 7 - 1)).date);
  int last7Days = countCases(dataEnd - 7, 7);
  int other7Days = countCases(dataEnd - 7 - 7, 7);

  // Display the last 14 days statistics
  printf("Last 14 days\nDate       Cases\n");
  PrintCovid(dataEnd - 14, 14);

  // Sort data for top 10 days
  qsort(data, count, sizeof(CovidData), compareCases);

  // Display top 10 days
  printf("\nTop 10 days\nDate       Cases\n");
  PrintCovid(data, 10);

  PrintStatistics(last7DaysFrom, last7DaysTo, other7DaysFrom, other7DaysTo,
                  last7Days, other7Days);

  free(last7DaysFrom);
  free(last7DaysTo);
  free(other7DaysFrom);
  free(other7DaysTo);
}

int compareCases(const void* a, const void* b) {
  CovidData* dataA = (CovidData*)a;
  CovidData* dataB = (CovidData*)b;
  return dataB->cases - dataA->cases;
}

int countCases(CovidData* data, int len) {
  int totalCases = 0;
  for (int i = 0; i < len; i++) {
    totalCases += data[i].cases;
  }
  return totalCases;
}

void PrintCovid(CovidData* data, int len) {
  for (int i = 0; i < len; i++) {
    printf("%s   %d\n", data[i].date, data[i].cases);
  }
}

int ReadFile(CovidData* data, const char* filename, enum Type fileType) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int count = 0;
  char line[256];

  // Skip the header line
  fgets(line, sizeof(line), file);
  if (fileType == CSV) {
    while (fgets(line, sizeof(line), file)) {
      if (count >= MAX_ENTRIES)
        break;
      sscanf(line, "%*[^,],%[^,],%d,%*[^,],%*[^,],%*[^,]", data[count].date,
             &data[count].cases);
      count++;
    }
  } else if (fileType == SPACE_DELIMITED) {
    while (fgets(line, sizeof(line), file)) {
      if (count >= MAX_ENTRIES)
        break;
      sscanf(line, "%*s %s %d,%*s %*s %*s", data[count].date,
             &data[count].cases);
      count++;
    }
  }

  fclose(file);
  return count;
}

void PrintStatistics(char* last7DaysFrom, char* last7DaysTo,
  char* other7DaysFrom, char* other7DaysTo, int last7Days,
  int other7Days) {

printf("\nTotal cases in last 7 days (%s - %s): %d\n", last7DaysFrom,
last7DaysTo, last7Days);
printf("Total cases in 7 days before that (%s - %s): %d\n", other7DaysFrom,
other7DaysTo, other7Days);
int totalCases = last7Days + other7Days;
float diffPercentage = ((float)last7Days) / ((float)totalCases);
printf("Difference in percentage between last 7 days and 7 days before that: "
"%.2f%%\n",
diffPercentage * 100);
if (diffPercentage > 1.0) {
printf("Trend is rising\n");
} else {
printf("Trend is falling\n");
}
}