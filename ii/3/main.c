#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For tolower

#define MAX_PERSONS 100
#define MAX_VEHICLES 200
#define TAX_WARNING_THRESHOLD 10.0

struct Person {
  long long int person_id;
  double income;
  double total_tax;
  double tax_percentage;
  char firstname[50];
  char lastname[50];
};

struct Vehicle {
  long long int person_id;
  double tax;
  char reg_nr[20];
};

// Function prototypes for file reading
int ReadPersons(struct Person* persons, int max_persons, const char* filename);
int ReadVehicles(struct Vehicle* vehicles, int max_vehicles, const char* filename);

// Function prototype for sorting
void SortPersons(struct Person* persons, int person_count);

// Function prototypes for displaying data
void DisplayDataPart1(struct Person* persons, int person_count, struct Vehicle* vehicles, int vehicle_count);
void DisplayDataPart2(struct Person* persons, int person_count, struct Vehicle* vehicles, int vehicle_count);

// Function prototype for tax calculation
void CalculateTaxes(struct Vehicle* vehicles, int vehicle_count, struct Person* persons, int person_count);


int main() {
  struct Person persons[MAX_PERSONS] = {0};
  struct Vehicle vehicles[MAX_VEHICLES] = {0};
  int person_count, vehicle_count;

  person_count = ReadPersons(persons, MAX_PERSONS, "person.txt");
  if (person_count == -1)
    return 1;
  vehicle_count = ReadVehicles(vehicles, MAX_VEHICLES, "vehicles.txt");
  if (vehicle_count == -1)
    return 1;

  SortPersons(persons, person_count);

  printf("--- Part 1 Output ---\n");
  DisplayDataPart1(persons, person_count, vehicles, vehicle_count);

  CalculateTaxes(vehicles, vehicle_count, persons, person_count);

  printf("\n--- Part 2 Output ---\n");
  DisplayDataPart2(persons, person_count, vehicles, vehicle_count);

  return 0;
}


// Function to read person data from file
int ReadPersons(struct Person* persons, int max_persons, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Failed to open person file");
    return -1; // Indicate error
  }

  int person_count = 0;
  struct Person* current_person = persons;

  while (person_count < max_persons &&
         fscanf(file, "%lld %s %s %lf", &(current_person->person_id),
                current_person->firstname, current_person->lastname,
                &(current_person->income)) == 4) {
    current_person++;
    person_count++;
  }

  fclose(file);
  return person_count;
}

// Function to read vehicle data from file
int ReadVehicles(struct Vehicle* vehicles, int max_vehicles, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Failed to open vehicle file");
    return -1; // Indicate error
  }

  int vehicle_count = 0;
  struct Vehicle* current_vehicle = vehicles;

  while (vehicle_count < max_vehicles &&
         fscanf(file, "%lld %19s %lf", &(current_vehicle->person_id),
                current_vehicle->reg_nr, &(current_vehicle->tax)) == 3) {
    current_vehicle++;
    vehicle_count++;
  }

  fclose(file);
  return vehicle_count;
}

int compareFirstNames(const char* name1, const char* name2) {
  while (*name1 && *name2) {
    int diff = tolower((unsigned char)*name1) - tolower((unsigned char)*name2);
    if (diff != 0) {
      return diff;
    }
    name1++;
    name2++;
  }
  return tolower((unsigned char)*name1) - tolower((unsigned char)*name2);
}

int compare_persons(const void *a, const void *b) {
  struct Person* p1 = (struct Person*)a;
  struct Person* p2 = (struct Person*)b;
  return compareFirstNames(p1->firstname, p2->firstname);
}

void SortPersons(struct Person* persons, int person_count) {
  qsort(persons, person_count, sizeof(struct Person), compare_persons);
}

// Function to display data for Part 1
void DisplayDataPart1(struct Person* persons, int person_count, struct Vehicle* vehicles, int vehicle_count) {
  for (struct Person* current_person = persons;
       current_person < persons + person_count; ++current_person) {
    printf("%lld %s %s (income: %.2f)\n", current_person->person_id,
           current_person->firstname, current_person->lastname,
           current_person->income);

    int vehicle_found = 0;
    for (struct Vehicle* current_vehicle = vehicles;
         current_vehicle < vehicles + vehicle_count; ++current_vehicle) {
      if (current_vehicle->person_id == current_person->person_id) {
        printf("        car %d: %s (tax: %.2f)\n", ++vehicle_found,
               current_vehicle->reg_nr, current_vehicle->tax);
      }
    }
    if (vehicle_found == 0) {
      printf("        *** No registered cars ***\n");
    }
    printf("\n");
  }
}

// Function to calculate taxes for Part 2
void CalculateTaxes(struct Vehicle* vehicles, int vehicle_count, struct Person* persons, int person_count) {
  for (struct Person* current_person = persons;
       current_person < persons + person_count; ++current_person) {
    double total_tax = 0.0;
    for (struct Vehicle* current_vehicle = vehicles;
         current_vehicle < vehicles + vehicle_count; ++current_vehicle) {
      if (current_vehicle->person_id == current_person->person_id) {
        total_tax += current_vehicle->tax;
      }
    }
    current_person->total_tax = total_tax;
    if (current_person->income > 0) {
      current_person->tax_percentage =
          (total_tax / current_person->income) * 100.0;
    } else {
      current_person->tax_percentage = 0.0;
    }
  }
}

// Function to display data for Part 2 with tax calculations
void DisplayDataPart2(struct Person* persons, int person_count, struct Vehicle* vehicles, int vehicle_count) {
  DisplayDataPart1(persons, person_count, vehicles, vehicle_count); // Part 1 output

  printf("\n\n"); // Separator for Part 2 output

  for (struct Person* current_person = persons;
       current_person < persons + person_count; ++current_person) {
    printf("\nName: %s %s\n", current_person->firstname,
           current_person->lastname);
    printf("------------------\n");
    printf("Income: %15.2f EUR\n", current_person->income);
    printf("Tax: %18.2f EUR\n", current_person->total_tax);
    printf("Tax pcnt: %12.2f %%\n", current_person->tax_percentage);

    if (current_person->income == 0.0) {
      printf("ERROR: Missing income\n");
    } else if (current_person->tax_percentage > TAX_WARNING_THRESHOLD) {
      printf("WARNING! Tax > %.0f%%\n", TAX_WARNING_THRESHOLD);
    }
    printf("\n");
  }
}
