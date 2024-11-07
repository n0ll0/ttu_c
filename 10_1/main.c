/**
 * File:        8_1_date_base.c
 * Author:      Risto Heinsar
 * Created:     05.10.2015
 * Modified:    12.10.2023
 *
 * Description: Basecode for the lab task to switch rows and columns in a
 *              matrix. Matrix is generated randomly and can be regenerated.
 *              Program runs infinitely in a menu loop until user exits.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Limits for the matrix size */
#define LIMIT_ROWS 10
#define LIMIT_COLS 20

/* Limits for the random numbers */
#define RAND_LOWER 0
#define RAND_UPPER 99

/* Limits for the menu */
#define MENU_OPTION_MIN 0
#define MENU_OPTION_MAX 4

int Menu(void);
int GetIntInRange(int min, int max);
void GenerateMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);
void DisplayMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);
void Swap(int *a, int *b);
void SwitchRows(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int rowFrom, int rowTo);
void SwitchColumns(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int colFrom, int colTo);

int main(void)
{
  int data[LIMIT_ROWS][LIMIT_COLS];
  int menuOption = 1, rows, cols;

  while (menuOption != 0)
  {
    menuOption = Menu();
    switch (menuOption)
    {
    case 1:
      puts("Case 1: Enter new matrix dimensions and generate matrix");

      printf("Enter width between 1 and %d\n", LIMIT_COLS);
      cols = GetIntInRange(1, LIMIT_COLS);

      printf("Enter length between 1 and %d\n", LIMIT_ROWS);
      rows = GetIntInRange(1, LIMIT_ROWS);

      GenerateMatrix(data, rows, cols);
      break;
    case 2:
      puts("Case 2: Print matrix");

      DisplayMatrix(data, rows, cols);
      break;
    case 3:
      puts("Case 3: Switch rows");

      printf("Enter source row between 1 and %d", rows);
      int row1 = -1 + GetIntInRange(0, rows);
      printf("Enter destination row between 1 and %d", rows);
      int row2 = -1 + GetIntInRange(0, rows);
      SwitchRows(data, rows, cols, row1, row2);
      break;
    case 4:
      puts("Case 4: Switch columns");
      /* 1. Prompt the user to enter the column numbers to switch
       * 2. Call SwitchColumns() to switch the rows */
      printf("Enter source column between 1 and %d", cols);
      int col1 = -1 + GetIntInRange(0, cols);
      printf("Enter destination column between 1 and %d", cols);
      int col2 = -1 + GetIntInRange(0, cols);
      SwitchColumns(data, rows, cols, col1, col2);

      break;
    case 0:
      puts("Case 0: Exiting");

      break;
    default:
      puts("Case ?: Sorry! We didn't understand Your request");
      break;
    }
  }

  return 0;
}

/**
 * Description:    Displays the possible menu options to the user,
 *                 allows to select an action to perform.
 *
 * Parameters:     None
 *
 * Return:         Menu item number selected
 */
int Menu(void)
{
  int selection;
  putchar('\n');
  puts("Select Your action!");
  puts("1 - Generate new matrix");
  puts("2 - Display matrix");
  puts("3 - Switch rows");
  puts("4 - Switch columns");
  puts("0 - Exit program");
  selection = GetIntInRange(MENU_OPTION_MIN, MENU_OPTION_MAX);
  return selection;
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
int GetIntInRange(int min, int max)
{
  int num;
  do
  {
    printf("> ");
    scanf("%d", &num);
    if (num < min || num > max)
    {
      printf("\nRetry! Input must be in between %d and %d\n", min, max);
    }
  } while (num < min || num > max);
  return num;
}

/**
 * Description:    Generates random numbers and stores them into the matrix.
 *                 Numbers are only generated within the area specified by rows
 *                 and cols (regardless of the defined size).
 *                 Random numbers will be in between RAND_LOWER and RAND_UPPER.
 *
 * Parameters:     matrix - 2-dimensional array to store the numbers into,
 *                          size at declaration is given by macros.
 *                 rows - number of rows to generate
 *                 cols - number of columns to generate
 *
 * Return:         none
 */
void GenerateMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
  srand(time(NULL));

  for (int row = 0; row < rows; ++row)
  {
    for (int col = 0; col < cols; ++col)
    {
      matrix[row][col] = rand() % (RAND_UPPER - RAND_LOWER + 1) + RAND_LOWER;
    }
  }
}

/**
 * Description:    Displays the matrix with its columns aligned for inegers
 *                 up to 999. Only prints the area specified by rows x cols.
 *
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 *
 * Return:         none
 */
void DisplayMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
  for (int row = 0; row < rows; ++row)
  {
    for (int col = 0; col < cols; ++col)
    {
      printf("%3d ", matrix[row][col]);
    }
    puts("");
  }
}

void Swap(int *a, int *b)
{
  *a = *b ^ *a;
  *b = *a ^ *b;
  *a = *b ^ *a;
}

void SwitchRows(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int rowFrom, int rowTo)
{
  for (int col = 0; col < cols; ++col)
  {
    Swap(&matrix[rowFrom][col], &matrix[rowTo][col]);
  }
}

void SwitchColumns(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int colFrom, int colTo)
{
  for (int row = 0; row < rows; ++row)
  {
    Swap(&matrix[row][colFrom], &matrix[row][colTo]);
  }
}
