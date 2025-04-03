#include "student.h"
#include <stdlib.h>
#include <string.h>

int ComparePersonNames(const void* a, const void* b) {
  // Get comparison for last names
  int ret = strcmp(((Person*)a)->lastName, ((Person*)b)->lastName);

  // When last names match, return difference by first name
  if (ret == 0)
    return strcmp(((Person*)a)->firstName, ((Person*)b)->firstName);

  // return difference by last name
  return ret;
}
int ComparePersonPoints(const void* a, const void* b) {
  return ((Person*)b)->points - ((Person*)a)->points;
}

void SortPeopleNames(People* people) {
  qsort(people->people, people->count, sizeof(Person), ComparePersonNames);
}
void SortPeoplePoints(People* people) {
  qsort(people->people, people->count, sizeof(Person), ComparePersonPoints);
}

void PrintPerson(const char* __restrict__ format, FILE* outputFile,
                 Person* person) {
  fprintf(outputFile, format, person->index, person->lastName,
          person->firstName, person->curriculum, person->points);
}

void PrintPeople(const char* __restrict__ format, FILE* outputFile,
                 People* people) {
  for (size_t i = 0; i < people->count; i++) {
    PrintPerson(format, outputFile, &people->people[i]);
  }
}

void AddPerson(People* people, Person* person) {
  if (people->people == NULL) {
    people->capacity = 1;
    people->people = calloc(people->capacity, sizeof(Person));
  }
  if (people->count == people->capacity) {
    people->capacity = people->capacity * 2 + 1;
    people->people = realloc(people->people, people->capacity * sizeof(Person));
  }

  people->people[people->count] = *person;
  people->count++;
}
Person* GetPerson(People* people, int index) {
  if (index < 0 || index >= people->count) {
    return NULL;
  }
  return &people->people[index];
}
void PutPeopleToWork(People* people) {
  if (people->people == NULL) {
    return;
  }
  for (size_t i = 0; i < people->count; i++) {
    if (people->people[i].lastName != NULL) {
      free(people->people[i].lastName);
      people->people[i].lastName = NULL;
    }
    if (people->people[i].firstName != NULL) {
      free(people->people[i].firstName);
      people->people[i].firstName = NULL;
    }
  }
  if (people->people != NULL) {
    free(people->people);
    people->people = NULL;
  }
  people->count = people->capacity = 0;
}
