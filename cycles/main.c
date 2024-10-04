#include <stdio.h>
#include <stdlib.h>

int Sum(int *arr, unsigned int length)
{
  int sum = 0;
  for (int i = 0; i < length; ++i)
    sum += arr[i];
  return sum;
}

int main()
{
  printf("This program takes n many numbers from the user and adds them up. Subtotal is shown after each addition until the last one.\n\nEnter how many numbers will be inputted: ");
  int numberOfInputs;
  if (scanf("%d", &numberOfInputs) == -1)
    return 1;
  if (numberOfInputs < 1)
    return 1;

  int *inputs = (int *)malloc(numberOfInputs * sizeof(int));
  if (inputs == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  for (unsigned int i = 0; i < numberOfInputs; ++i)
  {
    int input;
    printf("Sisesta arv %d / %d: ", i + 1, numberOfInputs);
    if (scanf("%d", &input) == -1)
      return 1;
    inputs[i] = input;

    if (i < numberOfInputs - 1)
      printf("\nSubtotal: %d\n", Sum(inputs, i + 1));
  }

  printf("The final sum is: %d\n", Sum(inputs, numberOfInputs));

  free(inputs);

  return 0;
}
