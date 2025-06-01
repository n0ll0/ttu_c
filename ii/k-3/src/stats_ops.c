#include "../include/stats_ops.h"
#include <stdio.h>

void stats_ops_menu(sqlite3* db, int option) {
    switch(option) {
        case 2:
            print_purchases_grouped_by_clients(db);
            break;
        case 3:
            print_avg_spending_by_client(db);
            break;
        case 4:
            print_avg_spending_by_client_per_shop(db);
            break;
        case 5:
            print_top10_clients_overall(db);
            break;
        case 6:
            print_top10_clients_per_shop(db);
            break;
        default:
            printf("Invalid statistics option.\n");
    }
}

void print_purchases_grouped_by_clients(sqlite3* db) {
    printf("Feature not implemented yet.\n");
}
void print_avg_spending_by_client(sqlite3* db) {
    printf("Feature not implemented yet.\n");
}
void print_avg_spending_by_client_per_shop(sqlite3* db) {
    printf("Feature not implemented yet.\n");
}
void print_top10_clients_overall(sqlite3* db) {
    printf("Feature not implemented yet.\n");
}
void print_top10_clients_per_shop(sqlite3* db) {
    printf("Feature not implemented yet.\n");
}
