#include "waitForUser.h"
#include <stdio.h>

void waitForUser() {
	printf("Press any key to continue\n");
	getchar();
	while (getchar() != 10);
}
