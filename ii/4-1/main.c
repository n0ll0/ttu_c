#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 256
#define MAX_PERSONS 2048
#define MAX_VEHICLES MAX_PERSONS

int ReadPersons(const char* file_name, Person dest[MAX_PERSONS]);
int ReadVehicles(const char* file_name, Vehicle dest[MAX_VEHICLES]);
void PrintPerson(Person* person);
void PrintVehicle(Vehicle* vehicle);

int main(int argc, char const* argv[]) {
  int person_count, vehicle_count;
  Person persons[MAX_PERSONS];
  Vehicle vehicles[MAX_VEHICLES];
  person_count = ReadPersons("data/person.txt", persons);
  vehicle_count = ReadVehicles("data/vehicles.txt", vehicles);
  
  puts("\nall peepel");
  for (int i = 0; i < person_count; ++i) {
    PrintPerson(&persons[i]);
    puts("");
    int j = 0, cnt = 0;
    for (; j < vehicle_count; ++j) {
      if (vehicles[j].person_id == persons[i].id) {
        printf("\tcar %d:  ", ++cnt);
        PrintVehicle(&vehicles[j]);
        puts("");
      }
    }
    if (cnt == 0) {
      puts("\t***No registered cars***\n");
    }
  }

  puts("\nall peepel");
  for (int i = 0; i < person_count; ++i) {
    Person person = persons[i];
    char missingIncome = person.annual_income == 0;
    printf("Name: %s %s\nIncome: %12.2lf EUR\n", person.name.first, person.name.last,
           person.annual_income);
    double sum = 0;
    for (int j = 0; j < vehicle_count; ++j) {
      if (vehicles[j].person_id == person.id) {
        sum += vehicles[j].annual_tax;
      }
    }

    double taxPcnt =
        missingIncome ? 0.0 : sum / person.annual_income * 100.0;
    printf("Tax: %15.2lf EUR\nTax pcnt: %10.2lf %%\n", sum, taxPcnt);
    if (taxPcnt > 10) {
      puts("WARNING! Tax > 10%%");
    }
    if (missingIncome) {
      puts("ERROR: Missing income");
    }
    puts("\n");
  }

  return 0;
}

int compare_names(void* a, void* b) {
  return ((Person*)a)->name.first > ((Person*)b)->name.first;
}

int ReadPersons(const char* file_name, Person persons[MAX_PERSONS]) {
  FILE* src = fopen(file_name, "r");
  if (src == NULL) {
    return -1;
  }

  int count = 0;
  const char lineBuffer[LINE_LENGTH];

  while (fgets(lineBuffer, LINE_LENGTH, src)) {
    if (sscanf(lineBuffer, "%lu %s %s %lf", &persons[count].id,
               persons[count].name.first, persons[count].name.last,
               &persons[count].annual_income) == 4) {
      ++count;
    }
  }
  fclose(src);

  qsort(persons, count, sizeof(Person), compare_names);

  return count;
}

int ReadVehicles(const char* file_name, Vehicle dest[MAX_VEHICLES]) {
  FILE* src = fopen(file_name, "r");
  if (src == NULL) {
    return -1;
  }

  int count = 0;
  const char lineBuffer[LINE_LENGTH];

  while (fgets(lineBuffer, LINE_LENGTH, src)) {
    if (sscanf(lineBuffer, "%lu %s %lf", &dest[count].person_id,
               dest[count].reg_num, &dest[count].annual_tax) == 3) {
      ++count;
    }
  }
  fclose(src);
  return count;
}

void PrintPerson(Person* person) {
  printf("%lu %s %s (income: %.2lf EUR)", person->id, person->name.first,
         person->name.last, person->annual_income);
}
void PrintVehicle(Vehicle* vehicle) {
  printf("%s (tax: %.2lf EUR)", vehicle->reg_num, vehicle->annual_tax);
}