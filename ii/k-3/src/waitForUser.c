#include "waitForUser.h"
#include "../include/logger.h"
#include <stdio.h>

/**
 * @brief Waits for the user to press any key to continue.
 *
 * This function logs a message prompting the user to press any key,
 * then waits for user input. It consumes all characters up to and including
 * the newline character to ensure the input buffer is cleared.
 */
void waitForUser() {
	fprintf(stdout, "Press any key to continue\n");
	getchar();
	while (getchar() != 10);
}
