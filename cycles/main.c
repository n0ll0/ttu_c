#include <stdio.h>
#include <stdlib.h>

int sum(int* arr, int length)
{
  int sum = 0;
  for (int i = 0; i < length; ++i)
    sum += arr[i];
  return sum;
}

int main()
{
  int numberOfInputs;
  if (scanf("%d", &numberOfInputs) == -1) return 1;
  if (numberOfInputs < 1)
    return 1;

  int* inputs = (int*)malloc(numberOfInputs * sizeof(int));

  for (int i = 0; i < numberOfInputs; ++i)
  {
    int input;
    printf("Sisesta arv %d / %d\n", i + 1, numberOfInputs);
    if (scanf("%d", &input) == -1) return 1;
    inputs[i] = input;

    printf("%d\n", sum(inputs, i+1));
  }

  free(inputs);

  return 0;
}
