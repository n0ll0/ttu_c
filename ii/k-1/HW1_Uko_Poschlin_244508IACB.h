#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 256
#define CODE_LENGTH 10
#define GRADES_LENGTH 6

#define MAX_PERSONS_COUNT 256
#define LINE_BUFFER_SIZE 256

struct Array {
  size_t capacity;
  size_t length;
  void* values;
};
struct IntArray {
  size_t capacity;
  size_t length;
  int* values;
};
struct StudentArray {
  size_t capacity;
  size_t length;
  struct Student* values;
};
struct Student {
  char name[NAME_LENGTH];
  char studentCode[CODE_LENGTH];
  int grades[GRADES_LENGTH];
};

struct StudentArray ReadStudents(const char* fileName);
void PrintStudent(struct Student* student);
int CalculateStudentStipendium(struct Student* student);
int GetStudentYear(struct Student* student);
void FreeStudentArray(struct StudentArray students);
void PrintAllStudentsStipendiums(struct StudentArray* students);
int compare_students(const void* a, const void* b) {
  int a_ = GetStudentYear((struct Student*)a);
  int b_ = GetStudentYear((struct Student*)b);
  return a_ > b_;
}
