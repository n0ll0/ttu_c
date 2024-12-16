#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum FLAGS {
  VERBOSE,
  DEBUG,
  HELP,
  NUM_FLAGS
};

char* FLAGS[NUM_FLAGS] = {
  "-v",
  "-d",
  "-h"
};

int main(int argc, char const *argv[])
{
  bool activeFlags[NUM_FLAGS] = {false,false,false};
  for (int arg = 1; arg < argc; ++arg)
  {
    for (int flag = 0; flag < NUM_FLAGS; ++flag)
    {
      if (strcmp(argv[arg], FLAGS[flag]) == 0)
      {
        activeFlags[flag] = true;
      }
    }
  }

  if (activeFlags[HELP])
  {
    printf("Usage: ");
  }
  if (activeFlags[DEBUG])
  {
    printf("-d ");
  }
  if (activeFlags[VERBOSE])
  {
    printf("-v ");
  }

  

  return 0;
}


