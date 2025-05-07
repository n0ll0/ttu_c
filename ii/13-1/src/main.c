#include "../include/main.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s input_file [linear|bst|trie]\n", argv[0]);
    return 1;
  }
  if (argc >= 3 && strcmp(argv[2], "bst") == 0) {
    RunBSTSolution(argv[1]);
  } else if (argc >= 3 && strcmp(argv[2], "trie") == 0) {
    RunTrieSolution(argv[1]);
  } else {
    RunLinearSolution(argv[1]);
  }
  return 0;
}
