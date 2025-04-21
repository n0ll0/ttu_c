#include "../include/cmenu.h"
#include <stdio.h>
#include <stdlib.h>

FUNCTION_STATUS MenuPrompt(Menu* m) {
  printf("\nProgram menu:\n");
  for (int i = 0; i < OPTION_COUNT; ++i) {
    printf("\t%d - %s\n", i, m->menu_options[i].preview);
  }
  do {
    printf("Select an option (0-%d): ", OPTION_COUNT - 1);
    if (scanf("%d", &m->option) != 1 || m->option < 0 || m->option >= OPTION_COUNT) {
      printf("Invalid choice. Please try again.\n");
      while (getchar() != '\n');
    } else {
      break;
    }
  } while (1);

  
  if (m->option == OPTION_COUNT) {
    return Error;
  }

  return Ok;
}
