/**
 * File:        4_2_sequence_gen_template.c
 * Author:      Risto Heinsar
 * Created:     20.09.2023
 * Last edit:   23.09.2023
 *
 * Description: Starter code for functions lab task that generates numerical
 *              sequences.
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* With for the divider line and menu */
#define WIDTH 65

/* Functions for visuals */
void PrintSeparator(int width);
void PrintMenu(int width);
void PrintAsciiWelcomeMsg(void);

/* Functions to handle arithmetic sequence */
void ArithmeticSequence(void);
void ArithmeticSequenceGenerator(float start, float diff, int cnt);

/* Functions to handle geometric sequence */
void GeometricSequence(void);
void GeometricSequenceGenerator(float start, float ratio, int cnt);

/* Functions to handle prime sequence */
void PrimeSequence(void);
void PrimeSequenceGenerator(int bounds);

int main(void)
{
    int option;

    PrintAsciiWelcomeMsg();
    PrintSeparator(WIDTH);

    /* TODO: Call the PrintMenu() function */
    PrintMenu(WIDTH);

    PrintSeparator(WIDTH);

    printf("Enter selection\n> ");
    scanf("%d", &option);

    PrintSeparator(WIDTH);

    /* Process the user action */
    switch (option)
    {
    case 0:
        printf("Exiting the program...\n");
        break;
    case 1:
        ArithmeticSequence();
        break;
    case 2:
        GeometricSequence();
        break;
    case 3:
        PrimeSequence();
        break;
    default:
        printf("Unknown option!\n");
    }

    PrintSeparator(WIDTH);

    return 0;
}

/**
 * Description:    Starting point for the arithmetic sequence calculator.
 *                 Prompts user for the inputs required
 *                 and calls ArithmeticSequenceGenerator()
 *
 * Parameters:     -
 *
 * Return:         -
 */
void ArithmeticSequence(void)
{
    float start, diff;
    int cnt;

    /* Header for this generation */
    printf("Arithmetic sequence generator\n");
    PrintSeparator(WIDTH);

    /* Get user input for the generator parameters */
    printf("Enter the first number in the sequence: ");
    scanf("%f", &start);
    printf("Enter the common difference: ");
    scanf("%f", &diff);
    printf("Enter the number of terms to generate: ");
    scanf("%d", &cnt);

    /* Call the generator with user specified parameters */
    ArithmeticSequenceGenerator(start, diff, cnt);
}

/**
 * Description:    Starting point for the geometric sequence calculator.
 *                 Prompts user for the inputs required
 *                 and calls GeometricSequenceGenerator()
 *
 * Parameters:     -
 *
 * Return:         -
 */
void GeometricSequence(void)
{
    float start, ratio;
    int cnt;

    /* Header for this generation */
    printf("Geometric sequence generator\n");
    PrintSeparator(WIDTH);

    /* Get user input for the generator parameters */
    printf("Enter the first number in the sequence: ");
    scanf("%f", &start);
    printf("Enter the common ratio: ");
    scanf("%f", &ratio);
    printf("Enter the number of terms to generate: ");
    scanf("%d", &cnt);

    /* Call the generator with user specified parameters */
    GeometricSequenceGenerator(start, ratio, cnt);
}

void PrimeSequence(void)
{
    int bounds;

    /* Header for this generation */
    printf("Prime sequence generator\n");
    PrintSeparator(WIDTH);

    printf("Enter the upper bound integer: ");
    scanf("%d", &bounds);

    /* Call the generator with user specified parameters */
    PrimeSequenceGenerator(bounds);
}

/**
 * Description:    Generates and prints an arithmetic sequence
 *
 * Parameters:     start - first number in the sequence
 *                 difference - common difference for the sequence
 *                 cnt - number of members to generate
 *
 * Return:         -
 */
void ArithmeticSequenceGenerator(float start, float diff, int cnt)
{
    char buffer[WIDTH] = "";
    char temp[20];
    printf("Results:\n");
    for (int i = 0; i < cnt; i++)
    {
        snprintf(temp, sizeof(temp), "%.2f ", start);
        if (strlen(buffer) + strlen(temp) >= WIDTH)
        {
            puts(buffer);
            buffer[0] = '\0';
        }
        strcat(buffer, temp);
        start += diff;
    }
    puts(buffer);
    printf("\n");
}

/**
 * Description:    Generates and prints a geometric sequence
 *
 * Parameters:     start - first number in the sequence
 *                 ratio - common ratio for the sequence
 *                 cnt - number of members to generate
 *
 * Return:         -
 */
void GeometricSequenceGenerator(float start, float ratio, int cnt)
{
    char buffer[WIDTH] = "";
    char temp[20];
    printf("Results:\n");
    for (int i = 0; i < cnt; i++)
    {
        snprintf(temp, sizeof(temp), "%.2f ", start);
        if (strlen(buffer) + strlen(temp) >= WIDTH)
        {
            puts(buffer);
            buffer[0] = '\0';
        }
        strcat(buffer, temp);
        start *= ratio;
    }
    puts(buffer);
    printf("\n");
}

int isPrime(int n)
{
    int i = 2;
    int check = sqrt(n);
    for (; i <= check; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void PrimeSequenceGenerator(int bounds)
{
    // for (int i = 2; i<bounds; i++)
    // {
    //     if (isPrime(i))
    //     {
    //         printf("%d ", i);
    //     }
    // }
    char buffer[WIDTH] = "";
    char temp[20];
    printf("Prime numbers:\n");
    for (int num = 2; num < bounds; num++) {
        if (isPrime(num)) {
            snprintf(temp, sizeof(temp), "%d ", num);
            if (strlen(buffer) + strlen(temp) >= WIDTH) {
                puts(buffer);
                buffer[0] = '\0'; // Reset buffer
            }
            strcat(buffer, temp);
        }
    }
    puts(buffer); // Print remaining content
    printf("\n");
}

/**
 * Description:    Prints a greeting message
 *
 * Parameters:     -
 *
 * Return:         -
 */
void PrintAsciiWelcomeMsg(void)
{
    /* TODO: add ASCII art */
    printf("\n  ________                                   __\n\
 /  _____/  ____   ____   ________________ _/  |_  ___________\n\
/   \\  ____/ __ \\ /    \\_/ __ \\_  __ \\__  \\\\   __\\/  _ \\_  __ \\\n\
\\    \\_\\  \\  ___/|   |  \\  ___/|  | \\// __ \\|  | (  <_> )  | \\/\n\
 \\______  /\\___  >___|  /\\___  >__|  (____  /__|  \\____/|__|\n\
        \\/     \\/     \\/     \\/           \\/\n\n");
}

/**
 * Description:    Prints the menu according to the allowed max width
 *
 * Parameters:     width - line width
 *
 * Return:         -
 */
void PrintMenu(int width)
{
    const int paddingLeft = 3;
    const int paddingRight = 2;

    /* Calculate area for a menu line text*/
    int textArea = width - (paddingLeft + paddingRight);

    /* Format: align left, give room up to 'textArea' characters, cut off
     *         anything that doesn't fit.
     */
    printf("#  %-*.*s #\n", textArea, textArea, "1 - Arithmetic sequence generator");
    printf("#  %-*.*s #\n", textArea, textArea, "2 - Geometric sequence generator");
    printf("#  %-*.*s #\n", textArea, textArea, "3 - Prime number generator");
    printf("#  %-*.*s #\n", textArea, textArea, "0 - exit");
}

/**
 * Description:    Prints a line with the specified width using # symbols
 *
 * Parameters:     width - line width
 *
 * Return:         -
 */
void PrintSeparator(int width)
{
    printf("\n");
    for (int i = 0; i < width; i++)
    {
        printf("#");
    }
    printf("\n\n");
}
