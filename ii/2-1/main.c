#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum file name length in modern systems
#define MAX_FILE_LEN 256

// TODO: Define the number of categories for array declaration
enum CATEGORY {
  Archive,
  Data,
  Document,
  Code,
  Text,
  Image,
  Other,
  None,
  COUNT,
};

// TODO: Add enum declaration

enum CATEGORY GetFileType(char* extension);
void FixTrailingNewline(char* str);
char* GetExtension(char* str);
void PrintOut(int arr[COUNT]);

int main(void) {
  // Stores the name of the file
  char name[MAX_FILE_LEN];

  // TODO: Declare the array to hold the a counter for each file category
  int categories[COUNT] = {0};

  // Read in the name of a file with the extension until EOF occurs
  while (fgets(name, MAX_FILE_LEN, stdin) != NULL) {
    // TODO: Call a function to fix the trailing newline
    FixTrailingNewline(name);
    // TODO: Call a function to find the position of the last point
    // Hint: think of what no point symbol in the string means!

    // TODO: Call a function that returns the category type and store it.
    // This is the predefined function from the requirements!

    // TODO: Increase the appropriate category counter value

    categories[GetFileType(GetExtension(name))]++;
  }

  // TODO: Call a function to print the results
  PrintOut(categories);

  return EXIT_SUCCESS;
}

int in(const char** arr, int len, char* target) {
  int i;
  for (i = 0; i < len; i++) {
    if (strncmp(arr[i], target, strlen(target)) == 0) {
      return 1;
    }
  }
  return 0;
}

enum CATEGORY GetFileType(char* extension) {
  if (strcmp(extension, "txt")) {
    return Text;
  }
  if (in((const char**){"csv", "xls", "xlsx", "ods"}, 4, extension)) {
    return Data;
  }
  if (in((const char**){"zip", "rar", "7z", "tar", "gz"}, 5, extension)) {
    return Archive;
  }
  if (in((const char**){"pdf", "doc", "docx", "rtf", "odt"}, 5, extension)) {
    return Document;
  }
  if (in((const char**){"c", "h", "cpp", "hpp", "py"}, 5, extension)) {
    return Code;
  }
  if (in((const char**){"jpg", "jpeg", "png", "svg"}, 4, extension)) {
    return Image;
  }
  if (strlen(extension) > 0) {
    return Other;
  }
  return None;
}

// Function to fix the trailing newline
void FixTrailingNewline(char* str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

// Function to get the substring after the last point
char* GetExtension(char* str) {
  char* last_point = strrchr(str, '.');
  if (last_point != NULL) {
    return last_point + 1;
  }
  return NULL; // Return NULL if no point is found
}

const char* GetCategoryAsString(enum CATEGORY n) {
  switch (n) {
  case Archive:
    return (const char*)"Archives";
  case Data:
    return (const char*)"Data";
  case Document:
    return (const char*)"Document";
  case Code:
    return (const char*)"Code";
  case Text:
    return (const char*)"Text";
  case Image:
    return (const char*)"Image";
  case Other:
    return (const char*)"Other";
  case None:
  default:
    return (const char*)"No extension";
  }
}

void PrintOut(int arr[COUNT]) {
  printf("\n");
  for (size_t i = 0; i < COUNT; ++i) {
    printf("%12s %9d\n", GetCategoryAsString(i), arr[i]);
  }
  printf("\n");
}
