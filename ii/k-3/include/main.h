#pragma once

enum MAIN_MENU_OPTION {
  MAIN_MENU_OPTION_PURCHASE_MODIFY,
  MAIN_MENU_OPTION_PURCHASES_GROUPED,
  MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_ALL_SHOP,
  MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_PER_SHOP,
  MAIN_MENU_OPTION_CLIENTS_TOP10_ALL_SHOP,
  MAIN_MENU_OPTION_CLIENTS_TOP10_PER_SHOP,
  MAIN_MENU_OPTION_COUNT
};

#define MAIN_MENU                                                              \
  {                                                                            \
    .title = "Client Statistics System", .count = MAIN_MENU_OPTION_COUNT,      \
    .menu_options =                                                            \
    { [MAIN_MENU_OPTION_PURCHASE_MODIFY] =                                     \
          {"Add, modify, and delete records in the PURCHASES table\n"},        \
      [MAIN_MENU_OPTION_PURCHASES_GROUPED] =                                   \
          {"Print all PURCHASES grouped by clients\n"},                        \
      [MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_ALL_SHOP] =                       \
          {"Find average spending by client over all shops\n"},                \
      [MAIN_MENU_OPTION_CLIENTS_AVG_SPENDING_PER_SHOP] =                       \
          {"Find average spending by client per shop (descending "             \
           "order)\n"},                                                        \
      [MAIN_MENU_OPTION_CLIENTS_TOP10_ALL_SHOP] =                              \
          {                                                                    \
              "Find the top 10 clients who spend the most over all shops "     \
              "(descending order)\n",                                          \
          },                                                                   \
      [MAIN_MENU_OPTION_CLIENTS_TOP10_PER_SHOP] = {                            \
          "6. Find the top 10 clients who spend the most per shop "            \
          "(descending order)\n"} }                                            \
  }
