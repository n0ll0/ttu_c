#include "HW1_Uko_Poschlin_244508IACB.h"

int main(int argc, char const* argv[]) {

  if (argc < 2) {
    fprintf(stderr, "ERROR! Missing argument at position 1 ($file_name)!\n");
    return EXIT_FAILURE;
  }

  struct StudentArray students = ReadStudents(argv[1]);

  qsort(students.values, students.length, sizeof(struct Student), gt);

  FILE* out = fopen(OUTPUT_FILE, "w");

  PrintAllStudentsStipendiums(&students, out);

  fclose(out);

  FreeStudentArray(students);
  return 0;
}

/* this function can exit */
struct StudentArray ReadStudents(const char* fileName) {
  FILE* file = fopen(fileName, "r");
  struct StudentArray students;
  students.capacity = MAX_PERSONS_COUNT;
  students.length = 0;
  students.values = calloc(students.capacity, sizeof(struct Student));
  if (!students.values) {
    fprintf(stderr, "Couldn't allocate memory (students)\n");
    exit(EXIT_FAILURE);
  }

  size_t buffer_size = LINE_BUFFER_SIZE;
  char* buffer = calloc(buffer_size, sizeof(char));
  if (!buffer) {
    perror("Failed to allocate buffer");
    exit(EXIT_FAILURE);
  }
  while (1) {
    if (fgets(buffer, buffer_size, file) == NULL)
      break;

    while (strchr(buffer, '\n') == NULL && !feof(file)) {
      buffer_size *= 2;
      char* new_buffer = realloc(buffer, buffer_size);
      if (!new_buffer) {
        perror("Failed to reallocate buffer");
        fclose(file);
        free(buffer);
        free(students.values);
        exit(EXIT_FAILURE);
      }
      buffer = new_buffer;
      fgets(buffer + strlen(buffer), buffer_size - strlen(buffer), file);
    }

    if (students.length >= students.capacity) {
      students.capacity *= 2;
      struct Student* new_values =
          realloc(students.values, students.capacity * sizeof(struct Student));
      if (!new_values) {
        perror("Failed to reallocate students array");
        fclose(file);
        free(buffer);
        free(students.values);
        exit(EXIT_FAILURE);
      }
      students.values = new_values;
    }

    struct Student* student = &students.values[students.length];
    sscanf(buffer, "%[^,],%[^,],%d,%d,%d,%d,%d,%d", student->name,
           student->studentCode, &student->grades[0], &student->grades[1],
           &student->grades[2], &student->grades[3], &student->grades[4],
           &student->grades[5]);
    students.length++;
  }

  free(buffer);
  fclose(file);
  return students;
}

void PrintStudent(struct Student* student, FILE* out) {
  fprintf(stdout, "%s %s [", student->name, student->studentCode);
  fprintf(out, "%s %s [", student->name, student->studentCode);
  for (int i = 0; i < GRADES_LENGTH; ++i) {
    fprintf(stdout, "%d", student->grades[i]);
    fprintf(out, "%d", student->grades[i]);
    if (i + 1 < GRADES_LENGTH) {
      fprintf(stdout, ", ");
      fprintf(out, ", ");
    }
  }
  fprintf(stdout, "]");
  fprintf(out, "]");
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

void PrintAllStudentsStipendiums(struct StudentArray* students, FILE* out) {
  for (int i = 0; i < students->length; ++i) {
    int stip = CalculateStudentStipendium(&(students->values[i]));
    if (stip != -1) {
      PrintStudent(&(students->values[i]), out);
      fprintf(stdout, " [stip] = %d\n", stip);
      fprintf(out, " [stip] = %d\n", stip);
    }
  }
}