#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_PERSONS 255
#define MAX_VEHICLES 255
#define TAX_WARNING_THRESHOLD 10.0

struct Person {
  char person_id[50];
  char firstname[50];
  char lastname[50];
  char city[50];
};

void PrintPerson(struct Person person);
int ReadPersons(struct Person* persons, int max_persons, const char* filename);
int findAllPersons(struct Person* persons, int person_count, int* results,
                   const char* search);
void SortPersons(struct Person* persons, int person_count);
int GetAllCities(struct Person* persons, int person_count, char** cities);

int main() {
  struct Person persons[MAX_PERSONS] = {0};
  char* cities[MAX_PERSONS] = {0};

  int person_count = ReadPersons(persons, MAX_PERSONS, "03_data_short.txt");
  if (person_count == -1)
    return 1;
  int city_count = GetAllCities(persons, person_count, cities);
  SortPersons(persons, person_count);
  for (int i = 0; i < person_count; ++i) {
    PrintPerson(persons[i]);
  }
  char search[50];
  int results[MAX_PERSONS];
  while (fscanf(stdin, "%49s", search) == 1) {
    search[strlen(search)] = '\0';
    if (strcmp(search, ":q") == 0 || strcmp(search, ":wq") == 0 ||
        strcmp(search, ":x") == 0) {
      break;
    }
    if (strcmp(search, ":?") == 0) {
      for (int i = 0; i < city_count; ++i) {
        printf("%s\n", cities[i]);
      }
      continue;
    }
    int result_count = findAllPersons(persons, person_count, results, search);

    if (result_count <= 0) {
      puts("no results");
      continue;
    }
    for (int i = 0; i < result_count; ++i) {
      PrintPerson(persons[results[i]]);
    }
  }

  return 0;
}

int ReadPersons(struct Person* persons, int max_persons, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Failed to open person file");
    return -1; // Indicate error
  }

  int person_count = 0;
  struct Person* current_person = persons;

  while (person_count < max_persons &&
         fscanf(file, "%s %s %s %s", current_person->person_id,
                current_person->firstname, current_person->lastname,
                &(current_person->city)) == 4) {
    current_person++;
    person_count++;
  }

  fclose(file);
  return person_count;
}

void extractBirthdate(const char *idCode) {
  if (strlen(idCode) != 11) {
    printf("Invalid ID code length.  Must be 11 digits.\n");
    return;
  }

  int genderDigit = idCode[0] - '0';
  int yearDigits = atoi(strncpy(malloc(3), idCode + 1, 2));
  int month = atoi(strncpy(malloc(3), idCode + 3, 2));
  int day = atoi(strncpy(malloc(3), idCode + 5, 2));

  int year;
  if (genderDigit == 1 || genderDigit == 2) {
    year = 1800 + yearDigits;
  } else if (genderDigit == 3 || genderDigit == 4) {
    year = 1900 + yearDigits;
  } else if (genderDigit == 5 || genderDigit == 6) {
    year = 2000 + yearDigits;
  } else {
    printf("Invalid gender digit.\n");
    return;
  }

  printf("Birthdate: %02d.%02d.%04d\n", day, month, year);
}
void PrintPerson(struct Person person) {
  printf("%s, %s\nCity: %s\n", person.lastname, person.firstname, person.city);
  extractBirthdate(person.person_id);
}


int compare_strings(const char* a, const char* b) {
  char* lower_a = strdup(a);
  char* lower_b = strdup(b);
  for (char* p = lower_a; *p; ++p) *p = tolower(*p);
  for (char* p = lower_b; *p; ++p) *p = tolower(*p);

  int result = strstr(lower_a, lower_b) != NULL;

  free(lower_a);
  free(lower_b);
  return result;
}
  
int findAllPersons(struct Person* persons, int person_count, int* results,
                   const char* search) {
  int results_count = 0;
  for (int i = 0; i < person_count; ++i) {
    if (compare_strings(persons[i].city, search)) {
      results[results_count++] = i;
    }
  }
  return results_count;
}

int compare_persons(const void* a, const void* b) {
  struct Person* p1 = (struct Person*)a;
  struct Person* p2 = (struct Person*)b;
  return strcmp(p1->lastname, p2->lastname);
}

void SortPersons(struct Person* persons, int person_count) {
  qsort(persons, person_count, sizeof(struct Person), compare_persons);
}

int GetAllCities(struct Person* persons, int person_count, char** cities) {
  if (person_count < 1)
    return 0;
  cities[0] = persons[0].city;
  int city_count = 1;

  for (int i = 1; i < person_count; ++i) {
    int found = 0;
    for (int j = 0; j < city_count; ++j) {
      if (strcmp(cities[j], persons[i].city) == 0) {
        found = 1;
        break;
      }
    }
    if (!found) {
      cities[city_count++] = strdup(persons[i].city);
    }
  }

  qsort(cities, city_count, sizeof(char*), strcmp);

  return city_count;
}