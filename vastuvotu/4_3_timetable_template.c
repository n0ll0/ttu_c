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

#define WORKDAY_START_HOUR 8
#define WORKDAY_START_MIN 0
#define WORKDAY_END_HOUR 17
#define WORKDAY_END_MIN 0
#define WORKDAY_BREAK_HOUR 0
#define WORKDAY_BREAK_MIN 10

void PrintTime(int hour, int min);

int GetPositiveInt();

void PrintTimetable(int startHour, int startMin, int nClients, int appLen, int breakMin, int breakHour, int workDayStartHour, int workDayStartMin, int workDayEndHour, int workDayEndMin);

int read_int(void (*askFn)(), int (*validity_comparisson)(int), void (*ErrorFunction)());
float read_float(void (*askFn)(), int (*validity_comparisson)(float), void (*ErrorFunction)());

int main(void)
{
    printf("Workday starts at ");
    PrintTime(WORKDAY_START_HOUR, WORKDAY_START_MIN);
    printf("\n\n");

    printf("Enter num of clients\n");
    int clients = GetPositiveInt();

    printf("Enter client session length\n");
    int sessionLength = GetPositiveInt();

    PrintTimetable(WORKDAY_START_HOUR, WORKDAY_START_MIN, clients, sessionLength, WORKDAY_BREAK_MIN, WORKDAY_BREAK_HOUR, WORKDAY_START_HOUR, WORKDAY_START_MIN, WORKDAY_END_HOUR, WORKDAY_END_MIN);

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
    return read_int(emptyFn, isPositiveInt, emptyFn);
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
 *                 breakMin - how long a break is after each appointment
 *                 breakHour - how long a break is after each appointment
 *                 workDayStartHour - start of the workday
 *                 workDayStartMin - start of the workday
 *                 workDayEndHour - start of the workday
 *                 workDayEndMin - start of the workday
 *
 * Return:         Hour value after adding the period
 */
int CalcNextHour(int cMin, int cHour, int interval, int workDayStartHour, int workDayStartMin, int workDayEndHour, int workDayEndMin)
{
    // Calculate total minutes to add
    int totalMinutes = interval;

    // Calculate new time in minutes
    int newMinutes = cMin + totalMinutes;
    int newHour = cHour + newMinutes / 60;
    newMinutes %= 60;
    newMinutes %= 24;

    // Adjust for workday boundaries
    if ((newHour < workDayStartHour || (newHour == workDayStartHour && newMinutes < workDayStartMin)))
    {
        newHour = workDayStartHour;
        newMinutes = workDayStartMin;
    }

    return newHour;
}

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
int CalcNextMin(int cMin, int cHour, int interval, int workDayStartHour, int workDayStartMin, int workDayEndHour, int workDayEndMin)
{
    // Calculate total minutes to add
    int totalMinutes = interval;

    // Calculate new time in minutes
    int newMinutes = cMin + totalMinutes;
    int newHour = cHour + newMinutes / 60;
    newMinutes %= 60;

    // Adjust for workday boundaries
    if ((newHour < workDayStartHour || (newHour == workDayStartHour && newMinutes < workDayStartMin)))
    {
        newHour = workDayStartHour;
        newMinutes = workDayStartMin;
    }

    return newMinutes;
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
void PrintTimetable(
    int startHour,
    int startMin,
    int nClients,
    int appLen,
    int breakMin,
    int breakHour,
    int workDayStartHour,
    int workDayStartMin,
    int workDayEndHour,
    int workDayEndMin)
{
    int nHour = startHour;
    int nMin = startMin;
    int i = 1;
    printf("\n\tDay %d\n", i);

    for (int cl = 0; cl < nClients; cl++)
    {
        nHour = CalcNextHour(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin) + breakHour;
        nMin = CalcNextMin(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin) + breakMin;
        int nextHour = CalcNextHour(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin);
        int nextMin = CalcNextMin(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin);
        int liigapikk = nextHour * 60 + nextMin > (workDayEndHour * 60 + workDayEndMin);
        if ((nHour * 60 + nMin) > (workDayEndHour * 60 + workDayEndMin) || (liigapikk))
        {
            i++;
            nHour = workDayStartHour;
            nMin = workDayStartMin;
            printf("\n\tDay %d\n", i);
        }
        PrintTimeInterval(nHour, nMin, CalcNextHour(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin), CalcNextMin(nMin, nHour, appLen, workDayStartHour, workDayStartMin, workDayEndHour, workDayEndMin));
        printf("\n");
    }
}

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
