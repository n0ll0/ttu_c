#pragma once

enum OPTION {
  OPTION_DISPLAY_ALL,
  OPTION_EDIT_PRODUCT,
  OPTION_SEARCH,
  OPTION_COUNT
};

#define OPTIONS                                                                \
  {[OPTION_DISPLAY_ALL] = {.preview = "Display all"},                          \
   [OPTION_EDIT_PRODUCT] = {.preview = "Edit product (more commands)"},        \
   [OPTION_SEARCH] = {.preview = "Search phones"}}

	 