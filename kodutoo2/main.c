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
#define WALK_SPEED 5

struct HikingPath
{
  char *name;
  double length;
};

int ReadHikingPaths(struct HikingPath *arr, int max_paths, int max_name_length);
void PrintHikingPath(struct HikingPath rada);
void PrintAllHikingPaths(struct HikingPath *arr, int length);
void PathsCompletableWithinTimeWithSpeed(struct HikingPath *arr, int length,
                                         double hours, double speed);
int PathComparator(const void *a, const void *b);

int main(int argc, char const *argv[])
{
  struct HikingPath hikingPaths[MAX_HIKE_PATHS];

  int length = ReadHikingPaths(hikingPaths, MAX_HIKE_PATHS, MAX_NAME_LENGTH);
  printf("Rajad: ");
  for (int i = 0; i < length; i++)
  {
    printf("%s", hikingPaths[i].name);
    if (i < length - 1)
      printf(", ");
  }
  printf("\n");
  PrintAllHikingPaths(hikingPaths, length);

  double hours;
  printf("\nSisesta tundide arv: ");
  scanf("%lf", &hours);
  printf("%lf\n", hours);
  if (hours <= 0)
  {
    fprintf(stderr, "\033[1;31mTundide arv peab olema positiivne!\033[0m\n");
    exit(EXIT_FAILURE);
  }

  qsort(hikingPaths, length, sizeof(struct HikingPath), PathComparator);

  PathsCompletableWithinTimeWithSpeed(hikingPaths, length, hours, WALK_SPEED);

  // free names memory
  for (size_t i = 0; i < length; i++)
  {
    free(hikingPaths[i].name);
  }

  return 0;
}

int PathComparator(const void *a, const void *b)
{
  struct HikingPath *pathA = (struct HikingPath *)a;
  struct HikingPath *pathB = (struct HikingPath *)b;

  // Compare the lengths of the paths and return the difference
  if ((pathA->length) < (pathB->length))
    return -1;
  if ((pathA->length) > (pathB->length))
    return 1;
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

  if (0 > n || n > max_paths)
  {
    fprintf(stderr, "\033[1;31mRajade arv peab olema vahemikus 1 kuni %d.\033[0m\n", max_paths);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; ++i)
  {
    char *name = calloc(max_name_length, sizeof(char));
    scanf("%s %lf", name, &arr[i].length);
    arr[i].name = strdup(name);
    if (arr[i].length < 0)
    {
      fprintf(stderr, "\033[1;31mNegatiivne rajapikkus pole lubatud! Hetkel asendame absoluutväärtusega.\n\033[0m");
      arr[i].length = -arr[i].length;
    }
    free(name);
  }
  return n;
}

/**
 * @brief Prints a single hiking path to standard output.
 *
 * This function takes a HikingPath structure and prints its name and length
 * to the standard output in a formatted string.
 *
 * @param rada The HikingPath structure containing the path information to be printed.
 *             It should have a 'name' field (string) and a 'length' field (double).
 *
 * @return This function does not return a value.
 */
void PrintHikingPath(struct HikingPath rada)
{
  fprintf(stdout, "%10s (%.2lf km)", rada.name, rada.length);
}

/**
 * @brief Prints all hiking paths in the given array.
 *
 * This function iterates through the array of HikingPath structures and prints
 * each path's information using the PrintHikingPath function. It includes a
 * header line before printing the paths.
 *
 * @param arr Pointer to an array of HikingPath structures containing the paths to be printed.
 * @param length The number of elements in the arr array.
 *
 * @return This function does not return a value.
 */
void PrintAllHikingPaths(struct HikingPath *arr, int length)
{
  printf("\n");
  for (int i = 0; i < length; ++i)
  {
    PrintHikingPath(arr[i]);
    printf("\n");
  }
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
    if (arr[i].length <= maxLength)
    {
      fprintf(stdout, "-\t");
      PrintHikingPath(arr[i]);
      double time = arr[i].length / speed;
      fprintf(stdout, " [%.2lf h]\n", time);
    }
  }
}

/*
@startuml
|Andmete lugemine|
start

:Loeb matkaradade arvu;
if (Kas rajad on õiges vahemikus?) then (jah)

  :Algab matkaradade lugemise tsükkel;
  while (Kas on veel radu lugeda?) is (jah)
    :Loeb järgmise raja nime ja pikkuse;
    :Kontrollib, kas pikkus on negatiivne;
    if (Kas pikkus negatiivne?) then (jah)
      :muutub iseenda absoluutväärtuseks;
    endif
  endwhile
else (ei)
  :Väljasta veateade ja lõpeta;
  stop
endif

:Küsi kasutajalt tunni arv;
if (Kas tunni arv on positiivne?) then (jah)
  :Korruta tundide arv kiirusel 5 km/h,
et arvutada läbitav kaugus;
else (ei)
  :Väljasta veateade ja lõpeta;
  stop
endif

:Sorteeri kasutades **quicksort** algoritmi;
:maksimaalne läbitav kaugus = kiirus * tunnid;
while (Kas on veel radu, mida saab läbida?) is (jah)
  if (Raja pikkus on lühem,
kui maksimaalne läbitav kaugus) then (jah)
    :Väljasta sobiv rada;
  endif
endwhile
:Vabasta mälu;

stop
@enduml
*/