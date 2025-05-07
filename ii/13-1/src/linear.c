#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void PrintTime(struct TimePoints t) {
  printf("Reading:  %9.6lf s\n", (double)(t.read - t.start) / CLOCKS_PER_SEC);
  printf("Printing: %9.6lf s\n", (double)(t.print - t.read) / CLOCKS_PER_SEC);
  printf("Freeing:  %9.6lf s\n", (double)(t.free - t.print) / CLOCKS_PER_SEC);
  printf("Total:    %9.6lf s\n", (double)(t.free - t.start) / CLOCKS_PER_SEC);
}

int GetNameIndex(NameEntry* arr, int size, const char* name) {
  for (int i = 0; i < size; ++i) {
    if (strcmp(arr[i].name, name) == 0)
      return i;
  }
  return -1;
}

void RunLinearSolution(const char* input_filename) {
  struct TimePoints tp;
  tp.start = clock();

  FILE* fin = fopen(input_filename, "r");
  if (!fin) {
    perror("Input file open failed");
    exit(1);
  }

  NameEntry* arr = NULL;
  int arr_size = 0, arr_cap = 0;

  char eid[32], fname[32], lname[32], city[32];
  char combined[NAME_LEN];

  // Reading and counting
  while (fscanf(fin, "%31s %31s %31s %31s", eid, fname, lname, city) == 4) {
    snprintf(combined, sizeof(combined), "%s %s", fname, lname);
    int idx = GetNameIndex(arr, arr_size, combined);
    if (idx >= 0) {
      arr[idx].count++;
    } else {
      if (arr_size == arr_cap) {
        arr_cap = arr_cap ? arr_cap * 2 : 128;
        arr = realloc(arr, arr_cap * sizeof(NameEntry));
        if (!arr) {
          fprintf(stderr, "Memory allocation failed\n");
          fclose(fin);
          exit(1);
        }
      }
      strncpy(arr[arr_size].name, combined, NAME_LEN - 1);
      arr[arr_size].name[NAME_LEN - 1] = '\0';
      arr[arr_size].count = 1;
      arr_size++;
    }
  }
  fclose(fin);
  tp.read = clock();

  // Output to file
  FILE* fout = fopen("output_linear.txt", "w");
  if (!fout) {
    perror("Output file open failed");
    free(arr);
    exit(1);
  }
  for (int i = 0; i < arr_size; ++i) {
    fprintf(fout, "%s %d\n", arr[i].name, arr[i].count);
  }
  fclose(fout);
  tp.print = clock();

  // Free memory
  free(arr);
  tp.free = clock();

  printf("Found %d names\n\n", arr_size);
  PrintTime(tp);
}
