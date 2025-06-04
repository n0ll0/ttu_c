

#include "../include/cmenu.h"
#include "../include/main.h"
#include "../include/purchase_ops.h"
#include "../include/setup_db.h"
#include "../include/stats_ops.h"
#include "../include/waitForUser.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  const char* DB_PATH = argv[1];
  sqlite3* db;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <database_path>\n", argv[0]);
    return 1;
  } if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    return 1;
  }
  enable_foreign_keys(db);
  create_purchases_table_if_not_exists(db);

  Menu menu = MAIN_MENU;

  while (MenuPrompt(&menu) == Ok) {
    if (menu.option == MAIN_MENU_OPTION_COUNT)
      break;
    switch (menu.option) {
    case MAIN_MENU_OPTION_PURCHASE_MODIFY:
      purchase_ops_menu(db);
      break;
    case MAIN_MENU_OPTION_PURCHASES_GROUPED:
      print_purchases_grouped_by_clients(db);
      break;
    case MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_ALL_SHOP:
      print_avg_spending_by_client(db);
      break;
    case MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_PER_SHOP:
      print_avg_spending_by_client_per_shop(db);
      break;
    case MAIN_MENU_OPTION_CLIENTS_TOP10_ALL_SHOP:
      print_top10_clients_overall(db);
      break;
    case MAIN_MENU_OPTION_CLIENTS_TOP10_PER_SHOP:
      print_top10_clients_per_shop(db);
      break;
    default:
      break;
    }
    waitForUser();
  }

  sqlite3_close(db);
  return 0;
}
