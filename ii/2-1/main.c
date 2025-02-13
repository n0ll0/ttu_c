#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum file name length in modern systems
#define MAX_FILE_LEN 256
#define TYPES_PER_CATEGORY 8

// TODO: Add enum declaration
// TODO: Define the number of categories for array declaration
enum CATEGORY {
  CATEGORY_Archive,
  CATEGORY_Data,
  CATEGORY_Document,
  CATEGORY_Code,
  CATEGORY_Text,
  CATEGORY_Image,
  CATEGORY_Other,
  CATEGORY_None,
  CATEGORY_COUNT,
};

struct category_type {
  size_t len;
  const char* name;
  const char** arr;
};

const char* text_ext[] = {"txt"};
const char* data_ext[] = {"csv", "xls", "xlsx", "ods", "json"};
const char* archive_ext[] = {"zip", "rar", "7z", "tar", "gz"};
const char* document_ext[] = {"pdf", "doc", "docx", "rtf", "odt"};
const char* code_ext[] = {"c", "h", "cpp", "hpp", "py", "js"};
const char* image_ext[] = {"jpg", "jpeg", "png", "svg"};

struct category_type CATEGORIES[CATEGORY_COUNT] = {
  [CATEGORY_Text]       = (struct category_type){.name = "Archives", .len = 1, .arr = text_ext},
  [CATEGORY_Data]       = (struct category_type){.name = "Data", .len = 5, .arr = data_ext},
  [CATEGORY_Archive]    = (struct category_type){.name = "Document", .len = 5, .arr = archive_ext},
  [CATEGORY_Document]   = (struct category_type){.name = "Code", .len = 5, .arr = document_ext},
  [CATEGORY_Code]       = (struct category_type){.name = "Text", .len = 6, .arr = code_ext},
  [CATEGORY_Image]      = (struct category_type){.name = "Image", .len = 4, .arr = image_ext},
  [CATEGORY_Other]      = (struct category_type){.name = "Other", .len = 0, .arr = NULL},
  [CATEGORY_None]       = (struct category_type){.name = "No extension", .len = 0, .arr = NULL}
};

enum CATEGORY GetFileType(char* extension);
void FixTrailingNewline(char* str);
char* GetExtension(char* str);
void PrintOut(int arr[CATEGORY_COUNT]);
const char* GetCategoryAsString(enum CATEGORY category);

int main(void) {
  char name[MAX_FILE_LEN];

  int categories[CATEGORY_COUNT] = {0};

  while (fgets(name, MAX_FILE_LEN, stdin) != NULL) {
    FixTrailingNewline(name);
    ++categories[GetFileType(GetExtension(name))];
    // char *ext = GetExtension(name);
    // enum CATEGORY category = GetFileType(ext);
    // ++categories[category];
  }

  PrintOut(categories);

  return EXIT_SUCCESS;
}

int ArrayIncludes(struct category_type arr, char* target) {
  if (arr.len <= 0) return 0;
  for (int i = 0; i < arr.len; i++) {
    if (strcmp(arr.arr[i], target) == 0) {
      return 1;
    }
  }
  return 0;
}

enum CATEGORY GetFileType(char* extension) {
  for (int category = 0; category < CATEGORY_COUNT; category++) {
    // printf("%s %s\n", extension, GetCategoryAsString((enum CATEGORY)category));
    if (category == CATEGORY_None) return category;
    if (category == CATEGORY_Other && strlen(extension)>1) return category;
    if (ArrayIncludes(CATEGORIES[category], extension)==1) {
      printf("%d\n",category);
      return (enum CATEGORY)category;
    }
  }
  return CATEGORY_None;

  // if (strcmp(extension, "txt")==0) {
  //   return CATEGORY_Text;
  // }
  // if (ArrayIncludes((const char*[4]){"csv", "xls", "xlsx", "ods"}, 4, extension)==0) {
  //   return CATEGORY_Data;
  // }
  // if (ArrayIncludes((const char*[5]){"zip", "rar", "7z", "tar", "gz"}, 5, extension)==0) {
  //   return CATEGORY_Archive;
  // }
  // if (ArrayIncludes((const char*[5]){"pdf", "doc", "docx", "rtf", "odt"}, 5, extension)==0) {
  //   return CATEGORY_Document;
  // }
  // if (ArrayIncludes((const char*[5]){"c", "h", "cpp", "hpp", "py"}, 5, extension)==0) {
  //   return CATEGORY_Code;
  // }
  // if (ArrayIncludes((const char*[4]){"jpg", "jpeg", "png", "svg"}, 4, extension)==0) {
  //   return CATEGORY_Image;
  // }
  // if (strlen(extension) > 0) {
  //   return CATEGORY_Other;
  // }
  // return CATEGORY_None;
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
  return "?"; // Return NULL if no point is found
}

const char* GetCategoryAsString(enum CATEGORY category) {
  return CATEGORIES[category].name;
  // switch (category) {
  // case CATEGORY_Archive:
  //   return (const char*)"Archives";
  // case CATEGORY_Data:
  //   return (const char*)"Data";
  // case CATEGORY_Document:
  //   return (const char*)"Document";
  // case CATEGORY_Code:
  //   return (const char*)"Code";
  // case CATEGORY_Text:
  //   return (const char*)"Text";
  // case CATEGORY_Image:
  //   return (const char*)"Image";
  // case CATEGORY_Other:
  //   return (const char*)"Other";
  // case CATEGORY_None:
  // default:
  //   return (const char*)"No extension";
  // }
}

void PrintOut(int arr[CATEGORY_COUNT]) {
  printf("\n");
  for (size_t i = 0; i < CATEGORY_COUNT; ++i) {
    printf("%12s %9d\n", GetCategoryAsString(i), arr[i]);
  }
  printf("\n");
}
