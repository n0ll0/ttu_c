#include <stdio.h>

int clearBuffer(int boolean, void (*ErrorFunction)())
{
  if (boolean)
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    (*ErrorFunction)();
  }
  return boolean;
}

int read_int(void (*askFn)(), int (*validity_comparisson)(int), void (*ErrorFunction)())
{
  int i;
  do
  {
    askFn();
  } while (clearBuffer((scanf("%d", &i) != 1) || !validity_comparisson(i), ErrorFunction));

  return i;
}

float read_float(void (*askFn)(), int (*validity_comparisson)(float), void (*ErrorFunction)())
{
  float i;
  do
  {
    askFn();
  } while (clearBuffer((scanf("%f", &i) != 1) || !validity_comparisson(i), ErrorFunction));

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

// void hi() { printf("Hi\n"); }
// int cond(int x) { return 1; }
// void err() { printf("nu uh\n"); }

// int main()
// {
//   printf("%d\n", read_int(hi, cond, err));
//   printf("%f\n", read_float(hi, cond, err));
//   return 0;
// }
