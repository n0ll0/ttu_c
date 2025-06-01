#include "../include/purchase_ops.h"
#include <sqlite3.h>
#include <stdio.h>

// Helper: Validate positive integer
int validate_positive_int(int value) { return value >= 0; }

// Add a purchase
void add_purchase(sqlite3* db) {
  int client_id, product_id, amount;
  printf("Enter client_id: ");
  scanf("%d", &client_id);
  printf("Enter product_id: ");
  scanf("%d", &product_id);
  printf("Enter amount: ");
  scanf("%d", &amount);
  if (!validate_positive_int(amount)) {
    printf("Amount must be non-negative.\n");
    return;
  }
  const char* sql =
      "INSERT INTO PURCHASES (client_id, product_id, amount) VALUES (?, ?, ?);";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
    printf("Prepare failed: %s\n", sqlite3_errmsg(db));
    return;
  }
  sqlite3_bind_int(stmt, 1, client_id);
  sqlite3_bind_int(stmt, 2, product_id);
  sqlite3_bind_int(stmt, 3, amount);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("Insert failed: %s\n", sqlite3_errmsg(db));
  } else {
    printf("Purchase added.\n");
  }
  sqlite3_finalize(stmt);
}

// Modify a purchase
void modify_purchase(sqlite3* db) {
  int id, amount;
  printf("Enter purchase id to modify: ");
  scanf("%d", &id);
  printf("Enter new amount: ");
  scanf("%d", &amount);
  if (!validate_positive_int(amount)) {
    printf("Amount must be non-negative.\n");
    return;
  }
  const char* sql = "UPDATE PURCHASES SET amount = ? WHERE id = ?;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
    printf("Prepare failed: %s\n", sqlite3_errmsg(db));
    return;
  }
  sqlite3_bind_int(stmt, 1, amount);
  sqlite3_bind_int(stmt, 2, id);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("Update failed: %s\n", sqlite3_errmsg(db));
  } else {
    printf("Purchase updated.\n");
  }
  sqlite3_finalize(stmt);
}

// Delete a purchase
void delete_purchase(sqlite3* db) {
  int id;
  printf("Enter purchase id to delete: ");
  scanf("%d", &id);
  const char* sql = "DELETE FROM PURCHASES WHERE id = ?;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
    printf("Prepare failed: %s\n", sqlite3_errmsg(db));
    return;
  }
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("Delete failed: %s\n", sqlite3_errmsg(db));
  } else {
    printf("Purchase deleted.\n");
  }
  sqlite3_finalize(stmt);
}

// Menu for add/modify/delete
void purchase_ops_menu(sqlite3* db) {
  int op;
  do {
    printf("\n1. Add purchase\n2. Modify purchase\n3. Delete purchase\n0. "
           "Back\nChoose: ");
    scanf("%d", &op);
    switch (op) {
    case 1:
      add_purchase(db);
      break;
    case 2:
      modify_purchase(db);
      break;
    case 3:
      delete_purchase(db);
      break;
    case 0:
      break;
    default:
      printf("Invalid.\n");
    }
  } while (op != 0);
}
