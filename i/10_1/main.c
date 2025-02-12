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
#define MENU_OPTION_MAX 9

int Menu(void);
int GetIntInRange(int min, int max);
void GenerateMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);
void DisplayMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);
void Swap(int *a, int *b);
void SwitchRows(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int rowFrom, int rowTo);
void SwitchColumns(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int colFrom, int colTo);
void DeleteRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int rowToDelete);
void DeleteColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int rowToDelete);
void GenerateRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int row);
void GenerateColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int col);
void AddRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int row);
void AddColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int col);
void TransposeMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);

int main(void)
{
  int data[LIMIT_ROWS][LIMIT_COLS];
  int menuOption = 1, rows, cols;

  while (menuOption != 0)
  {
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
      if (rows <= 0 || cols <= 0)
      {
        puts("Error: Matrix is empty");
        break;
      }
      printf("Enter source row between 1 and %d", rows);
      int row1 = -1 + GetIntInRange(1, rows);
      printf("Enter destination row between 1 and %d", rows);
      int row2 = -1 + GetIntInRange(1, rows);
      SwitchRows(data, rows, cols, row1, row2);
      break;
    case 4:
      puts("Case 4: Switch columns");
      if (rows <= 0 || cols <= 0)
      {
        puts("Error: Matrix is empty");
        break;
      }
      printf("Enter source column between 1 and %d", cols);
      int col1 = -1 + GetIntInRange(1, cols);
      printf("Enter destination column between 1 and %d", cols);
      int col2 = -1 + GetIntInRange(1, cols);
      SwitchColumns(data, rows, cols, col1, col2);

      break;
    case 5:
      puts("Case 5: Delete row");
      if (rows <= 0 || cols <= 0)
      {
        puts("Error: Matrix is empty");
        break;
      }
      printf("Enter row to delete between 1 and %d", rows);
      int rowToDelete = -1 + GetIntInRange(1, rows);
      DeleteRow(data, &rows, &cols, rowToDelete);
      break;
    case 6:
      puts("Case 6: Delete column");
      if (rows <= 0 || cols <= 0)
      {
        puts("Error: Matrix is empty");
        break;
      }
      printf("Enter column to delete between 1 and %d", cols);
      int colToDelete = -1 + GetIntInRange(1, cols);
      DeleteColumn(data, &rows, &cols, colToDelete);
      break;
    case 7:
      puts("Case 7: Generate new row");
      printf("Enter row index to generate between 0 and %d", rows);
      int rowTo = GetIntInRange(0, rows);
      AddRow(data, &rows, &cols, rowTo);
      break;
    case 8:
      puts("Case 8: Generate new column");
      printf("Enter column index to generate between 0 and %d", cols);
      int colTo = GetIntInRange(0, cols);
      AddColumn(data, &rows, &cols, colTo);
      break;
    case 9:
      if (rows <= 0 || cols <= 0)
      {
        puts("Error: Matrix is empty");
        break;
      }
      puts("Case 9: Transpose matrix");
      TransposeMatrix(data, rows, cols);
      break;
    case 0:
      puts("Case 0: Exiting");

      break;
    default:
      puts("Case ?: Sorry! We didn't understand Your request");
      break;
    }
    if (cols <= 0 || rows <= 0)
    {
      puts("Warning: matrix is empty. Use case 1 to generate a new matrix.");
    }
    menuOption = Menu();
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
  puts("5 - Delete row");
  puts("6 - Delete column");
  puts("7 - Generate new row");
  puts("8 - Generate new column");
  puts("9 - Transpose matrix");
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
  int row = 0;
  // int col;
  do
  {
    GenerateRow(matrix, rows, cols, row);
  } while (row++ < rows);
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
  int row = 0;
  int col;
  while (row < rows)
  {
    col = 0;
    while (col < cols)
    {
      printf("%3d ", matrix[row][col]);
      ++col;
    }
    puts("");
    ++row;
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
  // idc about memory safety, but it's fine for this case
  Swap(matrix[rowFrom], matrix[rowTo]);
  // int col = 0;
  // while (col < cols)
  // {
  //   Swap(&matrix[rowFrom][col], &matrix[rowTo][col]);
  //   ++col;
  // }
}

void SwitchColumns(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int colFrom, int colTo)
{
  for (int row = 0; row < rows; ++row)
  {
    Swap(&matrix[row][colFrom], &matrix[row][colTo]);
  }
}

void DeleteRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int rowToDelete)
{
  SwitchRows(matrix, *rows, *cols, rowToDelete, *rows - 1);
  (*rows)--;
}

void DeleteColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int rowToDelete)
{
  SwitchColumns(matrix, *rows, *cols, rowToDelete, *cols - 1);
  (*cols)--;
}

void GenerateRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int row)
{
  int col = 0;
  while (col < cols)
  {
    matrix[row][col] = rand() % (RAND_UPPER - RAND_LOWER + 1) + RAND_LOWER;
    ++col;
  }
}

void GenerateColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int col)
{
  int row = 0;
  while (row < rows)
  {
    matrix[row][col] = rand() % (RAND_UPPER - RAND_LOWER + 1) + RAND_LOWER;
    ++row;
  }
}

void AddRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int row)
{
  GenerateRow(matrix, *rows, *cols, *rows);
  for (int otherRow = *rows; otherRow > row; --otherRow)
  {
    printf("Swapping indexes %d and %d\n", otherRow, otherRow - 1);
    SwitchRows(matrix, *rows, *cols, otherRow, otherRow - 1);
  }
  (*rows)++;
}

void AddColumn(int matrix[LIMIT_ROWS][LIMIT_COLS], int *rows, int *cols, int col)
{
  GenerateColumn(matrix, *rows, *cols, *cols);
  for (int otherColumn = *cols; otherColumn > col; --otherColumn)
  {
    SwitchColumns(matrix, *rows, *cols, otherColumn, otherColumn - 1);
  }
  (*cols)++;
}

void TransposeMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = i + 1; j < cols; ++j)
    {
      Swap(&matrix[i][j], &matrix[j][i]);
    }
  }
}
