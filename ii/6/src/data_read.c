#include "../include/data_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_LENGTH 2048

void FreeData(Data* data) {
  if (data->lines != NULL) {
    for (size_t i = 0; i < data->count; ++i) {
      free(data->lines[i].title);
      free(data->lines[i].grades);
    }
    free(data->lines);
  }
}

int getLine(char** line, size_t* line_size, FILE* file) {
  printf("getLine\n");
  int ch;
  size_t i = 0;

  if (*line == NULL || *line_size == 0) {
    *line_size = 128;
    *line = (char*)calloc(*line_size, sizeof(char));
    if (*line == NULL) {
      perror("Unable to allocate memory for the line buffer.");
      return -1;
    }
  }

  while ((ch = fgetc(file)) != '\n' && ch != EOF) {
    if (i >= *line_size - 1) {
      *line_size *= 2;
      *line = (char*)realloc(*line, *line_size);
      if (*line == NULL) {
        perror("Unable to allocate memory for the line buffer.");
        return -1;
      }
    }
    (*line)[i++] = ch;
  }

  (*line)[i] = '\0';
  *line_size = i + 1;

  return (ch == EOF && i == 0) ? -1 : 1;
}

void ReadFileByLine(const char* filename, int (*handleLine)(char*, void*),
                    void* dest) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }
  printf("ReadFileByLine");

  char* line = calloc(INITIAL_LENGTH, sizeof(char));
  size_t line_size = INITIAL_LENGTH;
  while (getLine(&line, &line_size, file) != -1) {
    if (!handleLine(line, dest))
      break;
  }
  free(line);
  fclose(file);
}

int HandleLine(char* line, void* _dest, const char* delimiter) {
  printf("HandleLine\n");
  Data* dest = (Data*)_dest;
  LineData lineData;
  char* token;
  size_t token_len;

  // Get the title
  token = strtok(line, delimiter);
  if (token == NULL) {
    return 0;
  }
  token_len = strlen(token) + 1;
  lineData.title = (char*)calloc(token_len, sizeof(char));
  strncpy(lineData.title, token, token_len);

  // Get the number of grades
  token = strtok(NULL, delimiter);
  if (token == NULL || sscanf(token, "%lu", &lineData.gradesLength) != 1) {
    free(lineData.title);
    return 0;
  }

  // Allocate memory for the grades
  lineData.grades = (float*)calloc(lineData.gradesLength, sizeof(float));
  if (lineData.grades == NULL) {
    free(lineData.title);
    return 0;
  }

  // Get the grades
  for (size_t i = 0; i < lineData.gradesLength; ++i) {
    token = strtok(NULL, delimiter);
    if (token == NULL || sscanf(token, "%f", &lineData.grades[i]) != 1) {
      free(lineData.grades);
      free(lineData.title);
      return 0;
    }
  }

  if (dest->capacity <= dest->count) {
    dest->lines = realloc(dest->lines, dest->capacity * 2);
    if (dest->lines == NULL) {
      perror("Couldn't reallocate datalines\n");
      free(lineData.grades);
      free(lineData.title);
      return 0;
    }
  }

  dest->lines[dest->count] = lineData;
  dest->count++;
  return 1;
}
int HandleLineCOMMAS(char* line, void* _data) {
  return HandleLine(line, _data, ",");
}
int HandleLineSPACE(char* line, void* _data) {
  return HandleLine(line, _data, " ");
}

Data ReadData(const char* filename, enum FileType fileType) {
  Data data;
  data.lines = calloc(INITIAL_LENGTH, sizeof(LineData));
  data.capacity = INITIAL_LENGTH * sizeof(LineData);
  data.count = 0;

  switch (fileType) {
  case CSV:
    ReadFileByLine(filename, HandleLineCOMMAS, &data);
    break;
  case TXT:
    ReadFileByLine(filename, HandleLineSPACE, &data);
    break;
  default:
    break;
  }

  if (data.count <= 0) {
    free(data.lines);
    data.lines = NULL;
    data.count = 0;
  }

  return data;
}
