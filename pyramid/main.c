#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NOT_MIRROR 1

int count_digits(int n);
void printEverythingWithPrintfFormatting(int size);

int main()
{
  unsigned int size;
  printf("Input tower size: ");
  scanf("%d", &size);
  printEverythingWithPrintfFormatting(size);
  return 0;
  // printf(" O\n-|-\n |\n/ \\");
  // int rowCount = 2;
  // int total_len = count_digits((size * 2) + (size * size / 2));
  // int row_len = count_digits(size);
  // printf("%*s %*s\n", size + 3, "row", total_len + 4, "total");
  // int total = 0;
  // for (int i = 0; i < size; ++i)
  // {
  //   printf("##");
  //   for (int j = 0; j < size; ++j)
  //   {
  //     if (j <= i)
  //     {
  //       printf("#");
  //       rowCount++;
  //     }
  //     else
  //     {
  //       printf(" ");
  //     }
  //   }
  //   total += rowCount;
  //   printf(" %*d     %*d\n", row_len, rowCount, total_len, total);

  //   rowCount = 2;
  // }
}

int count_digits(int n)
{
  if (n == 0)
    return 1;

  int count = 0;
  while (n > 0)
  {
    n /= 10;
    count++;
  }
  return count;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

void printEverythingWithPrintfFormatting(int size)
{
#if NOT_MIRROR
  printf(" O\n-|-\n |\n/ \\");
  int row_len = max(count_digits(size), 4);
  int total_len = max(count_digits((size * 2) + (size * size / 2)), 7);
  int total_count = 3;
  char *row = (char *)malloc((size + 1) * sizeof(char));
  row[0] = '#';
  row[1] = '#';
  row[size] = '\0';

  printf("%-*s  %*s  %*s\n", size, "",
         row_len, "row",
         total_len, "total");

  for (int i = 3; i <= size; i++)
  {
    row[i-1] = '#';
    printf("%-*s  %*d  %*d\n", size + 3, row,
           row_len + 1, i,
           total_len + 2, total_count);
    total_count += i+1;
  }

  free(row);
#else
  printf("%*s%*s%*s%*s",size+1," O \n",size+1,"-|-\n",size+1," | \n",size,"/ \\");
  int row_len = max(count_digits(size), 4);
  int total_len = max(count_digits((size * 2) + (size * size / 2)), 7);
  int total_count = 3;
  char *row = (char *)malloc((size + 1) * sizeof(char));
  for (int u=0;u<size+1;u++) row[u]=' ';
  row[size] = '\0';
  row[size-1] = '#';
  row[size-2] = '#';

  printf("%*s  %*s\n",
         row_len, "row",
         total_len, "total");

  for (int i = 3; i <= size; i++)
  {
    row[size-i] = '#';
    printf("%s  %*d  %*d\n", row,
           row_len-2, i,
           total_len, total_count);
    total_count += i+1;
  }

  free(row);
#endif
}
