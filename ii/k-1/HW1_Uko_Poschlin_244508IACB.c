/**
 * Teema: Stipendiumid
 * Rakenduse eesmärk on määrata tudengitele vastavalt nende hinnetele
 * stipendiumid.
 *
 * Ülesanne
 * Määra tudengitele stipendiumid. Väljastuses esitatakse ainult tudengid,
 * kellele määrati stipendiumid. Loetle kasvavas järjekorras vastavalt
 * stipendiumi summale: Tudengitele, kelle kõik hinded olid '5', määratakse
 * stipendium 200€ Tudengitele, kellel oli kuni kaks '4', määratakse stipendium
 * 100€ Tudengitele, kellel oli kuni neli '4', määratakse stipendium 50€
 * Stipendiumi saavate tudengite väljastamisel peavad tudengid olema järjestatud
 * sisseastumisaasta alusel, mille määravad esimesed kaks numbrit
 * tudengikoodist.
 *
 * Andmefaili väljad
 * Nimi
 * Tudengikood (vastavalt TalTech nimetamisreeglitele 6 numbrit + õppekava kood)
 * Hinded (kokku 6 tk)
 */
#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 256
#define CODE_LENGTH 10
#define GRADES_LENGTH 6
#define GRADES_BUFFER 256

struct Array {
  size_t length;
  void* values;
};
struct IntArray {
  size_t length;
  int* values;
};
struct StudentArray {
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
int compare_students(const void* a, const void* b) {
  int a_ = GetStudentYear((struct Student*)a);
  int b_ = GetStudentYear((struct Student*)b);
  return a_ > b_;
}

int main(int argc, char const* argv[]) {
  struct StudentArray students = ReadStudents(argv[1]);
  // for (int i = 0; i < students.length; ++i) {
  //   PrintStudent(&(students.values[i]));
  //   puts("");
  // }

  qsort(students.values, students.length, sizeof(struct Student),
        compare_students);

  for (int i = 0; i < students.length; ++i) {
    int stip = CalculateStudentStipendium(&(students.values[i]));
    if (stip != -1) {
      PrintStudent(&(students.values[i]));
      printf(" [stip] = %d\n", stip);
    }
  }

  FreeStudentArray(students);
  return 0;
}

struct StudentArray ReadStudents(const char* fileName) {
  FILE* file = fopen(fileName, "r");
  struct StudentArray students = {
      .length = 0, .values = calloc(255, sizeof(struct Student))};
  char buffer[NAME_LENGTH + CODE_LENGTH + GRADES_BUFFER];
  while (fgets(buffer, sizeof(buffer), file)) {
    struct Student* student = &students.values[students.length];
    sscanf(buffer, "%[^,],%[^,],%d,%d,%d,%d,%d,%d", student->name,
           student->studentCode, &student->grades[0], &student->grades[1],
           &student->grades[2], &student->grades[3], &student->grades[4],
           &student->grades[5]);
    students.length++;
  }
  fclose(file);
  return students;
}

void PrintStudent(struct Student* student) {
  printf("%s %s [", student->name, student->studentCode);
  for (int i = 0; i < GRADES_LENGTH; ++i) {
    printf("%d", student->grades[i]);
    if (i + 1 < GRADES_LENGTH)
      printf(", ");
  }
  printf("]");
}

void FreeStudentArray(struct StudentArray students) {
  // for (; students.length > 0; --students.length) {
  //   free(students.values[students.length].name);
  // }
  free(students.values);
}

int GetStudentYear(struct Student* student) {
  return (student->studentCode[0] - '0') * 10 + (student->studentCode[1] - '0');
}

int CalculateStudentStipendium(struct Student* student) {
  int count5 = 0;
  int count4 = 0;
  for (int i = 0; i < GRADES_LENGTH; ++i) {
    if (student->grades[i] == 5) {
      ++count5;
      continue;
    }
    if (student->grades[i] == 4) {
      ++count4;
      continue;
    }
  }
  if (count5 + count4 != GRADES_LENGTH)
    return -1;
  if (count4 == 0)
    return 200;
  if (count4 <= 2)
    return 100;
  if (count4 <= 4)
    return 50;
  return -1;
}