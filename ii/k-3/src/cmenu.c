#include "../include/cmenu.h"
#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Displays a menu prompt to the user and handles option selection.
 *
 * This function logs the menu title and all available menu options, including an option to close the menu.
 * It then prompts the user to select an option by entering a number corresponding to the menu choices.
 * The function validates the user input, ensuring it is within the valid range. If the input is invalid,
 * the user is prompted again until a valid selection is made.
 *
 * @param m Pointer to a Menu structure containing menu options and state.
 * @return FUNCTION_STATUS Returns Ok if a valid menu option is selected, or Error if the user chooses to close the menu.
 */
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

