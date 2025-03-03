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
#define CONFIG_FILE "config.ini"

#define DEFAULT_OUTPUT_FILE "HW1_Uko_Poschlin_244508IACB_sisend.txt"
#define DEFAULT_INPUT_FILE argv[1]

#define TRUE 1

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 256
#define CODE_LENGTH 10
#define GRADES_LENGTH 6

#define MAX_PERSONS_COUNT 256
#define LINE_BUFFER_SIZE 256
#define CONFIG_HANDLERS_LENGTH 4
#define REALLOCATE_CONSTANT 2

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

typedef struct {
  char* input_file;
  char* output_file;
  uint8_t console_output;
  uint8_t file_output;
} CustomFlags;

typedef struct {
  CustomFlags flags;

  FILE* out_file;

  void (*handlers[CONFIG_HANDLERS_LENGTH])(CustomFlags*, const char*);
} ConfigState;

struct StudentArray ReadStudents(const char*);
void PrintStudent(struct Student*, ConfigState*);
int CalculateStudentStipendium(struct Student*);
int GetStudentYear(struct Student*);
void FreeStudentArray(struct StudentArray);
void PrintAllStudentsStipendiums(struct StudentArray*, ConfigState*);
int gt(const void* a, const void* b) {
  int a_ = GetStudentYear((struct Student*)a);
  int b_ = GetStudentYear((struct Student*)b);
  return a_ > b_;
};

ConfigState UseConfig(const char*, int, char* const*);
