/**
 * File:        5_minmax_template.c
 * Author:      Risto Heinsar
 * Created:     29.09.2023
 * Last edit:   29.09.2023
 *
 * Description: Starter code for arrays lab task. Allows the user to enter
 *              an array of integers, finds the min and max values in part 1.
 *              Finds the positions of the extreme values and the number of
 *              times they occur in the array in part 2.
 */
#include <stdio.h>
#define LENGTH 6

void ReadIntArray(int nums[], int len);
void PrintArray(int nums[], int len);
int Min(int nums[], int len);
int Max(int nums[], int len);

int main(void)
{
    int nums[LENGTH];

    ReadIntArray(nums, LENGTH);
    PrintArray(nums, LENGTH);

    printf("\n");
    printf("Min value is: %d\n", Min(nums, LENGTH));
    printf("Max value is: %d\n", Max(nums, LENGTH));

    return 0;
}

/**
 * Description:  Reads values from the user and stores them into the
 *               integer array provided
 *
 * Parameters:   nums - location to store values at
 *               len - length of the array
 *
 * Return:       -
 */
void ReadIntArray(int nums[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int number;
        printf("Enter number %d / %d: ", i + 1, len);
        scanf("%d", &number);
        nums[i] = number;
    }

    printf("\n");
}

/**
 * Description:  Prints all integers from the array on the same line, space
 *               separated.
 *
 * Parameters:   nums - values that are printed
 *               len - length of the array
 *
 * Return:       -
 */
void PrintArray(int nums[], int len)
{
    printf("Entered numbers:\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", nums[i]);
    }
}

/**
 * Description:  Find the maximum value from the nums array and returns it
 *
 * Parameters:   nums - values from which the max is searched in
 *               len - length of the array
 *
 * Return:       Maximum value in the nums array
 */
int Max(int nums[], int len)
{
    int max = -2147483648;
    for (int i = 1; i < len; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }
    return max;
}

/**
 * Description:  Find the minimum value from the nums array and returns it
 *
 * Parameters:   nums - values from which the min is searched in
 *               len - length of the array
 *
 * Return:       Minimum value in the array
 */
int Min(int nums[], int len)
{
    int min = 2147483647;

    for (int i = 1; i < len; i++)
    {
        if (nums[i] < min)
        {
            min = nums[i];
        }
    }
    return min;
}