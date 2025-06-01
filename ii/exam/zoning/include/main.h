#pragma once

enum OPTION {
  OPTION_DISPLAY_ALL,
  OPTION_GROUP_BY_TYPE,
  OPTION_SEARCH,
  OPTION_PRICES,
  OPTION_COUNT
};

#define MAIN_MENU {.title = "Main program menu",                                           \
                  .option = OPTION_DISPLAY_ALL,                                            \
                  .menu_options = {                                                        \
                    [OPTION_DISPLAY_ALL] = {.preview = "Display all"},                     \
                    [OPTION_GROUP_BY_TYPE] = {.preview = "Group buildings by their type"}, \
                    [OPTION_SEARCH] = {.preview = "Search zones (more commands)"},         \
                    [OPTION_PRICES] = {.preview = "Figure out prices"}          \
                  },                                                                       \
                  .count = OPTION_COUNT}
