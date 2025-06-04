#ifndef STATS_OPS_H
#define STATS_OPS_H

#include <sqlite3.h>

void print_purchases_grouped_by_clients(sqlite3* db);
void print_avg_spending_by_client(sqlite3* db);
void print_avg_spending_by_client_per_shop(sqlite3* db);
void print_top10_clients_overall(sqlite3* db);
void print_top10_clients_per_shop(sqlite3* db);

#endif // STATS_OPS_H
