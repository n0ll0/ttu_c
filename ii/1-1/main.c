/**
 * File:           t1_swap_template.c
 * Author:         Risto Heinsar
 * Created:        19.08.2014
 * Last edit:      29.01.2023
 *
 * Description:    Lab task template. 
 *                 Read and swap two numbers using pointers.
 */
 
#include <stdio.h>

// TODO: Write your prototypes for the functions here
void GetValues(int* a, int* b);
void Swap(int* a, int* b);


int main(void)
{
    int x, y;
    
    // TODO: Print the addresses of the variables
    printf("Addresses in function %s\n", __FUNCTION__);
    
    
    // TODO: Call your first function that scans for the values
    GetValues(&x, &y);
    
    
    // Print out the values to verify that the numbers are scanned correctly.
    printf("\n\nOriginal values in %s\nx = %d\ny = %d\n\n", __FUNCTION__, x, y);
    
    // TODO: Call the function that swaps the values
    Swap(&x, &y);
    
    // Print out the values to confirm that swapping worked
    printf("Updated values in %s\nx = %d\ny = %d\n", __FUNCTION__, x, y);
    return 0;
}


/**
 * Description:    Scan for two integer values and stores the values to the
 *                 locations passed as pointers. It will also print
 *                 out the two locations where the values are stored.
 *
 * Parameters:     a - pointer to the first value
 *                 b - pointer to the second value
 *
 * Return:         none
 */

// TODO: Write your function here!
void GetValues(int* a, int* b) {
    scanf("%d %d", a, b);
    printf("\n%p\n%p", a, b);
}


/**
 * Description:    Swaps the two values pointed by the pointers passed to this
 *                 function. It will also print out the locations of the two 
 *                 values that are being swapped.
 *
 * Parameters:     a - pointer to the first value
 *                 b - pointer to the second value
 *
 * Return:         none
 */

// TODO: Write your function here
void Swap(int* a, int* b) {
    printf("%p\n%p\n", a, b);
    int temp = *a;
    *a = *b;
    *b = temp;
}