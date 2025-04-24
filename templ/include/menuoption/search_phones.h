#pragma once

enum OPTION_PHONE {
  OPTION_PHONE_OS,
  OPTION_PHONE_RAM,
  OPTION_PHONE_SCREEN,
  OPTION_PHONE_NAME,
  OPTION_PHONE_COUNT,
};

#define OPTIONS_PHONE                                                          \
  {[OPTION_PHONE_OS] = {"OS"},                                                 \
   [OPTION_PHONE_RAM] = {"RAM (minimum MB)"},                                  \
   [OPTION_PHONE_SCREEN] = {"Screen size (minimum inches)"},                   \
   [OPTION_PHONE_NAME] = {"Name contains"}}

void search_phones();
