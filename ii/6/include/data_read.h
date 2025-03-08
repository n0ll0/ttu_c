#pragma once
#include <stdlib.h>

enum FileType {
  CSV,
  TXT
};

typedef struct {
  char* title;
  size_t gradesLength;
  float* grades;
} LineData;

typedef struct {
  LineData* lines;
  size_t capacity;
  size_t count;
} Data;

Data ReadData(const char* filename, enum FileType fileType);
void FreeData(Data*);