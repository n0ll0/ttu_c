#include <stdio.h>
#include <math.h>

int count_digits(int n) {
  return ((int)floor(log10(n)))+1;
};

int main()
{
  unsigned int size;
  printf("Input tower size: ");
  scanf("%d", &size);
  printf(" O\n-|-\n |\n/ \\");
  int rowCount = 2;
  int total_len = count_digits((size * 2) + (size * size / 2));
  int row_len = count_digits(size);
  printf("%*s %*s\n", size+3, "row", total_len+4, "total");
  int total = 0;
  for (int i = 0; i < size; ++i)
  {
    printf("##");
    for (int j = 0; j < size; ++j)
    {
      if (j <= i)
      {
        printf("#");
        rowCount++;
      }
      else
      {
        printf(" ");
      }
    }
    total += rowCount;
    printf(" %*d     %*d\n", row_len, rowCount, total_len, total);
    
    rowCount = 2;
  }
}
