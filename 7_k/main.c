#include <stdio.h>

#define PACKAGE_COUNT 5
#define TRACKING_CODE_LEN 8

int main(void)
{
  char packages[PACKAGE_COUNT][TRACKING_CODE_LEN + 1];
  float packageWeights[PACKAGE_COUNT];
  float ratioToMin, ratioToMax;
  int i, minInd, maxInd;

  for (i = 0; i < PACKAGE_COUNT; i++)
  {
    printf("Enter %d-character package tracking code (%d / %d): ",
           TRACKING_CODE_LEN,
           i + 1,
           PACKAGE_COUNT);
    scanf("%s", packages[i]);
    do
    {
      printf("Enter package (%s) weight in kg: ", packages[i]);
      scanf("%f", &packageWeights[i]);
    } while (packageWeights[i] <= 0);
  }
  printf("\n\n");

  for (minInd = maxInd = 0, i = 0; i < PACKAGE_COUNT; i++)
  {
    if (packageWeights[minInd] > packageWeights[i])
    {
      minInd = i;
    }
    else if (packageWeights[maxInd] < packageWeights[i])
    {
      maxInd = i;
    }
  }

  printf("Min is %s with weight %.3f\n", packages[minInd], packageWeights[minInd]);
  printf("Max is %s with weight %.3f\n\n", packages[maxInd], packageWeights[maxInd]);

  printf("%-*s %8s %7s %7s\n", TRACKING_CODE_LEN, "Code", "Weight", "To min", "To max");
  for (i = 0; i < PACKAGE_COUNT; i++)
  {
    ratioToMin = packageWeights[i] / packageWeights[minInd];
    ratioToMax = packageWeights[i] / packageWeights[maxInd];

    printf("%*s ", TRACKING_CODE_LEN, packages[i]);
    printf("%8.3f ", packageWeights[i]);
    printf("%7.2f %7.2f\n", ratioToMin, ratioToMax);
  }

  return 0;
}