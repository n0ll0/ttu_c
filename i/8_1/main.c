/**
 * File:        8_1_date_base.c
 * Author:      Risto Heinsar
 * Created:     20.10.2014
 * Modified:    12.10.2023
 *
 * Description: Basecode for the date verification lab task. The code is
 *              intended to be used with stream redirection, so it doesn't
 *              write any prompts. It can be executed by just typing inputs
 *              from the keyboard. To stop entry and run the checks this way,
 *              press Ctrl+D (end of file signal) at any point during input.
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX 100

#define DATE_VALID 0
#define DATE_INVALID 1
#define DATE_INVALID_YEAR_OOB 2
#define DATE_INVALID_DAY_OOB 3
#define DATE_INVALID_FEB 4

bool IsLeapYear(int year);
int GetDaysInMonth(int month, int year);
int ValidateDate(int day, int month, int year);
int ReadDates(int day[], int month[], int year[], int max);
void PrintDates(int day[], int month[], int year[], int n);

int main(void)
{

  int day[MAX], month[MAX], year[MAX];
  int n = ReadDates(day, month, year, MAX);
  PrintDates(day, month, year, n);
  return 0;
}

/**
 * Description:    Reads in the dates to the day month and year arrays.
 *                 The same index in each of the arrays are used for the
 *                 same date.
 *
 * Parameters:     day - an array of day values
 *                 month -array of month values
 *                 year - array of year values
 *                 max - maximum size of the arrays.
 *
 * Return:         number of dates read by the program
 */
int ReadDates(int day[], int month[], int year[], int max)
{
  int count = 0;

  while (count < max && scanf("%2d%2d%4d", &day[count], &month[count], &year[count]) == 3)
  {
    ++count;
    if (getchar() == EOF)
      return count;
  }

  return count;
}

/**
 * Description:    Prints the dates in the arrays, assumes dates with
 *                 the same index in all three arrays are related.
 *
 * Parameters:     day - an array of day values
 *                 month -array of month values
 *                 year - array of year values
 *                 n - umber of dates in the arrays
 *
 * Return:         none
 */
void PrintDates(int day[], int month[], int year[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    int result = ValidateDate(day[i], month[i], year[i]);
    printf("%02d.%02d.%04d < %s\n", day[i], month[i], year[i],
           result == DATE_INVALID ? "Invalid date" :
           result == DATE_INVALID_YEAR_OOB? "Year out of bounds" :
           result == DATE_INVALID_DAY_OOB? "Day out of months bounds" :
           result == DATE_INVALID_FEB? "29th of February only exists on leap year!" :
           result == DATE_VALID ? "Ok" : "Ok");
  }
}

/**
 * Description:    Checks wheather the passed year is a leap year.
 *
 * Parameters:     year - the year to check
 *
 * Return:         true for leap year, false for normal year.
 */
bool IsLeapYear(int year)
{
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

/**
 * Description:    Function finds and returns the number of days in a month.
 *                 Month is given as an integer, starting from 1 (january).
 *                 Function handles leap years.
 *
 * Parameters:     month - month number starting from 1.
 *                 year - year number
 *
 * Return:         For valid dates, returns the number of days in a month.
 *                 For invalid dates, returns 0.
 *
 */
int GetDaysInMonth(int month, int year)
{
  if (month < 1 || month > 12)
    return 0;

  switch (month)
  {
  case 2:
    return IsLeapYear(year) ? 29 : 28;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  default:
    return 31;
  }
}

/**
 * Description:    Function finds if the date passed is valid or not.
 *
 * Parameters:     day - the day value.
 *                 month - month number starting from 1.
 *                 year - the year of the date
 *
 * Return:         For valid dates, returns DATE_VALID (0),
 *                 For invalid dates, returns DATE_INVALID (1).
 */
int ValidateDate(int day, int month, int year)
{
  // Hint: use the functions GetDaysInMonth
  // to assist in formulating the conditional statements
  // to validate the date.
  if (day < 1)
    return DATE_INVALID;
  if (year < 1900 || year >= 2100)
    return DATE_INVALID_YEAR_OOB;
  if (day > GetDaysInMonth(month, year))
    return DATE_INVALID_DAY_OOB;
  if (month == 2 && IsLeapYear(year) && day == 29)
    return DATE_INVALID_FEB;

  return DATE_VALID;
}
