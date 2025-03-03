#pragma once
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
#define OUTPUT_FILE "out.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 256
#define CODE_LENGTH 10
#define GRADES_LENGTH 6

#define MAX_PERSONS_COUNT 256
#define LINE_BUFFER_SIZE 256

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
void PrintStudent(struct Student* student, FILE* out);
int CalculateStudentStipendium(struct Student* student);
int GetStudentYear(struct Student* student);
void FreeStudentArray(struct StudentArray students);
void PrintAllStudentsStipendiums(struct StudentArray* students, FILE* out);
int gt(const void* a, const void* b) {
  int a_ = GetStudentYear((struct Student*)a);
  int b_ = GetStudentYear((struct Student*)b);
  return a_ > b_;
}
