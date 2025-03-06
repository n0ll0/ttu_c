/**
 * File:         employee_db.c
 * Author:       Risto Heinsar
 * Created:      10.02.2015
 * Modified:     25.02.2023
 *
 * Description:  Library to work with employee struct
 */
#include "employee_db.h"
#include <string.h>
#include <stdio.h>
// TODO: implement the functions in the header
void PrintStructArray(employee* staff, int len) {
  for (int i = 0; i < len; i++) {
    printf("%s %s, %.2f, %d\n", staff[i].fName, staff[i].lName, staff[i].wage,
           staff[i].yearsEmployed);
  }
}

int ComparFuncStructEmploymentLength(const void* x, const void* y) {
  const employee* a = x;
  const employee* b = y;
  return b->yearsEmployed - a->yearsEmployed;
}

int ComparFuncStructFirstName(const void* x, const void* y) {
  const employee* a = x;
  const employee* b = y;
  return strcmp(b->fName, a->fName);
}

int ComparFuncStructLastFirstName(const void* x, const void* y) {
  const employee* a = x;
  const employee* b = y;
  const int lN = strcmp(b->lName, a->lName);

  if (lN == 0) {
    return strcmp(b->fName, a->fName);
  }

  return lN;

}
