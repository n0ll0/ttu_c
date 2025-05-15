#pragma once
#include <sqlite3.h>

// Utility to read SQL from file
char* read_sql_from_file(const char* filename);

// Print error and exit
void print_sqlite_error_and_exit(sqlite3* db, const char* msg);
