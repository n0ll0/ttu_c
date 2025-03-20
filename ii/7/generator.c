/**
 * File:        generator.c
 * Author:      Risto Heinsar
 * Created:     12.03.2015
 * Modified     14.03.2023
 *
 * Description: This is a random data generator
 * 
 * Note:        This is a starter code for a lab task
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name_pools.h"
#include "generator.h"

int main(void)
{
    /* Names are assigned from the pools in the header*/
    const char *firstNames[] = FIRST_NAME_POOL;
    const char *lastNames[] = LAST_NAME_POOL;
    const char *curriculumCodes[] = CURRICULUM_CODES;

    /* Find the counts for the pool sizes */
    int firstNamePoolSize = sizeof(firstNames) / sizeof(char *);
    int lastNamePoolSize = sizeof(lastNames) / sizeof(char *);
    int curriculumCodePoolSize = sizeof(curriculumCodes) / sizeof(char *);

    printf("The database contains:\n"
           "\t%4d first names\n"
           "\t%4d last names\n"
           "\t%4d curriculum codes\n",
           firstNamePoolSize, lastNamePoolSize, curriculumCodePoolSize);




    return EXIT_SUCCESS;
}

/**
 * Description:    Generates a random number in range provided, ends inclusive
 *
 * Parameters:     min, minimum value
 *                 max, maximum vale
 *
 * Return:         integer, generated random number
 */
int GetRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}
