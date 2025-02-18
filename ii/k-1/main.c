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
  char* name;
  char studentCode[CODE_LENGTH];
  int grades[GRADES_LENGTH];
};

struct StudentArray* ReadData(const char* fileName);
void PrintStudent(struct Student* student);

int main(int argc, char const* argv[]) {
  struct StudentArray* students = ReadData(argv[1]);
  for (int i = 0; i < students->length; ++i) {
    PrintStudent(&(struct Student)students->values[i]);
  }
  free(students->values);
  return 0;
}

struct StudentArray* ReadData(const char* fileName) {
  FILE* file = fopen(fileName, "r");
  struct StudentArray students = {
      .length = 0, .values = {0}};
  struct Student student;
  char* grades_buffer = calloc(GRADES_BUFFER, sizeof(char));
  int grade = -1;
  while (fscanf(file, "%s,%s,%s;", student.name, student.studentCode,
                grades_buffer) == 3) {
    for (int grades =
             sscanf(grades_buffer, "%d %d %d %d %d %d", &student.grades[0],
                    &student.grades[1], &student.grades[2], &student.grades[3],
                    &student.grades[4], &student.grades[5]);
         grades < GRADES_LENGTH; ++grades) {
      student.grades[grades] = -1;
    }
    PrintStudent(&student);
    students.values[++students.length] = student;
  }
  free(grades_buffer);
  fclose(file);
  return &students;
}

void PrintStudent(struct Student* student) {
  printf("%s %s [", student->name, student->studentCode);
  for (int i = 0; i < GRADES_LENGTH; ++i) {
    printf("%d, ", student->grades[i]);
  }
  puts("");
}