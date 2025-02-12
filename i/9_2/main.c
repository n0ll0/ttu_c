#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

#define NUM_OF_ROWS 14
#define NUM_OF_COLS 17

#define SEAT_MISSING 0
#define SEAT_FREE 1
#define SEAT_OCCUPIED 2
#define SEAT_MISSING_SELECTED SEAT_MISSING + 3
#define SEAT_FREE_SELECTED SEAT_FREE + 3
#define SEAT_OCCUPIED_SELECTED SEAT_OCCUPIED + 3

#define SEAT_AVAILABLE 1
#define SEAT_UNAVAILABLE 0

struct coordinate
{
  int row;
  int col;
};

void PrintMatrix(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols);
void PrintSeatMap(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols);
void CleanSeatMapOfSelection(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols);
uint8_t CheckSeatAvailability(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols, int row, int col);
void BookSeats(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols, int column, int row, int numberOfSeats);
int GetInt(const char *prompt);
int GetColumnIndex(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int row, int col);
int GetRowIndex(int rows, int row);
int main(void)
{
  uint8_t cinemaHall[NUM_OF_ROWS][NUM_OF_COLS] =
      {{2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1},
       {0, 0, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1},
       {0, 0, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1},
       {0, 0, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1},
       {0, 0, 1, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1},
       {0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 0},
       {0, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 0},
       {0, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 0},
       {0, 0, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 0, 0},
       {0, 0, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0},
       {0, 0, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 1, 0, 0},
       {0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0},
       {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
       {0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 0, 0, 0}};

  int userStaisfied = 0;

  PrintMatrix(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);

  while (userStaisfied == 0)
  {
    PrintSeatMap(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);

    int userReadableRow = GetInt(COLOR_YELLOW "Enter row: " COLOR_RESET);
    int userReadableCol = GetInt(COLOR_YELLOW "Enter column: " COLOR_RESET);

    int row = GetRowIndex(NUM_OF_ROWS, userReadableRow);
    int column = GetColumnIndex(cinemaHall, row, userReadableCol);

    if (column == -1)
      return 1;

    printf(COLOR_YELLOW "Selected seat: Row %d (%d), Column %d (%d)\n" COLOR_RESET, userReadableRow, row, userReadableCol, column);

    if (CheckSeatAvailability(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS, row, column) == SEAT_UNAVAILABLE)
    {
      printf(COLOR_RED "Selected seat is unavailable.\n");
      continue;
    };

    int numberOfSeats = GetInt(COLOR_YELLOW "Enter number of seats you want to book: ");

    BookSeats(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS, row, column, numberOfSeats);

    PrintSeatMap(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);

    if (GetInt(COLOR_YELLOW "Are you sure, you want to book these seats? [1 - yes; 0 - no]: " COLOR_RESET) == 1)
    {
      userStaisfied = 1;
    }

    CleanSeatMapOfSelection(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
  }

  return 0;
}

void CleanSeatMapOfSelection(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (data[i][j] == SEAT_FREE_SELECTED)
      {
        data[i][j] = SEAT_FREE;
      }
    }
  }
}

int GetColumnIndex(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int row, int col)
{
  for (int i = 0; i < NUM_OF_COLS; i++)
  {
    if (data[row][i] != SEAT_MISSING)
    {
      return i + col - 1;
    }
  }
  return -1;
}
int GetRowIndex(int rows, int row)
{
  return rows - row;
}

void PrintMatrix(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols)
{
  printf("\n");
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      printf("%" PRId8 " ", data[i][j]);
    }
    printf("\n\n");
  }
}

void PrintSeatMap(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols)
{
  for (int row = 0; row < rows; row++)
  {
    printf(COLOR_RESET "%2d ", rows - row);
    int seatNumber = 1;
    for (int col = 0; col < cols; col++)
    {
      switch (data[row][col])
      {
      case SEAT_MISSING:
        printf("    ");
        break;
      case SEAT_OCCUPIED:
        printf(COLOR_RED "  X " COLOR_RESET);
        seatNumber++;
        break;
      case SEAT_FREE:
        printf(COLOR_GREEN "%3d " COLOR_RESET, seatNumber);
        seatNumber++;
        break;
      case SEAT_FREE_SELECTED:
        printf(COLOR_YELLOW "%3d " COLOR_RESET, seatNumber);
        seatNumber++;
        break;
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

uint8_t CheckSeatAvailability(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols, int row, int col)
{
  printf("Checking availability for seat at row %d, column %d... [%d]\n", row, col, data[row][col]);
  if (data[row][col] != SEAT_FREE)
  {
    return SEAT_UNAVAILABLE;
  }
  return SEAT_AVAILABLE;
}

int GetInt(const char *prompt)
{
  int num;
  printf("%s", prompt);
  while (scanf("%d", &num) != 1)
  {
    printf("Invalid input. Please enter an integer: ");
    while (getchar() != 10)
      ;
  }
  printf("\n");
  return num;
}

uint8_t AreConsecutiveSeatsAvailable(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int row, int col, int numberOfSeats)
{
  for (int i = 0; i < numberOfSeats; i++)
  {
    switch (data[row][col + i])
    {
    case SEAT_OCCUPIED:
    case SEAT_MISSING:
    case SEAT_FREE_SELECTED:
      return SEAT_UNAVAILABLE;
    default:
      break;
    }
  }
  return SEAT_AVAILABLE;
}

void BookConsecutiveSeats(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int row, int col, int numberOfSeats)
{
  for (int i = 0; i < numberOfSeats; i++)
  {
    data[row][col + i] = SEAT_FREE_SELECTED;
  }
  printf("Seats booked successfully.\n");
}

void BookSeats(uint8_t data[NUM_OF_ROWS][NUM_OF_COLS], int rows, int cols, int row, int col, int numberOfSeats)
{
  if (numberOfSeats > 1)
  {
    for (int i = -numberOfSeats+1; i < numberOfSeats-1; i++)
    {
      if (AreConsecutiveSeatsAvailable(data, row, col + i, numberOfSeats) == SEAT_AVAILABLE)
      {
        BookConsecutiveSeats(data, row, col + i, numberOfSeats);
        break;
      }
    }
  }
  else
  {
    if (CheckSeatAvailability(data, rows, cols, row, col) == SEAT_AVAILABLE)
    {
      data[row][col] = SEAT_FREE_SELECTED;
    }
  }

  printf("Seat(s) booked successfully.\n");
}