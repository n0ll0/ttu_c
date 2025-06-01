#include "waitForUser.h"
#include "../include/logger.h"
#include <stdio.h>

void waitForUser() {
	log_event("Press any key to continue\n");
	getchar();
	while (getchar() != 10);
}
