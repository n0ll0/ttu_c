/**
 * File:        4_3_timetable_template.c
 * Author:      Risto Heinsar
 * Created:     21.09.2023
 * Last edit:   24.09.2023
 *
 * Description: Starter code for the functions lab task, generating an
 *              appointment schedule for clients.
 */
#include <stdio.h>
#include "../input.c"

#define WORKDAY_START_HOUR 8
#define WORKDAY_START_MIN 0

void PrintTime(int hour, int min);

int GetPositiveInt();

void PrintTimetable(int startHour, int startMin, int nClients, int appLen);

int main(void)
{
    printf("Workday starts at ");
    PrintTime(WORKDAY_START_HOUR, WORKDAY_START_MIN);
    printf("\n\n");

    printf("Enter num of clients\n");
    int clients = GetPositiveInt();

    printf("Enter client session length\n");
    int sessionLength = GetPositiveInt();

    PrintTimetable(WORKDAY_START_HOUR, WORKDAY_START_MIN, clients, sessionLength);

    return 0;
}

int isPositiveInt(int a)
{
    return a > 0;
}

void emptyFn() {};

/**
 * Description:    Returns a positive integer from the user. On non-positive
 *                 input, gives an error and reprompts the user
 *
 * Parameters:     -
 *
 * Return:         Positive integer entered by the user
 */
int GetPositiveInt()
{
    return read_int(emptyFn, isPositiveInt);
}

int better_int_div(int numerator, int denominator) // only for positive integers!
{
    if (numerator < denominator)
        return 0;
    return numerator / denominator;
};

/**
 * Description:    Finds the hour value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *
 * Return:         Hour value after adding the period
 */
int CalcNextHour(int cMin, int cHour, int interval)
{
    return (cHour + better_int_div(cMin + interval, 60))%24;
}

/**
 * Description:    Finds the minute value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *
 * Return:         Minute value after adding the period
 */
int CalcNextMin(int cMin, int cHour, int interval)
{
    return (cMin + interval) % 60;
}

/**
 * Description:    Prints the time passed using hh:mm format. Hour values below
 *                 10 are space-padded and minue values below 10 are zero-padded
 *
 * Parameters:     hour - current hour value
 *                 min - current minute value
 *
 * Return:         -
 */
void PrintTime(int hour, int min)
{
    printf("%02d:%02d", hour, min);
}

/**
 * Description:    Prints a time interval using hh:mm - hh:mm format.
 *
 * Parameters:     startHour - Starting hour value
 *                 startMin - Starting minute value
 *                 endHour - End hour value
 *                 endMin - End minute value
 *
 * Return:         -
 */
void PrintTimeInterval(int startHour, int startMin, int endHour, int endMin)
{
    PrintTime(startHour, startMin);
    printf(" - ");
    PrintTime(endHour, endMin);
}

/**
 * Description:    Prints the timetable for the client appointments
 *
 * Parameters:     startHour - Start of the work day (hours)
 *                 startMin - Start of the workday (minutes)
 *                 nClients - number of clients to schedule an appointment for
 *                 appLen - appointment length
 *
 * Return:         -
 */
void PrintTimetable(int startHour, int startMin, int nClients, int appLen)
{
    int nHour = startHour;
    int nMin = startMin;
    for (int cl = 0; cl < nClients; cl++)
    {
        nHour = CalcNextHour(nMin, nHour, appLen);
        nMin = CalcNextMin(nMin, nHour, appLen);
        PrintTimeInterval(nHour, nMin, CalcNextHour(nMin, nHour, appLen), CalcNextMin(nMin, nHour, appLen));
        printf("\n");
    }
}
