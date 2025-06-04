#ifndef PURCHASE_OPS_H
#define PURCHASE_OPS_H

#include "cmenu.h"
#include <sqlite3.h>

// Enum for purchase operations
enum PURCHASE_OPS_OPTION {
  PURCHASE_OPS_ADD,
  PURCHASE_OPS_MODIFY,
  PURCHASE_OPS_DELETE,
  PURCHASE_OPS_COUNT
};

#define PURCHASE_OPS_MENU                                                      \
  {                                                                            \
    .title = "Purchase Operations",                                            \
    .menu_options = {[PURCHASE_OPS_ADD] = {"Add purchase"},                    \
                     [PURCHASE_OPS_MODIFY] = {"Modify purchase"},              \
                     [PURCHASE_OPS_DELETE] = {"Delete purchase"}},             \
    .count = PURCHASE_OPS_COUNT                                                \
  }

void purchase_ops_menu(sqlite3* db);
void add_purchase(sqlite3* db);
void modify_purchase(sqlite3* db);
void delete_purchase(sqlite3* db);

#endif // PURCHASE_OPS_H
