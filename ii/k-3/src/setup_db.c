#include "../include/setup_db.h"
#include <stdio.h>
#include <stdlib.h>

void enable_foreign_keys(sqlite3* db) {
  char* err = NULL;
  if (sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, &err) != SQLITE_OK) {
    fprintf(stderr, "Failed to enable foreign keys: %s\n", err);
    sqlite3_free(err);
    exit(1);
  }
}

void create_purchases_table_if_not_exists(sqlite3* db) {
  const char* sql = "CREATE TABLE IF NOT EXISTS PURCHASES ("
                    "id INTEGER PRIMARY KEY,"
                    "client_id INTEGER NOT NULL,"
                    "product_id INTEGER NOT NULL,"
                    "amount INTEGER NOT NULL,"
                    "FOREIGN KEY(client_id) REFERENCES CLIENTS(id),"
                    "FOREIGN KEY(product_id) REFERENCES PRODUCTS(id)"
                    ");";
  char* err = NULL;
  if (sqlite3_exec(db, sql, 0, 0, &err) != SQLITE_OK) {
    fprintf(stderr, "Failed to create PURCHASES table: %s\n", err);
    sqlite3_free(err);
    exit(1);
  }
}
