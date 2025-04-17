#include <stdio.h>
#include <stdlib.h>

#include "../lib/read_line.h"
#include "../src/student.h"

void PrintMvps(People*, FILE*);

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  // FILE* outFile = fopen("out", "w");
  // if (outFile == NULL) {
  //   perror("out");
  //   return 1;
  // }
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror(argv[1]);
    return 1;
  }

  char* line;

  People people = {0};

  while ((line = readline(fp)) != NULL) {
    // printf("%s\n", line);

    Person person = {0};
    if (sscanf(line, "%lu %ms %ms %5s %f", &person.index, &person.lastName,
               &person.firstName, person.curriculum, &person.points) == 5) {
      AddPerson(&people, &person);
    }

    free(line);
  }
  // printf("\n=====hello=====\n");

  PrintPeople("%lu %s %s %s %.1f\n", stdout, &people);
  puts("");

  // Stipendiumi saavad: Igast järgnevast erialast kuni 7 kõige kõrgema
  // punktisummaga tudengit: IACB, EARB ja MVEB. Kuva stipendiumi saajate
  // nimekiri ning näita mitu tudengit igalt erialalt stipendiumi sai.

  PrintMvps(&people, stdout);

  PutPeopleToWork(&people);

  fclose(fp);
  // fclose(outFile);
}

void PrintMvps(People* people, FILE* file) {
  People IACBcandidates = {0};
  People EARBcandidates = {0};
  People MVEBcandidates = {0};
  for (size_t i = 0; i < people->count; i++) {
    Person* p = GetPerson(people, i);
    if (p != NULL) {
      Person copy_p = {0};
      copy_p.index = p->index;
      copy_p.lastName = strdup(p->lastName);
      copy_p.firstName = strdup(p->firstName);
      strncpy(copy_p.curriculum, p->curriculum, 5);
      copy_p.curriculum[5] = '\0';
      copy_p.points = p->points;

      if (strcmp(copy_p.curriculum, "IACB") == 0 && IACBcandidates.count < 7) {
        AddPerson(&IACBcandidates, &copy_p);

      } else if (strcmp(copy_p.curriculum, "EARB") == 0 &&
                 EARBcandidates.count < 7) {
        AddPerson(&EARBcandidates, &copy_p);

      } else if (strcmp(copy_p.curriculum, "MVEB") == 0 &&
                 MVEBcandidates.count < 7) {
        AddPerson(&MVEBcandidates, &copy_p);

      } else {
        free(copy_p.lastName);
        free(copy_p.firstName);
      }
    }
  }
  SortPeoplePoints(&IACBcandidates);
  SortPeoplePoints(&EARBcandidates);
  SortPeoplePoints(&MVEBcandidates);
  fprintf(file, "\nIACB stipendiumi saajate nimekiri:\n");
  PrintPeople("%lu %s %s %s %.1f\n", file, &IACBcandidates);
  fprintf(file, "IACB stipendiumi saajate arv: %zu\n", IACBcandidates.count);
  fprintf(file, "\nEARB stipendiumi saajate nimekiri:\n");
  PrintPeople("%lu %s %s %s %.1f\n", file, &EARBcandidates);
  fprintf(file, "EARB stipendiumi saajate arv: %zu\n", EARBcandidates.count);
  fprintf(file, "\nMVEB stipendiumi saajate nimekiri:\n");
  PrintPeople("%lu %s %s %s %.1f\n", file, &MVEBcandidates);
  fprintf(file, "MVEB stipendiumi saajate arv: %zu\n", MVEBcandidates.count);

  PutPeopleToWork(&IACBcandidates);
  PutPeopleToWork(&EARBcandidates);
  PutPeopleToWork(&MVEBcandidates);
}