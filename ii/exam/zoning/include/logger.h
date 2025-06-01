#pragma once
#include <stdio.h>
#include <stdarg.h>

void log_event(const char* format, ...);
void log_error(const char* format, ...);