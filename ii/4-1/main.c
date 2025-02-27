#include "main.h"

int main(void) {
  int person_count, vehicle_count;
  Person persons[MAX_PERSONS];
  Vehicle vehicles[MAX_VEHICLES];
  person_count = ReadPersons(PERSON_FILE, persons);
  vehicle_count = ReadVehicles(VEHICLE_FILE, vehicles);
  if (person_count == -1) {
    fprintf(stderr, "Error reading %s (skill issue)\n", PERSON_FILE);
    return 1;
  }
  if (vehicle_count == -1) {
    fprintf(stderr, "Error reading %s (skill issue)\n", VEHICLE_FILE);
    return 1;
  }

  Part1(persons, person_count, vehicles, vehicle_count);
  Part2(persons, person_count, vehicles, vehicle_count);

  return 0;
}

int compare_names(const void* a, const void* b) {
  return ((Person*)a)->name.first > ((Person*)b)->name.first;
}

int ReadPersons(const char* file_name, Person persons[MAX_PERSONS]) {
  FILE* src = fopen(file_name, "r");
  if (src == NULL) {
    return -1;
  }

  int count = 0;
  char lineBuffer[LINE_LENGTH] = {0};

  while (fgets(lineBuffer, LINE_LENGTH, src)) {
    if (count >= MAX_PERSONS) {
      fprintf(stderr, "Error: Too many persons in file %s (max %d allowed)\n",
              file_name, MAX_PERSONS);
      break;
    }
    if (sscanf(lineBuffer, "%lu %s %s %lf", &(persons + count)->id,
               (persons + count)->name.first, (persons + count)->name.last,
               &(persons + count)->annual_income) == 4) {
      ++count;
    } else {
      fprintf(stderr, "Error reading line (Person) %d\n", count);
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
  char lineBuffer[LINE_LENGTH] = {0};

  while (fgets(lineBuffer, LINE_LENGTH, src)) {
    if (count >= MAX_VEHICLES) {
      fprintf(stderr, "Error: Too many vehicles in file %s (max %d allowed)\n",
              file_name, MAX_VEHICLES);
      break;
    }
    if (sscanf(lineBuffer, "%lu %s %lf", &(dest + count)->person_id,
               (dest + count)->reg_num, &(dest + count)->annual_tax) == 3) {
      ++count;
    } else {
      fprintf(stderr, "Error reading line (Vehicle) %d\n", count);
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

double _sum_taxes(Id id, Vehicle* vehicles, int vehicle_count) {
  double sum = 0.0;
  for (int i = 0; i < vehicle_count; ++i) {
    if ((vehicles + i)->person_id == id) {
      sum += (vehicles + i)->annual_tax;
    }
  }
  return sum;
}

double _calc_tax_pcnt(double annual_income, double tax_sum) {
  if (annual_income == 0)
    return 0;

  return tax_sum / annual_income * 100;
}

void Part2(Person* persons, int person_count, Vehicle* vehicles, int vehicle_count) {
  puts("Part 1");
  for (int i = 0; i < person_count; ++i) {
    Person person = *(persons + i);
    char missingIncome = person.annual_income == 0;
    printf("Name: %s %s\nIncome: %12.2lf EUR\n", person.name.first,
           person.name.last, person.annual_income);
    double sum = _sum_taxes(person.id, vehicles, vehicle_count);

    double taxPcnt = _calc_tax_pcnt(person.annual_income, sum);
    printf("Tax: %15.2lf EUR\nTax pcnt: %10.2lf %%\n", sum, taxPcnt);
    if (taxPcnt > 10) {
      fprintf(stderr, "WARNING! Tax > 10%%");
    }
    if (missingIncome) {
      fprintf(stderr, "ERROR: Missing income");
    }
    puts("\n");
  }
}

void _print_persons_vehicles(Id id, Vehicle* vehicles, int vehicle_count) {
  int j = 0, cnt = 0;
  for (; j < vehicle_count; ++j) {
    if ((vehicles + j)->person_id == id) {
      printf("\tcar %d:  ", ++cnt);
      PrintVehicle(vehicles + j);
      puts("");
    }
  }
  if (cnt == 0) {
    puts("\t***No registered cars***\n");
  }
}

void Part1(Person* persons, int person_count, Vehicle* vehicles, int vehicle_count) {
  puts("Part 2");
  for (int i = 0; i < person_count; ++i) {
    PrintPerson(persons + i);
    puts("");
    _print_persons_vehicles((persons + i)->id, vehicles, vehicle_count);
  }
}