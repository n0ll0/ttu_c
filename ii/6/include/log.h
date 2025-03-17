#pragma once

#define LOG_FILE "program.log"
#define ANSI_RESET "\x1b[0m"

typedef enum {
  LOG_INFO,
  LOG_SUCCESS,
  LOG_WARNING,
  LOG_ERROR,
  LOG_COUNT
} LogLevel;

void Log(LogLevel level, const char* format, ...);
