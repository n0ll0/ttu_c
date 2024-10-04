/**
 * File:        4_3_timetable_template.c
 * Author:      Risto Heinsar
 * Created:     21.09.2023
 * Last edit:   24.09.2023
 *
 * Description: Starter code for the functions lab task, generating an
 *              appointment schedule for clients.
 */

/**
******************************************************************************
* @file main.c
* @author n0ll0
* @version 0.1
* @date 01.10.2024
* @brief Generating an appointment schedule for clients
******************************************************************************
*/
#include <stdio.h>

#define WORKDAY_START_HOUR 8
#define WORKDAY_START_MIN 0
#define WORKDAY_END_HOUR 17
#define WORKDAY_END_MIN 0
#define WORKDAY_BREAK_HOUR 0
#define WORKDAY_BREAK_MIN 10

#define MAX_SESSION_LENGTH (WORKDAY_END_HOUR * 60 + WORKDAY_END_MIN) - (WORKDAY_START_HOUR * 60 + WORKDAY_START_MIN)

void PrintTime(int hour, int min);
int GetPositiveInt();
void PrintTimetable(
    int startHour,
    int startMin,
    int nClients,
    int appLen,
    int breakHour,
    int breakMin,
    int workDayStartHour,
    int workDayStartMin,
    int workDayEndHour,
    int workDayEndMin);

int main(void)
{
    printf("Workday starts at ");
    PrintTime(WORKDAY_START_HOUR, WORKDAY_START_MIN);
    printf("\n\n");

    printf("Enter num of clients\n");
    int clients = GetPositiveInt();

    printf("Enter client session length\n");
    int sessionLength = GetPositiveInt();

    if (sessionLength > MAX_SESSION_LENGTH)
    {
        printf("Session length is at max %d minutes ",
               (MAX_SESSION_LENGTH));
        printf("\n");
        return 1;
    }

    PrintTimetable(
        WORKDAY_START_HOUR,
        WORKDAY_START_MIN,
        clients,
        sessionLength,
        WORKDAY_BREAK_HOUR,
        WORKDAY_BREAK_MIN,
        WORKDAY_START_HOUR,
        WORKDAY_START_MIN,
        WORKDAY_END_HOUR,
        WORKDAY_END_MIN);

    return 0;
}

/**
 * Boolean comparisson function
 */
int isPositiveInt(int a)
{
    return a > 0;
}

/**
 * self explanatory
 */
void empty_function() {};

void PrintErrorAfterFailure()
{
    printf("Please input a positive integer!\n");
};

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
    int result;

    while (scanf("%d", &result) != 1 || result < 1)
    {
        printf("Please enter a positive integer: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    return result;
}

// only for positive integers!
int better_int_div(int numerator, int denominator)
{
    if (numerator < denominator)
        return 0;
    return numerator / denominator;
};

int GetHourFromTs(int timestamp)
{
    return timestamp / 60;
}
int GetMinFromTs(int timestamp)
{
    return timestamp % 60;
}
int GetTimestamp(int hours, int minutes)
{
    return hours * 60 + minutes;
}

// int CalcNextTimestamp(int cTimestamp, int interval)
// {
//     // Calculate new time in minutes
//     int newTimestamp = cTimestamp + interval;

//     return newTimestamp;
// }

/**
 * Description:    Finds the hour value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *                 breakMin - how long a break is after each appointment
 *                 breakHour - how long a break is after each appointment
 *                 workDayStartHour - start of the workday
 *                 workDayStartMin - start of the workday
 *                 workDayEndHour - end of the workday
 *                 workDayEndMin - end of the workday
 *
 * Return:         Hour value after adding the period
 */
/*int CalcNextHour(
    int cTimestamp,
    int interval,
    int workDayStartTimestamp,
    int workDayEndTimestamp)
{
    int newTimestamp = CalcNextTimestamp(
        cTimestamp,
        interval,
        workDayStartTimestamp,
        workDayEndTimestamp);

    return GetHourFromTimestamp(newTimestamp);
}*/

/**
 * Description:    Finds the minute value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *                 breakMin - how long a break is after each appointment
 *                 breakHour - how long a break is after each appointment
 *                 workDayStartHour - start of the workday
 *                 workDayStartMin - start of the workday
 *                 workDayEndHour - start of the workday
 *                 workDayEndMin - start of the workday
 *
 * Return:         Minute value after adding the period
 */
/*int CalcNextHour(
    int cTimestamp,
    int interval,
    int workDayStartTimestamp,
    int workDayEndTimestamp)
{
    int newTimestamp = CalcNextTimestamp(
        cTimestamp,
        interval,
        workDayStartTimestamp,
        workDayEndTimestamp);

    return GetMinFromTimestamp(newTimestamp);
}*/

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
void PrintTimeInterval(
    int startHour,
    int startMin,
    int endHour,
    int endMin)
{
    PrintTime(startHour, startMin);
    printf(" - ");
    PrintTime(endHour, endMin);
}

int count_digits(int n)
{
    if (n == 0)
        return 1;

    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

/**
 * Description:    Prints the timetable for the client appointments
 *
 * Parameters:     startHourstartHour - Start of the work day (hours)
 *                 startMinstartMin - Start of the workday (minutes)
 *                 nClientsnClients - number of clients to schedule an 
 *                                    appointment for
 *                 appLenappLen - appointment length
 *                 breakHour - break hour
 *                 breakMin - break minute
 *                 workDayStartHour - work day start hour
 *                 workDayStartMin - work day start min
 *                 workDayEndHour - work day end hour
 *                 workDayEndMin - work day end min
 *
 * Return:         -
 */
void PrintTimetable(
    int startHour,
    int startMin,
    int nClients,
    int appLen,
    int breakHour,
    int breakMin,
    int workDayStartHour,
    int workDayStartMin,
    int workDayEndHour,
    int workDayEndMin)
{
    int nTs = GetTimestamp(startHour, startMin);
    int breakTime = GetTimestamp(breakHour, breakMin);
    int wStartTs = GetTimestamp(workDayStartHour, workDayStartMin);
    int wEndTs = GetTimestamp(workDayEndHour, workDayEndMin);
    int clientPadding = count_digits(nClients);
    int nextTs = nextTs + appLen + breakTime;

    int day = 1;
    printf("\nDay %d\n", day);
    for (int client = 0; client < nClients; client++)
    {
        nextTs = nTs + appLen;
        if (nextTs > wEndTs)
        {
            day++;
            nTs = wStartTs;
            nextTs = nTs + appLen;
            printf("\nDay %d\n", day);
        }
        printf("\tClient %*d:\t\t", clientPadding, client);
        PrintTimeInterval(
            GetHourFromTs(nTs),
            GetMinFromTs(nTs),
            GetHourFromTs(nextTs),
            GetMinFromTs(nextTs));
        printf("\n");
        nTs = nextTs + breakTime;
    }
}
