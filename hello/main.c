#include <stdio.h>

int main()
{
  int n;

  printf("Sisesta täisarv: ");
  scanf("%d", &n);

  if (n%2==0) {
    printf("Sisestatud arv on paaris!\n");
  } else {
    printf("Sisestatud arv on paaritu!\n");
  }

  return 0;
}
