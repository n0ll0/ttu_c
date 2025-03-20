#include "candidate.h"

int ComparCandidate(const void* a, const void* b) {
  // Get comparison for last names
  int ret = strcmp(((Candidate*)a)->lastName, ((Candidate*)b)->lastName);

  // When last names match, return difference by first name
  if (ret == 0)
    return strcmp(((Candidate*)a)->firstName, ((Candidate*)b)->firstName);

  // return difference by last name
  return ret;
}

void PrintCandidate(enum FILE_TYPE fmt, const char* file_type_formats[], FILE* outputFile, Candidate* candidate) {
  fprintf(outputFile, file_type_formats[fmt], candidate->index,
          candidate->lastName, candidate->firstName, candidate->curriculumCode,
          candidate->admissionPoints);
}