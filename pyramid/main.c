#include <stdio.h>

int main(int argc, char const **argv)
{
  int size = argv[argc-1];
  for(int i=size;i-->0;)
  {
    for(int j=size-i;j-->0;)
    {
      printf("*");
      printf("%d", j);
    }
    printf("%d", i);
    printf("\n");
  }
}