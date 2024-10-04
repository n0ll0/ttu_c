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

void ReadIntArray(int nums[], size_t len);
void PrintArray(int nums[], size_t len);
int Min(int nums[], size_t len);
int Max(int nums[], size_t len);
int CountNumbers(int nums[], size_t len, int val);
void PrintPositions(int nums[], size_t len, int val);
int Sum(int nums[], size_t len);
long Product(int nums[], size_t len);
double ArithmeticMean(int nums[], size_t len);

int main(void)
{
    size_t length;
    printf("How many numbers wil you enter?: ");
    scanf("%ld", &length);
    int nums[length];

    ReadIntArray(nums, length);
    PrintArray(nums, length);

    printf("\n");

    int min = Min(nums, length);
    printf("Min value is: %d\n", min);
    printf("Min value position(s) is/are: ");
    PrintPositions(nums, length, min);
    printf("\nMin value occurred %d times\n\n", CountNumbers(nums, length, min));

    int max = Max(nums, length);
    printf("Max value is: %d\n", max);
    printf("Max value position(s) is/are: ");
    PrintPositions(nums, length, max);
    printf("\nMax value occurred %d times\n\n", CountNumbers(nums, length, max));

    printf("Sum is: %d\n", Sum(nums, length));
    printf("Product is: %ld\n", Product(nums, length));
    printf("Arithmetic mean is: %.3lf\n\n", ArithmeticMean(nums, length));

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
void ReadIntArray(int nums[], size_t len)
{
    for (int i = 0; i < len; i++)
    {
        int number;
        printf("Enter number %d / %ld: ", i + 1, len);
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
void PrintArray(int nums[], size_t len)
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
int Max(int nums[], size_t len)
{
    int max = -2147483648;
    for (int i = 1; i < len; i++)
    {
        if (nums[i] > max)
            max = nums[i];
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
int Min(int nums[], size_t len)
{
    int min = 2147483647;

    for (int i = 1; i < len; i++)
    {
        if (nums[i] < min)
            min = nums[i];
    }
    return min;
}

/**
 * Description:  Counts the number of times val is present in the array
 *
 * Parameters:   nums - values that are checked
 *               len - length of the array
 *               val - value to search for
 *
 * Return:       number of times val occurred in array
 */
int CountNumbers(int nums[], size_t len, int val)
{
    int count = 0;
    for (int n = 0; n < len; ++n)
    {
        if (nums[n] == val)
            count++;
    }
    return count;
}

/**
 * Description:  Prints all positions of val in the array. Shows positions
 *               (starting from 1), instead of indexes.
 *
 * Parameters:   nums - values that are checked
 *               len - length of the array
 *               val - value for which the positions will be printed
 *
 * Return:       -
 */
void PrintPositions(int nums[], size_t len, int val)
{
    for (int pos = 0; pos < len; ++pos)
    {
        if (nums[pos] == val)
            printf("%d ", pos);
    }
};

int Sum(int nums[], size_t len)
{
    int sum = nums[0];
    for (int i = 1; i < len; i++)
        sum += nums[i];
    return sum;
};

long Product(int nums[], size_t len)
{
    long product = (long)nums[0];
    for (int i = 1; i < len; i++)
        product *= (long)nums[i];
    return product;
};

double ArithmeticMean(int nums[], size_t len)
{
    return (double)Sum(nums, len) / (double)len;
};
