#include "../include/cmenu.h"
#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>

FUNCTION_STATUS MenuPrompt(Menu* m) {
  log_event("%s", m->title);
  for (int i = 0; i < m->count; ++i) {
    log_event("\t%d - %s", i, m->menu_options[i].preview);
  }
  log_event("\t%d - Close menu (%s)", m->count, m->title);
  do {
    log_event("Select an option (0-%d): ", m->count - 1);
    if (scanf("%d", &m->option) != 1 || m->option < 0 || m->option > m->count) {
      log_event("Invalid choice. Please try again.\n");
      while (getchar() != '\n')
        ;
    } else {
      break;
    }
  } while (1);

  if (m->option == m->count) {
    return Error;
  }

  return Ok;
}

