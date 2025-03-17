#include "../include/main.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const* argv[]) {
  if (argc!= 2) {
    fprintf(stderr, "Usage: %s /<filename>.(csv|txt)/\n", argv[0]);
    return 1;
  }

  enum FileType fileType;
  if (strstr(argv[1], ".txt") != NULL) {
    fileType = TXT;
  } else if (strstr(argv[1], ".csv") != NULL) {
    fileType = CSV;
  }

  Data data = ReadData(argv[1], fileType);

  if (data.lines != NULL) {
    // Log(LOG_SUCCESS, "Data read successfully. Count: %zu\n", data.count);
    // You can add code here to process the data if needed
    for (size_t i = 0; i < data.count; ++i) {
      printf("Line %zu: Title: %s, Grades Length: %zu, Grades: ", i,
             data.lines[i].title, data.lines[i].gradesLength);
      for (size_t j = 0; j < data.lines[i].gradesLength; ++j) {
        printf("%.2f ", data.lines[i].grades[j]);
      }
      printf("\n");
    }
  } else {
    Log(LOG_ERROR, "No data read or error occurred.\n");
  }

  FreeData(&data); // Free the allocated memory
  return 0;
}
