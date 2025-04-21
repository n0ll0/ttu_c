#include "../include/cmenu.h"
#include <stdio.h>
#include <stdlib.h>

FUNCTION_STATUS MenuPrompt(Menu* m) {
  printf("\n%s\n", m->title);
  for (int i = 0; i < m->count; ++i) {
    printf("\t%d - %s\n", i, m->menu_options[i].preview);
  }
  printf("\t%d - Close menu (%s)\n", m->count, m->title);
  do {
    printf("Select an option (0-%d): ", m->count - 1);
    if (scanf("%d", &m->option) != 1 || m->option < 0 || m->option > m->count) {
      printf("Invalid choice. Please try again.\n");
      while (getchar() != '\n');
    } else {
      break;
    }
  } while (1);

  if (m->option == m->count) {
    return Error;
  }

  return Ok;
}
