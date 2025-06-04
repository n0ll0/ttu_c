/**
 * @file stats_ops.c
 * @brief Implementation of statistics operations for client purchases.
 *
 * Functions in this file provide various statistics and reports
 * based on purchase data stored in an SQLite database.
 */


#include "../include/stats_ops.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

/**
 * @brief Prints all purchases grouped by clients.
 * @param db Pointer to the opened SQLite database.
 */
void print_purchases_grouped_by_clients(sqlite3* db) {
    const char *sql =
        "SELECT clients.first_name || ' ' || clients.last_name AS client_name, "
        "purchases.id, products.shop_id, purchases.amount "
        "FROM purchases "
        "JOIN clients ON purchases.client_id = clients.id "
        "JOIN products ON purchases.product_id = products.id "
        "ORDER BY client_name;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return;
    }
    char last_client[128] = "";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        int purchase_id = sqlite3_column_int(stmt, 1);
        int shop_id = sqlite3_column_int(stmt, 2);
        double amount = sqlite3_column_double(stmt, 3);

        if (strcmp(last_client, client) != 0) {
            printf("\nClient: %s\n", client);
            printf("  %-10s %-8s %-10s\n", "PurchaseID", "ShopID", "Amount");
            strncpy(last_client, client, sizeof(last_client));
            last_client[sizeof(last_client)-1] = '\0';
        }
        printf("  %-10d %-8d %-10.2f\n", purchase_id, shop_id, amount);
    }
    sqlite3_finalize(stmt);
}

/**
 * @brief Prints the average spending by each client.
 * @param db Pointer to the opened SQLite database.
 */
void print_avg_spending_by_client(sqlite3* db) {
    const char *sql =
        "SELECT clients.first_name || ' ' || clients.last_name AS client_name, AVG(purchases.amount) "
        "FROM purchases "
        "JOIN clients ON purchases.client_id = clients.id "
        "GROUP BY clients.id "
        "ORDER BY client_name;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return;
    }
    printf("%-30s %-10s\n", "Client", "Avg Amount");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        double avg = sqlite3_column_double(stmt, 1);
        printf("%-30s %-10.2f\n", client, avg);
    }
    sqlite3_finalize(stmt);
}

/**
 * @brief Prints the average spending by each client per shop.
 * @param db Pointer to the opened SQLite database.
 */
void print_avg_spending_by_client_per_shop(sqlite3* db) {
    const char *sql =
        "SELECT clients.first_name || ' ' || clients.last_name AS client_name, shops.name, AVG(purchases.amount) "
        "FROM purchases "
        "JOIN clients ON purchases.client_id = clients.id "
        "JOIN products ON purchases.product_id = products.id "
        "JOIN shops ON products.shop_id = shops.id "
        "GROUP BY clients.id, shops.id "
        "ORDER BY client_name, shops.name;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return;
    }
    printf("%-30s %-20s %-10s\n", "Client", "Shop", "Avg Amount");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        const char *shop = (const char*)sqlite3_column_text(stmt, 1);
        double avg = sqlite3_column_double(stmt, 2);
        printf("%-30s %-20s %-10.2f\n", client, shop, avg);
    }
    sqlite3_finalize(stmt);
}

/**
 * @brief Prints the top 10 clients by total spending overall.
 * @param db Pointer to the opened SQLite database.
 */
void print_top10_clients_overall(sqlite3* db) {
    const char *sql =
        "SELECT clients.first_name || ' ' || clients.last_name AS client_name, SUM(purchases.amount) as total "
        "FROM purchases "
        "JOIN clients ON purchases.client_id = clients.id "
        "GROUP BY clients.id "
        "ORDER BY total DESC "
        "LIMIT 10;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return;
    }
    printf("%-3s %-30s %-10s\n", "No", "Client", "Total");
    int rank = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        double total = sqlite3_column_double(stmt, 1);
        printf("%-3d %-30s %-10.2f\n", rank++, client, total);
    }
    sqlite3_finalize(stmt);
}

/**
 * @brief Prints the top 10 clients by total spending for each shop.
 * @param db Pointer to the opened SQLite database.
 */
void print_top10_clients_per_shop(sqlite3* db) {
    const char *sql =
        "SELECT shops.name, clients.first_name || ' ' || clients.last_name AS client_name, SUM(purchases.amount) as total "
        "FROM purchases "
        "JOIN clients ON purchases.client_id = clients.id "
        "JOIN products ON purchases.product_id = products.id "
        "JOIN shops ON products.shop_id = shops.id "
        "GROUP BY shops.id, clients.id "
        "ORDER BY shops.name, total DESC;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return;
    }
    char last_shop[128] = "";
    int rank = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *shop = (const char*)sqlite3_column_text(stmt, 0);
        const char *client = (const char*)sqlite3_column_text(stmt, 1);
        double total = sqlite3_column_double(stmt, 2);

        if (strcmp(last_shop, shop) != 0) {
            if (last_shop[0] != '\0') printf("\n");
            printf("Shop: %s\n", shop);
            printf("%-3s %-30s %-10s\n", "No", "Client", "Total");
            rank = 1;
            strncpy(last_shop, shop, sizeof(last_shop));
            last_shop[sizeof(last_shop)-1] = '\0';
        }
        if (rank <= 10) {
            printf("%-3d %-30s %-10.2f\n", rank, client, total);
        }
        rank++;
    }
    sqlite3_finalize(stmt);
}
