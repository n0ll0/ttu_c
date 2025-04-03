#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>

#include "file_type.h"

#define LEN_CURRICULUM 4

typedef struct {
  size_t index;
  char *firstName;
  char *lastName;
  char curriculum[LEN_CURRICULUM + 1];
  float points;
} Person;

typedef struct {
  Person* people;
  size_t capacity;
  size_t count;
} People;

int ComparePersonNames(const void*, const void*);
void SortPeopleNames(People*);
void SortPeoplePoints(People*);
void PrintPerson(const char* __restrict__ format, FILE* outputFile, Person* person);
void PrintPeople(const char* __restrict__ format, FILE* outputFile, People* people);

void AddPerson(People*, Person*);
Person* GetPerson(People*, int index);
void PutPeopleToWork(People*);
#endif // STUDENT_H
