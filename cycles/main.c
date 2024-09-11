// Tsüklid
// Laiendatud labori kirjeldus

// Kodutöö: Toidukaalu programmi edasiarendus

// Menüü peab olema kahetasemeline
// Esimese taseme menüüst valitakse toote kategooria (nt puuviljad, juurviljad). Sul peab olema vähemalt 3 kategooriat.
// Teise taseme menüüst valitakse valitud kategooriasse kuuluv toode. Igas kategoorias peab olema 3 toodet.
// Näita konkreetsele veale omast veateadet. Peab toetama järgnevaid:
// Toode pole kaalu peal / kaal negatiivne
// Tundmatu kategooria / kategooriat ei eksisteeri
// Tundmatu toode / toodet ei eksisteeri

#include <stdio.h>
#include "../input.c"

#define INPUT_LENGTH 5

int sum(int* arr)
{
  int sum = 0;
  int length = sizeof(arr)/sizeof(arr[0]);
  for (int i = 0; i < length; ++i)
    sum += arr[i];
  return sum;
}

int main()
{
  int inputs[INPUT_LENGTH];

  for (int i = 0; i < INPUT_LENGTH; ++i)
  {
    int input;
    printf("Sisesta arv %d / %d\n", i + 1, INPUT_LENGTH);
    scanf("%d", &input);
    inputs[i] = input;

    printf("%d\n", sum(inputs));
  }

  return 0;
}
