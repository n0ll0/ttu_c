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

#define MAX_N 20

double GetDoubleInRange(double min, double max, char prompt[], char error[]);
int GetIntInRange(int min, int max, char prompt[], char error[]);
void Table(double A, double H, int N, double func(double));
double f(double x);

int main()
{
  double A, H;
  int N;
  // Initial value
  A = GetDoubleInRange(-INFINITY, INFINITY, "Algväärtus: ", "Vigane sisend!");
  // step size
  H = GetDoubleInRange(-INFINITY, INFINITY, "Sammu suurus: ", "Vigane sisend!");
  // step count
  N = GetIntInRange(1, MAX_N, "Mitu sammu?", "Vigane sisend!");

  Table(A, H, N, f);

  return 0;
}

void Table(double A, double H, int N, double func(double))
{
  double x = A;
  double y;
  printf("#-----------------------------#\n");
  printf("| %-12s | %-12s |\n", "x", "y");
  for (int i = 0; i < N; ++i)
  {
    y = func(x);
    // if (y == NAN)
    //   continue;
    printf("|--------------|--------------|\n");
    printf("| %12.2lf | %12.2lf |\n", x, y);
    x += H;
  }
  printf("#-----------------------------#\n");
}

/**
 * √(x^3+1)/(3−x^2)
 */
double f(double x)
{
  double x_sqr = x*x;
  if (x_sqr == 3) return NAN;
  return sqrt((x_sqr * x) + 1) / (3 - (x_sqr));
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Repeats until requirements are met and returns the number.
 *
 * Parameters:     min - lower bound for the user input (inclusive)
 *                 max - upper bound for the user input (inclusive)
 *                 prompt - prompt for user input, printed before entry
 *                 error - printed after errory entry
 *
 * Return:         number within the specified limits
 */
double GetDoubleInRange(double min, double max, char prompt[], char error[])
{
  double num;
  printf("\n%s", prompt);
  while (scanf("%lf", &num) != 1 || num < min || num > max)
  {
    while (getchar() != 10)
      ;
    printf("\n%s\n\n%s", error, prompt);
  }
  return num;
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Repeats until requirements are met and returns the number.
 *
 * Parameters:     min - lower bound for the user input (inclusive)
 *                 max - upper bound for the user input (inclusive)
 *                 prompt - prompt for user input, printed before entry
 *                 error - printed after errory entry
 *
 * Return:         number within the specified limits
 */
int GetIntInRange(int min, int max, char prompt[], char error[])
{
  int num;
  printf("\n%s", prompt);
  while (scanf("%d", &num) != 1 || num < min || num > max)
  {
    printf("\n%s\n\n%s", error, prompt);
    while (getchar() != 10)
      ;
  }
  return num;
}
