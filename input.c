#include <stdio.h>

int clearBuffer(int boolean)
{
  if (boolean)
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
  }
  return boolean;
}

int read_int(void (*askFn)(), int (*validity_comparisson)(int))
{
  int i;
  do
  {
    askFn();
  } while (clearBuffer((scanf("%d", &i) != 1) || !validity_comparisson(i)));

  return i;
}

float read_float(void (*askFn)(), int (*validity_comparisson)(float))
{
  float i;
  do
  {
    askFn();
  } while (clearBuffer((scanf("%f", &i) != 1) || !validity_comparisson(i)));

  return i;
}

int input_i(const char *str)
{
  int i;
  printf(str);
  scanf("%d", &i);
  return i;
}

float input_f(char *string)
{
  float i;
  printf(string);
  scanf("%f", &i);
  return i;
}

double input_d(char *string)
{
  double i;
  printf(string);
  scanf("%lf", &i);
  return i;
}

char *input_s(char *string)
{
  char *i;
  printf(string);
  scanf("%s", i);
  return i;
}
