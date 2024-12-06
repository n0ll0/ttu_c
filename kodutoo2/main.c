/**
TEEMA: Matkarajad
On antud kaks massiivi – matkaradade massiiv ja kauguste massiiv (kaugused on antud kilomeetrites). Maksimaalselt on massiivides 15 elementi. Kasutaja käest küsitakse tundide arvu t.

Koosta programm, mis väljastab matkarajad kasvavas järjekorras ja etteantud aja jooksul läbitavad rajad.

Lahenduses kasuta funktsioone:
Massiivide lugemiseks
Matkaradade väljastamiseks
Matkaradade järjestamiseks kauguste põhjal (järjesta kaks massiivi korraga)
Radade ja pikkuste väljastamiseks
Radade leidmiseks, mida on võimalik läbida t tunniga (s = v * t, kus v = 5km/h)

NB! Tegu on minimaalse loeteluga funktsioonidest. Neid on mõistlik luua rohkem, vastavalt ülesande püstitusele ja sinu lahendusele!

Näide:
Loodav kood peaks toimima kui sellele anda ükskõik milline järgnevatest failidest. See peaks ka töötama ükskõik missuguse failiga, mis on loodud sama struktuuri, kuid erinevate väärtustega. Esimene number või numbrid tähistavad massiivi dimensiooni(de) pikkust. Sellele järgnevad massiivi liikmete väärtused. Kui ülesandes on ka küsitud täiendavat sisendit, siis need väärtused paikenvad pärast massiivide liikmeid.
081

082

Rajad: Keskmine, Ronimine, Pikk, Lyhike, Rada2, Mets, Soo3, Lyhike2, Varemed

Matkaradade pikkused:
1. rada: Ronimine pikkusega 3.10
2. rada: Lyhike pikkusega 3.73
3. rada: Lyhike2 pikkusega 3.81
4. rada: Mets pikkusega 4.92
5. rada: Soo3 pikkusega 5.05
6. rada: Varemed pikkusega 5.99
7. rada: Rada2 pikkusega 6.19
8. rada: Keskmine pikkusega 9.98
9. rada: Pikk pikkusega 17.52

Ajaga 1h saab läbida ühe radadest: Ronimine, Lyhike, Lyhike2, Mets
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 15
#define KIIRUS 5

struct Matkarada {
  char *nimi;
  double pikkus;
};

int ReadMatkarajad(struct Matkarada *arr);
void PrintMatkarada(struct Matkarada rada);
void RajadMidaSaabLabida(struct Matkarada *arr, int length, double hours, double speed);
void qs(struct Matkarada *arr, int low, int high);

int main(int argc, char const *argv[])
{
  struct Matkarada matkarajad[MAX_ITEMS];

  int length = ReadMatkarajad(matkarajad);
  printf("Rajad: ");
  for (int i = 0; i < length; i++)
  {
    printf("%s", matkarajad[i].nimi);
    if (i<length-1)
      printf(", ");
  }
  printf("\n");

  double tunnid;
  printf("\nSisesta tundide arv: ");
  scanf("%lf", &tunnid);
  printf("%lf\n", tunnid);

  qs(matkarajad, 0, length-1);

  // for (int i = 0; i < length; ++i)
  // {
  //   PrintMatkarada(matkarajad[i]);
  // }

  RajadMidaSaabLabida(matkarajad, length, tunnid, KIIRUS);

  return 0;
}

int ReadMatkarajad(struct Matkarada *arr)
{
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    char *nimi = calloc(100, sizeof(char));
    scanf("%s %lf", nimi, &arr[i].pikkus);
    arr[i].nimi = strdup(nimi);
  }
  return n;
}

void PrintMatkarada(struct Matkarada rada)
{
  printf("%s: %.2f", rada.nimi, rada.pikkus);
}

void RajadMidaSaabLabida(struct Matkarada *arr, int length, double hours, double speed)
{
  const int maxLength = speed * hours;
  printf("\nAjaga %.1f h saab läbida:\n", hours);
  for (int i = 0; i < length; i++)
  {
    if (arr[i].pikkus <= maxLength)
    {
      PrintMatkarada(arr[i]);
      printf("\n");
    }
  }
}

// this is something, that just works
void qs(struct Matkarada *arr, int low, int high)
{
  if (low < high)
  {
    double pivot = arr[(low + high) / 2].pikkus; // Selecting the middle element as the pivot
    int i = low;
    int j = high;
    struct Matkarada temp;

    while (i <= j)
    {
      // printf("1");
      while (arr[i].pikkus < pivot)
        i++; // Moving elements smaller than pivot to the left
      while (arr[j].pikkus > pivot)
        j--; // Moving elements greater than pivot to the right
      if (i <= j)
      {
        temp = arr[i]; // Swapping elements
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
      }
    }

    // Recursively sort the two partitions
    qs(arr, low, j);
    qs(arr, i, high);
  }
}
