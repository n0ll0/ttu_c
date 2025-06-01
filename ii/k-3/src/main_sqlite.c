

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../include/menu.h"
#include "../include/purchase_ops.h"
#include "../include/setup_db.h"
#include "../include/stats_ops.h"

int main() {
  sqlite3* db;
  if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    return 1;
  }
  enable_foreign_keys(db);
  create_purchases_table_if_not_exists(db);

  int choice;
    do {
        print_main_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            break;
        switch (choice) {
            case 1:
                purchase_ops_menu(db);
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                stats_ops_menu(db, choice);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

  sqlite3_close(db);
  return 0;
}
