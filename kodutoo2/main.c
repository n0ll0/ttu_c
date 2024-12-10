/**
 * TEEMA: Matkarajad
 * On antud kaks massiivi – matkaradade massiiv ja kauguste massiiv (kaugused on antud kilomeetrites). Maksimaalselt on massiivides 15 elementi. Kasutaja käest küsitakse tundide arvu t.
 *
 * Koosta programm, mis väljastab matkarajad kasvavas järjekorras ja etteantud aja jooksul läbitavad rajad.
 *
 * Lahenduses kasuta funktsioone:
 * Massiivide lugemiseks
 * Matkaradade väljastamiseks
 * Matkaradade järjestamiseks kauguste põhjal (järjesta kaks massiivi korraga)
 * Radade ja pikkuste väljastamiseks
 * Radade leidmiseks, mida on võimalik läbida t tunniga (s = v * t, kus v = 5km/h)
 *
 * NB! Tegu on minimaalse loeteluga funktsioonidest. Neid on mõistlik luua rohkem, vastavalt ülesande püstitusele ja sinu lahendusele!
 *
 * Näide:
 * Loodav kood peaks toimima kui sellele anda ükskõik milline järgnevatest failidest. See peaks ka töötama ükskõik missuguse failiga, mis on loodud sama struktuuri, kuid erinevate väärtustega. Esimene number või numbrid tähistavad massiivi dimensiooni(de) pikkust. Sellele järgnevad massiivi liikmete väärtused. Kui ülesandes on ka küsitud täiendavat sisendit, siis need väärtused paikenvad pärast massiivide liikmeid.
 * 081
 *
 * 082
 *
 * Rajad: Keskmine, Ronimine, Pikk, Lyhike, Rada2, Mets, Soo3, Lyhike2, Varemed
 *
 * Matkaradade pikkused:
 * 1. rada: Ronimine pikkusega 3.10
 * 2. rada: Lyhike pikkusega 3.73
 * 3. rada: Lyhike2 pikkusega 3.81
 * 4. rada: Mets pikkusega 4.92
 * 5. rada: Soo3 pikkusega 5.05
 * 6. rada: Varemed pikkusega 5.99
 * 7. rada: Rada2 pikkusega 6.19
 * 8. rada: Keskmine pikkusega 9.98
 * 9. rada: Pikk pikkusega 17.52
 *
 * Ajaga 1h saab läbida ühe radadest: Ronimine, Lyhike, Lyhike2, Mets
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HIKE_PATHS 15
#define MAX_NAME_LENGTH 20
#define KIIRUS 5

struct HikingPath
{
  char *nimi;
  double pikkus;
};

int ReadHikingPaths(struct HikingPath *arr, int max_paths, int max_name_length);
void PrintHikingPath(struct HikingPath rada);
void PathsCompletableWithinTimeWithSpeed(struct HikingPath *arr, int length,
                                         double hours, double speed);
void qs(struct HikingPath *arr, int low, int high);

int main(int argc, char const *argv[])
{
  struct HikingPath hikingPaths[MAX_HIKE_PATHS];

  int length = ReadHikingPaths(hikingPaths, MAX_HIKE_PATHS, MAX_NAME_LENGTH);
  printf("Rajad: ");
  for (int i = 0; i < length; i++)
  {
    printf("%s", hikingPaths[i].nimi);
    if (i < length - 1)
      printf(", ");
  }
  printf("\n");

  double hours;
  printf("\nSisesta tundide arv: ");
  scanf("%lf", &hours);
  printf("%lf\n", hours);

  qs(hikingPaths, 0, length - 1);

  // for (int i = 0; i < length; ++i)
  // {
  //   PrintHikingPath(hikingPaths[i]);
  // }

  PathsCompletableWithinTimeWithSpeed(hikingPaths, length, hours, KIIRUS);

  // free names memory
  for (size_t i = 0; i < length; i++)
  {
    free(hikingPaths[i].nimi);
  }

  return 0;
}

/**
 * @brief Reads hiking trail data from standard input and stores it in an array
 * of Matkarada structures.
 *
 * This function reads the number of hiking trails, followed by the name and
 * length of each trail.
 * It allocates memory for each trail name and stores the data in the provided
 * array.
 *
 * @param arr Pointer to an array of Matkarada structures where the trail data
 * will be stored.
 * @return The number of hiking trails read and stored in the array.
 */
int ReadHikingPaths(struct HikingPath *arr, int max_paths, int max_name_length)
{
  int n;
  fscanf(stdin, "%d", &n);

  if (0 > n && n > max_paths)
    exit(1);

  for (int i = 0; i < n; ++i)
  {
    char *nimi = calloc(max_name_length, sizeof(char));
    scanf("%s %lf", nimi, &arr[i].pikkus);
    arr[i].nimi = strdup(nimi);
  }
  return n;
}

void PrintHikingPath(struct HikingPath rada)
{
  fprintf(stdout, "%s: %.2f", rada.nimi, rada.pikkus);
}

/**
 * @brief Prints the hiking trails that can be completed within a given time.
 *
 * This function calculates the maximum distance that
 * can be covered in the given time
 * at the specified speed, and then prints all trails
 * from the array that are within
 * this distance.
 *
 * @param arr Pointer to an array of HikingPath structures
 * containing the hiking trails.
 * @param length The number of elements in the arr array.
 * @param hours The time available for hiking, in hours.
 * @param speed The hiking speed, in kilometers per hour.
 *
 * @return This function does not return a value.
 */
void PathsCompletableWithinTimeWithSpeed(struct HikingPath *arr, int length,
                                         double hours, double speed)
{
  const int maxLength = speed * hours;
  printf("\nAjaga %.1f h saab läbida:\n", hours);
  for (int i = 0; i < length; i++)
  {
    if (arr[i].pikkus <= maxLength)
    {
      PrintHikingPath(arr[i]);
      fprintf(stdout, "\n");
    }
  }
}

/** Quicksort implementation for sorting the trails by length
 * @link https://www.geeksforgeeks.org/quick-sort-in-c/
 */
void qs(struct HikingPath *arr, int low, int high)
{
  if (low < high)
  {
    // Selecting the middle element as the pivot
    double pivot = arr[(low + high) / 2].pikkus;
    int i = low;
    int j = high;
    struct HikingPath temp;

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
