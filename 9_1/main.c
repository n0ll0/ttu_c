#include <stdio.h>
#include <inttypes.h>

#define SIZE 7

void ReadMatrix(int matrix[SIZE][SIZE], int rows, int cols);
void PrintMatrix(int data[SIZE][SIZE], int rows, int cols);
int64_t MainDiagonalNegSum(int data[SIZE][SIZE], int rows, int cols);
int64_t AboveSecondaryDiagonalPosProduct(int data[SIZE][SIZE], int rows, int cols);
void FindMaxInRows(int data[SIZE][SIZE], int rows, int cols);

int main(void)
{
    int matrix[SIZE][SIZE];

    ReadMatrix(matrix, SIZE, SIZE);

    PrintMatrix(matrix, SIZE, SIZE);

    int64_t sum = MainDiagonalNegSum(matrix, SIZE, SIZE);
    printf("Sum of main diagonal elements with negative values: %" PRId64 "\n", sum);

    int64_t secondaryProduct = AboveSecondaryDiagonalPosProduct(matrix, SIZE, SIZE);
    printf("Sum of secondary diagonal elements with positive values: %" PRId64 "\n", secondaryProduct);

    FindMaxInRows(matrix, SIZE, SIZE);

    return 0;
}

/**
 * Description:    Reads a 2-dimensional array with size of rows x cols
 *                 from the standard input stream stdin.
 *
 * Parameters:     data - 2-dim array that needs to be read
 *                 rows - number of rows in data
 *                 cols - number of columns in data
 *
 * Return:         None
 */
void ReadMatrix(int data[SIZE][SIZE], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            // printf("Enter value for matrix[%d][%d] = ", i, j);
            scanf("%d", &data[i][j]);
        }
    }
}

void PrintMatrix(int data[SIZE][SIZE], int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%3d ", data[i][j]);
        }
        printf("\n");
    }
}

int64_t MainDiagonalNegSum(int data[SIZE][SIZE], int rows, int cols)
{
    int64_t sum = 0;
    for (int i = 0; i < rows && i < cols; i++)
    {
        if (data[i][i] < 0)
        {
            sum += data[i][i];
        }
    }
    return sum;
}

int64_t AboveSecondaryDiagonalPosProduct(int data[SIZE][SIZE], int rows, int cols)
{
    int64_t product = 1;
    int found = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - i - 1; j++)
        {
            if (data[i][j] > 0)
            {
                product *= data[i][j];
                found = 1;
            }
        }
    }
    return found ? product : 0;
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
    int max = nums[0];
    for (int i = 1; i < len; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }
    return max;
}

void FindMaxInRows(int data[SIZE][SIZE], int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        int max = Max(data[i], rows);
        printf("Max in row %d: %d\n", i, max);
    }
}
