#ifndef PURCHASE_OPS_H
#define PURCHASE_OPS_H


#include <sqlite3.h>

// All purchase add/modify/delete menu logic
void purchase_ops_menu(sqlite3* db);
void add_purchase(sqlite3* db);
void modify_purchase(sqlite3* db);
void delete_purchase(sqlite3* db);

#endif // PURCHASE_OPS_H
