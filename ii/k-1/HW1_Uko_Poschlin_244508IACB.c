#include "HW1_Uko_Poschlin_244508IACB.h"

int main(int argc, char* const* argv) {
  ConfigState config = UseConfig(CONFIG_FILE, argc, argv);

  StudentArray students = ReadStudents(config.flags.input_file);

  qsort(students.values, students.length, sizeof(Student), gt);

  if (config.flags.file_output) {
    config.out_file = fopen(config.flags.output_file, "w");
    if (config.out_file == NULL) {
      fprintf(stderr, "Error opening output file.\n");
      FreeStudentArray(students);
      exit(EXIT_FAILURE);
    }
  }

  PrintAllStudentsStipendiums(&students, &config);

  if (config.flags.file_output)
    fclose(config.out_file);

  FreeStudentArray(students);
  return 0;
}

/// @brief For given configuration, functions like printf
/// @param config config has the flags and the out file to print to depending on
/// config
void MyPrint(ConfigState* config, const char* __restrict__ __format, ...) {
  va_list args;

  if (config->flags.file_output) {
    va_start(args, __format);
    vfprintf(config->out_file, __format, args);
    va_end(args);
  }

  if (config->flags.console_output) {
    va_start(args, __format);
    vfprintf(stdout, __format, args);
    va_end(args);
  }
}

/// @brief Sets the configuration for input_file
/// @param config_state state of program
/// @param str line from "config.ini" file
void _HandleInputFileFlag(CustomFlags* config_state, const char* str) {
  const char* flag_name = "input_file";
  if (strstr(str, flag_name) == NULL)
    return;
  if (sscanf(str, "input_file %s", config_state->input_file) != 1) {
    config_state->input_file = "HW1_Uko_Poschlin_244508IACB_sisend.txt";
  }
};
/// @brief Sets the configuration for output_file
/// @param config_state state of program
/// @param str line from "config.ini" file
void _HandleOutputFileFlag(CustomFlags* config_state, const char* str) {
  const char* flag_name = "output_file";
  if (strstr(str, flag_name) == NULL)
    return;
  if (sscanf(str, "output_file %s", config_state->output_file) != 1) {
    config_state->output_file = "HW1_Uko_Poschlin_244508IACB_valjund.txt";
  }
};
/// @brief Sets the configuration for console_output
/// @param config_state state of program
/// @param str line from "config.ini" file
void _HandleConsoleOutputFlag(CustomFlags* config_state, const char* str) {
  const char* flag_name = "console_output";
  if (strstr(str, flag_name) == NULL)
    return;
  if (sscanf(str, "console_output %hhd", &config_state->console_output) != 1) {
    config_state->console_output = TRUE;
  }
};
/// @brief Sets the configuration for file_output
/// @param config_state state of program
/// @param str line from "config.ini" file
void _HandleFileOutputFlag(CustomFlags* config_state, const char* str) {
  const char* flag_name = "file_output";
  if (strstr(str, flag_name) == NULL)
    return;
  if (sscanf(str, "file_output %hhd", &config_state->file_output) != 1) {
    config_state->file_output = TRUE;
  }
};

/// @brief (this function can exit)
/// @param config_file_name "config.ini"
/// @return State of program
ConfigState UseConfig(const char* config_file_name, int argc,
                      char* const* argv) {
  ConfigState config = {0};
  if (argc >= 2) {
    config.flags.console_output = TRUE;
    config.flags.file_output = TRUE;
    config.flags.input_file = DEFAULT_INPUT_FILE;
    config.flags.output_file = DEFAULT_OUTPUT_FILE;
    return config;
  }
  FILE* configFile = fopen(config_file_name, "r");
  if (configFile == NULL) { // default files
    config.flags.input_file = "HW1_Uko_Poschlin_244508IACB_sisend.txt";
    config.flags.output_file = "HW1_Uko_Poschlin_244508IACB_valjund.txt";
    FILE* _configFile = fopen(config_file_name, "w");
    fprintf(_configFile, "input_file %s\n", config.flags.input_file);
    fprintf(_configFile, "output_file %s\n", config.flags.output_file);
    fprintf(_configFile, "console_output %d\n", config.flags.console_output);
    fprintf(_configFile, "file_output %d\n", config.flags.file_output);
    fclose(_configFile);
    return config;
  }

  void (*handlers[CONFIG_HANDLERS_LENGTH])(CustomFlags*, const char*);

  handlers[0] = _HandleInputFileFlag;
  handlers[1] = _HandleOutputFileFlag;
  handlers[2] = _HandleConsoleOutputFlag;
  handlers[3] = _HandleFileOutputFlag;

  int handlers_length = CONFIG_HANDLERS_LENGTH;

  size_t line_buffer_size = LINE_BUFFER_SIZE;
  char* line = calloc(line_buffer_size, sizeof(char));
  if (line == NULL) {
    fprintf(stderr, "Failed to allocate config line buffer");
    exit(EXIT_FAILURE);
  }

  while (1) {
    if (fgets(line, line_buffer_size, configFile) == NULL) {
      break;
    }
    while (strchr(line, '\n') == NULL && !feof(configFile)) {
      line_buffer_size *= REALLOCATE_CONSTANT;
      char* new_buffer = realloc(line, line_buffer_size);
      if (!new_buffer) {
        fprintf(stderr, "Failed to reallocate buffer");
        fclose(configFile);
        free(line);
        exit(EXIT_FAILURE);
      }
      line = new_buffer;
      fgets(line + strlen(line), line_buffer_size - strlen(line), configFile);
    }
    for (int i = 0; i < handlers_length; ++i) {
      if (line[0] == ';')
        continue;
      (handlers[i])(&config.flags, line);
    }
  }

  free(line);
  fclose(configFile);

  return config;
}

/// @brief Reads all the students in the input file (this function can exit)
/// @param fileName the file path to read from
/// @return array of students
StudentArray ReadStudents(const char* fileName) {
  FILE* file = fopen(fileName, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening input file.\n");
    exit(EXIT_FAILURE);
  }
  StudentArray students;
  students.capacity = MAX_PERSONS_COUNT;
  students.length = 0;
  students.values = calloc(students.capacity, sizeof(Student));
  if (!students.values) {
    fprintf(stderr, "Couldn't allocate memory (students)\n");
    exit(EXIT_FAILURE);
  }

  size_t buffer_size = LINE_BUFFER_SIZE;
  char* buffer = calloc(buffer_size, sizeof(char));
  if (!buffer) {
    fprintf(stderr, "Failed to allocate buffer");
    exit(EXIT_FAILURE);
  }
  while (1) {
    if (fgets(buffer, buffer_size, file) == NULL)
      break;

    while (strchr(buffer, '\n') == NULL && !feof(file)) {
      buffer_size *= REALLOCATE_CONSTANT;
      char* new_buffer = realloc(buffer, buffer_size);
      if (!new_buffer) {
        fprintf(stderr, "Failed to reallocate buffer");
        fclose(file);
        free(buffer);
        free(students.values);
        exit(EXIT_FAILURE);
      }
      buffer = new_buffer;
      fgets(buffer + strlen(buffer), buffer_size - strlen(buffer), file);
    }

    if (students.length >= students.capacity) {
      students.capacity *= REALLOCATE_CONSTANT;
      Student* new_values =
          realloc(students.values, students.capacity * sizeof(Student));
      if (!new_values) {
        fprintf(stderr, "Failed to reallocate students array");
        fclose(file);
        free(buffer);
        free(students.values);
        exit(EXIT_FAILURE);
      }
      students.values = new_values;
    }

    Student* student = &students.values[students.length];
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

/// @brief Prints the student name, code and grades
/// @param student
/// @param config state of program
void PrintStudent(Student* student, ConfigState* config) {
  MyPrint(config, "%s %s [", student->name, student->studentCode);
  for (int i = 0; i < GRADES_LENGTH; ++i) {
    MyPrint(config, "%d", student->grades[i]);
    if (i + 1 < GRADES_LENGTH) {
      MyPrint(config, ", ");
    }
  }
  MyPrint(config, "]");
}

void FreeStudentArray(StudentArray students) {
  // for (; students.length > 0; --students.length) {
  //   free(students.values[students.length].name);
  // }
  free(students.values);
}

/// @brief gets the year part from the student code
/// @param student
/// @return years last 2 digits
int GetStudentYear(Student* student) {
  return (student->studentCode[0] - '0') * 10 + (student->studentCode[1] - '0');
}

/// @brief counts the number of 4s and 5s and based on rules grants stipendium
/// (-1 if no stipendium)
/// @param student
/// @return stipendium amount
int CalculateStudentStipendium(Student* student) {
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

/// @brief
/// @param students
/// @param config
void PrintAllStudentsStipendiums(StudentArray* students, ConfigState* config) {
  for (int i = 0; i < students->length; ++i) {
    int stip = CalculateStudentStipendium(&(students->values[i]));
    if (stip != -1) {
      PrintStudent(&(students->values[i]), config);
      MyPrint(config, " [stip] = %d\n", stip);
    }
  }
}
