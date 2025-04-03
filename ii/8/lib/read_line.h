#ifndef READ_LINE_H
#define READ_LINE_H

#include <stdio.h>

// Read a line of arbitrary size from a file
//
// Returns a pointer to the line.
// Returns NULL on EOF or error.
//
// It's up to the caller to free() this pointer when done with it.
//
// Note that this strips the newline from the result. If you need
// it in there, probably best to switch this to a do-while.

char* readline(FILE* fp);

#endif // !READ_LINE_H
