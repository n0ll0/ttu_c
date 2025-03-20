/**
 * File:        generator.c
 * Author:      Risto Heinsar
 * Created:     12.03.2015
 * Modified     14.03.2023
 *
 * Description: This is a random data generator
 *
 * Note:        This is a starter code for a lab task
 */

#include "generator.h"
#include "candidate.h"
#include "file_type.h"
#include "name_pools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  /* Names are assigned from the pools in the header*/
  const char* firstNames[] = FIRST_NAME_POOL;
  const char* lastNames[] = LAST_NAME_POOL;
  const char* curriculumCodes[] = CURRICULUM_CODES;
  const char* file_type_formats_extensions[] = FILE_TYPE_FORMATS_EXTENSIONS;
  const char* file_type_formats[] = FILE_TYPE_FORMATS;

  /* Find the counts for the pool sizes */
  int firstNamePoolSize = sizeof(firstNames) / sizeof(char*);
  int lastNamePoolSize = sizeof(lastNames) / sizeof(char*);
  int curriculumCodePoolSize = sizeof(curriculumCodes) / sizeof(char*);

  printf("Valige failitüüp:\n");
  for (int i = 0; i < FILE_TYPE_COUNT; i++) {
    printf("\t%d. %s\n", i, file_type_formats_extensions[i]);
  }
  int fileType = FILE_TYPE_TXT;
  if (scanf("%d", &fileType) != 1 || fileType < 0 ||
      fileType >= FILE_TYPE_COUNT) {
    fprintf(stderr, "Vale failitüüp! (jätkame .txt formaadis)\n");
    fileType = FILE_TYPE_TXT;
  }

  char outFileName[256] = "generated_candidates";
  strcat(outFileName, file_type_formats_extensions[fileType]);

  printf("The database contains:\n"
         "\t%4d first names\n"
         "\t%4d last names\n"
         "\t%4d curriculum codes\n",
         firstNamePoolSize, lastNamePoolSize, curriculumCodePoolSize);

  printf("Mitu kandidaati soovite genereerida?\n> ");
  int numCandidates;
  scanf("%d", &numCandidates);

  Candidate* candidates = calloc(numCandidates, sizeof(Candidate));
  if (candidates == NULL) {
    fprintf(stderr, "Mälu eraldamine ebaõnnestus\n");
    return EXIT_FAILURE;
  }

  GenerateCandidates(numCandidates, candidates, firstNames, firstNamePoolSize,
                     lastNames, lastNamePoolSize, curriculumCodes,
                     curriculumCodePoolSize);

  qsort(candidates, numCandidates, sizeof(Candidate), ComparCandidate);

  FILE* outputFile = fopen(outFileName, "w");
  if (outputFile == NULL) {
    fprintf(stderr, "Faili avamine ebaõnnestus\n");
    return EXIT_FAILURE;
  }

  if (fileType == FILE_TYPE_CSV) {
    fprintf(outputFile,
            "Index,Last name,First name,Curriculum code,Admission points\n");
  }

  for (int i = 0; i < numCandidates; i++) {
    PrintCandidate(fileType, file_type_formats, outputFile, &candidates[i]);
  }
  fclose(outputFile);
  printf("Andmed edukalt kirjutatud faili '%s'\n", outFileName);

  for (int i = 0; i < numCandidates; i++) {
    free(candidates[i].firstName);
    free(candidates[i].lastName);
    free(candidates[i].curriculumCode);
  }
  free(candidates);

  return EXIT_SUCCESS;
}

/**
 * Description:    Generates a random number in range provided, ends inclusive
 *
 * Parameters:     min, minimum value
 *                 max, maximum vale
 *
 * Return:         integer, generated random number
 */
int GetRand(int min, int max) { return (rand() % (max - min + 1)) + min; }

/**
 * Description:    Generates candidates with random data and saves them to the
 * array
 *
 * Parameters:     numCandidates, number of candidates to generate
 *                 candidates, array to store the candidates
 *                 firstNames, array of first names
 *                 firstNamePoolSize, size of the firstNames array
 *                 lastNames, array of last names
 *                 lastNamePoolSize, size of the last names array
 *                 curriculumCodes, array of curriculum codes
 *                 curriculumCodePoolSize, size of the curriculumCodes array
 */
void GenerateCandidates(int numCandidates, Candidate* candidates,
                        const char* firstNames[], int firstNamePoolSize,
                        const char* lastNames[], int lastNamePoolSize,
                        const char* curriculumCodes[],
                        int curriculumCodePoolSize) {
  for (int i = 0; i < numCandidates; i++) {
    candidates[i].index = i + 1;
    candidates[i].lastName =
        strdup(lastNames[GetRand(0, lastNamePoolSize - 1)]);
    candidates[i].firstName =
        strdup(firstNames[GetRand(0, firstNamePoolSize - 1)]);
    candidates[i].curriculumCode =
        strdup(curriculumCodes[GetRand(0, curriculumCodePoolSize - 1)]);
    candidates[i].admissionPoints = GetRand(0, 100);
  }
}