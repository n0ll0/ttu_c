#pragma once

#include <inttypes.h>
#define NAME_MAX_LENGTH 32
#define REG_NUM_LENGTH 10

typedef uint64_t Id;

typedef struct {
  Id id;
  struct {
    char first[NAME_MAX_LENGTH];
    char last[NAME_MAX_LENGTH];
  } name;
  double annual_income;
} Person;

typedef struct {
  Id person_id;
  char reg_num[REG_NUM_LENGTH];
  double annual_tax;
} Vehicle;
