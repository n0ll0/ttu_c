#include "../include/menu.h"
#include <stdio.h>

void print_main_menu() {
    printf("\nClient Statistics System\n");
    printf("1. Add, modify, and delete records in the PURCHASES table\n");
    printf("2. Print all PURCHASES grouped by clients\n");
    printf("3. Find average spending by client over all shops\n");
    printf("4. Find average spending by client per shop (descending order)\n");
    printf("5. Find the top 10 clients who spend the most over all shops (descending order)\n");
    printf("6. Find the top 10 clients who spend the most per shop (descending order)\n");
    printf("0. Exit\n");
}
