#include "../include/log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char* LOGTYPESARR[LOG_COUNT] = {[LOG_INFO] = "",
                                      [LOG_SUCCESS] = "\x1b[32m[SUCCESS]",
                                      [LOG_WARNING] = "\x1b[33m[WARNING]",
                                      [LOG_ERROR] = "\x1b[31m[ERROR]"};

void Log(LogLevel level, const char* format, ...) {

  // Get timestamp
  time_t now;
  struct tm* time_info;
  char timestamp[26];
  time(&now);
  time_info = localtime(&now);
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);

  // Get level string and color
  const char* color = LOGTYPESARR[level];

  // Format the message
  va_list args1, args2;
  va_start(args1, format);
  va_copy(args2, args1);

  // Calculate required buffer size
  int size = vsnprintf(NULL, 0, format, args1) + 1;
  va_end(args1);

  // Allocate buffer and format message
  char* message = malloc(size);
  if (message == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    va_end(args2);
    return;
  }

  vsnprintf(message, size, format, args2);
  va_end(args2);

  fprintf(stdout, "[%s] %s: %s" ANSI_RESET "\n", timestamp, color, message);
  FILE* log_file = fopen(LOG_FILE, "a");
  if (log_file == NULL) {
    fprintf(stderr, "Warning: Could not open log file\n");
    free(message);
    return;
  }

  fprintf(log_file, "[%s] %s: %s\n", timestamp, color, message);
  fflush(log_file);
  fclose(log_file);

  free(message);
}
