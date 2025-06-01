#ifndef SETUP_DB_H
#define SETUP_DB_H

#include <sqlite3.h>

#define DB_PATH "../db/shop1.db"

// All DB setup logic (enabling foreign keys, creating tables)
void enable_foreign_keys(sqlite3 *db);
void create_purchases_table_if_not_exists(sqlite3 *db);

#endif // SETUP_DB_H
