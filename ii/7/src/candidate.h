#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <stdio.h>
#include <string.h>

#include "file_type.h"

typedef struct {
  int index;
  char* firstName;
  char* lastName;
  char* curriculumCode;
  float admissionPoints;
} Candidate;
int ComparCandidate(const void* a, const void* b);
void PrintCandidate(enum FILE_TYPE fmt, const char* file_type_formats[], FILE* outputFile, Candidate* candidate);

#endif // CANDIDATE_H
