#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 1024
#define MAX_PERSONS 8
#define MAX_VEHICLES MAX_PERSONS

#define NAME_MAX_LENGTH 32
#define REG_NUM_LENGTH 10

#define PERSON_FILE "data/person.txt"
#define VEHICLE_FILE "data/vehicles.txt"

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

int ReadPersons(const char* file_name, Person dest[MAX_PERSONS]);
int ReadVehicles(const char* file_name, Vehicle dest[MAX_VEHICLES]);
void PrintPerson(Person* person);
void PrintVehicle(Vehicle* vehicle);
void Part1(Person* persons, int person_count, Vehicle* vehicles,
           int vehicle_count);
void Part2(Person* persons, int person_count, Vehicle* vehicles,
           int vehicle_count);