#include "../include/logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#define LOG_FILE "application.log"

// Helper function to get the current timestamp
static void get_timestamp(char* buffer, size_t size) {
  time_t now = time(NULL);
  strftime(buffer, size, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

// Variadic log_error function
void log_error(const char* format, ...) {
  FILE* log = fopen(LOG_FILE, "a");
  if (!log) {
    fprintf(stderr, "Error: Could not open log file.\n");
    return;
  }

  char timestamp[20];
  get_timestamp(timestamp, sizeof(timestamp));

  fprintf(log, "[%s] ERROR: ", timestamp);

  va_list args;
  va_start(args, format);
  vfprintf(log, format, args);
  va_end(args);

  fprintf(log, "\n");
  fclose(log);

  // Also print to stderr
  va_start(args, format);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
  va_end(args);
}

// Variadic log_event function
void log_event(const char* format, ...) {
  FILE* log = fopen(LOG_FILE, "a");
  if (!log) {
    log_error("Error: Could not open log file.\n");
    return;
  }

  char timestamp[20];
  get_timestamp(timestamp, sizeof(timestamp));

  fprintf(log, "[%s] EVENT: ", timestamp);

  va_list args;
  va_start(args, format);
  vfprintf(log, format, args);
  va_end(args);

  fprintf(log, "\n");
  fclose(log);

  fprintf(stdout, "[%s] EVENT: ", timestamp);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}
