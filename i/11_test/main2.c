#include <stdio.h>

#define MIN_KOGUS 2
#define MAX_KOGUS 64

int GetUserNumbInRange(int min, int max);
int IsNumInRange(int num, int min, int max);

int main()
{

    int arvudeKogus = GetUserNumbInRange(MIN_KOGUS, MAX_KOGUS);
    int arvud[64];
    int unikaalsed[64];
    for (size_t i = 0; i < arvudeKogus; i++)
    {
        int n;
        scanf("%d", &n);
        arvud[i] = n;
    }

    int unikaalseteArv = 0;

    for (size_t i = 0; i < arvudeKogus; i++)
    {
        int leitud = 0;
        for (size_t j = 0; j < unikaalseteArv; j++)
        {
            if (arvud[i] == arvud[j])
                leitud = 1;
        }
        if (leitud==0)
        {
            unikaalsed[unikaalseteArv] = arvud[i];
            ++unikaalseteArv;
        }

    }
    printf("\nUnikaalsed arvud: ");

    for (size_t i = 0; i < unikaalseteArv; i++)
    {
        printf("%d ", unikaalsed[i]);
    }

    printf("\narvude kogus: %d", arvudeKogus);
    printf("\nunikaalsete arvude kogus: %d", unikaalseteArv);
    printf("\nunikaalsete protsent: %d %%\n", (int)(((float)unikaalseteArv/(float)arvudeKogus)*100.0));

    return 0;
}

int GetUserNumbInRange(int min, int max)
{
  int num;
  do
  {
    printf("\nSisesta number vahemikus %d ja %d: ", min, max);
    scanf("%d", &num);
  } while (IsNumInRange(num, min, max) == 0);
  return num;
}

int IsNumInRange(int num, int min, int max)
{
  return num >= min && num <= max;
}



