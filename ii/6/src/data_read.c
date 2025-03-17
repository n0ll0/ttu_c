#include "../include/data_read.h"
#include "../include/log.h"
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
  int ch;
  size_t i = 0;

  if (*line == NULL || *line_size == 0) {
    *line_size = 128;
    *line = (char*)calloc(*line_size, sizeof(char));
    if (*line == NULL) {
      Log(LOG_ERROR, "Memory allocation failed for line buffer");
      return -1;
    }
  }

  while ((ch = fgetc(file)) != '\n' && ch != EOF) {
    if (i >= *line_size - 1) {
      *line_size *= 2;
      *line = (char*)realloc(*line, *line_size);
      if (*line == NULL) {
        Log(LOG_ERROR, "Memory reallocation failed for line buffer");
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
    Log(LOG_ERROR, "Failed to open file: %s", filename);
    return;
  }
  Log(LOG_INFO, "Starting to read file: %s", filename);

  char* line = calloc(INITIAL_LENGTH, sizeof(char));
  size_t line_size = INITIAL_LENGTH;
  int line_count = 0;

  while (getLine(&line, &line_size, file) != -1) {
    if (!handleLine(line, dest))
      break;
    line_count++;
  }

  Log(LOG_SUCCESS, "Successfully read %d lines from file", line_count);
  free(line);
  fclose(file);
}

int HandleLine(char* line, void* _dest, const char* delimiter) {
  Data* dest = (Data*)_dest;
  LineData lineData;
  char* token;
  size_t token_len;

  // First token is the title (don't call strtok twice)
  token = strtok(line, delimiter);
  if (token == NULL) {
    Log(LOG_WARNING, "Empty line encountered");
    return 0;
  }

  // Copy the title
  token_len = strlen(token) + 1;
  lineData.title = (char*)calloc(token_len, sizeof(char));
  if (lineData.title == NULL) {
    Log(LOG_ERROR, "Memory allocation failed for title");
    return 0;
  }
  strncpy(lineData.title, token, token_len);

  // Get the number of grades
  token = strtok(NULL, delimiter);
  if (token == NULL || sscanf(token, "%zu", &lineData.gradesLength) != 1) {
    Log(LOG_WARNING, "Invalid grade count format");
    free(lineData.title);
    return 0;
  }

  // Allocate memory for the grades
  lineData.grades = (float*)calloc(lineData.gradesLength, sizeof(float));
  if (lineData.grades == NULL) {
    Log(LOG_ERROR, "Memory allocation failed for grades");
    free(lineData.title);
    return 0;
  }

  // Get the grades
  for (size_t i = 0; i < lineData.gradesLength; ++i) {
    token = strtok(NULL, delimiter);
    if (token == NULL || sscanf(token, "%f", &lineData.grades[i]) != 1) {
      Log(LOG_WARNING, "Invalid grade format at position %zu", i);
      free(lineData.grades);
      free(lineData.title);
      return 0;
    }
  }

  // Resize array if needed
  if (dest->count >= dest->capacity) {
    size_t new_capacity = dest->capacity * 2;
    LineData* new_lines = realloc(dest->lines, new_capacity * sizeof(LineData));
    if (new_lines == NULL) {
      Log(LOG_ERROR, "Failed to reallocate memory for data lines");
      free(lineData.grades);
      free(lineData.title);
      return 0;
    }
    dest->lines = new_lines;
    dest->capacity = new_capacity;
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
  Log(LOG_INFO, "Starting to read data from %s (type: %s)", filename,
      fileType == CSV ? "CSV" : "TXT");

  Data data = {.lines = NULL, .capacity = INITIAL_LENGTH, .count = 0};

  data.lines = calloc(data.capacity, sizeof(LineData));
  if (data.lines == NULL) {
    Log(LOG_ERROR, "Failed to allocate initial memory for data");
    return data;
  }

  switch (fileType) {
  case CSV:
    ReadFileByLine(filename, HandleLineCOMMAS, &data);
    break;
  case TXT:
    ReadFileByLine(filename, HandleLineSPACE, &data);
    break;
  default:
    Log(LOG_ERROR, "Unknown file type specified");
    break;
  }

  if (data.count == 0) {
    Log(LOG_WARNING, "No data was read from file");
    free(data.lines);
    data.lines = NULL;
    data.capacity = 0;
  } else {
    Log(LOG_SUCCESS, "Successfully read %zu records", data.count);
  }

  return data;
}
