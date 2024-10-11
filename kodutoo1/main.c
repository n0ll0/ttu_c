/**
 *
 * Meetod
 * 3. Sisendiks on argumendi x algväärtus A, samm H ning sammude arv N.
 * Kehtivad tingimused: H > 0; N > 0.
 * Funktsiooni väärtust y arvutatakse punktides:
 * A
 * A + H
 * A + 2H
 * ...
 * A + (N-1)H.
 *
 * Funktsioon
 * 9.
 */

#include <stdio.h>
#include <math.h>

double GetDoubleInRange(double min, double max, char prompt[], char error[]);
void Table(double A, double H, int N, double func());
double f(double x);

int main()
{
  double A = 1.7320508075688772;
  double H = 1;
  int N = 10;

  Table(A, H, N, f);

  return 0;
}

void Table(double A, double H, int N, double func())
{
  printf("-------------------------------\n");
  printf("| %-12s | %-12s |\n", "x", "y");
  double x = A;
  for (int i = 0; i < N; ++i)
  {
    double y = func(x);
    if (y == NAN)
      continue;
    printf("|--------------|--------------|\n");
    printf("| %12.2lf | %12.2lf |\n", x, y);
    x += H;
  }
  printf("-------------------------------\n");
}

/**
 * √(x^3+1)/(3−x^2)
 */
double f(double x)
{
  if (x*x == 3) return NAN;
  return sqrt((x * x * x) + 1) / (3 - (x * x));
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Repeats until requirements are met and returns the number.
 *
 * Parameters:     min - lower bound for the user input (inclusive)
 *                 max - upper bound for the user input (inclusive)
 *                 prompt - prompt for user input, printed before entry
 *
 * Return:         number within the specified limits
 */
double GetDoubleInRange(double min, double max, char prompt[], char error[])
{
  printf("\n%s", prompt);
  double num;
  while (scanf("%lf", &num) != 1 || num < min || num > max)
  {
    printf("\n%s\n\n%s", error, prompt);
    while (getchar() != 10)
      ;
  }
  return num;
}