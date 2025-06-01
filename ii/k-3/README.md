
# Homework III: Client Statistics System

**Course:** IAX0584 Programming II  
**Topic:** SQL, C, sqlite3

## Overview
You are developing software for a retail store chain. Your goal is to make a system for analyzing clients’ shopping habits using an SQLite database and C (`sqlite3.h`).

## Data Structure

The database consists of the following tables:

| Table     | Columns                                          |
|-----------|--------------------------------------------------|
| CLIENTS   | id (PK), first_name, last_name                   |
| PURCHASES | id (PK), client_id (FK), product_id (FK), amount |
| PRODUCTS  | id (PK), shop_id (FK), price, name               |
| SHOPS     | id (PK), name                                    |

**Note:** The tables CLIENTS, PRODUCTS, and SHOPS are provided. You must create the PURCHASES table.

## Requirements

- Enable foreign key constraints (`PRAGMA foreign_keys = ON`).
- On launch, check if the PURCHASES table exists; create it if not.
- Implement a menu-driven interface that allows the user to execute commands until they choose to exit.
- All SQL queries using user input must use prepared statements with parameter binding (`sqlite3_prepare_v2` and `sqlite3_bind`).
- Validate all inputs:
  - Price and amount cannot be negative.
  - id values, product names, and shop names must be unique.
  - No fields are nullable.
  - Warn the user if inputs are invalid.

## Menu Commands

1. Add, modify, and delete records in the PURCHASES table.
2. Print all PURCHASES grouped by clients.
3. Find average spending by client over all shops.
4. Find average spending by client per shop (descending order).
5. Find the top 10 clients who spend the most over all shops (descending order).
6. Find the top 10 clients who spend the most per shop (descending order).

## Database

You can use the following database for testing:
[shop1.db](https://blue.pri.ee/ttu/files/db/shop1.db)

## Contact

For questions, contact: rene.pihlak@taltech.ee
