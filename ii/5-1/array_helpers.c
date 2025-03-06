/**
 * File:         array_helpers.c
 * Author:       Risto Heinsar
 * Created:      10.02.2015
 * Modified:     25.02.2023
 *
 * Description:  Common helper functions to work with basic array types
 * .
 * Note:         Partial sample solution for array helpers.
 */
#include <stdio.h>
#include "array_helpers.h"


void PrintIntegerArray(int *numbers, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}


void PrintFloatArray(float *numbers, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%.2f ", numbers[i]);
    }
    printf("\n");
}


// TODO: implement the rest of the functions in the header

int ComparFuncInt(const void *x, const void *y) {
    int *a = x;
    int *b = y;
    return a - b;
}

int ComparFuncFloat(const void *x, const void *y) {
    float *a = x;
    float *b = y;
    return a - b;
}