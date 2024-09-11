#include <stdio.h>

int input_i(const char* str)
{
  int i;
  printf(str);
  scanf("%d", &i);
  return i;
}

float input_f(char* string)
{
  float i;
  printf(string);
  scanf("%f", &i);
  return i;
}

double input_d(char* string)
{
  double i;
  printf(string);
  scanf("%lf", &i);
  return i;
}

char* input_s(char* string)
{
  char* i;
  printf(string);
  scanf("%s", i);
  return i;
}
