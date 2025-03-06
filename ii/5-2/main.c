#include "main.h"
#include "data_processor.h"
#include "file_helper.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  DownloadCovidData(CSV);
  // DownloadCovidData(CSV);
  processCovidData(OUT_FILE_NAME_CSV, CSV);

  return EXIT_SUCCESS;
}
