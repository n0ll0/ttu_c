#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define TOTAL_LOTTO 5 /* lototroni poolt genereeritavate numbrite arv */
#define TOTAL_USR TOTAL_LOTTO    /* kasutaja poolt sisestavate numbrite arv */

#define BALL_MIN 1 /* v�him lubatud lotonumber */
#define BALL_MAX 12 /* maksimaalne lubatud lotonumber */

void CollectUserNums(int nums[], int len);
int GetUserNumbInRange(int min, int max);
void GenerateLotteryNumbers(int nums[], int len);
int GenerateRandomNum(int min, int max);
void PrintNumbers(int nums[], int len);
int FindMatchCount(int lotteryNumbers[], int lenLottery, int userNumbers[],
                   int lenUser);
bool IsNumInArray(int nums[], int len, int num);
bool IsNumInRange(int num, int min, int max);

/*
Enter lottery number [1 ... 25] (1 / 6): 11
Enter lottery number [1 ... 25] (2 / 6): 12
Enter lottery number [1 ... 25] (3 / 6): 14
Enter lottery number [1 ... 25] (4 / 6): 21
Enter lottery number [1 ... 25] (5 / 6): 22
Enter lottery number [1 ... 25] (6 / 6): 23

User numbers are
11 12 14 21 22 23

Lottery numbers are
17 18 10 1 20 25 4 9 13 15

Matched 0 out of 6!

None of the numbers matched. Better luck next time!
 */
int main(void)
{
  /* 0. Deklareeri k�ik oma vajalikud muutujad */
  int userNumbers[TOTAL_USR];
  int lotteryNumbers[TOTAL_LOTTO];

  srand(time(NULL));

  /* 1. Kutsu funktsioon kasutaja arvude lugemiseks (CollectUserNums) */
  CollectUserNums(userNumbers, TOTAL_USR);

  /* 2. Kutsu funktsioon lotoarvude
   *    genereerimiseks (GenerateLotteryNumbers) */
  GenerateLotteryNumbers(lotteryNumbers, TOTAL_LOTTO);

  /* 3. Kutsu funktsioon kasutaja v�ljastamiseks (PrintNumbers) */
  printf("Kasutaja sisestatud numbrid:\n");
  PrintNumbers(userNumbers, TOTAL_USR);

  /* 4. Kutsu funktsioon kattuvate numbrite leidmiseks
   *    ja kuvamiseks (FindMatchCount) */
  int matchCount = FindMatchCount(lotteryNumbers, TOTAL_LOTTO, userNumbers,
                                  TOTAL_USR);
  printf("Sinu numbrid kattuvad %d lotoarvuga.\n", matchCount);

  /* 5. Kuva lõppjäreldus - selle võid siin teha või uue funktsiooni luua */
  if (matchCount == 0)
  {
    printf("None of the numbers matched. Better luck next time!\n");
  }
  else if (matchCount == TOTAL_USR)
  {
    printf("Jackpot!\n");
  }

  return 0;
}

/**
 * @brief Checks if a given number is within a specified range.
 *
 * This function takes three parameters: an integer representing the number to be checked,
 * and two integers representing the minimum and maximum values of the range.
 * The function returns true if the given number is within the range (inclusive),
 * and false otherwise.
 *
 * @param num The number to be checked.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 *
 * @return True if the number is within the range, false otherwise.
 */
bool IsNumInRange(int num, int min, int max)
{
  return num >= min && num <= max;
}

/**
 * Funktsioon loeb sisse kasutaja poolt antavad numbrid. Funktsioonis
 * ise lugemisk�ske ei ole, vaid funktsioon kutsub esile j�rgmise funktsiooni
 * GetUserNumbInRange(), et lugeda �KS arv sisse ning salvestab tagastatud
 * v��rtuse massiivi. Seda tehakse ts�klis len arv kordi.
 */
void CollectUserNums(int nums[], int len)
{
  for (int i = 0; i < len; i++)
  {
    do
    {
      nums[i] = GetUserNumbInRange(BALL_MIN, BALL_MAX);
      // printf("Number %d, %d on sisestatud.\n", i, nums[i]);
    } while (IsNumInArray(nums, i, nums[i]));
  }
}

/**
 * Funktsioon loeb kasutajalt �he arvu. Kontrollitakse, et arv oleks vahemikus
 * min ja max. Otspunktid on mitteranged ehk min ja max on samuti lubatud.
 * Funktsioon k�sib arvu senikaua, kuniks sisestus j��b
 * etteantud vahemikku, seej�rel tagastab v��rtuse.
 */
int GetUserNumbInRange(int min, int max)
{
  int num;
  do
  {
    printf("\nSisesta number vahemikus %d ja %d: ", min, max);
    scanf("%d", &num);
  } while (!IsNumInRange(num, min, max));
  return num;
}

/**
 * Funktsioon tr�kib kaasa antud massiivi (nums) v��rtused �hele reale, j�ttes
 * iga numbri vahele t�hiku. Massiivi pikkuseks on len. Numbrite v�ljatr�kile
 * j�rgneb reavahetus.
 */
void PrintNumbers(int nums[], int len)
{
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
}

/**
 * Funktsioon genereerib lotonumbreid ja salvestab need massiivi.
 * Funktsiooni sees ise numbrit ei genereerita, vaid kutsutakse v�lja vastav
 * j�rgnev funktsioon GenerateRandomNum(), mis tagastab juhusliku numbri.
 * Tagastatud number salvestatakse massiivi
 *
 * Midagi ekraanile kuvada siin funktsioonis ei tohi.
 */
void GenerateLotteryNumbers(int nums[], int len)
{
  for (int i = 0; i < len; i++)
  {
    do
    {
      nums[i] = GenerateRandomNum(BALL_MIN, BALL_MAX);
      printf("Lottery number %d, %d on genereeritud.\n", i, nums[i]);
      // printf("Lottery number %d, %d on genereeritud.\n", i, nums[i]);
    } while (IsNumInArray(nums, i, nums[i]));
  }
}

/**
 * Antud funktsioon genereerib �he juhuarvu. Juhuarv genereeritakse vahemikus
 * min .. max, kusjuures otspunktid on lubatud. Genereeritud arv tagastatakse.
 *
 * �ldvalem: rand() % unikaalsete_tulemuste_arv + v�him_lubatud_arv
 */
int GenerateRandomNum(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

/**
 * Funktsioon v�tab endale 2 massiivi ja nende massiivide pikkused.
 * Funktsiooni eesm�rgiks on teada saada mitu numbrit massiivides osutuvad
 * kattuvateks. �he massiivi numbri esinemist teises massiivis kontrollitakse
 * kasutades funktsiooni IsNumInArray(). Kattuvuste arv tagastatakse.
 *
 * Kattuvuse leidmisel tr�kitakse kattuv number v�lja siin funktsoonis.
 */
int FindMatchCount(int lotteryNumbers[], int lenLottery, int userNumbers[],
                   int lenUser)
{
  int matchCount = 0;
  for (int i = 0; i < lenUser; i++)
  {
    if (IsNumInArray(lotteryNumbers, lenLottery, userNumbers[i]))
    {
      matchCount++;
    }
  }
  return matchCount;
}

/**
 * J�rgnev funktsioon kontrollib kas muutuja value v��rtus
 * esineb juba massiivis nums v�i mitte. Nums massiiv pikkus on len.
 * Tagastatakse vastus kas number oli massiivis v�i mitte.
 *
 * Midagi ekraanile kuvada siin funktsioonis ei tohi.
 */
bool IsNumInArray(int nums[], int len, int value)
{
  if (len < 1)
    return false;
  for (int i = 0; i < len; i++)
  {
    if (nums[i] == value)
    {
      return true;
    }
  }
  return false;
}
