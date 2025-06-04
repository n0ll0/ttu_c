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
#include "../include/logger.h"

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
        log_error("Failed to prepare statement.\n");
        return;
    }
    char last_client[128] = "";
    char buffer[256];
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        int purchase_id = sqlite3_column_int(stmt, 1);
        int shop_id = sqlite3_column_int(stmt, 2);
        double amount = sqlite3_column_double(stmt, 3);

        if (strcmp(last_client, client) != 0) {
            snprintf(buffer, sizeof(buffer), "\nClient: %s\n", client);
            log_event(buffer);
            snprintf(buffer, sizeof(buffer), "  %-10s %-8s %-10s\n", "PurchaseID", "ShopID", "Amount");
            log_event(buffer);
            strncpy(last_client, client, sizeof(last_client));
            last_client[sizeof(last_client)-1] = '\0';
        }
        snprintf(buffer, sizeof(buffer), "  %-10d %-8d %-10.2f\n", purchase_id, shop_id, amount);
        log_event(buffer);
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
        log_error("Failed to prepare statement.\n");
        return;
    }
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%-30s %-10s\n", "Client", "Avg Amount");
    log_event(buffer);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        double avg = sqlite3_column_double(stmt, 1);
        snprintf(buffer, sizeof(buffer), "%-30s %-10.2f\n", client, avg);
        log_event(buffer);
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
        log_error("Failed to prepare statement.\n");
        return;
    }
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%-30s %-20s %-10s\n", "Client", "Shop", "Avg Amount");
    log_event(buffer);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        const char *shop = (const char*)sqlite3_column_text(stmt, 1);
        double avg = sqlite3_column_double(stmt, 2);
        snprintf(buffer, sizeof(buffer), "%-30s %-20s %-10.2f\n", client, shop, avg);
        log_event(buffer);
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
        log_error("Failed to prepare statement.\n");
        return;
    }
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%-3s %-30s %-10s\n", "No", "Client", "Total");
    log_event(buffer);
    int rank = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *client = (const char*)sqlite3_column_text(stmt, 0);
        double total = sqlite3_column_double(stmt, 1);
        snprintf(buffer, sizeof(buffer), "%-3d %-30s %-10.2f\n", rank++, client, total);
        log_event(buffer);
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
        log_error("Failed to prepare statement.\n");
        return;
    }
    char last_shop[128] = "";
    char buffer[256];
    int rank = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *shop = (const char*)sqlite3_column_text(stmt, 0);
        const char *client = (const char*)sqlite3_column_text(stmt, 1);
        double total = sqlite3_column_double(stmt, 2);

        if (strcmp(last_shop, shop) != 0) {
            if (last_shop[0] != '\0') log_event("\n");
            snprintf(buffer, sizeof(buffer), "Shop: %s\n", shop);
            log_event(buffer);
            snprintf(buffer, sizeof(buffer), "%-3s %-30s %-10s\n", "No", "Client", "Total");
            log_event(buffer);
            rank = 1;
            strncpy(last_shop, shop, sizeof(last_shop));
            last_shop[sizeof(last_shop)-1] = '\0';
        }
        if (rank <= 10) {
            snprintf(buffer, sizeof(buffer), "%-3d %-30s %-10.2f\n", rank, client, total);
            log_event(buffer);
        }
        rank++;
    }
    sqlite3_finalize(stmt);
}
